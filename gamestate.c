#include "gamestate.h"

GameState * createState(GAME_STATES whatState, String * highscores, String * config, TextureManager * pTextureManager, SoundManager * pSoundManager, FontManager * pFontManager)
{
      GameState * pGameState = ALLOC(GameState, 1);

      pGameState->m_stateID = whatState;
      pGameState->m_scenes = NULL;
      pGameState->m_timer = createTimer();
      pGameState->m_currentScene = 0;
      pGameState->m_highscores = highscores;
      pGameState->m_config = config;

      switch(whatState)
      {
            case INTRO_STATE:
                  createIntroState(pGameState, pTextureManager, pSoundManager, pFontManager);
                  break;
            case MENU_STATE:
                  createMenuState(pGameState, pTextureManager, pSoundManager, pFontManager);
                  break;
            case PLAY_STATE:
                  createPlayState(pGameState, pTextureManager, pSoundManager, pFontManager);
                  break;
      }
      startTimer(pGameState->m_timer);
      return pGameState;
}

void destroyState(GAME_STATES whatState, GameState * pGameState, TextureManager * pTextureManager, SoundManager * pSoundManager)
{
      if(!pGameState)
            return;

      switch(whatState)
      {
            case INTRO_STATE:
                  destroyIntroState(pGameState, pTextureManager, pSoundManager);
                  break;
            case MENU_STATE:
                  destroyMenuState(pGameState, pTextureManager, pSoundManager);
                  break;
            case PLAY_STATE:
                  destroyPlayState(pGameState, pTextureManager, pSoundManager);
                  break;
      }

      int i;

      for(i = 0; i < pGameState->m_scenes->m_arraySize; i++)
            destroyScene(getItem(pGameState->m_scenes, i));

      clearArray(pGameState->m_scenes, true, NO_ALLEGRO);

      FREE(pGameState->m_scenes);
      FREE(pGameState);
}

void createIntroState(GameState * pGameState, TextureManager * pTextureManager, SoundManager * pSoundManager, FontManager * pFontManager)
{
      Scene * pTempScene = NULL;

      pGameState->m_scenes = createArray(pGameState->m_scenes, 1);

      loadTexture("images/intro_background.png", "INTRO_BG", pTextureManager);

      loadSound("music/MenuMusic2.ogg", "MENU_MUSIC", MUSIC, pSoundManager);

      // INTRO TITLE SCENE
      pTempScene = createScene(INTRO_TITLE_SCENE, pGameState->m_highscores, pGameState->m_config, pFontManager);
      pGameState->m_scenes = insertObject(pGameState->m_scenes, pTempScene);


      pGameState->m_currentScene = INTRO_TITLE_SCENE;
}

void createMenuState(GameState * pGameState, TextureManager * pTextureManager, SoundManager * pSoundManager, FontManager * pFontManager)
{
      Scene * pTempScene = NULL;

      pGameState->m_scenes = createArray(pGameState->m_scenes, 4);
      pGameState->m_currentScene = TITLE;

      loadTexture("images/menu_background.png", "MENU_BG", pTextureManager);
      loadTexture("images/play_button.png", "PLAY_BTN", pTextureManager);
      loadTexture("images/options_button.png", "OPTIONS_BTN", pTextureManager);
      loadTexture("images/highscores_button.png", "HSCORES_BTN", pTextureManager);
      loadTexture("images/about_button.png", "ABOUT_BTN", pTextureManager);
      loadTexture("images/exit_button.png", "EXIT_BTN", pTextureManager);
      loadTexture("images/frame.png", "FRAME", pTextureManager);
      loadTexture("images/sound_button.png", "SOUND_BTN", pTextureManager);
      loadTexture("images/music_button.png", "MUSIC_BTN", pTextureManager);
      loadTexture("images/left_arrow.png", "LARROW", pTextureManager);
      loadTexture("images/right_arrow.png", "RARROW", pTextureManager);

      loadSound("music/GameMusic.ogg", "GAME_MUSIC", MUSIC, pSoundManager);

      // MENU TITLE SCREEN SCENE
      pTempScene = createScene(MENU_TITLE_SCENE, pGameState->m_highscores, pGameState->m_config, pFontManager);
      pGameState->m_scenes = insertObject(pGameState->m_scenes, pTempScene);

      // MENU OPTION SCREEN SCENE
      pTempScene = createScene(MENU_OPTION_SCENE, pGameState->m_highscores, pGameState->m_config, pFontManager);
      pGameState->m_scenes = insertObject(pGameState->m_scenes, pTempScene);

      // MENU HIGHSCORE SCREEN SCENE
      pTempScene = createScene(MENU_HIGHSCORE_SCENE, pGameState->m_highscores, pGameState->m_config, pFontManager);
      pGameState->m_scenes = insertObject(pGameState->m_scenes, pTempScene);
      printf("Tu jestem\n");

      // MENU ABOUT SCREEN SCENE
      pTempScene = createScene(MENU_ABOUT_SCENE, pGameState->m_highscores, pGameState->m_config, pFontManager);
      pGameState->m_scenes = insertObject(pGameState->m_scenes, pTempScene);
      printf("Tu jestem\n");

      playSound("MENU_MUSIC", MUSIC, true, pSoundManager);
}

