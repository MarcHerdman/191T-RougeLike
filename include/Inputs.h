//Handle controls for the active scene
#ifndef INPUTS_H
#define INPUTS_H

#include<windows.h>
#include<Entity.h>
#include<Maze.h>
#include<Timer.h>
#include<Buttons.h>

class Inputs
{
    public:
        Inputs(Timer*);                     //Must provide a timer from the active scene
        virtual ~Inputs();

        void SetPlayer(Entity*);            //Add a player to be notified of relevant inputs
        void SetMaze(Maze*);                //Add a maze to be notified of relevant inputs
        void SetBtns(Buttons*);             //Add a set of buttons to be notified of relevant inputs

        void KeyPressed();                  //Respond to the first instant a key is pressed
        void KeyReleased();                 //Respond to the first instant a key is released

        void mouseEventDown(double ,double);    //Respond to the first instant the mouse is clicked
        std::string mouseEventUp();             //Respond to the first instance the mouse is released
        void mouseWheel(double);                //NOT IMPLIMENTED
        void mouseMove(double ,double );        //Respond to movements of the mouse

        double prevMouseX;                  //The last know position of the mouse
        double prevMouseY;

        WPARAM wParam;                      //Input data from Windows

        Entity* ply;                        //The listening player
        Maze* maze;                         //The listening maze
        Buttons* btns;                      //The listening buttons
        Timer* timer;                       //The active timer from the scene


    protected:

    private:
};

#endif // INPUTS_H
