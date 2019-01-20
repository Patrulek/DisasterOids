#include "timer.h"

Timer * createTimer()
{
      Timer * pTimer = ALLOC(Timer, 1);

      pTimer->m_counting = false;
      pTimer->m_startTime = 0.0;
      pTimer->m_endTime = 0.0;

      return pTimer;
}

void startTimer(Timer * timer)
{
      timer->m_counting = true;
      timer->m_startTime = al_get_time();
}

double getTime(Timer * timer)
{
      if(timer->m_counting)
            return al_get_time() - timer->m_startTime;

      return timer->m_endTime - timer->m_startTime;
}

void resetTimer(Timer * timer)
{
      timer->m_startTime = al_get_time();
}

void stopTimer(Timer * timer)
{
      timer->m_counting = false;
      timer->m_endTime = al_get_time();
}
