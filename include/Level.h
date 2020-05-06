//A generic level with randomized maze

#ifndef LEVEL_H
#define LEVEL_H

#include <Scene.h>
#include <Buttons.h>
#include <Popup.h>
#include <HelpScreen.h>

class Level : public Scene
{
    public:
        Level(std::stack<Scene*>*);     //All scenes must have access to the scene stack
        virtual ~Level();

        void Init(int, int);            //Initialize the scene
        void Draw();                    //Draw the scene
        void Action(std::string);       //Process any actions
        void ScreenResized(int,int);    //Recalculate the borders of the buttons
        void NewLevel();                //Move to next level when exit is passed
        void CalculateChanges();

        HelpScreen* help;
        Player* ply;                    //The player
        Monster* mon;                   //The Monsters
        Maze* maze;                     //The maze
        Popup* popup;
        Popup* deathPopup;
        Popup* winPopup;
        Sound* sound;
        Square* square;
        Square* alphaSquare;
        Stencil* mask;
        Shader* shader;
        int levelnum;

        float maskRandomizer;
        int footstepSpacer;
        bool playerInMonsterRoom;

    protected:

    private:
};

#endif // LEVEL_H
