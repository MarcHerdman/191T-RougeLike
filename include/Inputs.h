#ifndef INPUTS_H
#define INPUTS_H

#include<windows.h>

class Inputs
{
    public:
        Inputs();
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

    protected:

    private:
};

#endif // INPUTS_H
