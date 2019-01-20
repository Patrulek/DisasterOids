#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include "geometry.h"
#include "texturemanager.h"
#include "memdebug.h"

/** \brief
 *
 * Struct which describes image
 *
 */
typedef struct Image
{
      char * m_textureID;  /**< \brief Key of texture of image */
      Point * m_position; /**< \brief Position on screen */

} Image;

/** \brief
 *
 * Struct which describes animated image (animation)
 *
 */
typedef struct AnimatedImage
{
      char * m_textureID; /**< \brief Key of textures of image */
      Point * m_position; /**< \brief Position on screen */
      int m_width;  /**< \brief Width in pixels */
      int m_height;  /**< \brief Height in pixels */
      int m_maxFrames;  /**< \brief Max number frames of animation */
      int m_currentFrame; /**< \brief Actual frame of animation */
      int m_animationSpeed; /**< \brief Animation speed in game frames per animation frame */
      int m_currentTime;  /**< \brief Actual game frame of animation frame */
      bool m_repeatable;  /**< \brief Check if animation is repeatable */
      bool m_endAnim;  /**< \brief Check if animation is ending */
} AnimatedImage;

/** \brief
 *
 * This function creates image
 *
 * \param textureID - Key texture of image
 * \param pPosition - Position on screen
 * \return Ptr on Image
 */
Image * createImage(const char * textureID, Point * pPosition);

/** \brief
 *
 * This function creates animated image
 *
 * \param textureID - Key texture of animation
 * \param pPosition - Position on screen
 * \param width - Width of image in pixels
 * \param height - Height of image in pixels
 * \param maxFrames - Max number frames of animation
 * \param currentFrame - Current frame of animation
 * \param animSpeed - Animation speed
 * \param repeatable - Animation is repeatable or not
 * \return Ptr on AnimatedImage
 *
 */
AnimatedImage * createAnimatedImage(const char * textureID, Point * pPosition, int width, int height, int maxFrames, int currentFrame, int animSpeed, bool repeatable);

/** \brief
 *
 * This function destroys image
 *
 * \param pImage - Ptr on Image
 * \return Nothing
 *
 */
void destroyImage(Image * pImage);

/** \brief
 *
 * This function destroys animated image
 *
 * \param pImage - Ptr on AnimatedImage
 * \return Nothing
 *
 */
void destroyAnimatedImage(AnimatedImage * pImage);

/** \brief
 *
 * This function set position of animated image on screen
 *
 * \param x - Position on x axis
 * \param y - Position on y axis
 * \param pImage - Ptr on AnimatedImage
 * \return Nothing
 *
 */
void setAnimatedImagePosition(float x, float y, AnimatedImage * pImage);

/** \brief
 *
 * This function update state of animation
 *
 * \param pImage - Ptr on AnimatedImage
 * \return Nothing
 *
 */
void updateAnimatedImage(AnimatedImage * pImage);

/** \brief
 *
 * This function draws image on screen
 *
 * \param pImage - Ptr on Image
 * \param pTextureManager - Ptr on TextureManager
 * \return Nothing
 *
 */
void drawImage(Image * pImage, TextureManager * pTextureManager);

/** \brief
 *
 * This function draws animation on screen
 *
 * \param pImage - Ptr on AnimatedImage
 * \param pTextureManager - Ptr on TextureManager
 * \return Nothing
 *
 */
void drawAnimatedImage(AnimatedImage * pImage, TextureManager * pTextureManager);

#endif // IMAGE_H_INCLUDED
