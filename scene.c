#include "scene.h"

#include "graphicmanager.h"

Scene * createScene(SCENES whatScene, String * highscores, String * config, FontManager * pFontManager)
{
      Scene * pScene = ALLOC(Scene, 1);
      pScene->m_player = NULL;
      pScene->m_powerup = NULL;
      pScene->m_activeButton = 0;
      pScene->m_highscores = highscores;
      pScene->m_config = config;

      pScene->m_strings = NULL;
      pScene->m_strings = createArray(pScene->m_strings, 1);

      pScene->m_bgImages = NULL;
      pScene->m_bgImages = createArray(pScene->m_bgImages, 1);

      pScene->m_explosions = NULL;
      pScene->m_explosions = createArray(pScene->m_explosions, 1);

      pScene->m_bulletHits = NULL;
      pScene->m_bulletHits = createArray(pScene->m_bulletHits, 1);

      pScene->m_asteroids = NULL;
      pScene->m_asteroids = createArray(pScene->m_asteroids, 1);

      pScene->m_buttons = NULL;
      pScene->m_buttons = createArray(pScene->m_buttons, 1);

      switch(whatScene)
      {
            case INTRO_TITLE_SCENE:
                  createIntroTitleScene(pScene);
                  break;
            case MENU_TITLE_SCENE:
                  createMenuTitleScene(pScene);
                  break;
            case MENU_OPTION_SCENE:
                  createMenuOptionScene(pScene, pFontManager);
                  break;
            case MENU_HIGHSCORE_SCENE:
                  createMenuHighscoreScene(pScene, pFontManager);
                  break;
            case MENU_ABOUT_SCENE:
                  createMenuAboutScene(pScene, pFontManager);
                  break;
            case PLAY_PLAY_SCENE:
                  createPlayPlayScene(pScene, pFontManager);
                  break;
            case PLAY_PAUSE_SCENE:
                  createPlayPauseScene(pScene);
                  break;
            case PLAY_GAMEOVER_SCENE:
                  createPlayGameoverScene(pScene);
                  break;
      }
      return pScene;
}

