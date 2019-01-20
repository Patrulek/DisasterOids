#include "game.h"

extern bool isRunning;

void loadHighscores(Game * pGame)
{
      pGame->m_highscores = readFile(pGame->m_highscores, "highscores.txt");

      int t;
      char * tempPoints = ALLOC(char, 21);
      for(t = 0; t < 10; t++)
      {
            int i;
            int j;
            bool getPoints = false;

            for(i = pGame->m_highscores->m_curPos, j = 0; ; i++, pGame->m_highscores->m_curPos++)
            {
                  if(getPoints)
                  {
                        tempPoints[j] = pGame->m_highscores->m_buffer[i];
                        j++;
                  }
                  if(pGame->m_highscores->m_buffer[i] == '#')
                        getPoints = true;
                  else if(pGame->m_highscores->m_buffer[i + 1] == '\n' || pGame->m_highscores->m_buffer[i + 1] == '\0')
                  {
                        pGame->m_highscores->m_curPos++;
                        tempPoints[j] = '\0';
                        pGame->m_points[t] = atoi(tempPoints);
                        break;
                  }
            }
      }
      printf("%s\n\n", pGame->m_highscores->m_buffer);
      FREE(tempPoints);
}

void loadConfig(Game* pGame)
{
      pGame->m_config = readFile(pGame->m_config, "config.ini");

      int soundPos = 8, musicPos = 18, fullscreenPos = 33;
      int soundOffset = 0, musicOffset = 0;
      bool fullscreenOn = false;

      char * tempLine = ALLOC(char, 21);

      getLineFromPos(tempLine, pGame->m_config->m_buffer, soundPos, true);
      int percentValue = atoi(tempLine);
      pGame->m_pSoundManager->m_soundVolume = (float)percentValue / 50;

      printf("SOUND VOLUME: %d\n", percentValue);

      if(percentValue >= 10 && percentValue < 100)
            soundOffset = 1;
      else if(percentValue == 100)
            soundOffset = 2;

      getLineFromPos(tempLine, pGame->m_config->m_buffer, musicPos + soundOffset, true);
      percentValue = atoi(tempLine);
      pGame->m_pSoundManager->m_musicVolume = (float)percentValue / 50;

      if(percentValue >= 10 && percentValue < 100)
            musicOffset = 1;
      else if(percentValue == 100)
            musicOffset = 2;

            printf("MUSIC VOLUME: %d\n", percentValue);

      getLineFromPos(tempLine, pGame->m_config->m_buffer, fullscreenPos + musicOffset + soundOffset, true);
      fullscreenOn = atoi(tempLine);
      pGame->m_pGraphicManager->m_fullscreenOn = fullscreenOn;

      FREE(tempLine);
}

void saveHighscores(Game * pGame, int playerPoints)
{
      int i, t, pos = 0;

      for(i = 0; i < 9; i++)
      {
            if(playerPoints > pGame->m_points[i])
                  break;
      }

      char * points = ALLOC(char, 10);
      char * pHighscores = ALLOC(char, 201);
      char * tempLine = ALLOC(char, 21);
      itoa(playerPoints, points, 10);

      for(t = 0; t < 10; t++)
      {
            if(t != i)
            {
                  getLineFromPos(tempLine, pGame->m_highscores->m_buffer, pos, true);
                  printf("Actual saving line: %s\n", tempLine);
                  pos = findChar(pGame->m_highscores->m_buffer, pos, '\n') + 1;
                  printf("New pos: %d\n", pos);
                  if(t == 0)
                  {
                        strcpy(pHighscores, tempLine);
                        continue;
                  }
                  pHighscores = mergeStrings(pHighscores, tempLine);
            }
            else
            {
                  if(t == 0)
                        strcpy(pHighscores, "PATRULEX");
                  else
                        pHighscores = mergeStrings(pHighscores, "PATRULEX");

                  pHighscores = mergeStrings(pHighscores, "#");
                  pHighscores = mergeStrings(pHighscores, points);
                  pHighscores = mergeStrings(pHighscores, "\n");
            }
      }

      String * pHajskory = createString(pHighscores);
      writeFile(pHajskory, "highscores.txt");
      destroyString(pHajskory);

      FREE(points);
      FREE(pHighscores);
      FREE(tempLine);
}

