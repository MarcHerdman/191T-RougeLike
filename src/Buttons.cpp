#include "Buttons.h"

Buttons::Buttons()
{
    //ctor
    tex = new Texture();
    click = new Sound();
}
Buttons::~Buttons()
{
    //dtor
}

//Initialize the texture used for all buttons in this instance of the class
//Requires filename(relative to root), # of cells wide, # of cells tall, and
//the offset from the top and left to begin act at the base draw point.
void Buttons::Init(char* filename, int x, int y, float pivX, float pivY)
{
    tex->CreateTexture(filename, x, y, pivX, pivY);
    click ->initSounds();
}

//Draw all buttons in this instance of the class to the screen
//Must PushMatrix before colling and PopMatrix after calling
//Loops through each button active and set the image to display based on the buttons status
void Buttons::Draw()
{
    tex->TextureBinder();
    for(int i=0; i<btns.size(); ++i)
    {
        if(btns[i]->isActive)
        {
            tex->curFrame = btns[i]->type*4+btns[i]->status;
            tex->Draw(btns[i]->posPercentX,btns[i]->posPercentY);
        }
    }
}

//Determine if the mouse is currently over any button in this instance of the class
//If it is, set that button's status to hover otherwise it is normal
void Buttons::Update(int mouseX, int mouseY)
{
    for(int i=0; i<btns.size(); ++i)
    {
        if(btns[i]->isActive)
        {
            if(mouseX > btns[i]->left && mouseX < btns[i]->right && mouseY > btns[i]->top && mouseY < btns[i]->bottom)
            {
                btns[i]->status = HOVER;
            }
            else
            {
                btns[i]->status = NORMAL;
            }
        }
    }
}

//Determine if the mouse is over any button that is currently set to hover status
//Returns the name of the last such button
//Assumes mouse is only ever over one button at a time
std::string Buttons::CheckClick()
{
    std::string clicked = "";
    for(int i=0; i<btns.size(); ++i)
    {
        if(btns[i]->isActive)
        {
            if(btns[i]->isActive && btns[i]->status == HOVER){
                click->playSound("sounds/click.wav");
                return clicked = btns[i]->name;}
        }
    }
    return clicked;
}

//Determine whether all buttons in this instance of the class are visible and clickable
void Buttons::SetActive(bool state)
{
    cout << btns.size() << " I totally work\n";

    for(int i=0; i<btns.size(); ++i)
    {
        cout << btns.size() << endl;
        btns[i]->isActive = state;
    }
}

//Determine the actual borders of the button in terms of screen pixels
//Must be run once each time the screen is resized
void Buttons::CalculateBorders(int screenWidth, int screenHeight)
{
    float offX = tex->widthPercentage * tex->pivotX;
    float offY = tex->heightPercentage * tex->pivotY;
    for(int i = 0; i<btns.size(); ++i)
    {
        btns[i]->left = (btns[i]->posPercentX - offX) * screenWidth;
        btns[i]->right = btns[i]->left + tex->widthPercentage * screenWidth;
        btns[i]->top = (btns[i]->posPercentY - offY) * screenHeight;
        btns[i]->bottom = btns[i]->top + tex->heightPercentage * screenHeight;
    }
}

//Add a button to this instance of the class
//Requires name, type, x and y positions in terms of percentage of the screen
//the current state of the button (legacy), and the current screen width and height
//to calculate its initial boarder.
void Buttons::AddButton(std::string n, int t, float x, float y, bool state, int screenWidth, int screenHeight)
{
    float offX = tex->widthPercentage * tex->pivotX;
    float offY = tex->heightPercentage * tex->pivotY;
    btn* b = new btn();
    b->name = n;
    b->type = t;
    b->posPercentX = x;
    b->posPercentY = y;
    b->isActive = state;
    b->left = (x - offX) * screenWidth;
    b->right = b->left + tex->widthPercentage * screenWidth;
    b->top = (y - offY) * screenHeight;
    b->bottom = b->top + tex->heightPercentage * screenHeight;
    btns.push_back(b);
    //std::cout << btns[0]->name << std::endl;
}
