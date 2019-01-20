#include "image.h"

Image * createImage(const char * textureID, Point * position)
{
      Image * pImage = ALLOC(Image, 1);

      pImage->m_textureID = textureID;
      pImage->m_position = position;

      return pImage;
}

AnimatedImage * createAnimatedImage(const char * textureID, Point * position, int width, int height, int maxFrames, int currentFrame, int animSpeed, bool repeatable)
{
      AnimatedImage * pImage = ALLOC(AnimatedImage, 1);

      pImage->m_textureID = textureID;
      pImage->m_position = position;
      pImage->m_maxFrames = maxFrames;
      pImage->m_currentFrame = currentFrame;
      pImage->m_width = width;
      pImage->m_height = height;
      pImage->m_animationSpeed = animSpeed;
      pImage->m_currentTime = 0;
      pImage->m_repeatable = repeatable;
      pImage->m_endAnim = false;

      return pImage;
}

void destroyImage(Image * pImage)
{
      if(!pImage)
            return;

      destroyPoint(pImage->m_position);

      FREE(pImage);
}

void destroyAnimatedImage(AnimatedImage * pImage)
{
      if(!pImage)
            return;

      destroyPoint(pImage->m_position);

      FREE(pImage);
}

void drawImage(Image * pImage, TextureManager * pTextureManager)
{
      ALLEGRO_BITMAP * pBitmap = getTexture(pImage->m_textureID, pTextureManager);

      if(pBitmap)
            al_draw_bitmap(pBitmap, pImage->m_position->m_x,
                        pImage->m_position->m_y, 0);
}

void updateAnimatedImage(AnimatedImage * pImage)
{
      if(pImage->m_currentTime < pImage->m_animationSpeed)
            pImage->m_currentTime++;
      else
            pImage->m_currentTime = 0;

      if(pImage->m_currentTime == 0)
            pImage->m_currentFrame++ ;

      if(pImage->m_currentFrame >= pImage->m_maxFrames)
      {
            if(pImage->m_repeatable)
                  pImage->m_currentFrame = 0;
      }
}

void drawAnimatedImage(AnimatedImage * pImage, TextureManager * pTextureManager)
{
      al_draw_bitmap_region(getTexture(pImage->m_textureID, pTextureManager), pImage->m_currentFrame * pImage->m_width,
                            0, pImage->m_width, pImage->m_height, pImage->m_position->m_x, pImage->m_position->m_y, 0);
}

void setAnimatedImagePosition(float x, float y, AnimatedImage * pImage)
{
      pImage->m_position->m_x = x;
      pImage->m_position->m_y = y;
}
