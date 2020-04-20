#include "Sound.h"

Sound::Sound()
{
    //ctor
}

Sound::~Sound()
{
    engine->drop();
}
void Sound::playMusic(char* File)
{
    engine->play2D(File,true);

}

void Sound::playSound(char* File)
{
        if(!engine->isCurrentlyPlaying(File))
    engine->play2D(File,false,false);
}

void Sound::pauseSound(char* File)
{
        engine->play2D(File,true,false);

}

int Sound::initSounds()
{
     if(!engine){cout<< "The Sound Engine did not startup\n";
       return 0;
    }
    return 1;
}
