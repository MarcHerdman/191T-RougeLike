#include "Popup.h"

Popup::Popup()
{
    //ctor
    msg = new Texture();
    btns = new Buttons();
    isActive = false;
}

Popup::~Popup()
{
    //dtor
}

void Popup::Init(int screenWidth, int screenHeight)
{
    btns->Init("images/RL_Buttons_1024.png", 4, 8);
    btns->AddButton("Accept", ACCEPT, 0.4, 0.33, false, screenWidth, screenHeight);
    btns->AddButton("Decline", DECLINE, 0.6, 0.33, false, screenWidth, screenHeight);
    msg->CreateTexture("images/RL_Exit.png",1,1,0.5,0.0);
}

void Popup::SetActive(bool status)
{
    isActive = status;
    btns->SetActive(status);
}

void Popup::Draw(int mouseX, int mouseY)
{
    glPushMatrix();
        msg->TextureBinder();
        msg->Draw(0.5,0.1);
        btns->Update(mouseX,mouseY);
        btns->Draw();
    glPopMatrix();
}