void saveConfig(Game * pGame)
{
      int sndVol = round(50 * pGame->m_pSoundManager->m_soundVolume);
      int musVol = round(50 * pGame->m_pSoundManager->m_musicVolume);

      char * pBuffer = ALLOC(char, 50);
      char * pValue = ALLOC(char, 4);

      itoa(sndVol, pValue, 10);

      strcpy(pBuffer, "Sound = ");
      pBuffer = mergeStrings(pBuffer, pValue);

      itoa(musVol, pValue, 10);

      pBuffer = mergeStrings(pBuffer, "\nMusic = ");
      pBuffer = mergeStrings(pBuffer, pValue);

      itoa(pGame->m_pGraphicManager->m_fullscreenOn, pValue, 10);

      pBuffer = mergeStrings(pBuffer, "\nFullscreen = ");
      pBuffer = mergeStrings(pBuffer, pValue);

      printf("pBuffer - %s\n", pBuffer);

      String * pString = createString(pBuffer);
      writeFile(pString, "config.ini");
      destroyString(pString);

      FREE(pValue);
      FREE(pBuffer);
}

Game * createGame()
{
      Game * pGame = ALLOC(Game, 1);

      if(pGame)
      {
            pGame->m_pGraphicManager = createGraphicManager();
            pGame->m_pInputHandler = createInputHandler(pGame->m_pGraphicManager->m_pDisplay);
            pGame->m_pTextureManager = createTextureManager();
            pGame->m_pSoundManager = createSoundManager();
            pGame->m_pFontManager = createFontManager();
      }

      loadFont("BEBAS.ttf", "BEBAS", 24, 0, pGame->m_pFontManager);
      pGame->m_config = NULL;
      pGame->m_highscores = NULL;
      pGame->m_pGameState = createState(INTRO_STATE, pGame->m_highscores, pGame->m_config, pGame->m_pTextureManager, pGame->m_pSoundManager, pGame->m_pFontManager);
      pGame->m_whatState = NO_STATE;
      pGame->m_changeState = false;

      srand(time(NULL) * rand());

      // open config
      loadConfig(pGame);

      // open highscores
      loadHighscores(pGame);

      return pGame;
}

void destroyGame(Game * pGame)
{
      if(!pGame)
            return;

      destroyString(pGame->m_config);
      destroyString(pGame->m_highscores);
      destroyState(pGame->m_pGameState->m_stateID, pGame->m_pGameState, pGame->m_pTextureManager, pGame->m_pSoundManager);
      destroyFontManager(pGame->m_pFontManager);
      destroySoundManager(pGame->m_pSoundManager);
      destroyTextureManager(pGame->m_pTextureManager);
      destroyInputHandler(pGame->m_pInputHandler);
      destroyGraphicManager(pGame->m_pGraphicManager);
      FREE(pGame);
}

void handleInput(InputHandler * pInputHandler)
{
      updateInputHandler(pInputHandler);
}

void doLogic(Game * pGame)
{
      switch(pGame->m_pGameState->m_stateID)
      {
            case INTRO_STATE:
                  logicIntroState(pGame);
                  break;
            case MENU_STATE:
                  logicMenuState(pGame);
                  break;
            case PLAY_STATE:
                  logicPlayState(pGame);
                  break;
            default:
                  break;
      }
}

void drawGame(Game * pGame)
{
      Scene * pScene = getItem(pGame->m_pGameState->m_scenes, pGame->m_pGameState->m_currentScene);

      clearScreen(al_map_rgb(0, 0, 0));

      if(pGame->m_pGameState->m_currentScene == PAUSE)
      {
            Scene * pBackgroundScene = getItem(pGame->m_pGameState->m_scenes, PLAY);
            drawScene(pBackgroundScene, pGame->m_pTextureManager, pGame->m_pFontManager);
      }

      drawScene(pScene, pGame->m_pTextureManager, pGame->m_pFontManager);
      renderDisplay();
}

void changeState(GAME_STATES whatState, Game * pGame)
{
      if(pGame->m_pGameState)
            destroyState(pGame->m_pGameState->m_stateID, pGame->m_pGameState, pGame->m_pTextureManager, pGame->m_pSoundManager);

      pGame->m_pGameState = createState(whatState, pGame->m_highscores, pGame->m_config, pGame->m_pTextureManager, pGame->m_pSoundManager, pGame->m_pFontManager);
      pGame->m_changeState = false;
      pGame->m_whatState = NO_STATE;
}

void logicIntroState(Game * pGame)
{
      pGame->m_changeState = true;
      pGame->m_whatState = MENU_STATE;
}

