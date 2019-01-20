#include "geometry.h"


// point

Point * createPoint(float x, float y)
{
      Point * pPoint = ALLOC(Point, 1);

      setPointPosition(x, y, pPoint);

      return pPoint;
}

void destroyPoint(Point * pPoint)
{
      if(!pPoint)
            return;

      FREE(pPoint);
}

void setPointPosition(float x, float y, Point* pPoint)
{
      pPoint->m_x = x;
      pPoint->m_y = y;
}

// Circle

Circle * createCircle(Point * position, float radius)
{
      Circle * pCircle = ALLOC(Circle, 1);

      pCircle->m_position = position;
      pCircle->m_radius = radius;

      return pCircle;
}

void moveCircle(float x, float y, Circle * pCircle)
{
      pCircle->m_position->m_x += x;
      pCircle->m_position->m_y += y;
}


void destroyCircle(Circle* pCircle)
{
      if(!pCircle)
            return;

      destroyPoint(pCircle->m_position);

      FREE(pCircle);
}

void setCirclePosition(float x, float y, Circle * pCircle)
{
      if(pCircle)
      {
            pCircle->m_position->m_x = x;
            pCircle->m_position->m_y = y;
      }
}