void drawScene(Scene * pScene, TextureManager * pTextureManager, FontManager * pFontManager)
{
      int i;
      // backgrounds
      for(i = 0; i < pScene->m_bgImages->m_arraySize; i++)
      {
            Image * pImage = getItem(pScene->m_bgImages, i);
            if(pImage)
                  drawImage(pImage, pTextureManager);
      }
      // objects

            // powerups
      if(pScene->m_powerup && pScene->m_powerup->m_spawnTimer > 0)
            drawPowerup(pScene->m_powerup, pTextureManager);

            // asteroids
      for(i = 0; i < pScene->m_asteroids->m_arraySize; i++)
      {
            Asteroid * pAsteroid = getItem(pScene->m_asteroids, i);
            if(pAsteroid)
                  drawAsteroid(pAsteroid, pTextureManager);
      }

            // buttons
      for(i = 0; i < pScene->m_buttons->m_arraySize; i++)
      {
            Button * pButton = getItem(pScene->m_buttons, i);
            if(pButton)
                  drawButton(pButton, pTextureManager);
      }

      for(i = 0; i < pScene->m_bulletHits->m_arraySize; i++)
      {
            AnimatedImage * pBulletHit = getItem(pScene->m_bulletHits, i);
            if(pBulletHit)
            {
                  drawAnimatedImage(pBulletHit, pTextureManager);
                  if(pBulletHit->m_currentTime == 0)
                        pBulletHit->m_currentFrame++;
                  if(pBulletHit->m_currentFrame >= pBulletHit->m_maxFrames)
                        pScene->m_bulletHits = removeObject(pScene->m_bulletHits, i , true, 0);
            }
      }


      for(i = 0; i < pScene->m_explosions->m_arraySize; i++)
      {
            AnimatedImage * pExplosion = getItem(pScene->m_explosions, i);
            if(pExplosion)
                  drawAnimatedImage(pExplosion, pTextureManager);
      }
      // player + foreground
      Player * pPlayer = pScene->m_player;
      if(pPlayer)
      {
            drawPlayer(pPlayer, pTextureManager);

            // bullets
            for(i = 0; i < pPlayer->m_bullets->m_arraySize; i++)
            {
                  Bullet * pBullet = getItem(pPlayer->m_bullets, i);
                  if(pBullet)
                        drawBullet(pBullet, pTextureManager);
            }
            // beam
            if(pPlayer->m_activeBeam)
            {
                  drawBeam(pPlayer->m_leftBeam, pTextureManager);
                  drawBeam(pPlayer->m_rightBeam, pTextureManager);
            }

            if(pPlayer->m_beamCharge < 30)
            {
                  al_draw_bitmap(getTexture("REDBEAMHUD", pTextureManager), 640, 548, 0);
                  al_draw_filled_rectangle(670, 555, 670 + pPlayer->m_beamCharge, 557, al_map_rgba(200, 20, 20, 255));
                  al_draw_filled_rectangle(670, 557, 670 + pPlayer->m_beamCharge, 560, al_map_rgba(255, 125, 125, 255));
                  al_draw_filled_rectangle(670, 560, 670 + pPlayer->m_beamCharge, 564, al_map_rgba(255, 200, 200, 255));
                  al_draw_filled_rectangle(670, 564, 670 + pPlayer->m_beamCharge, 568, al_map_rgba(255, 255, 255, 255));
                  al_draw_filled_rectangle(670, 568, 670 + pPlayer->m_beamCharge, 572, al_map_rgba(255, 200, 200, 255));
                  al_draw_filled_rectangle(670, 572, 670 + pPlayer->m_beamCharge, 575, al_map_rgba(255, 125, 125, 255));
                  al_draw_filled_rectangle(670, 575, 670 + pPlayer->m_beamCharge, 578, al_map_rgba(200, 20, 20, 255));
            }
            else
            {
                  al_draw_bitmap(getTexture("GREENBEAMHUD", pTextureManager), 640, 548, 0);
                  al_draw_filled_rectangle(670, 555, 670 + pPlayer->m_beamCharge, 557, al_map_rgba(20, 200, 20, 255));
                  al_draw_filled_rectangle(670, 557, 670 + pPlayer->m_beamCharge, 560, al_map_rgba(125, 255, 125, 255));
                  al_draw_filled_rectangle(670, 560, 670 + pPlayer->m_beamCharge, 564, al_map_rgba(200, 255, 200, 255));
                  al_draw_filled_rectangle(670, 564, 670 + pPlayer->m_beamCharge, 568, al_map_rgba(255, 255, 255, 255));
                  al_draw_filled_rectangle(670, 568, 670 + pPlayer->m_beamCharge, 572, al_map_rgba(200, 255, 200, 255));
                  al_draw_filled_rectangle(670, 572, 670 + pPlayer->m_beamCharge, 575, al_map_rgba(125, 255, 125, 255));
                  al_draw_filled_rectangle(670, 575, 670 + pPlayer->m_beamCharge, 578, al_map_rgba(20, 200, 20, 255));
            }

            double t = getTime(pPlayer->m_bombTimer);

            al_draw_bitmap(getTexture("BOMB", pTextureManager), 670, 505, 0);

            al_draw_rectangle(706, 509, 711, 537, al_map_rgb(200, 70, 35), 1);

            if(t >= BOMB_COOLDOWN)
                  al_draw_filled_rectangle(706, 509, 710, 536, al_map_rgb(0, 225, 0));
            else
                  al_draw_filled_rectangle(706, 536 - t, 710, 536, al_map_rgb(250 - t * 10, t * 10, 0));

            if(pScene->m_player->m_bombs == 0)
                  al_draw_text(getFont("BEBAS", pFontManager), al_map_rgb(200, 70, 35), 735, 505, ALLEGRO_ALIGN_CENTRE, "x0");
            else if(pScene->m_player->m_bombs == 1)
                  al_draw_text(getFont("BEBAS", pFontManager), al_map_rgb(200, 70, 35), 735, 505, ALLEGRO_ALIGN_CENTRE, "x1");
            else
                  al_draw_text(getFont("BEBAS", pFontManager), al_map_rgb(200, 70, 35), 735, 505, ALLEGRO_ALIGN_CENTRE, "x2");


            for(i = 0; i < pPlayer->m_lives; i++)
            {
                  al_draw_tinted_scaled_rotated_bitmap_region(getTexture(pPlayer->m_textureID, pTextureManager), 0, 0, pPlayer->m_width,
                              pPlayer->m_height, al_map_rgba(255, 255, 255, 255), pPlayer->m_width/2, pPlayer->m_height/2,
                              i * 50 + 35, 570, 1.0, 1.0, -90 / (180/PI), 0);
            }

            if(pPlayer->m_bombEffect)
            {
                  double t = getTime(pPlayer->m_bombEffectTimer);
                  printf("T = %f\n", t);
                  if(t > DELAY_BOMB_EFFECT - 0.2 && t < DELAY_BOMB_EFFECT)
                        al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, al_map_rgba(1250 * t - 750, 1250 * t - 750, 1250 * t - 750, 1250 * t - 750));
                  else if(t >= DELAY_BOMB_EFFECT && t < BOMB_EFFECT)
                        al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, al_map_rgba(255 - 32 * t, 255 - 32 * t, 255 - 32 * t, 255 - 32 * t));

            }
      }

      // draw text
      for(i = 0; i < pScene->m_strings->m_arraySize; i++)
      {
            DisplayText * pDisplayText = getItem(pScene->m_strings, i);
            if(pDisplayText)
                  drawDisplayText(pDisplayText);
      }
}