void createPlayState(GameState * pGameState, TextureManager * pTextureManager, SoundManager * pSoundManager, FontManager * pFontManager)
{
      Scene * pTempScene = NULL;

      pGameState->m_scenes = createArray(pGameState->m_scenes, 3);
      pGameState->m_currentScene = PLAY;

      loadTexture("images/play_background.png", "PLAY_BG", pTextureManager);
      loadTexture("images/mybullet.png", "BULLET", pTextureManager);
      loadTexture("images/myship.png", "PLAYER_SHIP", pTextureManager);
      loadTexture("images/myasteroid_normal.png", "ASTEROID_NORMAL", pTextureManager);
      loadTexture("images/myasteroid_verybig.png", "ASTEROID_VERYBIG", pTextureManager);
      loadTexture("images/myasteroid_big.png", "ASTEROID_BIG", pTextureManager);
      loadTexture("images/myasteroid2_normal.png", "ASTEROID2_NORMAL", pTextureManager);
      loadTexture("images/myasteroid2_verybig.png", "ASTEROID2_VERYBIG", pTextureManager);
      loadTexture("images/myasteroid2_big.png", "ASTEROID2_BIG", pTextureManager);
      loadTexture("images/myasteroid3_normal.png", "ASTEROID3_NORMAL", pTextureManager);
      loadTexture("images/myasteroid3_verybig.png", "ASTEROID3_VERYBIG", pTextureManager);
      loadTexture("images/myasteroid3_big.png", "ASTEROID3_BIG", pTextureManager);
      loadTexture("images/mybeam.png", "BEAM", pTextureManager);
      loadTexture("images/shield_powerup.png", "SHIELD_POWERUP", pTextureManager);
      loadTexture("images/bullet_powerup.png", "BULLET_POWERUP", pTextureManager);
      loadTexture("images/beam_powerup.png", "BEAM_POWERUP", pTextureManager);
      loadTexture("images/bomb_powerup.png", "BOMB_POWERUP", pTextureManager);
      loadTexture("images/ship_powerup.png", "SHIP_POWERUP", pTextureManager);
      loadTexture("images/freeze_powerup.png", "FREEZE_POWERUP", pTextureManager);
      loadTexture("images/gameover_screen.png", "GAMEOVER_SCR", pTextureManager);
      loadTexture("images/myshield.png", "SHIELD", pTextureManager);
      loadTexture("images/blockofice1_normal.png", "BLOCKOFICE1_NORMAL", pTextureManager);
      loadTexture("images/blockofice1_big.png", "BLOCKOFICE1_BIG", pTextureManager);
      loadTexture("images/blockofice1_verybig.png", "BLOCKOFICE1_VERYBIG", pTextureManager);
      loadTexture("images/blockofice2_normal.png", "BLOCKOFICE2_NORMAL", pTextureManager);
      loadTexture("images/blockofice2_big.png", "BLOCKOFICE2_BIG", pTextureManager);
      loadTexture("images/blockofice2_verybig.png", "BLOCKOFICE2_VERYBIG", pTextureManager);
      loadTexture("images/blockofice3_normal.png", "BLOCKOFICE3_NORMAL", pTextureManager);
      loadTexture("images/blockofice3_big.png", "BLOCKOFICE3_BIG", pTextureManager);
      loadTexture("images/blockofice3_verybig.png", "BLOCKOFICE3_VERYBIG", pTextureManager);
      loadTexture("images/explosion.png", "EXPLOSION", pTextureManager);
      loadTexture("images/redbeamhudbig.png", "REDBEAMHUD", pTextureManager);
      loadTexture("images/greenbeamhudbig.png", "GREENBEAMHUD", pTextureManager);
      loadTexture("images/mybullethit.png", "BULLET_HIT", pTextureManager);
      loadTexture("images/bomb.png", "BOMB", pTextureManager);
      loadTexture("images/beam_icon.png", "BEAM_ICON", pTextureManager);
      loadTexture("images/pause_screen.png", "PAUSE_SCR", pTextureManager);

      loadSound("sounds/laser4.ogg", "LASER", SFX, pSoundManager);
      loadSound("sounds/poweruppicked.ogg", "POWERUPPICKED", SFX, pSoundManager);
      loadSound("sounds/bullet.ogg", "BULLET", SFX, pSoundManager);
      loadSound("sounds/explo.ogg", "EXPLOSION", SFX, pSoundManager);
      loadSound("sounds/wtfbomb.ogg", "WTFBOMB", SFX, pSoundManager);
      loadSound("sounds/accelerate2.ogg", "ACCELERATE", SFX, pSoundManager);

      // PLAY PLAY SCREEN SCENE
      pTempScene = createScene(PLAY_PLAY_SCENE, pGameState->m_highscores, pGameState->m_config, pFontManager);
      pGameState->m_scenes = insertObject(pGameState->m_scenes, pTempScene);



      // PLAY PAUSE SCREEN SCENE

      pTempScene = createScene(PLAY_PAUSE_SCENE, pGameState->m_highscores, pGameState->m_config, pFontManager);
      pGameState->m_scenes = insertObject(pGameState->m_scenes, pTempScene);

      // PLAY GAMEOVER SCREEN SCENE

      pTempScene = createScene(PLAY_GAMEOVER_SCENE, pGameState->m_highscores, pGameState->m_config, pFontManager);
      pGameState->m_scenes = insertObject(pGameState->m_scenes, pTempScene);

      playSound("GAME_MUSIC", MUSIC, true, pSoundManager);
}