void logicMenuState(Game * pGame)
{
      switch(pGame->m_pGameState->m_currentScene)
      {
            case TITLE:
                  logicMenuTitleScene(pGame);
                  break;
            case OPTION:
                  logicMenuOptionsScene(pGame);
                  break;
            case HIGHSCORE:
                  logicMenuHighscoresScene(pGame);
                  break;
            case ABOUT:
                  logicMenuAboutScene(pGame);
                  break;
            default:
                  break;
      }
}

void logicPlayPlayScene(Game * pGame)
{
      int i = 0;
      static double asteroidTimer;
      static bool resetTimerr = true;

      Scene * pScene = getItem(pGame->m_pGameState->m_scenes, pGame->m_pGameState->m_currentScene);

      if(pScene->m_player->m_needToSpawn)
            spawnPlayer(pScene->m_player, createPoint(400, 300));

      updatePlayer(pScene->m_player, pGame->m_pInputHandler);

      if(pScene->m_player->m_fireBullets)
      {
            playSound("BULLET", SFX, false, pGame->m_pSoundManager);
            fireBullets(pScene->m_player);
      }

      if(pScene->m_powerup)
      {
            updatePowerup(pScene->m_powerup->m_type, pScene->m_powerup);
            if(checkPlayerPowerupCollision(pScene->m_player, pScene->m_powerup))
            {
                  playSound("POWERUPPICKED", SFX, false, pGame->m_pSoundManager);
                  switch(pScene->m_powerup->m_type)
                  {
                        case SHIELD_POWERUP:
                        {
                              resetTimer(pScene->m_player->m_shieldTimer);
                              break;
                        }
                        case FREEZE_POWERUP:
                              for(i = 0; i < pScene->m_asteroids->m_arraySize; i++)
                              {
                                    Asteroid * pAsteroid = getItem(pScene->m_asteroids, i);
                                    if(pAsteroid)
                                          freezeAsteroid(pAsteroid);
                              }
                              break;
                        case LIFEUP_POWERUP:
                              if(++pScene->m_player->m_lives > MAX_LIVES)
                                    pScene->m_player->m_lives = MAX_LIVES;
                              break;
                        case BOMB_POWERUP:
                              if(++pScene->m_player->m_bombs > MAX_BOMBS)
                                    pScene->m_player->m_bombs = MAX_BOMBS;
                              break;
                        case BULLET_POWERUP:
                              if(++pScene->m_player->m_bulletTimerLevel > MAX_BULLET_COOLDOWN_LEVEL)
                                    pScene->m_player->m_bulletTimerLevel = MAX_BULLET_COOLDOWN_LEVEL;

                              if(++pScene->m_player->m_bulletDamageLevel > MAX_BULLET_DAMAGE_LEVEL)
                                    pScene->m_player->m_bulletDamageLevel = MAX_BULLET_DAMAGE_LEVEL;

                              for(i = 0; i < 45; i++)
                              {
                                    Bullet * pBullet = createBullet(pScene->m_player->m_bulletTextureID, createPoint(pScene->m_powerup->m_collisionCircle->m_position->m_x,
                                    pScene->m_powerup->m_collisionCircle->m_position->m_y), i * 8);

                                    pScene->m_player->m_bullets = insertObject(pScene->m_player->m_bullets, pBullet);
                              }
                              break;
                        case BEAM_POWERUP:
                              if(++pScene->m_player->m_beamChargingLevel > MAX_BEAM_CHARGING_LEVEL)
                                    pScene->m_player->m_beamChargingLevel = MAX_BEAM_CHARGING_LEVEL;
                              pScene->m_player->m_beamCharge = pScene->m_player->m_beamCharge + 10 > 100 ? 100 : pScene->m_player->m_beamCharge + 10;
                              break;
                        default:
                              break;
                  }
                  pScene->m_powerup->m_pickedUp = true;
            }
      }

      for(i = 0; i < pScene->m_explosions->m_arraySize; i++)
      {
            AnimatedImage * pImage = getItem(pScene->m_explosions, i);
            if(pImage)
            {
                  if(pImage->m_currentFrame >= pImage->m_maxFrames)
                  {
                        destroyAnimatedImage(pImage);
                        pScene->m_explosions = removeObject(pScene->m_explosions, i, true, NO_ALLEGRO);
                  }
                  else
                        updateAnimatedImage(pImage);
            }
      }

      for(i = 0; i < pScene->m_asteroids->m_arraySize; i++)
      {
            Asteroid * pAsteroid = getItem(pScene->m_asteroids, i);
            if(pAsteroid)
            {
                  updateAsteroid(pAsteroid);
                  if(checkPlayerAsteroidCollision(pScene->m_player, pAsteroid))
                  {
                        pAsteroid->m_healthPoints -= 100;
                        if(!pScene->m_player->m_shielded)
                        {
                              playSound("EXPLOSION", SFX, false, pGame->m_pSoundManager);

                              pScene->m_player->m_lives-- ;
                              AnimatedImage * pExplosion = createAnimatedImage("EXPLOSION", createPoint(pScene->m_player->m_position->m_x - 21, pScene->m_player->m_position->m_y - 19),
                                                                         50, 50, 5, 0, 4, false);
                              pScene->m_explosions = insertObject(pScene->m_explosions, pExplosion);
                              if(pScene->m_player->m_lives > 0)
                                    pScene->m_player->m_needToSpawn = true;
                              else
                              {
                                    pGame->m_pGameState->m_currentScene = GAMEOVER;
                                    resetTimer(pGame->m_pGameState->m_timer);

                                    if(pScene->m_player->m_points > pGame->m_points[9])
                                    {
                                          saveHighscores(pGame, pScene->m_player->m_points);
                                          loadHighscores(pGame);
                                    }
                              }
                        }
                  }
                  if(pAsteroid->m_destroy)
                  {
                        AnimatedImage * pExplosion = createAnimatedImage("EXPLOSION", createPoint(pAsteroid->m_position->m_x - 26, pAsteroid->m_position->m_y - 26),
                                                                               50, 50, 5, 0, 4, false);
                        pScene->m_explosions = insertObject(pScene->m_explosions, pExplosion);

                        pScene->m_player->m_points += pAsteroid->m_points;
                        char * points = ALLOC(char, 10);
                        itoa(pScene->m_player->m_points, points, 10);
                        changeDisplayText(points, getItem(pScene->m_strings, 1));
                        FREE(points);

                        int ast_size = pAsteroid->m_size;

                        if(ast_size > 0 && !pAsteroid->m_freezed && !pAsteroid->m_bombed)
                        {
                              al_play_sample(getSound("EXPLOSION", SFX, pGame->m_pSoundManager), 1.0, 0.0, 1.0,
                                             ALLEGRO_PLAYMODE_ONCE, 0);

                              Asteroid * newAsteroid;
                              float newVelX, newVelY;
                              int alfa = rand()%45 + 15;
                              newVelX = pAsteroid->m_velX * cos(alfa * PI/180) - pAsteroid->m_velY * sin(alfa * PI/180);
                              newVelY = pAsteroid->m_velY * cos(alfa * PI/180) + pAsteroid->m_velX * sin(alfa * PI/180);
                              newAsteroid = createAsteroid(ast_size - 1, pAsteroid->m_type, createPoint(pAsteroid->m_position->m_x, pAsteroid->m_position->m_y),
                                                            pAsteroid->m_angle, newVelX * 1.2, newVelY * 1.2);
                              pScene->m_asteroids = insertObject(pScene->m_asteroids, newAsteroid);

                              alfa = rand()%45 - 15;
                              newVelX = pAsteroid->m_velX * cos(-alfa * PI/180) - pAsteroid->m_velY * sin(-alfa * PI/180);
                              newVelY = pAsteroid->m_velY * cos(-alfa * PI/180) + pAsteroid->m_velX * sin(-alfa * PI/180);
                              newAsteroid = createAsteroid(ast_size - 1, pAsteroid->m_type, createPoint(pAsteroid->m_position->m_x, pAsteroid->m_position->m_y),
                                                            pAsteroid->m_angle, newVelX * 1.2, newVelY * 1.2);
                              pScene->m_asteroids = insertObject(pScene->m_asteroids, newAsteroid);
                        }
                        destroyAsteroid(pAsteroid);
                        pScene->m_asteroids = removeObject(pScene->m_asteroids, i, true, 0);
                        i-- ;
                  }
            }
      }

      for(i = 0; i < pScene->m_player->m_bullets->m_arraySize; i++)
      {
            Bullet * pBullet = getItem(pScene->m_player->m_bullets, i);
            if(pBullet)
            {
                  int j;
                  updateBullet(pBullet);
                  for(j = 0; j < pScene->m_asteroids->m_arraySize; j++)
                  {
                        Asteroid * pAsteroid = getItem(pScene->m_asteroids, j);
                        if(checkBulletAsteroidCollision(pBullet, pAsteroid))
                        {
                              pAsteroid->m_healthPoints -= pBullet->m_damage;
                              pBullet->m_destroy = true;

                              AnimatedImage * pBulletHit = createAnimatedImage("BULLET_HIT", createPoint(pBullet->m_position->m_x, pBullet->m_position->m_y),
                                                                               7, 7, 3, 0, 2, false);
                              pScene->m_bulletHits = insertObject(pScene->m_bulletHits, pBulletHit);
                              break;
                        }
                  }
                  if(pBullet->m_destroy)
                  {
                        destroyBullet(pBullet);
                        pScene->m_player->m_bullets = removeObject(pScene->m_player->m_bullets, i, true, NO_ALLEGRO);
                        i-- ;
                  }
            }
      }

      // update beam

      if(pScene->m_player->m_activeBeam)
      {
            playSound("LASER", SFX, false, pGame->m_pSoundManager);

            Point p = *pScene->m_player->m_leftBeamPos;
            updateBeam(pScene->m_player->m_angle, p, pScene->m_player->m_leftBeam);
            Point p2 = *pScene->m_player->m_rightBeamPos;
            updateBeam(pScene->m_player->m_angle, p2, pScene->m_player->m_rightBeam);

            for(i = 0; i < pScene->m_asteroids->m_arraySize; i++)
            {
                  Asteroid * pAsteroid = getItem(pScene->m_asteroids, i);
                  if(checkBeamAsteroidCollision(pScene->m_player->m_leftBeam, pAsteroid))
                        pAsteroid->m_healthPoints -= pScene->m_player->m_leftBeam->m_damage;
                  if(checkBeamAsteroidCollision(pScene->m_player->m_rightBeam, pAsteroid))
                        pAsteroid->m_healthPoints -= pScene->m_player->m_rightBeam->m_damage;
            }
      }

      if(pScene->m_player->m_bombActivated)
      {
            playSound("WTFBOMB", SFX, false, pGame->m_pSoundManager);

            pScene->m_player->m_bombs--;
            pScene->m_player->m_bombActivated = false;
            pScene->m_player->m_bombDelayed = true;
      }

      // create asteroids and powerups

      if(resetTimerr)
      {
            asteroidTimer = al_get_time();
            resetTimerr = false;
      }


      if(pScene->m_player->m_bombDelayed &&
         getTime(pScene->m_player->m_bombEffectTimer) > DELAY_BOMB_EFFECT - 0.2 && getTime(pScene->m_player->m_bombEffectTimer) < DELAY_BOMB_EFFECT - 0.15)
      {
            pScene->m_player->m_bombEffect = true;
            pScene->m_player->m_bombDelayed = false;
            for(i = 0; i < pScene->m_asteroids->m_arraySize; i++)
            {
                  Asteroid * pAsteroid = getItem(pScene->m_asteroids, i);
                  if(pAsteroid)
                  {
                        pAsteroid->m_destroy = true;
                        pAsteroid->m_bombed = true;
                  }
            }
      }
      else if(getTime(pScene->m_player->m_bombEffectTimer) >= BOMB_EFFECT)
            pScene->m_player->m_bombEffect = false;

      if(al_get_time() - asteroidTimer > 3 + rand()%3 && !pScene->m_player->m_bombEffect)
      {
            Asteroid * newAsteroid;
            if(rand()%2 == 0)
                  newAsteroid = createAsteroid(rand()%3, rand()%2, createPoint(rand()%26 - 53, rand()%26 - 53), rand()%360, rand()%3 + 1, rand()%3 + 1);
            else
                  newAsteroid = createAsteroid(rand()%3, rand()%2, createPoint(rand()%26 + SCREEN_WIDTH, rand()%26 + SCREEN_HEIGHT), rand()%360, -rand()%3 - 1, -rand()%3 - 1);
            pScene->m_asteroids = insertObject(pScene->m_asteroids, newAsteroid);
            resetTimerr = true;
      }


      if(pScene->m_player->m_accelerating)
      {
            playSound("ACCELERATE", SFX, false, pGame->m_pSoundManager);
      }

      if(pScene->m_powerup->m_needToSpawn)
      {
            Point * pPoint = createPoint(rand() % 700, rand() % 500);
            spawnPowerup(pScene->m_powerup, pPoint);
            pScene->m_powerup->m_needToSpawn = false;
      }

      if(isKeyDown(pGame->m_pInputHandler, ALLEGRO_KEY_K))
            {pScene->m_player->m_beamCharge = 100; pScene->m_player->m_lives = 5; pScene->m_player->m_bulletTimerLevel = 5;
            pScene->m_player->m_bulletDamageLevel = 3; pScene->m_player->m_bombs = 2;}

      if(isKeyDown(pGame->m_pInputHandler, ALLEGRO_KEY_ESCAPE) && !pGame->m_pInputHandler->m_oldKeyStates[ALLEGRO_KEY_ESCAPE])
      {
            pGame->m_pInputHandler->m_oldKeyStates[ALLEGRO_KEY_ESCAPE] = true;

            pGame->m_pGameState->m_currentScene = PAUSE;
      }


      if(pGame->m_points[0] < pScene->m_player->m_points)
      {
            char * points = ALLOC(char, 10);
            itoa(pScene->m_player->m_points, points, 10);
            changeDisplayText(points, getItem(pScene->m_strings, 3));
            FREE(points);
      }
}

