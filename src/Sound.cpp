#include "Sound.h"

Sound::Sound()
{
    currentSound = 0;
    volume = 50;
    position = 0;

    engine->setSoundVolume(0.5);

}

Sound::~Sound()
{
    engine->drop();
}
void Sound::playMusic(char* File)
{
    currentSound = engine->play2D(File,true);
    file = File;
    //position = currentSound->getPlayPosition();


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
void Sound::pauseMusic() {
    //position = currentSound->getPlayPosition();
    engine->setAllSoundsPaused();

}
void Sound::resumeMusic()
{
        engine->setAllSoundsPaused(false);
    //currentSound = engine->play2D(file,true);
    //if(position != -1) {
    //    currentSound -> setPlayPosition(position);
    //}
}

int Sound::initSounds()
{
    if(!engine)
    {
        cout<< "The Sound Engine did not startup\n";
        return 0;
    }
    return 1;
}
