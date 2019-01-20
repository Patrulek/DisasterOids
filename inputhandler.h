#ifndef INPUTHANDLER_H_INCLUDED
#define INPUTHANDLER_H_INCLUDED

#include <allegro5/allegro5.h>

#include "memdebug.h"


/** \brief
 *
 * Struct which describes input handler
 *
 */
typedef struct InputHandler
{
      ALLEGRO_EVENT_QUEUE * m_pEventQueue;  /**< \brief Allegro event queue (for more info see allegro documentation) */
      ALLEGRO_DISPLAY * m_pDisplay;  /**< \brief Ptr on ALLEGRO_DISPLAY (for more info see allegro documentation) */
      bool m_keyStates[ALLEGRO_KEY_MAX];  /**< \brief Key states */
      bool m_oldKeyStates[ALLEGRO_KEY_MAX]; /**< \brief Key states from last frame */
} InputHandler;


/** \brief
 *
 * This function creates input handler
 *
 * \param pDisplay - Ptr on ALLEGRO_DISPLAY
 * \return - Ptr on InputHandler
 *
 */
InputHandler * createInputHandler(ALLEGRO_DISPLAY * pDisplay);

/** \brief
 *
 * This function destroys input handler
 *
 * \param pInputHandler - Ptr on InputHandler
 * \return Nothing
 *
 */
void destroyInputHandler(InputHandler * pInputHandler);

/** \brief
 *
 * This function creates allegro event queue
 *
 * \return Ptr on ALLEGRO_EVENT_QUEUE
 *
 */
ALLEGRO_EVENT_QUEUE * createEventQueue();

/** \brief
 *
 * This function destroys allegro event queue
 *
 * \param pEventQueue - Ptr on ALLEGRO_EVENT_QUEUE
 * \return Nothing
 *
 */
void destroyEventQueue(ALLEGRO_EVENT_QUEUE * pEventQueue);

/** \brief
 *
 * This function updates key states
 *
 * \param pInputHandler - Ptr on InputHandler
 * \return Nothing
 *
 */
void updateInputHandler(InputHandler * pInputHandler);

/** \brief
 *
 * This function install keyboard (it is needed for receiving events from keyboard)
 *
 */
void installKeyboard();

/** \brief
 *
 * This function register event sources to receiving events from its. This sources are keyboard and window
 *
 * \param pInputHandler - Ptr on InputHandler
 * \return Nothing
 *
 */
void registerEventSources(InputHandler * pInputHandler);

/** \brief
 *
 * This function checks if key is pressed
 *
 * \param pInputHandler - Ptr on InputHandler
 * \param keyCode - Code of key to check
 * \return True if key is down, false otherwise.
 *
 */
bool isKeyDown(InputHandler * pInputHandler, int keyCode);

/** \brief
 *
 * This function checks if key was pressed in last frame
 *
 * \param pInputHandler - Ptr on InputHandler
 * \param keyCode - Code of key to check
 * \return True if key was pressed in last frame, false otherwise.
 *
 */
bool wasKeyPressed(InputHandler * pInputHandler, int keyCode);

/** \brief
 *
 * This function updates key states when any key is pressed
 *
 * \param pInputHandler - Ptr on InputHandler
 * \param keyCode - Code of key to update
 * \return Nothing
 *
 */
void onKeyDown(InputHandler * pInputHandler, int keyCode);

/** \brief
 *
 * This function updates key states when any key is released
 *
 * \param pInputHandler - Ptr on InputHandler
 * \param keyCode - Code of key to update
 * \return Nothing
 *
 */
void onKeyUp(InputHandler * pInputHandler, int keyCode);

#endif // INPUTHANDLER_H_INCLUDED
