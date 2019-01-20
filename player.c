#include "player.h"

#include "graphicmanager.h"

#define isPressed(keycode) (isKeyDown(pInputHandler, keycode))

Player * createPlayer(const char * textureID, const char * bullettextureID)
{
      Player * pPlayer = ALLOC(Player, 1);

      pPlayer->m_textureID = textureID;
      pPlayer->m_bulletTextureID = bullettextureID;
      pPlayer->m_angle = 0;
      pPlayer->m_width = 39;
      pPlayer->m_height = 38;
      pPlayer->m_accelerating = false;
      pPlayer->m_bullets = NULL;
      pPlayer->m_bullets = createArray(pPlayer->m_bullets, 10);
      pPlayer->m_leftBeam = createBeam("BEAM", createPoint(0, 0), 0);
      pPlayer->m_rightBeam = createBeam("BEAM", createPoint(0, 0), 0);
      pPlayer->m_activeBeam = false;
      pPlayer->m_bulletTimer = createTimer();
      pPlayer->m_bombTimer = createTimer();
      pPlayer->m_bombEffectTimer = createTimer();
      pPlayer->m_bulletDamageLevel = 0;
      pPlayer->m_bulletTimerLevel = 0;
      pPlayer->m_beamChargingLevel = 0;
      pPlayer->m_beamCharge = 50;
      pPlayer->m_beamNeedToCharge = true;
      pPlayer->m_needToSpawn = true;
      pPlayer->m_lives = 3;
      pPlayer->m_bombs = 0;
      pPlayer->m_bombActivated = false;
      pPlayer->m_invulnerability = false;
      pPlayer->m_invulnerabilityTimer = createTimer();
      pPlayer->m_shielded = false;
      pPlayer->m_shieldTimer = createTimer();
      pPlayer->m_points = 0;
      pPlayer->m_fireBullets = false;
      pPlayer->m_bombEffect = false;
      pPlayer->m_shield = createAnimatedImage("SHIELD", createPoint(0, 0), 75, 75, 20, 0, 3, true);
      pPlayer->m_leftBeamPos = createPoint(0, 0);
      pPlayer->m_rightBeamPos = createPoint(0, 0);
      pPlayer->m_bombDelayed = false;

      startTimer(pPlayer->m_bulletTimer);
      startTimer(pPlayer->m_bombTimer);
      startTimer(pPlayer->m_bombEffectTimer); pPlayer->m_bombEffectTimer->m_startTime = -8.0;
      startTimer(pPlayer->m_invulnerabilityTimer); pPlayer->m_invulnerabilityTimer->m_startTime = -3.5;
      startTimer(pPlayer->m_shieldTimer); pPlayer->m_shieldTimer->m_startTime = -2.5;

      return pPlayer;
}

void destroyPlayer(Player * pPlayer)
{
      if(!pPlayer)
            return;

      destroyBeam(pPlayer->m_leftBeam);
      destroyBeam(pPlayer->m_rightBeam);
      destroyPoint(pPlayer->m_leftBeamPos);
      destroyPoint(pPlayer->m_rightBeamPos);
      destroyPoint(pPlayer->m_position);
      destroyPoint(pPlayer->m_turretPosition);
      destroyPoint(pPlayer->m_turretPosition2);
      destroyPoint(pPlayer->m_turretPosition3);
      destroyAnimatedImage(pPlayer->m_shield);

      int i;
      for(i = 0; i < pPlayer->m_bullets->m_arraySize; i++)
      {
            Bullet * pBullet = getItem(pPlayer->m_bullets, i);
            if(pBullet)
                  destroyBullet(pBullet);
      }
      clearArray(pPlayer->m_bullets, true, NO_ALLEGRO);
      FREE(pPlayer->m_bullets);

      FREE(pPlayer);
}

void movePlayer(float x, float y, Player* player)
{
      player->m_position->m_x += x;
      player->m_position->m_y += y;
}

void setPlayerPosition(float x, float y, Player* player)
{
      player->m_position->m_x = x;
      player->m_position->m_y = y;
}

