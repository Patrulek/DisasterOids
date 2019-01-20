#ifndef SHIELD_H_INCLUDED
#define SHIELD_H_INCLUDED

#include "texturemanager.h"
#include "geometry.h"
#include "memdebug.h"

/** \brief
 *
 * Enum for types of powerup
 *
 */
typedef enum POWERUPS
{
      NO_POWERUP,
      SHIELD_POWERUP,
      BULLET_POWERUP,
      BEAM_POWERUP,
      BOMB_POWERUP,
      LIFEUP_POWERUP,
      FREEZE_POWERUP
} POWERUPS;

/** \brief
 *
 * Struct which describes powerup
 *
 */
typedef struct Powerup
{
      char * m_textureID;  /**< \brief Key texture of powerup */

      Point * m_position;  /**< \brief Position on screen */
      Circle * m_collisionCircle;  /**< \brief Collision circle of powerup */

      bool m_destroy;  /**< \brief Check if powerup has to be destroyed */

      int m_width;  /**< \brief Width in pixels */
      int m_height;  /**< \brief Height in pixels */

      POWERUPS m_type;  /**< \brief Type of powerup */

      bool m_needToSpawn;  /**< \brief Check if powerup has to be spawned */
      bool m_pickedUp;  /**< \brief Check if powerup was picked up */

      double m_spawnTimer;  /**< \brief How long powerup will be on screen */
      double m_spawnCooldown;  /**< \brief How long we need to wait to spawn powerup */
} Powerup;

/** \brief
 *
 * This function creates powerup
 *
 * \param width - Width in pixels
 * \param height - Height in pixels
 * \return Ptr on Powerup
 *
 */
Powerup * createPowerup(int width, int height);

/** \brief
 *
 * This function destroys powerup
 *
 * \param pPowerup - Ptr on Powerup
 * \return Nothing
 *
 */
void destroyPowerup(Powerup * pPowerup);

/** \brief
 *
 * This function updates state of powerup
 *
 * \param type - Type of Powerup
 * \param pPowerup - Ptr on Powerup
 * \return Nothing
 *
 */
void updatePowerup(POWERUPS type, Powerup * pPowerup);

/** \brief
 *
 * This function draws powerup on screen
 *
 * \param pPowerup - Ptr on Powerup
 * \param pTextureManager - Ptr on TextureManager
 * \return Nothing
 *
 */
void drawPowerup(Powerup * pPowerup, TextureManager * pTextureManager);

/** \brief
 *
 * This function spawns powerup
 *
 * \param pPowerup - Ptr on Powerup
 * \param position - Position on screen
 *
 */
void spawnPowerup(Powerup * pPowerup, Point * position);

/** \brief
 *
 * This function random type of powerup
 *
 * \param pPowerup - Ptr on Powerup
 * \return Nothing
 *
 */
void randomPowerup(Powerup * pPowerup);

#endif // SHIELD_H_INCLUDED
