#ifndef SOUNDMANAGER_H_INCLUDED
#define SOUNDMANAGER_H_INCLUDED

#define MAX_VOLUME 2.0  /**< \brief Max value of volume */
#define MIN_VOLUME 0.0  /**< \brief Min value of volume */

#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

#include "dynamicarray.h"
#include "memdebug.h"

/** \brief
 *
 * Enum for types of sound
 *
 */
typedef enum SOUND_TYPE
{
      SFX,
      MUSIC
} SOUND_TYPE;


/** \brief
 *
 * Struct which describe sound manager
 *
 */
typedef struct SoundManager
{
      float m_musicVolume;  /**< \brief Value of music volume */
      float m_soundVolume;  /**< \brief Value of sound volume */

      DynamicArray * m_samples;  /**< \brief Sounds stored as pointers on ALLEGRO_SAMPLE */
      DynamicArray * m_sampleKeys;  /**< \brief Sample keys stored as cstrings */
      DynamicArray * m_music;  /**< \brief Music stored as pointers on ALLEGRO_SAMPLE  */
      DynamicArray * m_musicKeys;  /**< \brief Music keys stored as cstrings */
      DynamicArray * m_sampleInstances;  /**< \brief Sound instances stored as pointers on ALLEGRO_SAMPLE_INSTANCE */
      DynamicArray * m_musicInstances;  /**< \brief Music instances stored as pointers on ALLEGRO_SAMPLE_INSTANCE */
} SoundManager;

/** \brief
 *
 * This function creates sound manager
 *
 * \return Ptr on SoundManager
 *
 */
SoundManager * createSoundManager();

/** \brief
 *
 * This function destroys sound manager
 *
 * \param pSoundManager - Ptr on SoundManager
 * \return Nothing
 *
 */
void destroySoundManager(SoundManager * pSoundManager);

/** \brief
 *
 * This function load sound or music to memory
 *
 * \param fileName - Path to file
 * \param soundID - Key of sound
 * \param soundType - Music or Sfx
 * \param pSoundManager - Ptr on SoundManager
 * \return Nothing
 *
 */
void loadSound(const char * filename, const char * soundID, SOUND_TYPE soundType, SoundManager * pSoundManager);

/** \brief
 *
 * This function frees memory of sound
 *
 * \param soundID - Key of sound
 * \param soundType - Music or Sfx
 * \param pSoundManager - Ptr on SoundManager
 * \return Nothing
 *
 */
void freeSound(const char * soundID, SOUND_TYPE soundType, SoundManager * pSoundManager);

/** \brief
 *
 * This function get loaded sound
 *
 * \param soundID - Key of sound
 * \param soundType - Music or Sfx
 * \param pSoundManager - Ptr on SoundManager
 * \return Ptr on ALLEGRO_SAMPLE
 *
 */
ALLEGRO_SAMPLE * getSound(const char * soundID, SOUND_TYPE soundType, SoundManager * pSoundManager);

/** \brief
 *
 * This function plays a sound
 *
 * \param soundID - Key of sound
 * \param soundType - Music or Sfx
 * \param loop - Check if sound has to be looped or not
 * \param pSoundManager - Ptr on SoundManager
 * \return Nothing
 *
 */
void playSound(const char * soundID, SOUND_TYPE soundType, bool loop, SoundManager * pSoundManager);

/** \brief
 *
 * This function gets sample instance
 *
 * \param soundID - Key of sound
 * \param soundType - Music or Sfx
 * \param pSoundManager - Ptr on SoundManager
 * \return Ptr on ALLEGRO_SAMPLE_INSTANCE
 *
 */
ALLEGRO_SAMPLE_INSTANCE * getSampleInstance(const char * soundID, SOUND_TYPE soundType, SoundManager * pSoundManager);

#endif // SOUNDMANAGER_H_INCLUDED