void logicPlayGameoverScene(Game * pGame)
{
      if(getTime(pGame->m_pGameState->m_timer) > 1.5)
      {
            pGame->m_changeState = true;
            pGame->m_whatState = MENU_STATE;
      }
}

void logicPlayState(Game * pGame)
{
      switch(pGame->m_pGameState->m_currentScene)
      {
            case PLAY:
                  logicPlayPlayScene(pGame);
                  break;
            case PAUSE:
                  logicPlayPauseScene(pGame);
                  break;
            case GAMEOVER:
                  logicPlayGameoverScene(pGame);
                  break;
            default:
                  break;
      }
}

void logicPlayPauseScene(Game * pGame)
{
      if(isPressed(ALLEGRO_KEY_ESCAPE) && !wasPressed(ALLEGRO_KEY_ESCAPE))
      {
            pGame->m_pInputHandler->m_oldKeyStates[ALLEGRO_KEY_ESCAPE] = true;
            pGame->m_pGameState->m_currentScene = PLAY;
      }
}

void logicMenuTitleScene(Game * pGame)
{
      Scene * pScene = getItem(pGame->m_pGameState->m_scenes, pGame->m_pGameState->m_currentScene);
      Button * pButton = getItem(pScene->m_buttons, pScene->m_activeButton);

      if(isPressed(ALLEGRO_KEY_TAB) && !wasPressed(ALLEGRO_KEY_TAB))
      {
            pGame->m_pInputHandler->m_oldKeyStates[ALLEGRO_KEY_TAB] = true;
            pGame->m_changeState = true;
            pGame->m_whatState = INTRO_STATE;
      }
      if(isPressed(ALLEGRO_KEY_UP) && !wasPressed(ALLEGRO_KEY_UP))
      {
            pGame->m_pInputHandler->m_oldKeyStates[ALLEGRO_KEY_UP] = true;
            if(pScene->m_activeButton != PLAY_BTN)
            {
                  pButton->m_active = false;
                  pScene->m_activeButton-- ;
            }
      }
      else if(isPressed(ALLEGRO_KEY_DOWN) && !wasPressed(ALLEGRO_KEY_DOWN))
      {
            pGame->m_pInputHandler->m_oldKeyStates[ALLEGRO_KEY_DOWN] = true;
            if(pScene->m_activeButton != EXIT_BTN)
            {
                  pButton->m_active = false;
                  pScene->m_activeButton++ ;
            }
      }

      pButton = getItem(pScene->m_buttons, pScene->m_activeButton);
      pButton->m_active = true;

      if(isPressed(ALLEGRO_KEY_ENTER) && !wasPressed(ALLEGRO_KEY_ENTER))
      {
            pGame->m_pInputHandler->m_oldKeyStates[ALLEGRO_KEY_ENTER] = true;
            switch(pScene->m_activeButton)
            {
                  case PLAY_BTN:
                        pGame->m_changeState = true;
                        pGame->m_whatState = PLAY_STATE;
                        break;
                  case OPTION_BTN:
                        pGame->m_pGameState->m_currentScene = OPTION;
                        break;
                  case HIGHSCORE_BTN:
                        pGame->m_pGameState->m_currentScene = HIGHSCORE;
                        break;
                  case ABOUT_BTN:
                        pGame->m_pGameState->m_currentScene = ABOUT;
                        break;
                  case EXIT_BTN:
                        isRunning = false;
                        break;
            }
      }
}

