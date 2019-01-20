#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED

#include "texturemanager.h"
#include "geometry.h"
#include "memdebug.h"

#define FREEZE_TIME 2 /**< Define how long asteroid will be freezed in seconds */

/** \brief
 *
 * Enum which define asteroid size (width and height)
 *
 */
typedef enum ASTEROID_SIZE
{
      NORMAL,
      BIG,
      VERYBIG

} ASTEROID_SIZE;

/** \brief
 *
 * Enum which define asteroid type (textures and collision circles)
 *
 */
typedef enum ASTEROID_TYPE
{
      TYPE1,
      TYPE2,
      TYPE3
} ASTEROID_TYPE;

/** \brief
 *
 * Struct which describe asteroid
 *
 */
typedef struct Asteroid
{
      Point * m_position; /**< \brief Position on a screen */
      int m_angle; /**< \brief Angle in degrees */

      float m_velX; /**< \brief Velocity in x axis in pixels */
      float m_velY; /**< \brief Velocity in y axis in pixels */

      int m_width;  /**< \brief Width in pixels */
      int m_height;  /**< \brief Height in pixels */

      char * m_textureID; /**< \brief Key of texture of asteroid */
      char * m_freezeTextureID; /**< \brief Key of texture of frozen asteroid */

      bool m_destroy; /**< \brief Check if asteroid has to be deleted */

      int m_healthPoints; /**< \brief HP of asteroid */

      bool m_freezed;   /**< \brief Check if asteroid is freezed */
      bool m_bombed;   /**< \brief Check if asteroid was destroyed by bomb */
      double m_freezeTimer; /**< \brief Time in moment when asteroid is being freeze */

      Circle * m_collisionCircle; /**< \brief First collision circle of asteroid (in all asteroid types) */
      Circle * m_collisionCircle2;  /**< \brief Second collision circle of asteroid (only in TYPE2) */

      ASTEROID_SIZE m_size;  /**< \brief Size of asteroid */
      ASTEROID_TYPE m_type; /**< \brief Type of asteroid */

      int m_points;  /**< \brief Points, which player get after destroying asteroid */
} Asteroid;

/** \brief
 *
 * This function create asteroid from parameters given below:
 *
 * \param size - Size defined by enum ASTEROID_SIZE
 * \param type - Type defined by enum ASTEROID_TYPE
 * \param position - Center of asteroid
 * \param angle - Angle in degrees
 * \param velX - Velocity in x axis
 * \param velY - Velocity in y axis
 *
 * \return Ptr on asteroid
 */
Asteroid * createAsteroid(ASTEROID_SIZE size, ASTEROID_TYPE type,
                          Point * position, int angle, float velX, float velY);

/** \brief
 *
 * This function destroy asteroid
 *
 * \param pAsteroid - Ptr on Asteroid
 * \return Nothing
 *
 */

void destroyAsteroid(Asteroid * pAsteroid);

/** \brief
 *
 * This function update state of a given asteroid
 *
 * \param pAsteroid - Ptr on Asteroid
 * \return Nothing
 *
 */
void updateAsteroid(Asteroid * pAsteroid);

/** \brief
 *
 * This function update collision circles after moving asteroid
 *
 * \param pAsteroid - Ptr on Asteroid
 * \return Nothing
 */
void updateAsteroidCollisionCircles(Asteroid * pAsteroid);

/** \brief
 *
 * This function moves asteroid by given parameters
 *
 * \param x - pixels to move in x axis
 * \param y - pixels to move in y axis
 * \param pAsteroid - Ptr on Asteroid
 * \return Nothing
 *
 */
void moveAsteroid(float x, float y, Asteroid * pAsteroid);

/** \brief
 *
 * This function draw a given asteroid on a screen
 *
 * \param pAsteroid - Ptr on Asteroid
 * \param pTextureManager - Ptr on TextureManager
 * \return Nothing
 *
 */
void drawAsteroid(Asteroid * pAsteroid, TextureManager * pTextureManager);

/** \brief
 *
 * This function freeze a given asteroid causing that it stops moving and rotating
 *
 * \param pAsteroid - Ptr on Asteroid
 * \return Nothing
 */
void freezeAsteroid(Asteroid * pAsteroid);

#endif // ASTEROID_H_INCLUDED
