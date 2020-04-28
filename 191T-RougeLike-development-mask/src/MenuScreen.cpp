#include "MenuScreen.h"

MenuScreen::MenuScreen(std::stack<Scene*>* s)
{
    //ctor
    sceneStack = s;
    background = new Texture();
    btns = new Buttons();
    kBMs = new Inputs(timer);
    kBMs->SetBtns(btns);
}

MenuScreen::~MenuScreen()
{
    //dtor
}

void MenuScreen::Init(int screenWidth, int screenHeight)
{
    background->CreateTexture("images/RL_MenuScreen.jpg",1,1);
    btns->Init("images/RL_Buttons_1024.png", 4, 8);
    btns->AddButton("Play", PLAY, 0.25, 0.33, true, screenWidth, screenHeight);
    btns->AddButton("Help", HELP, 0.5, 0.33, true, screenWidth, screenHeight);
    btns->AddButton("Quit", QUIT, 0.75, 0.33, true, screenWidth, screenHeight);
}


void MenuScreen::Draw()
{
    glPushMatrix();
        background->TextureBinder();
        background->Draw(0.0,0.0);
    glPopMatrix();
    btns->Update(mouseX,mouseY);
    glPushMatrix();
        btns->Draw();
    glPopMatrix();
}

void MenuScreen::Action(std::string action)
{
    if(action == "Play" || action == "KB_P")
    {
        Level* lvl = new Level(sceneStack);
        lvl->InitGL();
        sceneStack->push(lvl);
    }
    if(action == "Help" || action == "KB_H")
    {
        HelpScreen* hs = new HelpScreen(sceneStack);
        hs->InitGL();
        sceneStack->push(hs);
    }
    if(action == "Quit" || action == "KB_Q" || action == "KB_Esc")
    {
        sceneStack->pop();
    }
    action == "";
}

void MenuScreen::ScreenResized(int screenWidth, int screenHeight)
{
    btns->CalculateBorders(screenWidth, screenHeight);
}
