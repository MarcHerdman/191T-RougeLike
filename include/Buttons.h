//Hold and process a collection of buttons as a single set

#ifndef BUTTONS_H
#define BUTTONS_H

#include <vector>
#include <iostream>

#include<Texture.h>

enum text{RETURN, BEGIN, HELP, QUIT, PLAY, ABOUT, ACCEPT, DECLINE};
enum style{NORMAL, CLICK, HOVER, BRIGHT};

struct btn
{
    //Texture* tex;                                   //The button image

    std::string name;                               //Name of this button
    int type;                                       //Enum tpye
    int status;                                     //Current status

    float posPercentX;
    float posPercentY;

    int left, right, top, bottom;                   //Pixel boundaries of the button
    bool isActive;                                  //Is this button is clickable
};


class Buttons
{
    public:
        Buttons();
        virtual ~Buttons();

        void Init(char*, int, int, float pivX = 0.5, float pivY = 0.5);//Initialize texture
        void Draw();                                    //Draw if active
        void CalculateBorders(int, int);                //Calculate the pixel boundaries of the button
        void Update(int, int);                          //Handle mouseover
        std::string CheckClick();                       //Check if mouse over button when clicked
        void SetActive(bool);                           //Set whether button can be clicked
        void AddButton(std::string, int, float, float, bool, int, int);   //Name, Enum Function, xPercentPos, yPercentPos, active, screenwidth, screenheight

        std::vector<btn*> btns;                         //Hold all buttons created
        Texture* tex;                                   //Texture containing button images
        float posPercentX;                              //The percentage screen X location
        float posPercentY;                              //The percentage screen Y location


    protected:

    private:
};

#endif // BUTTONS_H
