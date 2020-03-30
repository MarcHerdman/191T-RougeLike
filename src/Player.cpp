#include "Player.h"

Player::Player()
{
    //ctor
}

Player::~Player()
{
    //dtor
}

void Player::Init(char* filename, int x, int y)
{
    tex->CreateTexture(filename, x, y);
    tex->AddAnimation("WalkUp", 0, 9);
    tex->AddAnimation("WalkLeft", 9, 9);
    tex->AddAnimation("WalkDown", 18, 9);
    tex->AddAnimation("WalkRight", 27, 9);
    tex->AddAnimation("IdleUp", 0, 1);
    tex->AddAnimation("IdleLeft", 9, 1);
    tex->AddAnimation("IdleDown", 18, 1);
    tex->AddAnimation("IdleRight", 27, 1);
    tex->SetAnimation("IdleDown",true,false,0);
}
