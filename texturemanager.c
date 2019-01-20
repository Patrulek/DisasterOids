#include "texturemanager.h"


TextureManager * createTextureManager()
{
      TextureManager * pTextureManager = ALLOC(TextureManager, 1);
      pTextureManager->m_keys = NULL;
      pTextureManager->m_textures = NULL;

      pTextureManager->m_keys = createArray(pTextureManager->m_keys, 10);
      pTextureManager->m_textures = createArray(pTextureManager->m_textures, 10);

      return pTextureManager;
}

void destroyTextureManager(TextureManager* pTextureManager)
{
      if(!pTextureManager)
            return;

      clearArray(pTextureManager->m_keys, true, NO_ALLEGRO);
      clearArray(pTextureManager->m_textures, true, ALLEGRO5_BITMAP);
      FREE(pTextureManager);
}

ALLEGRO_BITMAP * getTexture(const char * textureID, TextureManager * pTextureManager)
{
      if(pTextureManager->m_textures->m_arraySize == 0)
            return NULL;

      int i;
      for(i = 0; i < pTextureManager->m_keys->m_arraySize; i++)
      {
            char * pBuffer = getItem(pTextureManager->m_keys, i);

            if(pBuffer)
                  if(!strcmp(pBuffer, textureID))
                        return getItem(pTextureManager->m_textures, i);
      }

      return NULL;
}


void loadTexture(const char * filename, const char * textureID, TextureManager * pTextureManager)
{
      int i;
      for(i = 0; i < pTextureManager->m_keys->m_arraySize; i++)
      {
            char * tempStr = (char *)getItem(pTextureManager->m_keys, i);

            if(tempStr)
                  if(!strcmp(textureID, tempStr))
                  {
                        printf("Texture already exists!\n");
                        return;
                  }
      }

      ALLEGRO_BITMAP * pBitmap = NULL;

      pBitmap = al_load_bitmap(filename);

      if(pBitmap)
      {
            printf("Texture - %s - loaded!\n", textureID);
            char * pBuffer = ALLOC(char, strlen(textureID) + 1);
            strcpy(pBuffer, textureID);
            pTextureManager->m_keys = insertObject(pTextureManager->m_keys, pBuffer);
            pTextureManager->m_textures = insertObject(pTextureManager->m_textures, pBitmap);
      }
}

void freeTexture(const char * textureID, TextureManager * pTextureManager)
{
      if(pTextureManager->m_keys->m_arraySize == 0)
            return;

      int index = -1, i;
      for(i = 0; i < pTextureManager->m_keys->m_arraySize; i++)
      {
            char * pBuffer = getItem(pTextureManager->m_keys, i);
            if(pBuffer)
                  if(!strcmp(textureID, pBuffer))
                  {
                        index = i;
                        break;
                  }
      }

      if(index == -1)
            return;


      printf("Texture - %s - deleted!\n", textureID);
      pTextureManager->m_keys = removeObject(pTextureManager->m_keys, index, true, NO_ALLEGRO);
      pTextureManager->m_textures = removeObject(pTextureManager->m_textures, index, true, ALLEGRO5_BITMAP);
}
