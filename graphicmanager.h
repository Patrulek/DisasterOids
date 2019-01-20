#ifndef GRAPHICMANAGER_H_INCLUDED
#define GRAPHICMANAGER_H_INCLUDED

#define SCREEN_WIDTH 800  /**< \brief Width of screen in pixels */
#define SCREEN_HEIGHT 600  /**< \brief Height of screen in pixels */

/** \brief
 *
 * This functions gets horizontal resolution of monitor
 *
 * \return Horizontal resolution in pixels
 *
 */
int getHorResolution();

/** \brief
 *
 * This functions gets vertical resolution of monitor
 *
 * \return Vertical resolution in pixels
 *
 */
int getVerResolution();

#define NEW_WINDOW_X (getHorResolution() - SCREEN_WIDTH)/2  /**< \brief Position of new created window in x axis */
#define NEW_WINDOW_Y (getVerResolution() - SCREEN_HEIGHT)/2  /**< \brief Position of new created window in y axis */

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#include "memdebug.h"
#include "scene.h"
#include "dynamicarray.h"
#include "texturemanager.h"

/** \brief
 *
 * Struct which describe graphic manager
 *
 */
typedef struct GraphicManager
{
      ALLEGRO_DISPLAY * m_pDisplay;  /**< \brief Pointer to window */

      bool m_fullscreenOn;  /**< Check if fullscreen is on or off */
} GraphicManager;

/** \brief
 *
 * This function creates graphic manager
 *
 * \return Ptr on GraphicManager
 *
 */
GraphicManager * createGraphicManager();

/** \brief
 *
 * This function destroys graphic manager
 *
 * \param pGraphicManager - Ptr on GraphicManager
 * \return Nothing
 *
 */
void destroyGraphicManager(GraphicManager * pGraphicManager);

/** \brief
 *
 * This function creates window
 *
 * \param title - Title of window
 * \param startX - Position of window in x axis
 * \param startY - Position of window in y axis
 * \param width - Width of window
 * \param height - Height of window
 * \return Ptr on ALLEGRO_DISPLAY (for more info see allegro documentation)
 *
 */
ALLEGRO_DISPLAY * createDisplay(const char * title, int startX, int startY, int width, int height);

/** \brief
 *
 * This function destroys display
 *
 * \param pDisplay - Ptr on ALLEGRO_DISPLAY
 * \return Nothing
 *
 */
void destroyDisplay(ALLEGRO_DISPLAY * pDisplay);

/** \brief
 *
 * This function draws backbuffer onto screen
 *
 * \return Nothing
 *
 */
void renderDisplay();

/** \brief
 *
 * This function clears of screen by given color
 *
 * \param color - Color which fills entire screen
 * \return Nothing
 *
 */
void clearScreen(ALLEGRO_COLOR color);

#endif // GRAPHICMANAGER_H_INCLUDED
