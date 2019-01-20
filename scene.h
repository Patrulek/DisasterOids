#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "dynamicarray.h"
#include "asteroid.h"
#include "texturemanager.h"
#include "player.h"
#include "button.h"
#include "image.h"
#include "powerups.h"
#include "displaytext.h"
#include "fontmanager.h"
#include "collision.h"
#include "memdebug.h"

/** \brief
 *
 * Enum for scenes in game
 *
 */
typedef enum SCENES
{
      INTRO_TITLE_SCENE,
      MENU_TITLE_SCENE,
      MENU_OPTION_SCENE,
      MENU_HIGHSCORE_SCENE,
      MENU_ABOUT_SCENE,
      PLAY_PLAY_SCENE,
      PLAY_PAUSE_SCENE,
      PLAY_GAMEOVER_SCENE

} SCENES;

/** \brief
 *
 * Enum for scenes in menu
 *
 */
typedef enum MENU_SCENES
{
      TITLE,
      OPTION,
      HIGHSCORE,
      ABOUT

} MENU_SCENES;

/** \brief
 *
 * Enum for scenes in gameplay state
 *
 */
typedef enum PLAY_SCENES
{
      PLAY,
      PAUSE,
      GAMEOVER

} PLAY_SCENES;

/** \brief
 *
 * Struct which describe scene
 *
 */
typedef struct Scene
{
      short m_activeButton;  /**< \brief ID of active button in scene */
      Player * m_player;  /**< \brief Ptr on Player */
      // objects:
      DynamicArray * m_bgImages;  /**< \brief Dynamic array of images stored as pointers on Image */
      DynamicArray * m_explosions;  /**< \brief Dynamic array of explosions stored as pointers on AnimatedImage */
      DynamicArray * m_bulletHits;  /**< \brief Dynamic array of bullet hits stored as pointers on AnimatedImage */
      DynamicArray * m_asteroids;  /**< \brief Dynamic array of asteroids stored as pointers on Asteroid */
      DynamicArray * m_buttons;  /**< \brief Dynamic array of button stored as pointers on Button */
            // powerups
      Powerup * m_powerup;  /**< \brief Ptr on Powerup */
      // texts
      DynamicArray * m_strings;  /**< \brief Dynamic array of text displayed on screen stored as pointers on DisplayText */

      String * m_highscores;  /**< \brief Pointer on text loaded from file */
      String * m_config;  /**< \brief Pointer on text loaded from file */
} Scene;

/** \brief
 *
 * This function creates scene
 *
 * \param whatScene - Specify what scene has to be created
 * \param highscores - Ptr on text with loaded highscores
 * \param config - Ptr on text with loaded config
 * \param pFontManager - Ptr on FontManager
 * \return Ptr on Scene
 *
 */
Scene * createScene(SCENES whatScene, String * highscores, String * config, FontManager * pFontManager);

/** \brief
 *
 * This function destroys scene
 *
 * \param pScene - Ptr on Scene
 * \return Nothing
 *
 */
void destroyScene(Scene * pScene);

/** \brief
 *
 * This function creates intro title scene
 *
 * \param pScene - Ptr on Scene
 * \return Nothing
 *
 */
void createIntroTitleScene(Scene * pScene);

/** \brief
 *
 * This function creates menu title scene
 *
 * \param pScene - Ptr on Scene
 * \return Nothing
 *
 */
void createMenuTitleScene(Scene * pScene);

/** \brief
 *
 * This function creates menu option scene
 *
 * \param pScene - Ptr on Scene
 * \return Nothing
 *
 */
void createMenuOptionScene(Scene * pScene, FontManager * pFontManager);

/** \brief
 *
 * This function creates menu highscores scene
 *
 * \param pScene - Ptr on Scene
 * \return Nothing
 *
 */
void createMenuHighscoreScene(Scene * pScene, FontManager * pFontManager);

/** \brief
 *
 * This function creates menu about scene
 *
 * \param pScene - Ptr on Scene
 * \return Nothing
 *
 */
void createMenuAboutScene(Scene * pScene, FontManager * pFontManager);

/** \brief
 *
 * This function creates game play scene
 *
 * \param pScene - Ptr on Scene
 * \return Nothing
 *
 */
void createPlayPlayScene(Scene * pScene, FontManager * pFontManager);

/** \brief
 *
 * This function creates game play pause scene
 *
 * \param pScene - Ptr on Scene
 * \return Nothing
 *
 */
void createPlayPauseScene(Scene * pScene);

/** \brief
 *
 * This function creates game play gameover scene
 *
 * \param pScene - Ptr on Scene
 * \return Nothing
 *
 */
void createPlayGameoverScene(Scene * pScene);

 /** \brief
 *
 * This function draws entire scene on screen
 *
 * \param pScene - Ptr on Scene
 * \param pTextureManager - Ptr on TextureManager
 * \param pFontManager - Ptr on FontManager
 * \return Nothing
 *
 */
void drawScene(Scene * pScene, TextureManager * pTextureManager, FontManager * pFontManager);


#endif // SCENE_H_INCLUDED
