#include "soundmanager.h"


SoundManager * createSoundManager()
{
      SoundManager * pSoundManager = ALLOC(SoundManager, 1);

      pSoundManager->m_sampleKeys = pSoundManager->m_musicKeys = pSoundManager->m_samples = pSoundManager->m_music =  pSoundManager->m_sampleInstances = pSoundManager->m_musicInstances = NULL;
      pSoundManager->m_music = createArray(pSoundManager->m_music, 0);
      pSoundManager->m_samples = createArray(pSoundManager->m_samples, 0);
      pSoundManager->m_musicKeys = createArray(pSoundManager->m_musicKeys, 0);
      pSoundManager->m_sampleKeys = createArray(pSoundManager->m_sampleKeys, 0);
      pSoundManager->m_sampleInstances = createArray(pSoundManager->m_sampleInstances, 0);
      pSoundManager->m_musicInstances = createArray(pSoundManager->m_musicInstances, 0);

      pSoundManager->m_musicVolume = pSoundManager->m_soundVolume = 1.0;

      al_install_audio();
      al_init_acodec_addon();
      al_reserve_samples(25);

      return pSoundManager;
}

void destroySoundManager(SoundManager* pSoundManager)
{
      if(!pSoundManager)
            return;

      clearArray(pSoundManager->m_musicKeys, true, NO_ALLEGRO);
      clearArray(pSoundManager->m_sampleKeys, true, NO_ALLEGRO);
      clearArray(pSoundManager->m_music, true, ALLEGRO5_SAMPLE);
      clearArray(pSoundManager->m_samples, true, ALLEGRO5_SAMPLE);
      clearArray(pSoundManager->m_musicInstances, true, ALLEGRO5_SAMPLE_INSTANCE);
      clearArray(pSoundManager->m_sampleInstances, true, ALLEGRO5_SAMPLE_INSTANCE);
      FREE(pSoundManager);
}

void loadSound(const char * filename, const char * soundID, SOUND_TYPE soundType, SoundManager * pSoundManager)
{
      ALLEGRO_SAMPLE_INSTANCE * pSampleInstance = NULL;
      ALLEGRO_SAMPLE * pSample = NULL;

      switch(soundType)
      {
            case SFX:
            {
                  int i;
                  for(i = 0; i < pSoundManager->m_sampleKeys->m_arraySize; i++)
                  {
                        char * tempStr = (char *)getItem(pSoundManager->m_sampleKeys, i);

                        if(tempStr)
                              if(!strcmp(soundID, tempStr))
                              {
                                    printf("Sample already exists!\n");
                                    return;
                              }
                  }
                  pSample = al_load_sample(filename);

                  if(pSample)
                  {
                        printf("Sample - %s - loaded!\n", soundID);
                        char * pBuffer = ALLOC(char, strlen(soundID) + 1);
                        strcpy(pBuffer, soundID);
                        pSoundManager->m_sampleKeys = insertObject(pSoundManager->m_sampleKeys, pBuffer);
                        pSoundManager->m_samples = insertObject(pSoundManager->m_samples, pSample);
                        pSampleInstance = al_create_sample_instance(pSample);
                        pSoundManager->m_sampleInstances = insertObject(pSoundManager->m_sampleInstances, pSampleInstance);
                        al_attach_sample_instance_to_mixer(pSampleInstance, al_get_default_mixer());
                  }
                  break;
            }
            case MUSIC:
            {
                  int i;
                  for(i = 0; i < pSoundManager->m_musicKeys->m_arraySize; i++)
                  {
                        char * tempStr = (char *)getItem(pSoundManager->m_musicKeys, i);

                        if(tempStr)
                              if(!strcmp(soundID, tempStr))
                              {
                                    printf("Music already exists!\n");
                                    return;
                              }
                  }
                  pSample = al_load_sample(filename);
                  if(pSample)
                  {
                        printf("Music - %s - loaded!\n", soundID);
                        char * pBuffer = ALLOC(char, strlen(soundID) + 1);
                        strcpy(pBuffer, soundID);
                        pSoundManager->m_musicKeys = insertObject(pSoundManager->m_musicKeys, pBuffer);
                        pSoundManager->m_music = insertObject(pSoundManager->m_music, pSample);
                        pSampleInstance = al_create_sample_instance(pSample);
                        pSoundManager->m_musicInstances = insertObject(pSoundManager->m_musicInstances, pSampleInstance);
                        al_attach_sample_instance_to_mixer(pSampleInstance, al_get_default_mixer());
                  }
                  break;
            }
      }
}

ALLEGRO_SAMPLE * getSound(const char* soundID, SOUND_TYPE soundType, SoundManager* pSoundManager)
{
      switch(soundType)
      {
            int i;
            case SFX:
                  if(pSoundManager->m_samples->m_arraySize == 0)
                        return NULL;

                  for(i = 0; i < pSoundManager->m_sampleKeys->m_arraySize; i++)
                  {
                        char * tempStr = getItem(pSoundManager->m_sampleKeys, i);
                        if(!strcmp(tempStr, soundID))
                              return getItem(pSoundManager->m_samples, i);
                  }
                  break;
            case MUSIC:
                  if(pSoundManager->m_music->m_arraySize == 0)
                        return NULL;

                  for(i = 0; i < pSoundManager->m_musicKeys->m_arraySize; i++)
                  {
                        char * tempStr = getItem(pSoundManager->m_musicKeys, i);
                        if(!strcmp(tempStr, soundID))
                              return getItem(pSoundManager->m_music, i);
                  }
                  break;
      }
      return NULL;
}

