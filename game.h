#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <math.h>
#include <allegro5/allegro5.h>
#include <stdio.h>

#include "graphicmanager.h"
#include "inputhandler.h"
#include "gamestate.h"
#include "dynamicarray.h"
#include "texturemanager.h"
#include "soundmanager.h"
#include "collision.h"
#include "powerups.h"
#include "io.h"
#include "fontmanager.h"
#include "timer.h"
#include "memdebug.h"

#define isPressed(keycode) (isKeyDown(pGame->m_pInputHandler, keycode))
#define wasPressed(keycode) (wasKeyPressed(pGame->m_pInputHandler, keycode))


/** \brief
 *
 * Struct which describes game
 *
 */
typedef struct Game
{
      // managers
      GraphicManager * m_pGraphicManager;   /**< \brief Ptr on GraphicManager */
      InputHandler * m_pInputHandler;  /**< \brief Ptr on InputHandler */
      SoundManager * m_pSoundManager;  /**< \brief Ptr on SoundManager */
      TextureManager * m_pTextureManager;  /**< \brief Ptr on TextureManager */
      FontManager * m_pFontManager;  /**< \brief Ptr on FontManager */

      // game variables
      GameState * m_pGameState;  /**< \brief Ptr on current game state */
      bool m_changeState;  /**< \brief Check if game state has to be changed */
      GAME_STATES m_whatState;  /**< \brief Specify which state has to be created */

      // loading variables
      String * m_config;  /**< \brief Ptr on text loaded from file */
      String * m_highscores;  /**< \brief Ptr on text loaded from file */
      int m_points[10];  /**< \brief Array of points stored in m_highscores */
} Game;

/** \brief
 *
 * This function creates game
 *
 * \return Ptr on Game
 *
 */
Game * createGame();

/** \brief
 *
 * This function destroys game
 *
 * \param pGame - Ptr on Game
 * \return Nothing
 *
 */
void destroyGame(Game * pGame);

/** \brief
 *
 * This function handles keyboard input
 *
 * \param pInputHandler - Ptr on InputHandler
 * \return Nothing
 *
 */
void handleInput(InputHandler * pInputHandler);

/** \brief
 *
 * This function handles all logic of game
 *
 * \param pGame - Ptr on Game
 * \return Nothing
 *
 */
void doLogic(Game * pGame);

/** \brief
 *
 * This function draws game
 *
 * \param pGame - Ptr on Game
 * \return Nothing
 *
 */
void drawGame(Game * pGame);

/** \brief
 *
 * This function changes game state
 *
 * \param whatState - Specify what is the new game state
 * \param pGame - Ptr on Game
 * \return Nothing
 *
 */
void changeState(GAME_STATES whatState, Game * pGame);

/** \brief
 *
 * This function handles logic of intro state
 *
 * \param pGame - Ptr on Game
 * \return Nothing
 *
 */
void logicIntroState(Game * pGame);

/** \brief
 *
 * This function handles logic of menu state
 *
 * \param pGame - Ptr on Game
 * \return Nothing
 *
 */
void logicMenuState(Game * pGame);

/** \brief
 *
 * This function handles logic of menu title scene
 *
 * \param pGame - Ptr on Game
 * \return Nothing
 *
 */
void logicMenuTitleScene(Game * pGame);

/** \brief
 *
 * This function handles logic of menu option scene
 *
 * \param pGame - Ptr on Game
 * \return Nothing
 *
 */
void logicMenuOptionsScene(Game * pGame);

/** \brief
 *
 * This function handles logic of menu highscores scene
 *
 * \param pGame - Ptr on Game
 * \return Nothing
 *
 */
void logicMenuHighscoresScene(Game * pGame);

/** \brief
 *
 * This function handles logic of menu about scene
 *
 * \param pGame - Ptr on Game
 * \return Nothing
 *
 */
void logicMenuAboutScene(Game * pGame);