void updatePlayer(Player * pPlayer, InputHandler * pInputHandler)
{
      if(isPressed(ALLEGRO_KEY_LEFT))
            pPlayer->m_angle -= 4.5;
      else if(isPressed(ALLEGRO_KEY_RIGHT))
            pPlayer->m_angle += 4.5;

      if(pPlayer->m_angle < 0)
            pPlayer->m_angle += 360;
      else if(pPlayer->m_angle > 360)
            pPlayer->m_angle -= 360;

      if(isPressed(ALLEGRO_KEY_UP))
      {
            pPlayer->m_accelerating = true;
            if(pPlayer->m_velX + cos(pPlayer->m_angle * PI/180)/5 > MAX_VELOCITY)
                  pPlayer->m_velX = MAX_VELOCITY;
            else if(pPlayer->m_velX + cos(pPlayer->m_angle * PI/180)/5 < -MAX_VELOCITY)
                  pPlayer->m_velX = -MAX_VELOCITY;
            else
                  pPlayer->m_velX += cos(pPlayer->m_angle * PI/180)/5;

            if(pPlayer->m_velY + sin(pPlayer->m_angle * PI/180)/5 > MAX_VELOCITY)
                  pPlayer->m_velY = MAX_VELOCITY;
            else if(pPlayer->m_velY + sin(pPlayer->m_angle * PI/180)/5 < -MAX_VELOCITY)
                  pPlayer->m_velY = -MAX_VELOCITY;
            else
                  pPlayer->m_velY += sin(pPlayer->m_angle * PI/180)/5;
      }
      else
            pPlayer->m_accelerating = false;

      movePlayer(pPlayer->m_velX, pPlayer->m_velY, pPlayer);
      setAnimatedImagePosition(pPlayer->m_position->m_x - 37, pPlayer->m_position->m_y - 39, pPlayer->m_shield);
      updateAnimatedImage(pPlayer->m_shield);

      pPlayer->m_leftBeamPos->m_x = pPlayer->m_position->m_x + (pPlayer->m_width/2 - 8) * cos(pPlayer->m_angle * PI/180) + pPlayer->m_height/3 * sin(pPlayer->m_angle * PI/180);
      pPlayer->m_leftBeamPos->m_y = pPlayer->m_position->m_y + (pPlayer->m_width/2 - 8) * sin(pPlayer->m_angle * PI/180) - pPlayer->m_height/3 * cos(pPlayer->m_angle * PI/180);

      pPlayer->m_rightBeamPos->m_x = pPlayer->m_position->m_x + (pPlayer->m_width/2 - 8) * cos(pPlayer->m_angle * PI/180) - pPlayer->m_height/3 * sin(pPlayer->m_angle * PI/180);
      pPlayer->m_rightBeamPos->m_y = pPlayer->m_position->m_y + (pPlayer->m_width/2 - 8) * sin(pPlayer->m_angle * PI/180) + pPlayer->m_height/3 * cos(pPlayer->m_angle * PI/180);

      switch(pPlayer->m_bulletDamageLevel)
      {
            case 0:
                  pPlayer->m_turretPosition->m_x = pPlayer->m_position->m_x + pPlayer->m_width/2 * cos(pPlayer->m_angle * PI/180);
                  pPlayer->m_turretPosition->m_y = pPlayer->m_position->m_y + pPlayer->m_width/2 * sin(pPlayer->m_angle * PI/180);
                  break;
            case 1:
                  pPlayer->m_turretPosition->m_x = pPlayer->m_position->m_x + pPlayer->m_width/2 * cos(pPlayer->m_angle * PI/180) + 5 * sin(pPlayer->m_angle * PI/180);
                  pPlayer->m_turretPosition->m_y = pPlayer->m_position->m_y + pPlayer->m_width/2 * sin(pPlayer->m_angle * PI/180) - 5 * cos(pPlayer->m_angle * PI/180);
                  pPlayer->m_turretPosition2->m_x = pPlayer->m_position->m_x + pPlayer->m_width/2 * cos(pPlayer->m_angle * PI/180) - 5 * sin(pPlayer->m_angle * PI/180);
                  pPlayer->m_turretPosition2->m_y = pPlayer->m_position->m_y + pPlayer->m_width/2 * sin(pPlayer->m_angle * PI/180) + 5 * cos(pPlayer->m_angle * PI/180);
                  break;
            case 2:
                  pPlayer->m_turretPosition->m_x = pPlayer->m_position->m_x + pPlayer->m_width/2 * cos(pPlayer->m_angle * PI/180);
                  pPlayer->m_turretPosition->m_y = pPlayer->m_position->m_y + pPlayer->m_width/2 * sin(pPlayer->m_angle * PI/180);
                  break;
            case 3:
                  pPlayer->m_turretPosition->m_x = pPlayer->m_position->m_x + pPlayer->m_width/2 * cos(pPlayer->m_angle * PI/180);
                  pPlayer->m_turretPosition->m_y = pPlayer->m_position->m_y + pPlayer->m_width/2 * sin(pPlayer->m_angle * PI/180);
                  pPlayer->m_turretPosition2->m_x = pPlayer->m_position->m_x + pPlayer->m_width/2 * cos(pPlayer->m_angle * PI/180) + 10 * sin(pPlayer->m_angle * PI/180);
                  pPlayer->m_turretPosition2->m_y = pPlayer->m_position->m_y + pPlayer->m_width/2 * sin(pPlayer->m_angle * PI/180) - 10 * cos(pPlayer->m_angle * PI/180);
                  pPlayer->m_turretPosition3->m_x = pPlayer->m_position->m_x + pPlayer->m_width/2 * cos(pPlayer->m_angle * PI/180) - 10 * sin(pPlayer->m_angle * PI/180);
                  pPlayer->m_turretPosition3->m_y = pPlayer->m_position->m_y + pPlayer->m_width/2 * sin(pPlayer->m_angle * PI/180) + 10 * cos(pPlayer->m_angle * PI/180);
                  break;
      }

      updateOBB(&pPlayer->m_obb, pPlayer->m_position, pPlayer->m_angle, -pPlayer->m_width/2, -pPlayer->m_height/2, pPlayer->m_width);
      updateAABBWithOBB(&pPlayer->m_aabb, &pPlayer->m_obb);

      if(getTime(pPlayer->m_shieldTimer) < SHIELD_TIME)
            pPlayer->m_shielded = true;
      else
            pPlayer->m_shielded = false;

      if(getTime(pPlayer->m_invulnerabilityTimer) < INVULNERABILITY_TIME)
            pPlayer->m_invulnerability = true;
      else
            pPlayer->m_invulnerability = false;

      if(pPlayer->m_aabb.x1 > SCREEN_WIDTH)
            pPlayer->m_position->m_x = -pPlayer->m_width/2;
      else if(pPlayer->m_aabb.x2 < 0)
            pPlayer->m_position->m_x = SCREEN_WIDTH + pPlayer->m_width/2;

      if(pPlayer->m_aabb.y1 > SCREEN_HEIGHT)
            pPlayer->m_position->m_y = -pPlayer->m_height/2;
      else if(pPlayer->m_aabb.y2 < 0)
            pPlayer->m_position->m_y = SCREEN_HEIGHT + pPlayer->m_height/2;

      if(isPressed(ALLEGRO_KEY_LCTRL) && getTime(pPlayer->m_bulletTimer) > BULLET_COOLDOWN - pPlayer->m_bulletTimerLevel * 0.04 && !pPlayer->m_activeBeam)
      {
            pPlayer->m_fireBullets = true;
            resetTimer(pPlayer->m_bulletTimer);
      }
      else if(isPressed(ALLEGRO_KEY_X) && pPlayer->m_beamCharge > 0 && !pPlayer->m_beamNeedToCharge)
      {
            pInputHandler->m_oldKeyStates[ALLEGRO_KEY_X] = true;
            pPlayer->m_beamCharge = pPlayer->m_beamCharge - 1 <= 0 ? 0 : pPlayer->m_beamCharge - 1;
            pPlayer->m_activeBeam = true;
            pPlayer->m_fireBullets = false;
      }
      else
      {
            pPlayer->m_beamCharge = pPlayer->m_beamCharge >= MAX_BEAMCHARGE ? MAX_BEAMCHARGE : pPlayer->m_beamCharge + 0.025 * (pPlayer->m_beamChargingLevel + 1);
            pPlayer->m_activeBeam = false;
            pPlayer->m_fireBullets = false;
      }

      if((pPlayer->m_beamCharge < 30 && !pInputHandler->m_oldKeyStates[ALLEGRO_KEY_X]) || pPlayer->m_beamCharge == 0)
            pPlayer->m_beamNeedToCharge = true;
      else if(pPlayer->m_beamCharge >= 30 && !pInputHandler->m_oldKeyStates[ALLEGRO_KEY_X])
            pPlayer->m_beamNeedToCharge = false;

      if(isPressed(ALLEGRO_KEY_SPACE) && pPlayer->m_bombs > 0 && getTime(pPlayer->m_bombTimer) > BOMB_COOLDOWN)
      {
            pPlayer->m_bombActivated = true;
            resetTimer(pPlayer->m_bombTimer);
            resetTimer(pPlayer->m_bombEffectTimer);
      }
}

