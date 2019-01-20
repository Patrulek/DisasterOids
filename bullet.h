#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include <stdbool.h>

#include "memdebug.h"
#include "geometry.h"
#include "texturemanager.h"

/** \brief
 *
 * Struct which describe player's bullet
 *
 */
typedef struct Bullet
{
      Point * m_position;  /**< \brief Position on a screen */
      int m_angle;  /**< \brief Angle in degrees */

      int m_width;  /**< \brief Width in pixels */
      int m_height;  /**< \brief Height in pixels */

      float m_velX; /**< \brief Velocity in x axis in pixels */
      float m_velY;  /**< \brief Velocity in y axis in pixels */

      char * m_textureID;  /**< \brief Key of texture of bullet */

      bool m_destroy;  /**< \brief Check if bullet has to be deleted */
      float m_damage;  /**< \brief Damage dealt by bullet */

      Circle * m_collisionCircle;  /**< \brief Collision circle of bullet */

} Bullet;

/** \brief
 *
 * This function creates bullet
 *
 * \param textureID - Ptr on cstring
 * \param position - Position of bullet on ship
 * \param angle - Angle in degrees
 * \return Ptr on Bullet
 *
 */
Bullet * createBullet(const char * textureID, Point * position, int angle);

/** \brief
 *
 * This function destroy bullet
 *
 * \param pBullet - Ptr on Bullet
 * \return Nothing
 *
 */
void destroyBullet(Bullet * pBullet);

/** \brief
 *
 * This function update state of bullet
 *
 * \param  pBullet - Ptr on Bullet
 * \return Nothing
 *
 */
void updateBullet(Bullet * pBullet);

/** \brief
 *
 * This function moves bullet on a screen
 *
 * \param x - Pixels in x axis to move
 * \param y - Pixels in y axis to move
 * \param pBullet - Ptr on Bullet
 * \return Nothing
 *
 */
void moveBullet(float x, float y, Bullet * pBullet);

/** \brief
 *
 * This function draws bullet on a screen
 *
 * \param pBullet - Ptr on Bullet
 * \param pTextureManager - Ptr on TextureManager
 * \return Nothing
 *
 */
void drawBullet(Bullet * pBullet, TextureManager * pTextureManager);


#endif // BULLET_H_INCLUDED


