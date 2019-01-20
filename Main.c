#define ALLEGRO_STATICLINK

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "gamevariables.h"
#include "game.h"

/** \brief
 * Initialize Allegro components: allegro, image, primitives, fonts, ttf
 */
void initAllegro();

/** \brief
 * Function with main game loop
 */
int main(int argc, char ** argv)
{
      initAllegro();

      Game * pGame = createGame();

      double startTime, timePassed;
      double timeForFrame = 1.0 / MAX_FPS;

      while(isRunning)
      {
            startTime = al_get_time();

            handleInput(pGame->m_pInputHandler);
            doLogic(pGame);
            drawGame(pGame);

            if(pGame->m_changeState)
                  changeState(pGame->m_whatState, pGame);

            timePassed = al_get_time() - startTime;

            if(timeForFrame - timePassed > 0)
                  al_rest(timeForFrame - timePassed);

            //printf("m: %d\tf:%d\n", mallocCounter, freeCounter);
      }

      destroyGame(pGame);
      return 0;
}

void initAllegro()
{
      al_init();
      al_init_image_addon();
      al_init_primitives_addon();
      al_init_font_addon();
      al_init_ttf_addon();
}