void decreaseOption(Game * pGame, Scene * pOptionScene)
{
      if(pOptionScene->m_activeButton == SOUND_BTN)
            pGame->m_pSoundManager->m_soundVolume = pGame->m_pSoundManager->m_soundVolume - 0.2 < MIN_VOLUME ? MIN_VOLUME : pGame->m_pSoundManager->m_soundVolume - 0.2;
      else if(pOptionScene->m_activeButton == MUSIC_BTN)
            pGame->m_pSoundManager->m_musicVolume = pGame->m_pSoundManager->m_musicVolume - 0.2 < MIN_VOLUME ? MIN_VOLUME : pGame->m_pSoundManager->m_musicVolume - 0.2;

      char * pBuffer = ALLOC(char, 4);

      int vol = round(pGame->m_pSoundManager->m_soundVolume * 50);
      itoa(vol, pBuffer, 10);
      changeDisplayText(pBuffer, getItem(pOptionScene->m_strings, 0));

      vol = round(pGame->m_pSoundManager->m_musicVolume * 50);
      itoa(vol, pBuffer, 10);
      changeDisplayText(pBuffer, getItem(pOptionScene->m_strings, 1));

      FREE(pBuffer);
}

void increaseOption(Game * pGame, Scene * pOptionScene)
{
      if(pOptionScene->m_activeButton == SOUND_BTN)
            pGame->m_pSoundManager->m_soundVolume = pGame->m_pSoundManager->m_soundVolume + 0.2 > MAX_VOLUME ? MAX_VOLUME : pGame->m_pSoundManager->m_soundVolume + 0.2;
      else if(pOptionScene->m_activeButton == MUSIC_BTN)
            pGame->m_pSoundManager->m_musicVolume = pGame->m_pSoundManager->m_musicVolume + 0.2 > MAX_VOLUME ? MAX_VOLUME : pGame->m_pSoundManager->m_musicVolume + 0.2;

      char * pBuffer = ALLOC(char, 4);

      int vol = round(pGame->m_pSoundManager->m_soundVolume * 50);
      itoa(vol, pBuffer, 10);
      changeDisplayText(pBuffer, getItem(pOptionScene->m_strings, 0));

      vol = round(pGame->m_pSoundManager->m_musicVolume * 50);
      itoa(vol, pBuffer, 10);
      changeDisplayText(pBuffer, getItem(pOptionScene->m_strings, 1));

      FREE(pBuffer);
}

