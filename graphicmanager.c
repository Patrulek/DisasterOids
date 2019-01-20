#include "graphicmanager.h"

GraphicManager * createGraphicManager()
{
      GraphicManager * pGraphicManager = ALLOC(GraphicManager, 1);

      if(pGraphicManager)
            pGraphicManager->m_pDisplay = createDisplay("Dis Asteroids", NEW_WINDOW_X, NEW_WINDOW_Y,
                                                        SCREEN_WIDTH, SCREEN_HEIGHT);

      return pGraphicManager;
}

void destroyGraphicManager(GraphicManager* pGraphicManager)
{
      if(!pGraphicManager)
            return;

      destroyDisplay(pGraphicManager->m_pDisplay);
      FREE(pGraphicManager);
}

ALLEGRO_DISPLAY * createDisplay(const char * title, int startX, int startY,
                  int width, int height)
{
      ALLEGRO_DISPLAY * pDisplay = al_create_display(width, height);

      if(pDisplay)
      {
            al_set_window_title(pDisplay, title);
            al_set_window_position(pDisplay, startX, startY);
      }

      return pDisplay;
}

void destroyDisplay(ALLEGRO_DISPLAY * pDisplay)
{
      al_destroy_display(pDisplay);
}

void clearScreen(ALLEGRO_COLOR color)
{
      al_clear_to_color(color);
}

void renderDisplay()
{
      al_flip_display();
}

int getHorResolution()
{
      ALLEGRO_MONITOR_INFO info;
      al_get_monitor_info(0, &info);
      return info.x2 - info.x1;
}

int getVerResolution()
{
      ALLEGRO_MONITOR_INFO info;
      al_get_monitor_info(0, &info);
      return info.y2 - info.y1;
}