void freeSound(const char * soundID, SOUND_TYPE soundType, SoundManager* pSoundManager)
{
      switch(soundType)
      {
            int index = -1, i;
            case SFX:
            {
                  if(pSoundManager->m_sampleKeys->m_arraySize == 0)
                        return;

                  for(i = 0; i < pSoundManager->m_sampleKeys->m_arraySize; i++)
                  {
                        char * pBuffer = getItem(pSoundManager->m_sampleKeys, i);
                        if(pBuffer)
                              if(!strcmp(soundID, pBuffer))
                              {
                                    index = i;
                                    break;
                              }
                  }

                  if(index == -1)
                        return;

                  ALLEGRO_SAMPLE_INSTANCE * pSampleInstance = getItem(pSoundManager->m_sampleInstances, i);
                  if(al_get_sample_instance_playing(pSampleInstance))
                        al_stop_sample_instance(pSampleInstance);

                  printf("Sample - %s - deleted!\n", soundID);
                  pSoundManager->m_sampleInstances = removeObject(pSoundManager->m_sampleInstances, index, true, ALLEGRO5_SAMPLE_INSTANCE);
                  pSoundManager->m_sampleKeys = removeObject(pSoundManager->m_sampleKeys, index, true, NO_ALLEGRO);
                  pSoundManager->m_samples = removeObject(pSoundManager->m_samples, index, true, ALLEGRO5_SAMPLE);
                  break;
            }
            case MUSIC:
            {
                  if(pSoundManager->m_musicKeys->m_arraySize == 0)
                        return;

                  for(i = 0; i < pSoundManager->m_musicKeys->m_arraySize; i++)
                  {
                        char * pBuffer = getItem(pSoundManager->m_musicKeys, i);
                        if(pBuffer)
                              if(!strcmp(soundID, pBuffer))
                              {
                                    index = i;
                                    break;
                              }
                  }

                  if(index == -1)
                        return;

                  ALLEGRO_SAMPLE_INSTANCE * pSampleInstance = getItem(pSoundManager->m_musicInstances, i);
                  if(al_get_sample_instance_playing(pSampleInstance))
                        al_stop_sample_instance(pSampleInstance);

                  printf("Music - %s - deleted!\n", soundID);
                  pSoundManager->m_musicInstances = removeObject(pSoundManager->m_musicInstances, index, true, ALLEGRO5_SAMPLE_INSTANCE);
                  pSoundManager->m_musicKeys = removeObject(pSoundManager->m_musicKeys, index, true, NO_ALLEGRO);
                  pSoundManager->m_music = removeObject(pSoundManager->m_music, index, true, ALLEGRO5_SAMPLE);
                  break;
            }
      }
}

void playSound(const char * soundID, SOUND_TYPE soundType, bool loop, SoundManager * pSoundManager)
{
      ALLEGRO_SAMPLE_INSTANCE * pSampleInstance = NULL;

      pSampleInstance = getSampleInstance(soundID, soundType, pSoundManager);

      if(pSampleInstance)
      {
            if(!al_get_sample_instance_playing(pSampleInstance))
            {
                  if(loop)
                        al_set_sample_instance_playmode(pSampleInstance, ALLEGRO_PLAYMODE_LOOP);
                  else
                        al_set_sample_instance_playmode(pSampleInstance, ALLEGRO_PLAYMODE_ONCE);

                  if(soundType == SFX)
                        al_set_sample_instance_gain(pSampleInstance, pSoundManager->m_soundVolume);
                  else
                        al_set_sample_instance_gain(pSampleInstance, pSoundManager->m_musicVolume);

                  al_play_sample_instance(pSampleInstance);
            }
      }
}

ALLEGRO_SAMPLE_INSTANCE * getSampleInstance(const char * soundID, SOUND_TYPE soundType, SoundManager * pSoundManager)
{
      int i;

      switch(soundType)
      {
            case SFX:
                  if(pSoundManager->m_sampleInstances->m_arraySize == 0)
                        return NULL;

                  for(i = 0; i < pSoundManager->m_sampleKeys->m_arraySize; i++)
                  {
                        char * pBuffer = getItem(pSoundManager->m_sampleKeys, i);
                        if(!strcmp(pBuffer, soundID))
                              return getItem(pSoundManager->m_sampleInstances, i);
                  }
                  break;
            case MUSIC:
                  if(pSoundManager->m_musicInstances->m_arraySize == 0)
                        return NULL;

                  for(i = 0; i < pSoundManager->m_musicKeys->m_arraySize; i++)
                  {
                        char * pBuffer = getItem(pSoundManager->m_musicKeys, i);
                        if(!strcmp(pBuffer, soundID))
                              return getItem(pSoundManager->m_musicInstances, i);
                  }
                  break;
      }
      return NULL;
}
