#include "Monster.h"

Monster::Monster()
{
    movementFlag = 0;
    walkSpeed    = 0.006;
    xPos         = 0.1;
    yPos         = 0.1;
}
Monster::~Monster()
{
    //dtor
}

void Monster::Init(char* filename, int x, int y)
{
    std::cout << "INITIALIZING A MONSTER" << std::endl;

    tex->CreateTexture(filename, x, y, 0.5, 0.5);
    tex->AddAnimation("WalkDown", 0, 3);
    tex->AddAnimation("WalkLeft", 12, 3);
    tex->AddAnimation("WalkRight", 24, 3);
    tex->AddAnimation("WalkUp", 36, 3);
    tex->AddAnimation("IdleDown", 0, 1);
    tex->AddAnimation("IdleLeft", 12, 1);
    tex->AddAnimation("IdleRight", 24, 1);
    tex->AddAnimation("IdleUp", 36, 1);
    tex->SetAnimation("IdleDown",true,false,0);
}

void Monster::Action(int input)
{
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

void Monster::Teleport(std::string dir)
{

    if(dir == "W")
    {
        xPos = 0.11;
        yPos = 0.6;
    }
    if(dir == "E")
    {
        xPos = 0.39;
        yPos = 0.11;
    }
    if(dir == "N")
    {
        xPos = 0.11;
        yPos = 0.11;
    }
    if(dir == "S")
    {
        xPos = 0.11;
        yPos = 0.6;
    }
}

std::string Monster::EnemyCollisionWithPlayer(fpair enemy, fpair player)
{
    if(player.first > enemy.first - 0.015 && player.first < enemy.first + 0.015
       && player.second > enemy.second - 0.015 && player.first < enemy.second + 0.015)
    {
        //Level->Action("KB_Esc");
        hasCaught = true;
        return "COLL_W_PLAYER";

    }
}

