#include "Inputs.h"

Inputs::Inputs(Timer* t)
{
    //ctor
    timer = t;
}

Inputs::~Inputs()
{
    //dtor
}

void Inputs::SetPlayer(Entity* e)
{
    ply = e;
}

void Inputs::SetMaze(Maze* m)
{
    maze = m;
}

void Inputs::SetBtns(Buttons* b)
{
    btns = b;
}

void Inputs::KeyPressed()//ONLY RESPOND ONCE WHEN THE KEY IS FIRST PRESSED
{
    if(!timer->IsPaused())
    {
        switch(wParam)
        {
            case VK_LEFT:
                if(ply) ply->Action(1);
                //if(ply) ply->tex->SetAnimation("WalkLeft", true, true, 0);
                //if(maze) maze->Moving(0);
                break;
            case VK_RIGHT:
                if(ply) ply->Action(4);
                //if(ply) ply->tex->SetAnimation("WalkRight", true, true, 0);
                //if(maze) maze->Moving(2);
                break;
            case VK_UP:
                if(ply) ply->Action(8);
                //if(ply) ply->tex->SetAnimation("WalkUp", true, true, 0);
                //if(maze) maze->Moving(3);
                break;
            case VK_DOWN:
                if(ply) ply->Action(2);
                //if(ply) ply->tex->SetAnimation("WalkDown", true, true, 0);
                //if(maze) maze->Moving(1);
                break;
            case VK_RETURN:
                break;
        }
    }
}

void Inputs::KeyReleased()
{
    if(!timer->IsPaused())
    {
        switch(wParam)
        {
            case VK_LEFT:
                if(ply) ply->Action(-1);
                //if(ply) ply->tex->SetAnimation("IdleLeft", true, false, 0);
                break;
            case VK_RIGHT:
                if(ply) ply->Action(-4);
                //if(ply) ply->tex->SetAnimation("IdleRight", true, false, 0);
                break;
            case VK_UP:
                if(ply) ply->Action(-8);
                //if(ply) ply->tex->SetAnimation("IdleUp", true, false, 0);
                break;
            case VK_DOWN:
                if(ply) ply->Action(-2);
                //if(ply) ply->tex->SetAnimation("IdleDown", true, false, 0);
                break;
        }
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

std::string Inputs::mouseEventUp()
{
    if(btns) return btns->CheckClick();
    return "";
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
