#include "Timer.h"

Timer::Timer()
{
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::Start()
{
    started = true;
    paused = false;

    startTicks = SDL_GetTicks();
}

void Timer::Stop()
{
    started = false;
    paused = false;
}

int Timer::getTicks()
{
    if (started == true)
    {
        if (paused == true)
        {
            return pausedTicks;
        }
        else
        {
            return SDL_GetTicks() - startTicks;
        }
    }

    return 0;
}

void Timer::Pause()
{
    if ( (started == true) && (paused == false) )
    {
        paused = true;

        paused = SDL_GetTicks() - startTicks;
    }
}

void Timer::UnPause()
{
    if (paused == true)
    {
        paused = false;

        startTicks = SDL_GetTicks() - pausedTicks;

        pausedTicks = 0;
    }
}

bool Timer::is_Started()
{
    return started;
}

bool Timer::is_Paused()
{
    return paused;
}
