#include "button.h"

Button * createButton(const char* textureID, Point * position, int width, int height, bool currentState)
{
      Button * pButton = ALLOC(Button, 1);

      pButton->m_textureID = textureID;
      pButton->m_position = position;
      pButton->m_height = height;
      pButton->m_width = width;
      pButton->m_maxFrames = 2;
      pButton->m_active = currentState;

      return pButton;
}

void destroyButton(Button * pButton)
{
      if(!pButton)
            return;

      destroyPoint(pButton->m_position);

      FREE(pButton);
}

void drawButton(Button* pButton, TextureManager* pTextureManager)
{
      al_draw_bitmap_region(getTexture(pButton->m_textureID, pTextureManager),
                            pButton->m_active * pButton->m_width, 0, pButton->m_width, pButton->m_height,
                            pButton->m_position->m_x, pButton->m_position->m_y, 0);
}
