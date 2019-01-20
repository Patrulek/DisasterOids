#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include "geometry.h"

/** \file
 *
 * Functions which calculate collisions and updates bounding boxes
 *
 */


#define MAX(x, y) (((x) > (y)) ? (x) : (y)) /**< \brief Returns greater value */
#define MIN(x, y) (((x) < (y)) ? (x) : (y)) /**< \brief Return lower value */

/** \brief
 *
 * This function updates values of AABB with given OBB
 *
 * \param pAABB - Ptr on AABB
 * \param pOBB - Ptr on OBB
 * \return Nothing
 *
 */
void updateAABBWithOBB(AABB * pAABB, OBB * pOBB);

/** \brief
 *
 * This functions updates AABB of object
 *
 * \param pAABB - Ptr on AABB
 * \param pPosition - Position of object
 * \param xOffset - How much we need to go left from object position to its left bound
 * \param yOffset - How much we need to go up from object position to its top bound
 * \param width - Width of object in pixels
 * \param height - Height of object in pixels
 * \return Nothing
 *
 */
void updateAABB(AABB * pAABB, Point * pPosition, float xOffset, float yOffset, int width, int height);

/** \brief
 *
 * This function updates OBB of object
 *
 * \param pOBB - Ptr on OBB
 * \param pPosition - Position of object
 * \param angle - Angle of object in degrees
 * \param xOffset - How much we need to go left from object position to its left bound
 * \param yOffset - How much we need to go up from object position to its top bound
 * \param width - Width of object in pixels
 * \return Nothing
 *
 */
void updateOBB(OBB * pOBB, Point * pPosition, int angle, float xOffset, float yOffset, int width);

/** \brief
 *
 * This function checks collision between two circles
 *
 * \param pCircle1 - Ptr on Circle
 * \param pCircle1 - Ptr on Circle
 * \return True if circles intersect, false otherwise
 *
 */
bool checkCircleCircleCollision(Circle * pCircle1, Circle * pCircle2);

/** \brief
 *
 * This function checks collision between circle and obb
 *
 * \param pCircle - Ptr on Circle
 * \param pObb - Ptr on OBB
 * \return True if figures intersect, false otherwise
 *
 */
bool checkCircleOBBCollision(Circle * pCircle, OBB * pOBB);


#endif // COLLISION_H_INCLUDED