void drawPlayer(Player * pPlayer, TextureManager * pTextureManager)
{
      int i;

      if(!pPlayer->m_invulnerability)
      {
            al_draw_tinted_scaled_rotated_bitmap_region(getTexture(pPlayer->m_textureID, pTextureManager), pPlayer->m_width * pPlayer->m_accelerating,
                              0, pPlayer->m_width, pPlayer->m_height, al_map_rgba(255, 255, 255, 255), pPlayer->m_width/2, pPlayer->m_height/2,
                              pPlayer->m_position->m_x, pPlayer->m_position->m_y, 1.0, 1.0, pPlayer->m_angle/(180/PI), 0);
      }
      else
      {
            if((int)(getTime(pPlayer->m_invulnerabilityTimer) * 100) % 60 < 30)
            {
                   al_draw_tinted_scaled_rotated_bitmap_region(getTexture(pPlayer->m_textureID, pTextureManager), pPlayer->m_width * pPlayer->m_accelerating,
                              0, pPlayer->m_width, pPlayer->m_height, al_map_rgba(255, 255, 255, 255), pPlayer->m_width/2, pPlayer->m_height/2,
                              pPlayer->m_position->m_x, pPlayer->m_position->m_y, 1.0, 1.0, pPlayer->m_angle/(180/PI), 0);
            }
      }
      if(pPlayer->m_shielded)
            drawAnimatedImage(pPlayer->m_shield, pTextureManager);
}

