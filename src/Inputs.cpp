#include "Inputs.h"

Inputs::Inputs(Entity* p)
{
    //ctor
    ply = p;
}

Inputs::~Inputs()
{
    //dtor
}


void Inputs::KeyPressed()
{
    //std::cout << wParam << std::endl;
    switch(wParam)
    {
        case VK_LEFT:
            ply->tex->SetAnimation("WalkLeft", true, true, 0);
            break;
        case VK_RIGHT:
            ply->tex->SetAnimation("WalkRight", true, true, 0);
            break;
        case VK_UP:
            ply->tex->SetAnimation("WalkUp", true, true, 0);
            break;
        case VK_DOWN:
            ply->tex->SetAnimation("WalkDown", true, true, 0);
            break;
    }
}

void Inputs::KeyReleased()
{
    switch(wParam)
    {
        case VK_LEFT:
            ply->tex->SetAnimation("IdleLeft", true, false, 0);
            break;
        case VK_RIGHT:
            ply->tex->SetAnimation("IdleRight", true, false, 0);
            break;
        case VK_UP:
            ply->tex->SetAnimation("IdleUp", true, false, 0);
            break;
        case VK_DOWN:
            ply->tex->SetAnimation("IdleDown", true, false, 0);
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
