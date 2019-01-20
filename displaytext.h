#ifndef DISPLAYString_H_INCLUDED
#define DISPLAYString_H_INCLUDED

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "geometry.h"
#include "io.h"
#include "memdebug.h"


/** \brief
 *
 * Struct which describe a text displayed on screen
 *
 */
typedef struct DisplayText
{
      char * m_buffer; /**< \brief Text stored as cstring */
      ALLEGRO_FONT * m_font; /**< \brief Font of text */
      Point * m_position; /**< \brief Position on screen */
      ALLEGRO_COLOR m_color; /**< \brief Color of text */
      bool m_active; /**< \brief Check if text is active or not; active texts are displayed, non-active not */

} DisplayText;

/** \brief
 *
 * This function creates a text to display
 *
 * \param pBuffer - Text to display
 * \param pFont - Font of text
 * \param pPosition - Position on screen
 * \param color - Color of text
 * \param m_active - If text is active
 * \return Ptr on DisplayText
 *
 */
DisplayText * createDisplayText(const char * pBuffer, ALLEGRO_FONT * pFont, Point * pPosition, ALLEGRO_COLOR color, bool active);

/** \brief
 *
 * This function destroys display text
 *
 * \param pDisplayText - Ptr on DisplayText
 * \return Nothing
 *
 */
void destroyDisplayText(DisplayText * pDisplayText);

/** \brief
 *
 * This function change text buffer of object
 *
 * \param pBuffer - Cstring which change actual buffer of object
 * \param pDisplayText - Ptr on DisplayText
 * \return Nothing
 *
 */
void changeDisplayText(const char * pBuffer, DisplayText * pDisplayText);

/** \brief
 *
 * This function draws text on screen
 *
 * \param pDisplayText - Ptr on DisplayText
 * \return Nothing
 *
 */
void drawDisplayText(DisplayText * pDisplayText);

#endif // DISPLAYString_H_INCLUDED
