//The main menu scene
#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <Scene.h>
#include <Level.h>
#include <HelpScreen.h>
#include <Buttons.h>

class MenuScreen : public Scene
{
    public:
        MenuScreen(std::stack<Scene*>*);    //All scenes must have access to the scene stack
        virtual ~MenuScreen();

        void Init(int, int);                //Initialize this screen
        void Draw();                        //Draw this screen
        void Action(std::string);           //Process any actions
        void ScreenResized(int,int);        //Recalculate the borders of the buttons

        Texture* background;                //The background of this screen
        Buttons* btns;                      //The buttons on this screen

    protected:

    private:
};

#endif // MENUSCREEN_H
