#ifndef SOUND_H
#define SOUND_H

#include<stdlib.h>
#include<SNDS/irrKlang.h>

#include<iostream>
#include<Timer.h>

using namespace std;
using namespace irrklang;

class Sound
{
    public:
        Sound();
        virtual ~Sound();
        Timer *tmr = new Timer();
        ISoundEngine *engine = createIrrKlangDevice();

        void playMusic(char *);
        void playSound(char *);
        void pauseSound(char *);
        int initSounds();
    protected:

    private:
};

#endif // SOUND_H
