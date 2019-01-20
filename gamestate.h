#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include "scene.h"
#include "soundmanager.h"
#include "memdebug.h"
#include "timer.h"

/** \brief
 *
 * Enum for gamestates
 *
 */
typedef enum GAME_STATES
{
      NO_STATE,
      INTRO_STATE,
      MENU_STATE,
      PLAY_STATE

} GAME_STATES;

/** \brief
 *
 * Struct which describes gamestate
 *
 */
typedef struct GameState
{
      GAME_STATES m_stateID;  /**< \brief GameState ID */

      SCENES m_currentScene; /**< \brief Current processing scene */

      DynamicArray * m_scenes;  /**< \brief Dynamic array of scenes stored as pointers on Scene */

      Timer * m_timer;  /**< \brief Count time */

      String * m_highscores;  /**< \brief Ptr on text loaded from file */
      String * m_config;  /**< \brief Ptr on text loaded from file */

} GameState;

/** \brief
 *
 * This function create game state
 *
 * \param newState - Specify what state has to be created
 * \param highscores - Ptr on text with highscores
 * \param config - Ptr on text with config
 * \param pTextureManager - Ptr on TextureManager
 * \param pSoundManager - Ptr on SoundManager
 * \param pFontManager - Ptr on FontManager
 * \return Ptr on GameState
 *
 */
GameState * createState(GAME_STATES newState, String * highscores, String * config, TextureManager * pTextureManager, SoundManager * pSoundManager, FontManager * pFontManager);

/** \brief
 *
 * This function creates intro state
 *
 * \param pGameState - Ptr on GameState
 * \param pTextureManager - Ptr on TextureManager
 * \param pSoundManager - Ptr on SoundManager
 * \param pFontManager - Ptr on FontManager
 * \return Nothing
 *
 */
void createIntroState(GameState * pGameState, TextureManager * pTextureManager, SoundManager * pSoundManager, FontManager * pFontManager);

/** \brief
 *
 * This function creates menu state
 *
 * \param pGameState - Ptr on GameState
 * \param pTextureManager - Ptr on TextureManager
 * \param pSoundManager - Ptr on SoundManager
 * \param pFontManager - Ptr on FontManager
 * \return Nothing
 *
 */
void createMenuState(GameState * pGameState, TextureManager * pTextureManager, SoundManager * pSoundManager, FontManager * pFontManager);

/** \brief
 *
 * This function creates gameplay state
 *
 * \param pGameState - Ptr on GameState
 * \param pTextureManager - Ptr on TextureManager
 * \param pSoundManager - Ptr on SoundManager
 * \param pFontManager - Ptr on FontManager
 * \return Nothing
 *
 */
void createPlayState(GameState * pGameState, TextureManager * pTextureManager, SoundManager * pSoundManager, FontManager * pFontManager);

/** \brief
 *
 * This function destroys state
 *
 * \param whatState - Specify which state has to be deleted
 * \param pGameState - Ptr on GameState
 * \param pTextureManager - Ptr on TextureManager
 * \param pSoundManager - Ptr on SoundManager
 * \return Nothing
 *
 */
void destroyState(GAME_STATES whatState, GameState * pGameState, TextureManager * pTextureManager, SoundManager * pSoundManager);


/** \brief
 *
 * This function destroys intro state
 *
 * \param pGameState - Ptr on GameState
 * \param pTextureManager - Ptr on TextureManager
 * \param pSoundManager - Ptr on SoundManager
 * \return Nothing
 *
 */
void destroyIntroState(GameState * pGameState, TextureManager * pTextureManager, SoundManager * pSoundManager);

/** \brief
 *
 * This function destroys menu state
 *
 * \param pGameState - Ptr on GameState
 * \param pTextureManager - Ptr on TextureManager
 * \param pSoundManager - Ptr on SoundManager
 * \return Nothing
 *
 */
void destroyMenuState(GameState * pGameState, TextureManager * pTextureManager, SoundManager * pSoundManager);

/** \brief
 *
 * This function destroys gameplay state
 *
 * \param pGameState - Ptr on GameState
 * \param pTextureManager - Ptr on TextureManager
 * \param pSoundManager - Ptr on SoundManager
 * \return Nothing
 *
 */
void destroyPlayState(GameState * pGameState, TextureManager * pTextureManager, SoundManager * pSoundManager);

#endif // GAMESTATE_H_INCLUDED
