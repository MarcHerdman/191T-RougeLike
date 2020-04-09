#include "Texture.h"

Texture::Texture()
{
    //ctor
    playAnim = false;
    loopAnim = false;
    curAnim = "";
    curFrame = 0;
}

Texture::~Texture()
{
    //dtor
}

//Requires filename (relative to the exe), number of cells wide and number of cells high
//Defaults to drawing from the top left corner.
void Texture::CreateTexture(char* fileName, int cx, int cy, float pivX, float pivY)
{
    glGenTextures(1,&tex);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, tex);
    image = SOIL_load_image(fileName,&width,&height, 0,SOIL_LOAD_RGBA);

    if(!image) std::cout << "fail to find image" << std::endl;

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width, height,0,GL_RGBA,GL_UNSIGNED_BYTE,image);
    SOIL_free_image_data(image);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    cellsX = cx;

    offsetX = 1.0/cx;
    offsetY = 1.0/cy;

    widthPercentage = width/cx/(float)defaultScreenSizeX;
    heightPercentage = height/cy/(float)defaultScreenSizeY;

    pivotX = pivX;
    pivotY = pivY;
}

void Texture::TextureBinder()
{
    glBindTexture(GL_TEXTURE_2D,tex);
}

void Texture::AddAnimation(std::string name, int start, int frames)
{
    animations[name] = std::make_pair(start,frames);
}

void Texture::SetAnimation(std::string name, bool isPlaying, bool isLooping, int startFrsme)
{
    //if(name != curAnim) //Dont change if already playing this animation
    //{
        curAnim = name;
        playAnim = isPlaying;
        loopAnim = isLooping;
        curFrame = startFrsme;
    //}
}
void Texture::Draw(float xPos, float yPos, float xScale, float yScale)
{
    int curFrameX, curFrameY;
    if(curAnim == "") //No animation so render current frame
    {
        //Convert frame number into x,y cells;
        curFrameX = curFrame % cellsX;
        curFrameY = curFrame / cellsX;
    }
    else //If animation is set
    {
        int start = animations[curAnim].first; //The first frame of this animation
        int frames = animations[curAnim].second; //The total number of frames of this animation

        //Calculate the x,y cell of the current frame of animation
        curFrameX = (start + curFrame) % cellsX;
        curFrameY = (start + curFrame) / cellsX;

        if(playAnim) //If this animation is set to play
        {
            //std::cout << "Playing " << curAnim << std::endl;
            curFrame++; //increase the frames
            if(curFrame >= frames) //if we go past the total number of frames...
            {
                if(loopAnim)//...If this animation is set to loop...
                {
                    //std::cout << "LOOPED " << frames << std::endl;
                    //std::cout << "Walk up frames " << animations["WalkUp"].second <<  std::endl;
                    //std::cout << "Walk down frames " << animations["WalkDown"].second <<  std::endl;
                    //std::cout << "Walk left frames " << animations["WalkLeft"].second <<  std::endl;
                    //std::cout << "Walk right frames " << animations["WalkRight"].second <<  std::endl;
                    curFrame = 0;//...Reset the counter to 0...
                }
                else//...Otherwise...
                {
                    //std::cout << "STALLED " << std::endl;
                    curFrame = frames; //...Leave the frame counter at the end of the animation
                }
            }
        }
    }

    //Calculate the percentages of the image to display
    float xMin = offsetX * curFrameX;
    float xMax = offsetX * curFrameX + offsetX;
    float yMin = offsetY * curFrameY;
    float yMax = offsetY * curFrameY + offsetY;

    //std::cout <<"PX: " << pivotX << std::endl;
    glBegin(GL_QUADS);
        glTexCoord2f(xMin,yMin);
        glVertex3f(xPos-(pivotX*widthPercentage*xScale),yPos-(pivotY*heightPercentage*yScale),0.0);

        glTexCoord2f(xMin,yMax);
        glVertex3f(xPos-(pivotX*widthPercentage*xScale),yPos-(pivotY*heightPercentage*yScale)+(heightPercentage*yScale),0.0);

        glTexCoord2f(xMax,yMax);
        glVertex3f(xPos-(pivotX*widthPercentage*xScale)+(widthPercentage*xScale),yPos-(pivotY*heightPercentage*yScale)+(heightPercentage*yScale),0.0);

        glTexCoord2f(xMax,yMin);
        glVertex3f(xPos-(pivotX*widthPercentage*xScale)+(widthPercentage*xScale),yPos-(pivotY*heightPercentage*yScale),0.0);
    glEnd();
}
