#include "collision.h"

void updateOBB(OBB * pOBB, Point * pPosition, int angle, float xOffset, float yOffset, int width)
{
      pOBB->A.m_x = pPosition->m_x + xOffset * cos(angle * PI/180) - yOffset * sin(angle * PI/180);
      pOBB->A.m_y = pPosition->m_y + yOffset * cos(angle * PI/180) + xOffset * sin(angle * PI/180);

      pOBB->B.m_x = pPosition->m_x + xOffset * cos(angle * PI/180) + yOffset * sin(angle * PI/180);
      pOBB->B.m_y = pPosition->m_y - yOffset * cos(angle * PI/180) + xOffset * sin(angle * PI/180);

      pOBB->C.m_x = pOBB->B.m_x + width * cos(angle * PI/180);
      pOBB->C.m_y = pOBB->B.m_y + width * sin(angle * PI/180);

      pOBB->D.m_x = pOBB->A.m_x + width * cos(angle * PI/180);
      pOBB->D.m_y = pOBB->A.m_y + width * sin(angle * PI/180);
}

void updateAABBWithOBB(AABB * pAABB, OBB * pOBB)
{
      pAABB->x1 = MIN(pOBB->A.m_x, MIN(pOBB->B.m_x, MIN(pOBB->C.m_x, pOBB->D.m_x)));
      pAABB->x2 = MAX(pOBB->A.m_x, MAX(pOBB->B.m_x, MAX(pOBB->C.m_x, pOBB->D.m_x)));
      pAABB->y1 = MIN(pOBB->A.m_y, MIN(pOBB->B.m_y, MIN(pOBB->C.m_y, pOBB->D.m_y)));
      pAABB->y2 = MAX(pOBB->A.m_y, MAX(pOBB->B.m_y, MAX(pOBB->C.m_y, pOBB->D.m_y)));
}

void updateAABB(AABB * pAABB, Point * pPosition, float xOffset, float yOffset, int width, int height)
{
      pAABB->x1 = pPosition->m_x + xOffset;
      pAABB->x2 = pAABB->x1 + width;
      pAABB->y1 = pPosition->m_y + yOffset;
      pAABB->y2 = pAABB->y1 + height;
}

bool checkCircleCircleCollision(Circle * pCircle1, Circle * pCircle2)
{
      if(((pCircle1->m_position->m_x - pCircle2->m_position->m_x) * (pCircle1->m_position->m_x - pCircle2->m_position->m_x)) +
         ((pCircle1->m_position->m_y - pCircle2->m_position->m_y) * (pCircle1->m_position->m_y - pCircle2->m_position->m_y)) >
         ((pCircle1->m_radius + pCircle2->m_radius) * (pCircle1->m_radius + pCircle2->m_radius)))
            return false;

      return true;
}