void destroyScene(Scene * pScene)
{
      if(!pScene)
            return;

      int i;

      destroyPlayer(pScene->m_player);
      destroyPowerup(pScene->m_powerup);

      // delete buttons
      for(i = 0; i < pScene->m_buttons->m_arraySize; i++)
      {
            Button * pButton = getItem(pScene->m_buttons, i);
            if(pButton)
                  destroyButton(pButton);
      }
      clearArray(pScene->m_buttons, true, NO_ALLEGRO);
      //FREE(pScene->m_buttons);

      // delete explosions
      for(i = 0; i < pScene->m_explosions->m_arraySize; i++)
      {
            AnimatedImage * pImage = getItem(pScene->m_explosions, i);
            if(pImage)
                  destroyAnimatedImage(pImage);
      }
      clearArray(pScene->m_explosions, true, NO_ALLEGRO);
      //FREE(pScene->m_explosions);

      // delete bullet hits
      for(i = 0; i < pScene->m_bulletHits->m_arraySize; i++)
      {
            AnimatedImage * pImage = getItem(pScene->m_bulletHits, i);
            if(pImage)
                  destroyAnimatedImage(pImage);
      }
      clearArray(pScene->m_bulletHits, true, NO_ALLEGRO);
      //FREE(pScene->m_bulletHits);

      // delete asteroids
      for(i = 0; i < pScene->m_asteroids->m_arraySize; i++)
      {
            Asteroid * pAsteroid = getItem(pScene->m_asteroids, i);
            if(pAsteroid)
                  destroyAsteroid(pAsteroid);
      }
      clearArray(pScene->m_asteroids, true, NO_ALLEGRO);
      //FREE(pScene->m_asteroids);

      // delete bg images
      for(i = 0; i < pScene->m_bgImages->m_arraySize; i++)
      {
            Image * pImage = getItem(pScene->m_bgImages, i);
            if(pImage)
                  destroyImage(pImage);
      }
      clearArray(pScene->m_bgImages, true, NO_ALLEGRO);
      //FREE(pScene->m_bgImages);

      // delete strings
      for(i = 0; i < pScene->m_strings->m_arraySize; i++)
      {
            DisplayText * pDisplayText = getItem(pScene->m_strings, i);
            if(pDisplayText)
                  destroyDisplayText(pDisplayText);
      }
      clearArray(pScene->m_strings, true, NO_ALLEGRO);
      //FREE(pScene->m_strings);

      FREE(pScene);
}

void createIntroTitleScene(Scene * pScene)
{
      Button * pButton = NULL;
      Image * pImage = NULL;

      pImage = createImage("INTRO_BG", createPoint(0, 0));
      pScene->m_bgImages = insertObject(pScene->m_bgImages, pImage);
}

void createMenuTitleScene(Scene * pScene)
{
      Button * pButton = NULL;
      Image * pImage = NULL;

      pImage = createImage("MENU_BG", createPoint(0, 0));
      pScene->m_bgImages = insertObject(pScene->m_bgImages, pImage);

      pScene->m_activeButton = PLAY_BTN;

      pButton = createButton("PLAY_BTN", createPoint(275, 20), 250, 80, false);
      pScene->m_buttons = insertObject(pScene->m_buttons, pButton);

      pButton = createButton("OPTIONS_BTN", createPoint(275, 140), 250, 80, false);
      pScene->m_buttons = insertObject(pScene->m_buttons, pButton);

      pButton = createButton("HSCORES_BTN", createPoint(275, 260), 250, 80, false);
      pScene->m_buttons = insertObject(pScene->m_buttons, pButton);

      pButton = createButton("ABOUT_BTN", createPoint(275, 380), 250, 80, false);
      pScene->m_buttons = insertObject(pScene->m_buttons, pButton);

      pButton = createButton("EXIT_BTN", createPoint(275, 500), 250, 80, false);
      pScene->m_buttons = insertObject(pScene->m_buttons, pButton);
}