void destroyIntroState(GameState * pGameState, TextureManager * pTextureManager, SoundManager * pSoundManager)
{
      freeTexture("INTRO_BG", pTextureManager);
}

void destroyMenuState(GameState * pGameState, TextureManager * pTextureManager, SoundManager * pSoundManager)
{
      freeTexture("MENU_BG", pTextureManager);
      freeTexture("PLAY_BTN", pTextureManager);
      freeTexture("OPTIONS_BTN", pTextureManager);
      freeTexture("HSCORES_BTN", pTextureManager);
      freeTexture("ABOUT_BTN", pTextureManager);
      freeTexture("EXIT_BTN", pTextureManager);
      freeTexture("FRAME", pTextureManager);
      freeTexture("LARROW", pTextureManager);
      freeTexture("RARROW", pTextureManager);
      freeTexture("SOUND_BTN", pTextureManager);
      freeTexture("MUSIC_BTN", pTextureManager);
}

void destroyPlayState(GameState * pGameState, TextureManager * pTextureManager, SoundManager * pSoundManager)
{
      freeTexture("PLAY_BG", pTextureManager);
      freeTexture("PLAYER_SHIP", pTextureManager);
      freeTexture("BULLET", pTextureManager);
      freeTexture("ASTEROID_NORMAL", pTextureManager);
      freeTexture("ASTEROID_BIG", pTextureManager);
      freeTexture("ASTEROID_VERYBIG", pTextureManager);
      freeTexture("ASTEROID2_NORMAL", pTextureManager);
      freeTexture("ASTEROID2_BIG", pTextureManager);
      freeTexture("ASTEROID2_VERYBIG", pTextureManager);
      freeTexture("ASTEROID3_NORMAL", pTextureManager);
      freeTexture("ASTEROID3_BIG", pTextureManager);
      freeTexture("ASTEROID3_VERYBIG", pTextureManager);
      freeTexture("BEAM", pTextureManager);
      freeTexture("SHIELD_POWERUP", pTextureManager);
      freeTexture("BULLET_POWERUP", pTextureManager);
      freeTexture("BEAM_POWERUP", pTextureManager);
      freeTexture("BOMB_POWERUP", pTextureManager);
      freeTexture("FREEZE_POWERUP", pTextureManager);
      freeTexture("SHIP_POWERUP", pTextureManager);
      freeTexture("GAMEOVER_SCR", pTextureManager);
      freeTexture("SHIELD", pTextureManager);
      freeTexture("BLOCKOFICE1_NORMAL", pTextureManager);
      freeTexture("BLOCKOFICE1_BIG", pTextureManager);
      freeTexture("BLOCKOFICE1_VERYBIG", pTextureManager);
      freeTexture("BLOCKOFICE2_NORMAL", pTextureManager);
      freeTexture("BLOCKOFICE2_BIG", pTextureManager);
      freeTexture("BLOCKOFICE2_VERYBIG", pTextureManager);
      freeTexture("BLOCKOFICE3_NORMAL", pTextureManager);
      freeTexture("BLOCKOFICE3_BIG", pTextureManager);
      freeTexture("BLOCKOFICE3_VERYBIG", pTextureManager);
      freeTexture("EXPLOSION", pTextureManager);
      freeTexture("BULLET_HIT", pTextureManager);
      freeTexture("REDBEAMHUD", pTextureManager);
      freeTexture("GREENBEAMHUD", pTextureManager);
      freeTexture("BOMB", pTextureManager);
      freeTexture("BEAM_ICON", pTextureManager);
      freeTexture("PAUSE_SCR", pTextureManager);

      freeSound("LASER", SFX, pSoundManager);
      freeSound("POWERUPPICKED", SFX, pSoundManager);
      freeSound("BULLET", SFX, pSoundManager);
      freeSound("EXPLOSION", SFX, pSoundManager);
      freeSound("WTFBOMB", SFX, pSoundManager);
      freeSound("ACCELERATE", SFX, pSoundManager);
}
