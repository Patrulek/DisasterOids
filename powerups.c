#include "powerups.h"


Powerup * createPowerup(int width, int height)
{
      Powerup * pPowerup = ALLOC(Powerup, 1);

      pPowerup->m_textureID = NULL;
      pPowerup->m_position = createPoint(0, 0);
      pPowerup->m_width = width;
      pPowerup->m_height = height;
      pPowerup->m_destroy = false;
      pPowerup->m_type = NO_POWERUP;
      pPowerup->m_needToSpawn = false;
      pPowerup->m_pickedUp = false;
      pPowerup->m_spawnTimer = 0;
      pPowerup->m_spawnCooldown = 0;
      pPowerup->m_collisionCircle = createCircle(pPowerup->m_position, 0);

      return pPowerup;
}

void updatePowerup(POWERUPS type, Powerup * pPowerup)
{
      if(pPowerup->m_pickedUp || al_get_time() - pPowerup->m_spawnTimer >= 5)
      {
            pPowerup->m_collisionCircle->m_position->m_x = -9999;
            pPowerup->m_collisionCircle->m_position->m_y = -9999;
            pPowerup->m_position->m_x = -9999;
            pPowerup->m_position->m_y = -9999;

            if(al_get_time() - pPowerup->m_spawnCooldown >= 5)
                  pPowerup->m_needToSpawn = true;
      }
      else
            pPowerup->m_spawnCooldown = al_get_time();
}


void destroyPowerup(Powerup * pPowerup)
{
      if(!pPowerup)
            return;

      destroyPoint(pPowerup->m_position);
      destroyCircle(pPowerup->m_collisionCircle);

      FREE(pPowerup);
}

void drawPowerup(Powerup * pPowerup, TextureManager * pTextureManager)
{
      al_draw_bitmap(getTexture(pPowerup->m_textureID, pTextureManager), pPowerup->m_position->m_x,
                     pPowerup->m_position->m_y, 0);

}

void randomPowerup(Powerup * pPowerup)
{
      int random = rand() % 100;

      if(random >= 0 && random < 33)
            pPowerup->m_type = BULLET_POWERUP;
      else if(random >= 33 && random < 50)
            pPowerup->m_type = BEAM_POWERUP;
      else if(random >= 50 && random < 65)
            pPowerup->m_type = FREEZE_POWERUP;
      else if(random >= 65 && random < 80)
            pPowerup->m_type = LIFEUP_POWERUP;
      else if(random >= 80 && random < 95)
            pPowerup->m_type = SHIELD_POWERUP;
      else
            pPowerup->m_type = BOMB_POWERUP;
}

void spawnPowerup(Powerup * pPowerup, Point * position)
{
      destroyPoint(pPowerup->m_position);
      destroyCircle(pPowerup->m_collisionCircle);

      randomPowerup(pPowerup);

      switch(pPowerup->m_type)
      {
            case SHIELD_POWERUP:
                  pPowerup->m_textureID = "SHIELD_POWERUP";
                  break;
            case BULLET_POWERUP:
                  pPowerup->m_textureID = "BULLET_POWERUP";
                  break;
            case BEAM_POWERUP:
                  pPowerup->m_textureID = "BEAM_POWERUP";
                  break;
            case BOMB_POWERUP:
                  pPowerup->m_textureID = "BOMB_POWERUP";
                  break;
            case LIFEUP_POWERUP:
                  pPowerup->m_textureID = "SHIP_POWERUP";
                  break;
            case FREEZE_POWERUP:
                  pPowerup->m_textureID = "FREEZE_POWERUP";
                  break;
      }
      pPowerup->m_position = position;
      pPowerup->m_collisionCircle = createCircle(createPoint(position->m_x + pPowerup->m_width / 2,
                                    position->m_y + pPowerup->m_width / 2), pPowerup->m_width / 2);
      pPowerup->m_needToSpawn = false;
      pPowerup->m_pickedUp = false;
      pPowerup->m_spawnTimer = al_get_time();
}
