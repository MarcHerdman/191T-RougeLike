//A scene to provide information about playing the game to the player
#ifndef HELPSCREEN_H
#define HELPSCREEN_H

#include <Scene.h>
#include <Buttons.h>

class HelpScreen : public Scene
{
    public:
        HelpScreen(std::stack<Scene*>*);    //All scenes must have access to the scene stack
        virtual ~HelpScreen();

        void Init(int, int);                //Initialize this screen
        void Draw();                        //Draw this screen
        void Action(std::string);           //Process any actions
        void ScreenResized(int,int);        //Recalculate the borders of the buttons

        Texture* background;                //The background of this screen
        Buttons* btns;                      //The buttons on this screen

    protected:

    private:
};

#endif // HELPSCREEN_H
