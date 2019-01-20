#include "displayText.h"

DisplayText * createDisplayText(const char * pBuffer, ALLEGRO_FONT * pFont, Point * pPosition, ALLEGRO_COLOR color, bool active)
{
      DisplayText * pDisplayText = ALLOC(DisplayText, 1);

      char * newBuffer = ALLOC(char, strlen(pBuffer) + 1);
      strcpy(newBuffer, pBuffer);

      pDisplayText->m_buffer = newBuffer;
      pDisplayText->m_font = pFont;
      pDisplayText->m_position = pPosition;
      pDisplayText->m_color = color;
      pDisplayText->m_active = active;

      return pDisplayText;
}

void changeDisplayText(const char * pBuffer, DisplayText * pDisplayText)
{
      if(!pDisplayText)
            return;

      FREE(pDisplayText->m_buffer);

      char * newBuffer = ALLOC(char, strlen(pBuffer) + 1);

      strcpy(newBuffer, pBuffer);
      pDisplayText->m_buffer = newBuffer;
}

void destroyDisplayText(DisplayText * pDisplayText)
{
      if(!pDisplayText)
            return;

      destroyPoint(pDisplayText->m_position);

      FREE(pDisplayText->m_buffer);
      FREE(pDisplayText);
}

void drawDisplayText(DisplayText * pDisplayText)
{
      if(pDisplayText->m_active)
            al_draw_text(pDisplayText->m_font, pDisplayText->m_color, pDisplayText->m_position->m_x,
                        pDisplayText->m_position->m_y, ALLEGRO_ALIGN_CENTRE, pDisplayText->m_buffer);
}
