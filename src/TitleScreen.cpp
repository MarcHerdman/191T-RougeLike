#include "TitleScreen.h"

TitleScreen::TitleScreen(std::stack<Scene*>* s)
{
    //ctor
    sceneStack = s;
    background = new Texture();
    btns = new Buttons();
    kBMs = new Inputs(timer);
    kBMs->SetBtns(btns);
}

TitleScreen::~TitleScreen()
{
    //dtor
}
void TitleScreen::Init(int screenWidth, int screenHeight)
{
    background->CreateTexture("images/RL_TitleScreenNEW.jpg",1,1);
    btns->Init("images/RL_Buttons_1024.png", 4, 8);
    btns->AddButton("Begin", BEGIN, 0.125, 0.33, true, screenWidth, screenHeight);
}

void TitleScreen::Draw()
{
    glPushMatrix();
        background->TextureBinder();
        background->Draw(0.0,0.0);
    //glPopMatrix();
    btns->Update(mouseX,mouseY);
    //glPushMatrix();
        btns->Draw();
    glPopMatrix();
}

void TitleScreen::Action(std::string action)
{
    if(action == "Begin" || action == "KB_Enter" || action == "KB_B")
    {
        sceneStack->pop();
        MenuScreen* ms = new MenuScreen(sceneStack);
        ms->InitGL();
        sceneStack->push(ms);
    }
    if(action == "KB_Esc") sceneStack->pop();
}

void TitleScreen::ScreenResized(int screenWidth, int screenHeight)
{
    btns->CalculateBorders(screenWidth, screenHeight);
}
