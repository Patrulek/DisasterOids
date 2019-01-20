#include "bullet.h"

#include "graphicmanager.h"

Bullet * createBullet(const char* textureID, Point * position, int angle)
{
      Bullet * pBullet = ALLOC(Bullet, 1);

      pBullet->m_textureID = textureID;
      pBullet->m_position = position;
      pBullet->m_angle = angle;
      pBullet->m_velX = 15 * cos(angle * PI/180);
      pBullet->m_velY = 15 * sin(angle * PI/180);
      pBullet->m_destroy = false;
      pBullet->m_width = 11;
      pBullet->m_height = 7;
      pBullet->m_damage = 25;
      pBullet->m_collisionCircle = createCircle(createPoint(pBullet->m_position->m_x + 4 ,
                                                pBullet->m_position->m_y + 1), pBullet->m_height/2);

      return pBullet;
}

void updateBullet(Bullet* pBullet)
{
      moveBullet(pBullet->m_velX, pBullet->m_velY, pBullet);

      setCirclePosition(pBullet->m_position->m_x + 4 * cos(pBullet->m_angle * PI/180),
                        pBullet->m_position->m_y + 4 * sin(pBullet->m_angle * PI/180), pBullet->m_collisionCircle);

      if(pBullet->m_position->m_x < -pBullet->m_width/2 || pBullet->m_position->m_x > SCREEN_WIDTH + pBullet->m_width/2 ||
         pBullet->m_position->m_y < -pBullet->m_height/2 || pBullet->m_position->m_y > SCREEN_HEIGHT + pBullet->m_height/2)
            pBullet->m_destroy = true;
}


void destroyBullet(Bullet * pBullet)
{
      if(!pBullet)
            return;

      destroyPoint(pBullet->m_position);
      destroyCircle(pBullet->m_collisionCircle);

      FREE(pBullet);
}

void drawBullet(Bullet * pBullet, TextureManager * pTextureManager)
{
      al_draw_rotated_bitmap(getTexture(pBullet->m_textureID, pTextureManager), pBullet->m_width/2, pBullet->m_height/2,
                             pBullet->m_position->m_x, pBullet->m_position->m_y, pBullet->m_angle/(180/PI), 0);
}

void moveBullet(float x, float y, Bullet * pBullet)
{
      pBullet->m_position->m_x += x;
      pBullet->m_position->m_y += y;
}
