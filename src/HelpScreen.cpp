#include "HelpScreen.h"

HelpScreen::HelpScreen(std::stack<Scene*>* s)
{
    //ctor
    sceneStack = s;
    background = new Texture();
    btns = new Buttons();
    kBMs = new Inputs(timer);
    kBMs->SetBtns(btns);
}

HelpScreen::~HelpScreen()
{
    //dtor
}

//Initialize this scene
//Must be called before all other functions
void HelpScreen::Init(int x, int y)
{
    background->CreateTexture("images/RL_HelpScreenNEW.jpg",1,1);
    btns->Init("images/RL_Buttons_1024.png", 4, 8, 0.0, 0.0);
    btns->AddButton("Return", RETURN, 0.05, 0.05, true, screenWidth, screenHeight);
}

//Draw this scene to the screen
void HelpScreen::Draw()
{
    glPushMatrix();
        background->TextureBinder();
        background->Draw(0.0,0.0);
        btns->Update(mouseX,mouseY); //Must call before drawing buttons to the screen
        btns->Draw();
    glPopMatrix();
}

//Collect user inputs relevant to this scene and act on them
void HelpScreen::Action(std::string action)
{
    if(action == "Return" || action == "KB_R" || action == "KB_Esc")
    {
        sceneStack->pop();
    }
}

//Recalculate the button edges each time screen is resized
void HelpScreen::ScreenResized(int screenWidth, int screenHeight)
{
    btns->CalculateBorders(screenWidth, screenHeight);
}
