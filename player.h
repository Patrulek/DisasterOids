#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#define BULLET_COOLDOWN 0.35  /**< \brief How long we need to wait before we can shoot bullet in seconds  */
#define MAX_BULLET_DAMAGE_LEVEL 3  /**< \brief How many upgrades of bullets we can do */
#define MAX_BULLET_COOLDOWN_LEVEL 5  /**< \brief How many upgrades of bullets cooldown we can do  */
#define MAX_BEAM_CHARGING_LEVEL 5  /**< \brief How many upgrades of beam charge we can do */
#define BOMB_COOLDOWN 25  /**< \brief How long we need to wait before we can use another bomb in seconds */
#define BOMB_EFFECT 8.0  /**< \brief How long will be last bomb effect in seconds */
#define DELAY_BOMB_EFFECT 0.8   /**< \brief How long we need to wait for effect after activate bomb */
#define SHIELD_TIME 2.5  /**< \brief How long shield will be last in seconds */
#define INVULNERABILITY_TIME 3 /**< \brief How long we will be immune to destroy after spawned in seconds */
#define MAX_BEAMCHARGE 100  /**< \brief Max capacity of beam */
#define MAX_LIVES 5  /**< \brief Max number of lives */
#define MAX_BOMBS 2  /**< \brief Max number of bombs */
#define MAX_VELOCITY 6.7  /**< \brief Max velocity */

#include <stdbool.h>

#include "collision.h"
#include "inputhandler.h"
#include "image.h"
#include "bullet.h"
#include "beam.h"
#include "memdebug.h"
#include "timer.h"

/** \brief
 *
 * Struct which describes a player
 *
 */
typedef struct Player
{
      char * m_textureID;  /**< \brief Key of texture */
      char * m_bulletTextureID; /**< \brief Key of bullet texture */

      Timer * m_bulletTimer;  /**< \brief Time between bullets */
      Timer * m_bombTimer;  /**< \brief Time between using bombs */
      Timer * m_bombEffectTimer;  /**< \brief Time of bomb effect */
      Timer * m_invulnerabilityTimer;  /**< \brief Time of immune to destroy */
      Timer * m_shieldTimer;  /**< \brief Time of during shield */

      AnimatedImage * m_shield;  /**< \brief Animation of shield */

      AABB m_aabb;  /**< Box bounding ship to check if player is out of screen */
      OBB m_obb;  /**< Oriented bounding box to check collision with objects */

      float m_velX; /**< \brief Velocity on x axis in pixels */
      float m_velY; /**< \brief Velocity on y axis in pixels */
      int m_angle; /**< \brief Angle in degrees */
      int m_width;  /**< \brief Width in pixels */
      int m_height;  /**< \brief Height in pixels */

      Point * m_position;  /**< \brief Position on screen */
      Point * m_leftBeamPos;  /**< \brief Position of left beam on screen */
      Point * m_rightBeamPos;  /**< \brief Postion of right beam on screen */
      Point * m_turretPosition;  /**< \brief Start position of bullets */
      Point * m_turretPosition2; /**< \brief Start position of bullets */
      Point * m_turretPosition3; /**< \brief Start position of bullets */

      DynamicArray * m_bullets;  /**< \brief Dynamic array of bullets stored as pointers on Bullet */

      int m_bulletDamageLevel; /**< \brief How much bullets will be shooted */
      int m_bulletTimerLevel;  /**< \brief How fast bullets will be shooted */

      Beam * m_leftBeam;  /**< \brief Ptr on left beam */
      Beam * m_rightBeam;  /**< \brief Ptr on right beam */

      bool m_activeBeam;  /**< \brief Check if beam is active */
      bool m_needToSpawn;  /**< \brief Check if player has to be spawned */
      float m_beamCharge;  /**< \brief How much laser we have */
      int m_beamChargingLevel;  /**< \brief How fast laser will be charged */
      bool m_beamNeedToCharge;  /**< \brief Check if laser has to be charged to use */

      int m_lives;  /**< \brief Number of lives */
      bool m_invulnerability;  /**< \brief Check if player is invulnerability */

      bool m_shielded;  /**< \brief Check if player is shielded */

      int m_bombs;  /**< \brief Number of bombs */
      bool m_bombActivated;  /**< \brief Check if bomb was activated */
      bool m_bombDelayed;  /**< \brief Check if bomb effect has to be delayed */

      bool m_accelerating;  /**< \brief Check if player accelerate */

      bool m_fireBullets; /**< \brief Check if player shot */

      int m_points;  /**< \brief Number of points */

      bool m_bombEffect;  /**< \brief Check if bomb effect is active */
} Player;

/** \brief
 *
 * This function creates player
 *
 * \param textureID - Key of texture
 * \param bullettextureID - Key of bullet texture
 * \return Ptr on Player
 *
 */
Player * createPlayer(const char * textureID, const char * bullettextureID);

/** \brief
 *
 * This function destroys player
 *
 * \param pPlayer - Ptr on Player
 * \return Nothing
 *
 */
void destroyPlayer(Player * pPlayer);

/** \brief
 *
 * This function moves player
 *
 * \param x - Pixels on x axis to move
 * \param y - Pixels on y axis to move
 * \param pPlayer - Ptr on Player
 * \return Nothing
 *
 */
void movePlayer(float x, float y, Player * pPlayer);

/** \brief
 *
 * This function set players position to given parameters
 *
 * \param x - Position on x axis
 * \param y - Position on y axis
 * \param pPlayer - Ptr on Player
 * \return Nothing
 *
 */
void setPlayerPosition(float x, float y, Player * pPlayer);

/** \brief
 *
 * This function updates state of player
 *
 * \param pPlayer - Ptr on Player
 * \param pInputHandler - Ptr on InputHandler
 * \return Nothing
 *
 */
void updatePlayer(Player * pPlayer, InputHandler * pInputHandler);

/** \brief
 *
 * This function draws player on screen
 *
 * \param pPlayer - Ptr on Player
 * \param pTextureManager - Ptr on TextureManager
 * \return Nothing
 *
 */
void drawPlayer(Player * pPlayer, TextureManager * pTextureManager);

/** \brief
 *
 * This functions spawns player after dead
 *
 * \param pPlayer - Ptr on Player
 * \param pPosition - Position on screen
 * \return Nothing
 *
 */
void spawnPlayer(Player * pPlayer, Point * pPosition);

/** \brief
 *
 * This function fires bullets
 *
 * \param pPlayer - Ptr on Player
 * \return Nothing
 *
 */
void fireBullets(Player * pPlayer);

#endif // PLAYER_H_INCLUDED