void logicMenuOptionsScene(Game * pGame)
{
      Scene * pScene = getItem(pGame->m_pGameState->m_scenes, pGame->m_pGameState->m_currentScene);
      Button * pButton = NULL;
      int i;

      for(i = 0; i < pScene->m_buttons->m_arraySize; i++)
      {
            pButton = getItem(pScene->m_buttons, i);
            if(pButton)
                  pButton->m_active = false;
      }

      pButton = getItem(pScene->m_buttons, pScene->m_activeButton);
      if(isKeyDown(pGame->m_pInputHandler, ALLEGRO_KEY_DOWN) && !pGame->m_pInputHandler->m_oldKeyStates[ALLEGRO_KEY_DOWN])
      {
            pGame->m_pInputHandler->m_oldKeyStates[ALLEGRO_KEY_DOWN] = true;
            if(pScene->m_activeButton != MUSIC_BTN)
            {
                  pButton->m_active = false;
                  pScene->m_activeButton += 3;
            }
      }
      else if(isKeyDown(pGame->m_pInputHandler, ALLEGRO_KEY_UP) && !pGame->m_pInputHandler->m_oldKeyStates[ALLEGRO_KEY_UP])
      {
            pGame->m_pInputHandler->m_oldKeyStates[ALLEGRO_KEY_UP] = true;
            if(pScene->m_activeButton != SOUND_BTN)
            {
                  pButton->m_active = false;
                  pScene->m_activeButton -= 3;
            }
      }

      pButton = getItem(pScene->m_buttons, pScene->m_activeButton);
      pButton->m_active = true;

      if(isPressed(ALLEGRO_KEY_LEFT))
      {
            if(!wasPressed(ALLEGRO_KEY_LEFT))
                  decreaseOption(pGame, pScene);

            pButton = getItem(pScene->m_buttons, pScene->m_activeButton + 1);
            pGame->m_pInputHandler->m_oldKeyStates[ALLEGRO_KEY_LEFT] = true;
            pButton->m_active = true;
      }
      else if(isPressed(ALLEGRO_KEY_RIGHT))
      {
            if(!wasPressed(ALLEGRO_KEY_RIGHT))
                  increaseOption(pGame, pScene);

            pButton = getItem(pScene->m_buttons, pScene->m_activeButton + 2);
            pGame->m_pInputHandler->m_oldKeyStates[ALLEGRO_KEY_RIGHT] = true;
            pButton->m_active = true;
      }


      if(isPressed(ALLEGRO_KEY_ESCAPE) && !wasPressed(ALLEGRO_KEY_ESCAPE))
      {
            pGame->m_pInputHandler->m_oldKeyStates[ALLEGRO_KEY_ESCAPE] = true;
            backToMainMenu(pGame);
      }
      else if(isPressed(ALLEGRO_KEY_ENTER) && !wasPressed(ALLEGRO_KEY_ENTER))
      {
            pGame->m_pInputHandler->m_oldKeyStates[ALLEGRO_KEY_ENTER] = true;
            backToMainMenu(pGame);
      }

      changeSamplesVolume(pGame);
}

