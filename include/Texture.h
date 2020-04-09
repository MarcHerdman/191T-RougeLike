//Handle the texture and drawing of objects

#ifndef TEXTURE_H
#define TEXTURE_H

#include <SOIL.h>
#include <GL/gl.h>
#include <iostream>
#include <map>
#include <utility>

#include <Util.h>

typedef std::pair<int,int> ipair;

class Texture
{
    public:
        Texture();
        virtual ~Texture();

        void CreateTexture(char*, int, int, float pivX = 0.0, float pivY = 0.0 );   //Setup the texture
        void TextureBinder();                                                       //Make this the active texture
        void AddAnimation(std::string,int,int);                                     //Create and animation
        void SetAnimation(std::string, bool, bool, int);                            //Set the active animation
        void Draw(float xPos, float yPos, float xScale = 1.0, float yScale=1.0);    //Draw the current frame at position and scale

        int width,height;                           //Height and width of the whole texture
        float widthPercentage, heightPercentage;    //Height and width of a single cell in terms of percentage of screen
        unsigned char* image;                       //The image used to create the texture
        GLuint tex;                                 //The assigned texture number
        int cellsX;                                 //Number of cells wide (for calculating index values of cells)
        float offsetX, offsetY;                     //The amount of the texture taken by one cell
        float pivotX, pivotY;                       //The point in the cell to act as the basis for drawing the image

        std::map<std::string,ipair> animations;     //Map of all created animations
        bool playAnim;                              //Whether the current animation is playing
        bool loopAnim;                              //Whether to loop the current animation
        std::string curAnim;                        //The name of the current animation
        int curFrame;                               //The current frame of the animation

    protected:

    private:
};

#endif // TEXTURE_H
