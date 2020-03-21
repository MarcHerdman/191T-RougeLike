#include "Texture.h"

Texture::Texture()
{
    //ctor
    bool playAnim = false;
    bool loopAnim = false;
    std::string curAnim = "";
    int curFrame = 0;
}

Texture::~Texture()
{
    //dtor
}
void Texture::CreateTexture(char* fileName, int x, int y)
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

    cellsX = x;

    offsetX = 1.0/x;
    offsetY = 1.0/y;
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

    if(name != curAnim) //Dont change if already playing this animation
    {
        curAnim = name;
        playAnim = isPlaying;
        loopAnim = isLooping;
        curFrame = startFrsme;
    }

}
void Texture::Draw()
{

    if(curAnim != "")
    {
        int start = animations[curAnim].first;
        int frames = animations[curAnim].second;
        int curFrameX = (start + curFrame) % cellsX;
        int curFrameY = (start + curFrame) / cellsX;
        std::cout << curFrameX << std::endl;
        float xMin = offsetX * curFrameX;
        float xMax = offsetX * curFrameX + offsetX;
        float yMin = offsetY * curFrameY;
        float yMax = offsetY * curFrameY + offsetY;
        glBegin(GL_QUADS);
            glTexCoord2f(xMin,yMax);
            glVertex3f(0.0,0.0,-10.0);

            glTexCoord2f(xMax,yMax);
            glVertex3f(1.0,0.0,-10.0);

            glTexCoord2f(xMax,yMin);
            glVertex3f(1.0,1.0,-10.0);

            glTexCoord2f(xMin,yMin);
            glVertex3f(0.0,1.0,-10.0);
        glEnd();
        if(playAnim)
        {
            curFrame++;
            if(curFrame >= frames)
            {
                if(loopAnim)
                {
                    curFrame = 0;
                }
                else
                {
                    curFrame = frames;
                }
            }
        }
    }
}

