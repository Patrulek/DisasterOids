#include "inputhandler.h"

extern isRunning;

InputHandler * createInputHandler(ALLEGRO_DISPLAY * pDisplay)
{
      InputHandler * pInputHandler = ALLOC(InputHandler, 1);

      if(pInputHandler)
      {
            pInputHandler->m_pEventQueue = createEventQueue();
            pInputHandler->m_pDisplay = pDisplay;

            int i;
            for(i = 0; i < ALLEGRO_KEY_MAX; i++)
                  pInputHandler->m_keyStates[i] = pInputHandler->m_oldKeyStates[i] = false;
      }

      installKeyboard();
      registerEventSources(pInputHandler);

      return pInputHandler;
}

void destroyInputHandler(InputHandler* pInputHandler)
{
      if(!pInputHandler)
            return;

      destroyEventQueue(pInputHandler->m_pEventQueue);
      FREE(pInputHandler);
}


ALLEGRO_EVENT_QUEUE * createEventQueue()
{
      ALLEGRO_EVENT_QUEUE * pEventQueue = al_create_event_queue();
      return pEventQueue;
}

void destroyEventQueue(ALLEGRO_EVENT_QUEUE* pEventQueue)
{
      al_destroy_event_queue(pEventQueue);
}

void updateInputHandler(InputHandler * pInputHandler)
{
      ALLEGRO_EVENT event;

      while(al_get_next_event(pInputHandler->m_pEventQueue, &event))
      {
            switch(event.type)
            {
                  case ALLEGRO_EVENT_DISPLAY_CLOSE:
                        isRunning = false;
                        break;

                  case ALLEGRO_EVENT_KEY_DOWN:
                        onKeyDown(pInputHandler, event.keyboard.keycode);
                        break;

                  case ALLEGRO_EVENT_KEY_UP:
                        onKeyUp(pInputHandler, event.keyboard.keycode);
                        break;
            }
      }
}

void installKeyboard()
{
      al_install_keyboard();
}

void registerEventSources(InputHandler * pInputHandler)
{
      al_register_event_source(pInputHandler->m_pEventQueue, al_get_keyboard_event_source());

      al_register_event_source(pInputHandler->m_pEventQueue, al_get_display_event_source(pInputHandler->m_pDisplay));
}


bool isKeyDown(InputHandler * pInputHandler, int keyCode)
{
      return pInputHandler->m_keyStates[keyCode];
}

bool wasKeyPressed(InputHandler * pInputHandler, int keyCode)
{
      return pInputHandler->m_oldKeyStates[keyCode];
}

void onKeyDown(InputHandler * pInputHandler, int keyCode)
{
      pInputHandler->m_keyStates[keyCode] = true;
}

void onKeyUp(InputHandler * pInputHandler, int keyCode)
{
      pInputHandler->m_oldKeyStates[keyCode] = pInputHandler->m_keyStates[keyCode] = false;
}
