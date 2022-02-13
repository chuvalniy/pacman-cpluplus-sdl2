#ifndef TIMER_H
#define TIMER_H
#include <SDL.h>

class Timer
{
private:
    int startTicks;
    int pausedTicks;

    bool paused;
    bool started;


public:
    Timer();

    void Start();
    void Stop();
    void Pause();
    void UnPause();

    int getTicks();

    bool is_Started();
    bool is_Paused();
};


#endif
