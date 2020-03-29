#ifndef TEXTURE_H
#define TEXTURE_H

#include <SOIL.h>
#include <GL/gl.h>
#include <iostream>
#include <map>
#include <utility>

typedef std::pair<int,int> ipair;

class Texture
{
    public:
        Texture();
        virtual ~Texture();
        void CreateTexture(char*, int, int); //Filename, # of cells wide, # of cells high
        void TextureBinder();
        void AddAnimation(std::string,int,int); //Name, start frame, # of frames
        void SetAnimation(std::string, bool, bool, int); //Name, start playing, loop it, frame to start on
        void Draw();

        int width,height;
        float widthPercentage, heightPercentage;
        unsigned char* image;
        GLuint tex;
        int cellsX;
        float offsetX, offsetY;

        std::map<std::string,ipair> animations;
        bool playAnim;
        bool loopAnim;
        std::string curAnim;
        int curFrame;

    protected:

    private:
};

#endif // TEXTURE_H