/** \brief
 *
 * This function handles logic of gameplay state
 *
 * \param pGame - Ptr on Game
 * \return Nothing
 *
 */
void logicPlayState(Game * pGame);

/** \brief
 *
 * This function handles logic of gameplay play scene
 *
 * \param pGame - Ptr on Game
 * \return Nothing
 *
 */
void logicPlayPlayScene(Game * pGame);

/** \brief
 *
 * This function handles logic of gameplay pause scene
 *
 * \param pGame - Ptr on Game
 * \return Nothing
 *
 */
void logicPlayPauseScene(Game * pGame);

/** \brief
 *
 * This function handles logic of gameplay gameover scene
 *
 * \param pGame - Ptr on Game
 * \return Nothing
 *
 */
void logicPlayGameoverScene(Game * pGame);

/** \brief
 *
 * This function checks collision between bullet and asteroid
 *
 * \param pBullet - Ptr on Bullet
 * \param pAsteroid - Ptr on Asteroid
 * \return True if collision exist, false otherwise.
 *
 */
bool checkBulletAsteroidCollision(Bullet * pBullet, Asteroid * pAsteroid);

/** \brief
 *
 * This function checks collision between beam and asteroid
 *
 * \param pBeam - Ptr on Beam
 * \param pAsteroid - Ptr on Asteroid
 * \return True if collision exist, false otherwise.
 *
 */
bool checkBeamAsteroidCollision(Beam * pBeam, Asteroid * pAsteroid);

/** \brief
 *
 * This function checks collision between player and asteroid
 *
 * \param pPlayer - Ptr on Player
 * \param pAsteroid - Ptr on Asteroid
 * \return True if collision exist, false otherwise.
 *
 */
bool checkPlayerAsteroidCollision(Player * pPlayer, Asteroid * pAsteroid);

/** \brief
 *
 * This function checks collision between player and powerup
 *
 * \param pPlayer - Ptr on Player
 * \param pPowerup - Ptr on Powerup
 * \return True if collision exist, false otherwise.
 *
 */
bool checkPlayerPowerupCollision(Player * pPlayer, Powerup * pPowerup);

/** \brief
 *
 * This function loads highscores from file "highscores.txt"
 *
 * \param pGame - Ptr on Game
 * \return Nothing
 *
 */
void loadHighscores(Game * pGame);

/** \brief
 *
 * This function saves highscores to file "highscores.txt"
 *
 * \param pGame - Ptr on Game
 * \param points - Points scored by player
 * \return Nothing
 *
 */
void saveHighscores(Game * pGame, int points);

/** \brief
 *
 * This function loads game configuration from "config.ini"
 *
 * \param pGame - Ptr on Game
 * \return Nothing
 *
 */
void loadConfig(Game * pGame);

/** \brief
 *
 * This function saves game configuration to "config.ini"
 *
 * \param pGame - Ptr on Game
 * \return Nothing
 *
 */
void saveConfig(Game * pGame);

/** \brief
 *
 * This function backs to main menu from highscore and about scene
 *
 * \param pGame - Ptr on Game
 * \return Nothing
 *
 */
void backToMainMenu(Game * pGame);

/** \brief
 *
 * This function changes samples volume
 *
 * \param pGame - Ptr on Game
 * \return Nothing
 *
 */
void changeSamplesVolume(Game * pGame);

/** \brief
 *
 * This function decrease option (in example sound volume)
 *
 * \param pGame - Ptr on Game
 * \param pOptionScene - Ptr on Scene
 * \return Nothing
 *
 */
void decreaseOption(Game * pGame, Scene * pOptionScene);

/** \brief
 *
 * This function increase option (in example sound volume)
 *
 * \param pGame - Ptr on Game
 * \param pOptionScene - Ptr on Scene
 * \return Nothing
 *
 */
void increaseOption(Game * pGame, Scene * pOptionScene);

#endif // GAME_H_INCLUDED
