#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include "memdebug.h"
#include <stdbool.h>

#define PI 3.14159

// point

/** \brief
 *
 * Struct which describe a point
 *
 */
typedef struct Point
{
      float m_x; /**< \brief Position on x axis */
      float m_y;  /**< \brief Position on y axis */

} Point;

/** \brief
 *
 * This function creates point
 *
 * \param x - Position on x axis
 * \param y - Position on y axis
 * \return Ptr on Point
 *
 */
Point * createPoint(float x, float y);

/** \brief
 *
 * This function destroys point
 *
 * \param pPoint - Ptr on Point
 * \return Nothing
 *
 */
void destroyPoint(Point * pPoint);

/** \brief
 *
 * This function set points coordinate from given as parameters
 *
 * \param x - Position on x axis
 * \param y - Position on y axis
 * \param pPoint - Ptr on Point
 * \return Nothing
 *
 */
void setPointPosition(float x, float y, Point * pPoint);

// circle

/** \brief
 *
 * Struct which describe a circle
 *
 */
typedef struct Circle
{
      Point * m_position; /**< \brief Position of center of circle */
      float m_radius; /**< \brief Radius in pixels */

} Circle;

/** \brief
 *
 * This function creates circle
 *
 * \param pPosition - Position on screen
 * \param radius - Radius in pixels
 * \return Ptr on Circle
 *
 */
Circle * createCircle(Point * pPosition, float radius);

/** \brief
 *
 * This function destroys circle
 *
 * \param pCircle - Ptr on Circle
 * \return Nothing
 *
 */
void destroyCircle(Circle * pCircle);

/** \brief
 *
 * This function moves circle from given parameters
 *
 * \param x - Pixels to move on x axis
 * \param y - Pixels to move on y axis
 * \param pCircle - Ptr on Circle
 * \return Nothing
 *
 */
void moveCircle(float x, float y, Circle * pCircle);

/** \brief
 *
 * This function set circle position to given parameters
 *
 * \param x - Position on x axis
 * \param y - Position on y axis
 * \param pCircle - Ptr on Circle
 * \return Nothing
 *
 */
void setCirclePosition(float x, float y, Circle * pCircle);

// bounding boxes

/** \brief
 *
 * Struct which describe Axis-Aligned Bounding Box
 *
 */
typedef struct AABB
{
      float x1; /**< \brief Left of AABB */
      float x2; /**< \brief Right of AABB */
      float y1; /**< \brief Top of AABB */
      float y2; /**< \brief Bottom of AABB */

} AABB;

/** \brief
 *
 * Struct which describe Oriented Bounding Box
 *
 *          A ----------- D\n|..................|\n|..................|\n|..................|\n B ----------- C
 *
 */

typedef struct OBB
{
      Point A; /**< \brief Point of OBB */
      Point B; /**< \brief Point of OBB */
      Point C; /**< \brief Point of OBB */
      Point D; /**< \brief Point of OBB */

} OBB;


#endif // GEOMETRY_H_INCLUDED
