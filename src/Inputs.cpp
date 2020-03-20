#include "Inputs.h"

Inputs::Inputs()
{
    //ctor
}

Inputs::~Inputs()
{
    //dtor
}


void Inputs::KeyPressed()
{
    switch(wParam)
    {
        case VK_LEFT:

            break;
        case VK_RIGHT:

            break;
        case VK_UP:

            break;
        case VK_DOWN:

            break;
        case VK_HOME:

            break;
        case VK_END:

            break;
    }
}

void Inputs::KeyReleased()
{
    switch(wParam)
    {
        default:
            break;
    }
}

void Inputs::mouseEventDown(double x, double y)
{
    //std::cout << "Mouse Down" << std::endl;
    prevMouseX = x;
    prevMouseY = y;

    switch(wParam)
    {
        case MK_LBUTTON:
            break;
        case MK_RBUTTON:
            break;
        case MK_MBUTTON:
            break;
        default:
            break;
    }
}

void Inputs::mouseEventUp()
{

}

void Inputs::mouseWheel(double delta)
{

}

void Inputs::mouseMove(double x, double y)
{
    //Code Here

    prevMouseX = x;
    prevMouseY = y;
}
