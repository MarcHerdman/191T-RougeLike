#ifndef INPUTS_H
#define INPUTS_H

#include<windows.h>
#include<Entity.h>

class Inputs
{
    public:
        Inputs(Entity*);
        virtual ~Inputs();

        void KeyPressed();
        void KeyReleased();

        void mouseEventDown(double ,double);
        void mouseEventUp();
        void mouseWheel(double);
        void mouseMove(double ,double );

        double prevMouseX;
        double prevMouseY;

        WPARAM wParam;

        Entity* ply;

    protected:

    private:
};

#endif // INPUTS_H
