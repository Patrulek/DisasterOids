#ifndef FONTMANAGER_H_INCLUDED
#define FONTMANAGER_H_INCLUDED

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "dynamicarray.h"


/** \brief
 *
 * Struct which describes font manager
 *
 */
typedef struct FontManager
{
      DynamicArray * m_fontKeys; /**< \brief Fonts keys stored as cstrings */
      DynamicArray * m_fonts; /**< \brief Fonts stored as pointers on ALLEGRO_FONT */

} FontManager;

/** \brief
 *
 * This function creates font manager
 *
 * \return Ptr on FontManager
 *
 */
FontManager * createFontManager();

/** \brief
 *
 * This function destroys font manager
 *
 * \param pFontManager - Ptr on FontManager
 * \return Nothing
 *
 */
void destroyFontManager(FontManager * pFontManager);

/** \brief
 *
 * This function loads font to memory
 *
 * \param filename - Path to font
 * \param fontID - Key of font
 * \param size - Size of font
 * \param flags - Flags of font (for more info go to allegro documentation - al_load_font)
 * \param pFontManager - Ptr on FontManager
 * \return Nothing
 *
 */
void loadFont(const char * filename, const char * fontID, int size, int flags, FontManager * pFontManager);

/** \brief
 *
 * This function frees memory of font
 *
 * \param fontID - Key of font
 * \param pFontManager - Ptr on FontManager
 * \return Nothing
 *
 */
void freeFont(const char * fontID, FontManager * pFontManager);

/** \brief
 *
 * This functions gets a font from given key
 *
 * \param fontID - Key of font
 * \param pFontManager - Ptr on FontManager
 * \return Ptr on ALLEGRO_FONT
 *
 */
ALLEGRO_FONT * getFont(const char * fontID, FontManager * pFontManager);

#endif // FONTMANAGER_H_INCLUDED