void createMenuOptionScene(Scene * pScene, FontManager * pFontManager)
{
      Button * pButton = NULL;
      Image * pImage = NULL;
      DisplayText * pDisplayText = NULL;

      pImage = createImage("MENU_BG", createPoint(0, 0));
      pScene->m_bgImages = insertObject(pScene->m_bgImages, pImage);

      pImage = createImage("FRAME", createPoint(80, 60));
      pScene->m_bgImages = insertObject(pScene->m_bgImages, pImage);

      pButton = createButton("SOUND_BTN", createPoint(100, 240), 250, 80, false);
      pScene->m_buttons = insertObject(pScene->m_buttons, pButton);

      pButton = createButton("LARROW", createPoint(390, 250), 30, 60, false);
      pScene->m_buttons = insertObject(pScene->m_buttons, pButton);

      pButton = createButton("RARROW", createPoint(450, 250), 30, 60, false);
      pScene->m_buttons = insertObject(pScene->m_buttons, pButton);

      pButton = createButton("MUSIC_BTN", createPoint(100, 360), 250, 80, false);
      pScene->m_buttons = insertObject(pScene->m_buttons, pButton);

      pButton = createButton("LARROW", createPoint(390, 370), 30, 60, false);
      pScene->m_buttons = insertObject(pScene->m_buttons, pButton);

      pButton = createButton("RARROW", createPoint(450, 370), 30, 60, false);
      pScene->m_buttons = insertObject(pScene->m_buttons, pButton);

      // setting sound/music/FS values from string
      int soundPos = 8, musicPos = 18, fullscreenPos = 33;
      int soundOffset = 0, musicOffset = 0;
      bool fullscreenOn = false;


      // sound value
      char * soundValue = ALLOC(char, 4);
      char * musicValue = ALLOC(char, 4);
      char * fullscreenValue = ALLOC(char, 4);


      getLineFromPos(soundValue, pScene->m_config->m_buffer, soundPos, false);
      int percentValue = atoi(soundValue);
      if(percentValue >= 10 && percentValue < 100)
            soundOffset = 1;
      else if(percentValue == 100)
            soundOffset = 2;

      pDisplayText = createDisplayText(soundValue, getFont("BEBAS", pFontManager), createPoint(520, 270),
                                       al_map_rgb(255, 255, 255), true);
      pScene->m_strings = insertObject(pScene->m_strings, pDisplayText);
      // music value
      getLineFromPos(musicValue, pScene->m_config->m_buffer, musicPos + soundOffset, false);
      percentValue = atoi(musicValue);
      if(percentValue >= 10 && percentValue < 100)
            musicOffset = 1;
      else if(percentValue == 100)
            musicOffset = 2;

      pDisplayText = createDisplayText(musicValue, getFont("BEBAS", pFontManager), createPoint(520, 370),
                                       al_map_rgb(255, 255, 255), true);
      pScene->m_strings = insertObject(pScene->m_strings, pDisplayText);
      // FS value
      getLineFromPos(fullscreenValue, pScene->m_config->m_buffer, fullscreenPos + soundOffset + musicOffset, false);

      pDisplayText = createDisplayText(fullscreenValue, getFont("BEBAS", pFontManager), createPoint(570, 370),
                                       al_map_rgb(255, 255, 255), true);
      pScene->m_strings = insertObject(pScene->m_strings, pDisplayText);

      // activating button
      pScene->m_activeButton = SOUND_BTN;

      pButton = getItem(pScene->m_buttons, pScene->m_activeButton);
      pButton->m_active = true;

      FREE(soundValue);
      FREE(musicValue);
      FREE(fullscreenValue);
}

