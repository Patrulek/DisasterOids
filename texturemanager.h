#ifndef StringUREMANAGER_H_INCLUDED
#define StringUREMANAGER_H_INCLUDED

#include <allegro5/allegro.h>

#include "memdebug.h"
#include "dynamicarray.h"
#include "string.h"


/** \brief
 *
 * Struct which describe texture manager
 *
 */
typedef struct TextureManager
{
      DynamicArray * m_keys;  /**< \brief Keys of textures stored as cstrings */
      DynamicArray * m_textures;  /**< \brief Textures stored as pointers on ALLEGRO_BITMAP  */

} TextureManager;

/** \brief
 *
 * This function creates texture manager
 *
 * \return Ptr on TextureManager
 *
 */
TextureManager * createTextureManager();

/** \brief
 *
 * This function destroys texture manager
 *
 * \param pTextureManager - Ptr on TextureManager
 * \return Nothing
 *
 */
void destroyTextureManager(TextureManager * pTextureManager);

/** \brief
 *
 * This function get loaded texture
 *
 * \param textureID - Key of texture
 * \param pTextureManager - Ptr on TextureManager
 * \return Ptr on ALLEGRO_BITMAP
 *
 */
ALLEGRO_BITMAP * getTexture(const char * textureID, TextureManager * pTextureManager);

/** \brief
 *
 * This function load texture from file
 *
 * \param fileName - Path to file
 * \param textureID - Key of texture
 * \param pTextureManager - Ptr on TextureManager
 * \return Nothing
 *
 */
void loadTexture(const char * filename, const char * textureID, TextureManager * pTextureManager);

/** \brief
 *
 * This function frees memory of texture
 *
 * \param textureID - Key of texture
 * \param pTextureManager - Ptr on TextureManager
 * \return Nothing
 *
 */
void freeTexture(const char * textureID, TextureManager * pTextureManager);


#endif // StringUREMANAGER_H_INCLUDED
