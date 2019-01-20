#ifndef BEAM_H_INCLUDED
#define BEAM_H_INCLUDED

#include <stdbool.h>

#include "texturemanager.h"
#include "collision.h"
#include "geometry.h"
#include "memdebug.h"

/** \brief
 *
 * Struct which describe laser beam in ship
 *
 */
typedef struct Beam
{
      Point * m_position; /**< \brief Position on a screen */
      int m_angle; /**< \brief Angle in degrees */

      OBB m_obb; /**< \brief OBB closing beam for checking collision with asteroids */

      int m_width; /**< \brief Width in pixels */
      int m_height; /**< \brief Height in pixels */

      char * m_textureID; /**< \brief Key of texture of beam */

      float m_damage; /**< \brief Damage dealt by beam */
} Beam;

/** \brief
 *
 * This function create a beam from given parameters
 *
 * \param textureID - Texture of a beam
 * \param position - Position of beam on a ship
 * \param angle - Angle in degrees
 * \return Ptr on Beam
 */
Beam * createBeam(const char * textureID, Point * position, int angle);

/** \brief
 *
 * This function destroy a beam
 *
 * \param pBeam - Ptr on Beam
 * \return Nothing
 *
 */
void destroyBeam(Beam * pBeam);

/** \brief
 *
 * This function update state of a beam
 *
 * \param angle - Angle in degrees
 * \param turretPosition - Position of beam on ship
 * \param pBeam - Ptr on Beam
 * \return Nothing
 *
 */
void updateBeam(int angle, Point turretPosition, Beam * pBeam);

/** \brief
 *
 * This function draws beam on a screen
 *
 * \param pBeam - Ptr on Beam
 * \param pTextureManager - Ptr on TextureManager
 * \return Nothing
 *
 */
void drawBeam(Beam * pBeam, TextureManager * pTextureManager);


#endif // BEAM_H_INCLUDED
