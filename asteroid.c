#include "asteroid.h"

#include "graphicmanager.h"

Asteroid * createAsteroid(ASTEROID_SIZE size, ASTEROID_TYPE type,
                          Point * position, int angle, float velX, float velY)
{
      Asteroid * pAsteroid = ALLOC(Asteroid, 1);

      pAsteroid->m_position = position;
      pAsteroid->m_angle = angle;
      pAsteroid->m_velX = velX;
      pAsteroid->m_velY = velY;
      pAsteroid->m_destroy = false;
      pAsteroid->m_freezed = false;
      pAsteroid->m_bombed = false;
      pAsteroid->m_freezeTimer = -3;
      pAsteroid->m_size = size;
      pAsteroid->m_type = type;

      switch(pAsteroid->m_size)
      {
            case VERYBIG:
                  switch(pAsteroid->m_type)
                  {
                        case TYPE1:
                              pAsteroid->m_width = 108;
                              pAsteroid->m_height = 108;
                              pAsteroid->m_textureID = "ASTEROID_VERYBIG";
                              pAsteroid->m_freezeTextureID = "BLOCKOFICE1_VERYBIG";
                              break;
                        case TYPE2:
                              pAsteroid->m_width = 90;
                              pAsteroid->m_height = 90;
                              pAsteroid->m_textureID = "ASTEROID2_VERYBIG";
                              pAsteroid->m_freezeTextureID = "BLOCKOFICE2_VERYBIG";
                              break;
                        case TYPE3:
                              pAsteroid->m_width = 135;
                              pAsteroid->m_height = 135;
                              pAsteroid->m_textureID = "ASTEROID3_VERYBIG";
                              pAsteroid->m_freezeTextureID = "BLOCKOFICE3_VERYBIG";
                              break;
                  }
                  pAsteroid->m_healthPoints = 400;
                  pAsteroid->m_points = 1000;
                  break;
            case BIG:
                  switch(pAsteroid->m_type)
                  {
                        case TYPE1:
                              pAsteroid->m_width = 72;
                              pAsteroid->m_height = 72;
                              pAsteroid->m_textureID = "ASTEROID_BIG";
                              pAsteroid->m_freezeTextureID = "BLOCKOFICE1_BIG";
                              break;
                        case TYPE2:
                              pAsteroid->m_width = 60;
                              pAsteroid->m_height = 60;
                              pAsteroid->m_textureID = "ASTEROID2_BIG";
                              pAsteroid->m_freezeTextureID = "BLOCKOFICE2_BIG";
                              break;
                        case TYPE3:
                              pAsteroid->m_width = 90;
                              pAsteroid->m_height = 90;
                              pAsteroid->m_textureID = "ASTEROID3_BIG";
                              pAsteroid->m_freezeTextureID = "BLOCKOFICE3_BIG";
                              break;
                  }
                  pAsteroid->m_healthPoints = 200;
                  pAsteroid->m_points = 400;
                  break;
            case NORMAL:
                  switch(pAsteroid->m_type)
                  {
                        case TYPE1:
                              pAsteroid->m_width = 48;
                              pAsteroid->m_height = 48;
                              pAsteroid->m_textureID = "ASTEROID_NORMAL";
                              pAsteroid->m_freezeTextureID = "BLOCKOFICE1_NORMAL";
                              break;
                        case TYPE2:
                              pAsteroid->m_width = 40;
                              pAsteroid->m_height = 40;
                              pAsteroid->m_textureID = "ASTEROID2_NORMAL";
                              pAsteroid->m_freezeTextureID = "BLOCKOFICE2_NORMAL";
                              break;
                        case TYPE3:
                              pAsteroid->m_width = 60;
                              pAsteroid->m_height = 60;
                              pAsteroid->m_textureID = "ASTEROID3_NORMAL";
                              pAsteroid->m_freezeTextureID = "BLOCKOFICE3_NORMAL";
                              break;
                  }
                  pAsteroid->m_healthPoints = 100;
                  pAsteroid->m_points = 160;
                  break;
      }
      switch(pAsteroid->m_type)
      {
            case TYPE1:
                  pAsteroid->m_collisionCircle = createCircle(createPoint(pAsteroid->m_position->m_x,
                                                pAsteroid->m_position->m_y), pAsteroid->m_width/2);
                  pAsteroid->m_collisionCircle2 = NULL;
                  break;
            case TYPE2:
                  pAsteroid->m_collisionCircle = createCircle(createPoint(pAsteroid->m_position->m_x - 0.2 * pAsteroid->m_width,
                                                pAsteroid->m_position->m_y + 0.2 * pAsteroid->m_height), 0.3 * pAsteroid->m_width);
                  pAsteroid->m_collisionCircle2 = createCircle(createPoint(pAsteroid->m_position->m_x + 0.1 * pAsteroid->m_width,
                                                pAsteroid->m_position->m_y - 0.1 * pAsteroid->m_height), 0.4 * pAsteroid->m_width);
                  break;
            case TYPE3:
                  pAsteroid->m_collisionCircle = createCircle(createPoint(pAsteroid->m_position->m_x,
                                                pAsteroid->m_position->m_y), pAsteroid->m_width/2);
                  pAsteroid->m_collisionCircle2 = NULL;
                  break;
      }

      return pAsteroid;
}