void spawnPlayer(Player * pPlayer, Point * position)
{
      FREE(pPlayer->m_position);
      FREE(pPlayer->m_turretPosition);
      FREE(pPlayer->m_turretPosition2);
      FREE(pPlayer->m_turretPosition3);

      pPlayer->m_bulletTimerLevel = pPlayer->m_bulletTimerLevel - 2 > 0 ? pPlayer->m_bulletTimerLevel - 2 : pPlayer->m_bulletTimerLevel >> 1;
      pPlayer->m_bulletDamageLevel = pPlayer->m_bulletDamageLevel - 1 > 0 ? pPlayer->m_bulletDamageLevel - 1 : pPlayer->m_bulletDamageLevel >> 1;
      pPlayer->m_beamChargingLevel = pPlayer->m_beamChargingLevel - 1 > 0 ? pPlayer->m_beamChargingLevel - 1 : pPlayer->m_beamChargingLevel >> 1;
      pPlayer->m_position = position;
      setPlayerPosition(position->m_x, position->m_y, pPlayer);

      pPlayer->m_turretPosition = createPoint(0, 0);
      pPlayer->m_turretPosition2 = createPoint(0, 0);
      pPlayer->m_turretPosition3 = createPoint(0, 0);

      pPlayer->m_velX = pPlayer->m_velY = 0.0;
      pPlayer->m_activeBeam = false;
      pPlayer->m_angle = 0.0;
      pPlayer->m_needToSpawn = false;

      resetTimer(pPlayer->m_invulnerabilityTimer);
}

