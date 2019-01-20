#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <allegro5/allegro5.h>

#include "memdebug.h"


/** \brief
 *
 * Struct which describes timer
 *
 */
typedef struct Timer
{
      double m_startTime;  /**< \brief Starting time */
      bool m_counting;  /**< \brief Check if timer is active */
      double m_endTime;  /**< \brief Ending time */

} Timer;

/** \brief
 *
 * This function creates timer
 *
 * \return Ptr on Timer
 *
 */
Timer * createTimer();

/** \brief
 *
 * This function starts counting
 *
 * \param timer - Ptr on Timer
 * \return Nothing
 *
 */
void startTimer(Timer * timer);

/** \brief
 *
 * This function resets starting time
 *
 * \param timer - Ptr on Timer
 * \return Nothing
 *
 */
void resetTimer(Timer * timer);

/** \brief
 *
 * This function gets actual time passed
 *
 * \param timer - Ptr on Timer
 * \return Time passed in seconds
 *
 */
double getTime(Timer * timer);

/** \brief
 *
 * This function stops timer
 *
 * \param timer - Ptr on Timer
 * \return Nothing
 *
 */
void stopTimer(Timer * timer);

#endif // TIMER_H_INCLUDED