void createMenuHighscoreScene(Scene * pScene, FontManager * pFontManager)
{
      DisplayText * pDisplayText = NULL;
      Image * pImage = NULL;

      pImage = createImage("MENU_BG", createPoint(0, 0));
      pScene->m_bgImages = insertObject(pScene->m_bgImages, pImage);

      pImage = createImage("FRAME", createPoint(80, 60));
      pScene->m_bgImages = insertObject(pScene->m_bgImages, pImage);

      char * tempLine = ALLOC(char, 21);

      int pos = 0; int i;
      for(i = 0; i < 10; i++)
      {
            getLineFromPos(tempLine, pScene->m_highscores->m_buffer, pos, false);
            pDisplayText = createDisplayText(tempLine, getFont("BEBAS", pFontManager), createPoint(400, 100 + i * 40),
                                             al_map_rgb(255, 255, 255), true);

            pScene->m_strings = insertObject(pScene->m_strings, pDisplayText);

            pos = findChar(pScene->m_highscores->m_buffer, pos, '\n') + 1;
      }
      FREE(tempLine);
}

void createMenuAboutScene(Scene * pScene, FontManager * pFontManager)
{
      Image * pImage = NULL;
      DisplayText * pDisplayText = NULL;

      pImage = createImage("MENU_BG", createPoint(0, 0));
      pScene->m_bgImages = insertObject(pScene->m_bgImages, pImage);

      pImage = createImage("FRAME", createPoint(80, 60));
      pScene->m_bgImages = insertObject(pScene->m_bgImages, pImage);

      char line1[] = "O grze ";
      char line2[] = " ";
      char line3[] = " ";

      pDisplayText = createDisplayText(line1, getFont("BEBAS", pFontManager), createPoint(400, 100),
                                       al_map_rgb(255, 255, 255), true);
      pScene->m_strings = insertObject(pScene->m_strings, pDisplayText);

      pDisplayText = createDisplayText(line2, getFont("BEBAS", pFontManager), createPoint(400, 130),
                                       al_map_rgb(255, 255, 255), true);
      pScene->m_strings = insertObject(pScene->m_strings, pDisplayText);

      pDisplayText = createDisplayText(line3, getFont("BEBAS", pFontManager), createPoint(400, 160),
                                       al_map_rgb(255, 255, 255), true);
      pScene->m_strings = insertObject(pScene->m_strings, pDisplayText);
}

void createPlayPlayScene(Scene * pScene, FontManager * pFontManager)
{
      Image * pImage = NULL;
      DisplayText * pDisplayText = NULL;

      pScene->m_player = createPlayer("PLAYER_SHIP", "BULLET");
      pScene->m_powerup = createPowerup(20, 20);

      pImage = createImage("PLAY_BG", createPoint(0, 0));
      pScene->m_bgImages = insertObject(pScene->m_bgImages, pImage);

      // points
      pDisplayText = createDisplayText("POINTS", getFont("BEBAS", pFontManager), createPoint(60, 6),
                                       al_map_rgb(255, 255, 255), true);
      pScene->m_strings = insertObject(pScene->m_strings, pDisplayText);

      pDisplayText = createDisplayText("0", getFont("BEBAS", pFontManager), createPoint(60, 36),
                                       al_map_rgb(255, 255, 255), true);
      pScene->m_strings = insertObject(pScene->m_strings, pDisplayText);

      // highscores
      pDisplayText = createDisplayText("HIGHSCORE", getFont("BEBAS", pFontManager), createPoint(400, 6),
                                       al_map_rgb(255, 255, 255), true);
      pScene->m_strings = insertObject(pScene->m_strings, pDisplayText);


      char * points = ALLOC(char, 10);
      getLineFromPos(points, pScene->m_highscores->m_buffer, findChar(pScene->m_highscores->m_buffer, 0, '#') + 1, false);

      pDisplayText = createDisplayText(points, getFont("BEBAS", pFontManager), createPoint(400, 36),
                                       al_map_rgb(255, 255, 255), true);
      pScene->m_strings = insertObject(pScene->m_strings, pDisplayText);

      FREE(points);
}

void createPlayPauseScene(Scene * pScene)
{
      Image * pImage = NULL;

      pImage = createImage("PAUSE_SCR", createPoint(0, 0));
      pScene->m_bgImages = insertObject(pScene->m_bgImages, pImage);
}

void createPlayGameoverScene(Scene * pScene)
{
      Image * pImage = NULL;

      pImage = createImage("GAMEOVER_SCR", createPoint(0, 0));
      pScene->m_bgImages = insertObject(pScene->m_bgImages, pImage);
}