bool checkCircleOBBCollision(Circle * pCircle, OBB * pOBB)
{
      if(pCircle && pOBB)
      {
            AABB aabb1, aabb2, aabb3, aabb4;

            // closed AB segment with radius offset
            aabb1.x1 = MIN(pOBB->A.m_x, pOBB->B.m_x) - pCircle->m_radius;
            aabb1.y1 = MIN(pOBB->A.m_y, pOBB->B.m_y) - pCircle->m_radius;
            aabb1.x2 = MAX(pOBB->A.m_x, pOBB->B.m_x) + pCircle->m_radius;
            aabb1.y2 = MAX(pOBB->A.m_y, pOBB->B.m_y) + pCircle->m_radius;

            // closed BC segment with radius offset
            aabb2.x1 = MIN(pOBB->C.m_x, pOBB->B.m_x) - pCircle->m_radius;
            aabb2.y1 = MIN(pOBB->C.m_y, pOBB->B.m_y) - pCircle->m_radius;
            aabb2.x2 = MAX(pOBB->C.m_x, pOBB->B.m_x) + pCircle->m_radius;
            aabb2.y2 = MAX(pOBB->C.m_y, pOBB->B.m_y) + pCircle->m_radius;

            // closed CD segment with radius offset
            aabb3.x1 = MIN(pOBB->D.m_x, pOBB->C.m_x) - pCircle->m_radius;
            aabb3.y1 = MIN(pOBB->D.m_y, pOBB->C.m_y) - pCircle->m_radius;
            aabb3.x2 = MAX(pOBB->D.m_x, pOBB->C.m_x) + pCircle->m_radius;
            aabb3.y2 = MAX(pOBB->D.m_y, pOBB->C.m_y) + pCircle->m_radius;

            // closed DA segment with radius offset
            aabb4.x1 = MIN(pOBB->A.m_x, pOBB->D.m_x) - pCircle->m_radius;
            aabb4.y1 = MIN(pOBB->A.m_y, pOBB->D.m_y) - pCircle->m_radius;
            aabb4.x2 = MAX(pOBB->A.m_x, pOBB->D.m_x) + pCircle->m_radius;
            aabb4.y2 = MAX(pOBB->A.m_y, pOBB->D.m_y) + pCircle->m_radius;

            int i;
            float distanceSquared;
            float A, C;

            if((pCircle->m_position->m_x > aabb1.x1 && pCircle->m_position->m_x < aabb1.x2) &&
               (pCircle->m_position->m_y > aabb1.y1 && pCircle->m_position->m_y < aabb1.y2))
            {

                  // B - A

                  A = -(pOBB->B.m_y - pOBB->A.m_y)/(pOBB->B.m_x - pOBB->A.m_x);
                  C = -A * pOBB->B.m_x - pOBB->B.m_y;

                  distanceSquared = (A * pCircle->m_position->m_x + pCircle->m_position->m_y + C) * (A * pCircle->m_position->m_x + pCircle->m_position->m_y + C)
                                    / (A * A + 1);

                  if((pCircle->m_radius * pCircle->m_radius) > distanceSquared)
                        return true;
            }

            if((pCircle->m_position->m_x > aabb2.x1 && pCircle->m_position->m_x < aabb2.x2) &&
               (pCircle->m_position->m_y > aabb2.y1 && pCircle->m_position->m_y < aabb2.y2))
            {

                  // C - B
                  A = -(pOBB->C.m_y - pOBB->B.m_y)/(pOBB->C.m_x - pOBB->B.m_x);
                  C = -A * pOBB->C.m_x - pOBB->C.m_y;

                  distanceSquared = (A * pCircle->m_position->m_x + pCircle->m_position->m_y + C) * (A * pCircle->m_position->m_x + pCircle->m_position->m_y + C)
                                    / (A * A + 1);

                  if((pCircle->m_radius * pCircle->m_radius) > distanceSquared)
                        return true;

            }
            if((pCircle->m_position->m_x > aabb3.x1 && pCircle->m_position->m_x < aabb3.x2) &&
               (pCircle->m_position->m_y > aabb3.y1 && pCircle->m_position->m_y < aabb3.y2))
            {
                  // D - C

                  A = -(pOBB->D.m_y - pOBB->C.m_y)/(pOBB->D.m_x - pOBB->C.m_x);
                  C = -A * pOBB->D.m_x - pOBB->D.m_y;

                  distanceSquared = (A * pCircle->m_position->m_x + pCircle->m_position->m_y + C) * (A * pCircle->m_position->m_x + pCircle->m_position->m_y + C)
                                    / (A * A + 1);

                  if((pCircle->m_radius * pCircle->m_radius) > distanceSquared)
                        return true;
            }
            if((pCircle->m_position->m_x > aabb4.x1 && pCircle->m_position->m_x < aabb4.x2) &&
               (pCircle->m_position->m_y > aabb4.y1 && pCircle->m_position->m_y < aabb4.y2))
            {
                  // A - D
                  A = -(pOBB->A.m_y - pOBB->D.m_y)/(pOBB->A.m_x - pOBB->D.m_x);
                  C = -A * pOBB->A.m_x - pOBB->A.m_y;

                  distanceSquared = (A * pCircle->m_position->m_x + pCircle->m_position->m_y + C) * (A * pCircle->m_position->m_x + pCircle->m_position->m_y + C)
                                    / (A * A + 1);

                  if((pCircle->m_radius * pCircle->m_radius) > distanceSquared)
                        return true;
            }
      }
      return false;
}
