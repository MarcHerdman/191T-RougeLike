#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <iostream>

class Timer
{
    public:
        Timer();
        virtual ~Timer();

        bool IsStarted();
        bool IsStopped();
        bool IsPaused();
        void Pause();
        void Resume();
        void Start();
        void Stop();
        void Reset();
        clock_t GetTicks();

        clock_t startedAt;
        clock_t pausedAt;
        bool started;
        bool paused;

        float FPS;
        clock_t baseTime;

    protected:

    private:
};

#endif // TIMER_H
