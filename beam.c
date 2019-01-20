#include "beam.h"

Beam * createBeam(const char * textureID, Point * position, int angle)
{
      Beam * pBeam = ALLOC(Beam, 1);

      pBeam->m_textureID = textureID;
      pBeam->m_position = position;
      pBeam->m_angle = angle;
      pBeam->m_width = 1000;
      pBeam->m_height = 12;
      pBeam->m_damage = 35;

      return pBeam;
}

void updateBeam(int angle, Point turretPosition, Beam* pBeam)
{
      pBeam->m_angle = angle;
      pBeam->m_position->m_x = turretPosition.m_x;
      pBeam->m_position->m_y = turretPosition.m_y;
      updateOBB(&pBeam->m_obb, pBeam->m_position, pBeam->m_angle, 0, -6, pBeam->m_width);
}


void destroyBeam(Beam * pBeam)
{
      if(!pBeam)
            return;

      destroyPoint(pBeam->m_position);

      FREE(pBeam);
}

void drawBeam(Beam * pBeam, TextureManager * pTextureManager)
{
      al_draw_rotated_bitmap(getTexture(pBeam->m_textureID, pTextureManager), 0, pBeam->m_height/2,
                             pBeam->m_position->m_x, pBeam->m_position->m_y, pBeam->m_angle/(180/PI), 0);
}