void logicMenuHighscoresScene(Game * pGame)
{
      if(isPressed(ALLEGRO_KEY_ESCAPE) && !wasPressed(ALLEGRO_KEY_ESCAPE))
      {
            pGame->m_pInputHandler->m_oldKeyStates[ALLEGRO_KEY_ESCAPE] = true;
            backToMainMenu(pGame);
      }
      else if(isPressed(ALLEGRO_KEY_ENTER) && !wasPressed(ALLEGRO_KEY_ENTER))
      {
            pGame->m_pInputHandler->m_oldKeyStates[ALLEGRO_KEY_ENTER] = true;
            backToMainMenu(pGame);
      }
}

void logicMenuAboutScene(Game * pGame)
{
      if(isPressed(ALLEGRO_KEY_ESCAPE) && !wasPressed(ALLEGRO_KEY_ESCAPE))
      {
            pGame->m_pInputHandler->m_oldKeyStates[ALLEGRO_KEY_ESCAPE] = true;
            backToMainMenu(pGame);
      }
      else if(isPressed(ALLEGRO_KEY_ENTER) && !wasPressed(ALLEGRO_KEY_ENTER))
      {
            pGame->m_pInputHandler->m_oldKeyStates[ALLEGRO_KEY_ENTER] = true;
            backToMainMenu(pGame);
      }
}