void moveAsteroid(float x, float y, Asteroid * pAsteroid)
{
      pAsteroid->m_position->m_x += x;
      pAsteroid->m_position->m_y += y;
}

void updateAsteroidCollisionCircles(Asteroid * pAsteroid)
{
      switch(pAsteroid->m_type)
      {
            case TYPE1:
                  setCirclePosition(pAsteroid->m_position->m_x , pAsteroid->m_position->m_y, pAsteroid->m_collisionCircle);
                  break;
            case TYPE2:
                  setCirclePosition(pAsteroid->m_position->m_x - 0.2 * pAsteroid->m_width * cos(pAsteroid->m_angle * PI/180) - 0.2 * pAsteroid->m_height * sin(pAsteroid->m_angle * PI/180),
                                    pAsteroid->m_position->m_y + 0.2 * pAsteroid->m_height * cos(pAsteroid->m_angle * PI/180) - 0.2 * pAsteroid->m_width * sin(pAsteroid->m_angle * PI/180), pAsteroid->m_collisionCircle);

                  setCirclePosition(pAsteroid->m_position->m_x + 0.1 * pAsteroid->m_width * cos(pAsteroid->m_angle * PI/180) + 0.1 * pAsteroid->m_height * sin(pAsteroid->m_angle * PI/180),
                                    pAsteroid->m_position->m_y - 0.1 * pAsteroid->m_height * cos(pAsteroid->m_angle * PI/180) + 0.1 * pAsteroid->m_width * sin(pAsteroid->m_angle * PI/180), pAsteroid->m_collisionCircle2);
                  break;
            case TYPE3:
                  setCirclePosition(pAsteroid->m_position->m_x , pAsteroid->m_position->m_y, pAsteroid->m_collisionCircle);
                  break;
      }
}

void updateAsteroid(Asteroid * pAsteroid)
{
      if(al_get_time() - pAsteroid->m_freezeTimer > FREEZE_TIME)
            pAsteroid->m_freezed = false;
      else
            pAsteroid->m_freezed = true;

      if(!pAsteroid->m_freezed)
      {
            pAsteroid->m_angle += 1;
            moveAsteroid(pAsteroid->m_velX, pAsteroid->m_velY, pAsteroid);
            updateAsteroidCollisionCircles(pAsteroid);
      }

      if(pAsteroid->m_healthPoints <= 0)
            pAsteroid->m_destroy = true;

      if(pAsteroid->m_position->m_x > SCREEN_WIDTH + pAsteroid->m_width/2)
            pAsteroid->m_position->m_x = -pAsteroid->m_width/2;
      else if(pAsteroid->m_position->m_x < -pAsteroid->m_width/2)
            pAsteroid->m_position->m_x = SCREEN_WIDTH + pAsteroid->m_width/2;

      if(pAsteroid->m_position->m_y > SCREEN_HEIGHT + pAsteroid->m_height/2)
            pAsteroid->m_position->m_y = -pAsteroid->m_height/2;
      else if(pAsteroid->m_position->m_y < -pAsteroid->m_height/2)
            pAsteroid->m_position->m_y = SCREEN_HEIGHT + pAsteroid->m_height/2;
}

void destroyAsteroid(Asteroid* pAsteroid)
{
      if(!pAsteroid)
            return;

      destroyPoint(pAsteroid->m_position);
      destroyCircle(pAsteroid->m_collisionCircle);
      destroyCircle(pAsteroid->m_collisionCircle2);

      FREE(pAsteroid);
}

void drawAsteroid(Asteroid * pAsteroid, TextureManager * pTextureManager)
{
      al_draw_rotated_bitmap(getTexture(pAsteroid->m_textureID, pTextureManager), pAsteroid->m_width/2, pAsteroid->m_height/2,
                        pAsteroid->m_position->m_x, pAsteroid->m_position->m_y, pAsteroid->m_angle/(180/PI), 0);

      if(pAsteroid->m_freezed)
      {
            int t = 200 - (al_get_time() - pAsteroid->m_freezeTimer) * 100;
            al_draw_tinted_rotated_bitmap(getTexture(pAsteroid->m_freezeTextureID, pTextureManager), al_map_rgba(t, t, t, t),
                              pAsteroid->m_width/2, pAsteroid->m_height/2, pAsteroid->m_position->m_x,
                              pAsteroid->m_position->m_y, pAsteroid->m_angle/(180/PI), 0);
      }
}


void freezeAsteroid(Asteroid * pAsteroid)
{
      pAsteroid->m_freezeTimer = al_get_time();
}
