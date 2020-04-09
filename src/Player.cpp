#include "Player.h"

Player::Player()
{
    //ctor
    movementFlag = 0;
    walkSpeed = 0.01;
    xPos = 0.5;
    yPos = 0.5;
}

Player::~Player()
{
    //dtor
}

void Player::Init(char* filename, int x, int y)
{
    std::cout << "Initializing Player" << std::endl;
    tex->CreateTexture(filename, x, y, 0.5, 0.50);
    tex->AddAnimation("WalkUp", 0, 9);
    tex->AddAnimation("WalkLeft", 9, 9);
    tex->AddAnimation("WalkDown", 18, 9);
    tex->AddAnimation("WalkRight", 27, 9);
    tex->AddAnimation("IdleUp", 0, 1);
    tex->AddAnimation("IdleLeft", 9, 1);
    tex->AddAnimation("IdleDown", 18, 1);
    tex->AddAnimation("IdleRight", 27, 1);
    tex->SetAnimation("IdleDown",true,false,0);
    //std::cout << "Walk up frames " << tex->animations["WalkUp"].second <<  std::endl;
    //std::cout << "Walk down frames " << tex->animations["WalkDown"].second <<  std::endl;
    //std::cout << "Walk left frames " << tex->animations["WalkLeft"].second <<  std::endl;
    //std::cout << "Walk right frames " << tex->animations["WalkRight"].second <<  std::endl;
}

void Player::Action(int input)
{
    //std::cout << input << std::endl;

    movementFlag+=input;
    if(input == 1)
    {
        tex->SetAnimation("WalkLeft", true, true, 0);
        whenIdle = "IdleLeft";
    }
    else if(input == 2)
    {
        tex->SetAnimation("WalkDown", true, true, 0);
        whenIdle = "IdleDown";
    }
    else if(input == 4)
    {
        tex->SetAnimation("WalkRight", true, true, 0);
        whenIdle = "IdleRight";
    }
    else if(input == 8)
    {
        tex->SetAnimation("WalkUp", true, true, 0);
        whenIdle = "IdleUp";
    }
    if(movementFlag == 0) tex->SetAnimation(whenIdle, true, false, 0);
}
