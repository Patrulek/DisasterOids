#include "fontmanager.h"

FontManager * createFontManager()
{
      FontManager * pFontManager = ALLOC(FontManager, 1);

      pFontManager->m_fontKeys = NULL;
      pFontManager->m_fonts = NULL;

      pFontManager->m_fontKeys = createArray(pFontManager->m_fontKeys, 1);
      pFontManager->m_fonts = createArray(pFontManager->m_fonts, 1);

      return pFontManager;
}

void destroyFontManager(FontManager* pFontManager)
{
      clearArray(pFontManager->m_fontKeys, true, NO_ALLEGRO);
      clearArray(pFontManager->m_fonts, true, ALLEGRO5_FONT);

      FREE(pFontManager);
}

void loadFont(const char* filename, const char* fontID, int size, int flags, FontManager* pFontManager)
{
      ALLEGRO_FONT * pFont = al_load_ttf_font(filename, size, flags);

      if(pFont)
      {
            char * pBuffer = ALLOC(char, strlen(fontID) + 1);
            strcpy(pBuffer, fontID);
            pFontManager->m_fontKeys = insertObject(pFontManager->m_fontKeys, pBuffer);
            pFontManager->m_fonts = insertObject(pFontManager->m_fonts, pFont);

            printf("Font - %s - loaded!\n", fontID);
      }
}

void freeFont(const char * fontID, FontManager * pFontManager)
{
      if(pFontManager->m_fontKeys->m_arraySize == 0)
            return;

      int index = -1, i;

      for(i = 0; i < pFontManager->m_fontKeys->m_arraySize; i++)
      {
            char * pBuffer = getItem(pFontManager->m_fontKeys, i);
            if(pBuffer)
                  if(!strcmp(pBuffer, fontID))
                  {
                        index = i;
                        break;
                  }
      }

      if(index == -1)
            return -1;


      printf("Font - %s - deleted!\n", fontID);
      pFontManager->m_fontKeys = removeObject(pFontManager->m_fontKeys, index, true, NO_ALLEGRO);
      pFontManager->m_fonts = removeObject(pFontManager->m_fonts, index, true, ALLEGRO5_FONT);
}

ALLEGRO_FONT * getFont(const char* fontID, FontManager* pFontManager)
{
      if(pFontManager->m_fontKeys->m_arraySize == 0)
            return NULL;

      int i;
      for(i = 0; i < pFontManager->m_fontKeys->m_arraySize; i++)
      {
            char * pBuffer = getItem(pFontManager->m_fontKeys, i);

            if(pBuffer)
                  if(!strcmp(pBuffer, fontID))
                        return getItem(pFontManager->m_fonts, i);

      }
      return NULL;
}
