//Used to hold open the OpenGL window just long enough for main to close the window down after all other scenes are closed
#ifndef BLANKSCREEN_H
#define BLANKSCREEN_H

#include <Scene.h>


class BlankScreen : public Scene
{
    public:
        BlankScreen(std::stack<Scene*>*);
        virtual ~BlankScreen();

        void Init(int, int);
        void Draw();
        void Action(std::string);
        void ScreenResized(int,int);

    protected:

    private:
};

#endif // BLANKSCREEN_H
