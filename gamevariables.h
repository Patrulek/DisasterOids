#ifndef GAMEVARIABLES_H_INCLUDED
#define GAMEVARIABLES_H_INCLUDED

/** \file
 *
 * This file is included only by Main.c
 *
 */


const int MAX_FPS = 60; /**< \brief Limit frames per second */
bool isRunning = true; /**< \brief Check if game is still processing */
int mallocCounter = 0; /**< \brief Needed if MEM_DEBUG for memdebug.h is defined */
int freeCounter = 0; /**< \brief Needed if MEM_DEBUG for memdebug.h is defined */


#endif // GAMECVARIABLES_H_INCLUDED