void changeSamplesVolume(Game * pGame)
{
      int i;
      for(i = 0; i < pGame->m_pSoundManager->m_music->m_arraySize; i++)
      {
            ALLEGRO_SAMPLE_INSTANCE * pSampleInstance = getItem(pGame->m_pSoundManager->m_musicInstances, i);
            if(pSampleInstance)
                  al_set_sample_instance_gain(pSampleInstance, pGame->m_pSoundManager->m_musicVolume);
      }

      for(i = 0; i < pGame->m_pSoundManager->m_samples->m_arraySize; i++)
      {
            ALLEGRO_SAMPLE_INSTANCE * pSampleInstance = getItem(pGame->m_pSoundManager->m_sampleInstances, i);
            if(pSampleInstance)
                  al_set_sample_instance_gain(pSampleInstance, pGame->m_pSoundManager->m_soundVolume);
      }
}

void backToMainMenu(Game * pGame)
{
      if(pGame->m_pGameState->m_currentScene == OPTION)
      {
            saveConfig(pGame);
            loadConfig(pGame);
      }
      pGame->m_pGameState->m_currentScene = TITLE;
}

bool checkBeamAsteroidCollision(Beam * pBeam, Asteroid * pAsteroid)
{
      if(pBeam && pAsteroid)
            return checkCircleOBBCollision(pAsteroid->m_collisionCircle, &pBeam->m_obb)
                   || checkCircleOBBCollision(pAsteroid->m_collisionCircle2, &pBeam->m_obb);

      return false;
}

bool checkBulletAsteroidCollision(Bullet * pBullet, Asteroid * pAsteroid)
{
      if(pBullet && pAsteroid)
      {
            if(checkCircleCircleCollision(pBullet->m_collisionCircle, pAsteroid->m_collisionCircle))
                  return true;

            if(pAsteroid->m_collisionCircle2)
                  if(checkCircleCircleCollision(pBullet->m_collisionCircle, pAsteroid->m_collisionCircle2))
                        return true;

      }
      return false;
}

bool checkPlayerAsteroidCollision(Player * pPlayer, Asteroid * pAsteroid)
{
      if(pPlayer && !pPlayer->m_invulnerability && pAsteroid)
            return checkCircleOBBCollision(pAsteroid->m_collisionCircle, &pPlayer->m_obb)
                   || checkCircleOBBCollision(pAsteroid->m_collisionCircle2, &pPlayer->m_obb);

      return false;
}

bool checkPlayerPowerupCollision(Player * pPlayer, Powerup * pPowerup)
{
      if(pPlayer && pPowerup)
            return checkCircleOBBCollision(pPowerup->m_collisionCircle, &pPlayer->m_obb);

      return false;
}
