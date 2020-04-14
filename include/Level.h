//A generic level with randomized maze

#ifndef LEVEL_H
#define LEVEL_H

#include <Scene.h>
//#include <Buttons.h>
#include <Popup.h>

class Level : public Scene
{
    public:
        Level(std::stack<Scene*>*);     //All scenes must have access to the scene stack
        virtual ~Level();

        void Init(int, int);            //Initialize the scene
        void Draw();                    //Draw the scene
        void Action(std::string);       //Process any actions
        void ScreenResized(int,int);    //Recalculate the borders of the buttons

        Player* ply;                    //The player
        Maze* maze;                     //The maze
        Popup* popup;
        Stencil* mask;

        //Texture* question;              //The popup message
        //Buttons* btns;                  //The popup buttons

    protected:

    private:
};

#endif // LEVEL_H
