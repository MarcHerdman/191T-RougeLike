//The title screen
#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <Scene.h>
#include <MenuScreen.h>
#include <Buttons.h>

class TitleScreen : public Scene
{
    public:
        TitleScreen(std::stack<Scene*>*);
        virtual ~TitleScreen();

        void Init(int, int);                //Initialize this screen
        void Draw();                        //Draw this screen
        void Action(std::string);           //Process any actions
        void ScreenResized(int,int);

        Texture* background;                //The background of this screen
        Buttons* btns;                      //The buttons on this screen

    protected:

    private:
};

#endif // TITLESCREEN_H