void fireBullets(Player * pPlayer)
{
      switch(pPlayer->m_bulletDamageLevel)
      {
            case 0:
            {
                  Point * pPoint = createPoint(pPlayer->m_turretPosition->m_x, pPlayer->m_turretPosition->m_y);
                  Bullet * pBullet = createBullet(pPlayer->m_bulletTextureID, pPoint, pPlayer->m_angle);

                  pPlayer->m_bullets = insertObject(pPlayer->m_bullets, pBullet);
                  break;
            }
            case 1:
            {
                  Bullet * pBullet = createBullet(pPlayer->m_bulletTextureID, createPoint(pPlayer->m_turretPosition->m_x,
                        pPlayer->m_turretPosition->m_y), pPlayer->m_angle);

                  pPlayer->m_bullets = insertObject(pPlayer->m_bullets, pBullet);

                  pBullet = createBullet(pPlayer->m_bulletTextureID, createPoint(pPlayer->m_turretPosition2->m_x,
                        pPlayer->m_turretPosition2->m_y), pPlayer->m_angle);

                  pPlayer->m_bullets = insertObject(pPlayer->m_bullets, pBullet);
                  break;
            }
            case 2:
            {
                  Bullet * pBullet = createBullet(pPlayer->m_bulletTextureID, createPoint(pPlayer->m_turretPosition->m_x,
                        pPlayer->m_turretPosition->m_y), pPlayer->m_angle - 5);

                  pPlayer->m_bullets = insertObject(pPlayer->m_bullets, pBullet);

                  pBullet = createBullet(pPlayer->m_bulletTextureID, createPoint(pPlayer->m_turretPosition->m_x,
                        pPlayer->m_turretPosition->m_y), pPlayer->m_angle);

                  pPlayer->m_bullets = insertObject(pPlayer->m_bullets, pBullet);

                  pBullet = createBullet(pPlayer->m_bulletTextureID, createPoint(pPlayer->m_turretPosition->m_x,
                        pPlayer->m_turretPosition->m_y), pPlayer->m_angle + 5);

                  pPlayer->m_bullets = insertObject(pPlayer->m_bullets, pBullet);
                  break;
            }
            case 3:
            {
                  Bullet * pBullet = createBullet(pPlayer->m_bulletTextureID, createPoint(pPlayer->m_turretPosition->m_x,
                        pPlayer->m_turretPosition->m_y), pPlayer->m_angle - 5);

                  pPlayer->m_bullets = insertObject(pPlayer->m_bullets, pBullet);

                  pBullet = createBullet(pPlayer->m_bulletTextureID, createPoint(pPlayer->m_turretPosition->m_x,
                        pPlayer->m_turretPosition->m_y), pPlayer->m_angle);

                  pPlayer->m_bullets = insertObject(pPlayer->m_bullets, pBullet);

                  pBullet = createBullet(pPlayer->m_bulletTextureID, createPoint(pPlayer->m_turretPosition->m_x,
                        pPlayer->m_turretPosition->m_y), pPlayer->m_angle + 5);

                  pPlayer->m_bullets = insertObject(pPlayer->m_bullets, pBullet);

                  pBullet = createBullet(pPlayer->m_bulletTextureID, createPoint(pPlayer->m_turretPosition2->m_x,
                        pPlayer->m_turretPosition2->m_y), pPlayer->m_angle - 10);

                  pPlayer->m_bullets = insertObject(pPlayer->m_bullets, pBullet);

                  pBullet = createBullet(pPlayer->m_bulletTextureID, createPoint(pPlayer->m_turretPosition3->m_x,
                        pPlayer->m_turretPosition3->m_y), pPlayer->m_angle + 10);

                  pPlayer->m_bullets = insertObject(pPlayer->m_bullets, pBullet);
                  break;
            }
      }
}
