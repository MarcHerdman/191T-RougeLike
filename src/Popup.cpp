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

void Popup::Init(int screenWidth, int screenHeight,int popupType)
{

    switch (popupType)
    {
    case 1:
        btns->Init("images/RL_Buttons_1024.png", 4, 8);
        btns->AddButton("Accept", ACCEPT, 0.35, 0.33, false, screenWidth, screenHeight);
        btns->AddButton("InGameHelp", HELP, 0.5, 0.33, false, screenWidth, screenHeight);
        btns->AddButton("Decline", DECLINE, 0.65, 0.33, false, screenWidth, screenHeight);
        msg->CreateTexture("images/RL_Exit.png",1,1,0.5,0.0);
        break;
    case 2:
        btns->Init("images/RL_Buttons_1024.png", 4, 8);
        btns->AddButton("Accept", ACCEPT, 0.35, 0.33, false, screenWidth, screenHeight);
        btns->AddButton("Quit", QUIT, 0.65, 0.33, false, screenWidth, screenHeight);
        msg->CreateTexture("images/RL_ExitDead.png",1,1,0.5,0.0);
        break;
    case 3:
        btns->Init("images/RL_Buttons_1024.png", 4, 8);
        btns->AddButton("Accept", ACCEPT, 0.35, 0.33, false, screenWidth, screenHeight);
        btns->AddButton("Quit", QUIT, 0.65, 0.33, false, screenWidth, screenHeight);
        msg->CreateTexture("images/RL_ExitWin.png",1,1,0.5,0.0);
        break;

    }

}

void Popup::SetActive(bool status)
{
    isActive = status;
    cout << "IWprld\n";
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
