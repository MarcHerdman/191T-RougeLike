#ifndef TEXTURE_H
#define TEXTURE_H

#include <SOIL.h>
#include<GL/gl.h>
#include <iostream>

class Texture
{
    public:
        Texture();
        virtual ~Texture();
        void CreateTexture(char *);
        void TextureBinder();

        int width,height;
        unsigned char* image;
        GLuint tex;

    protected:

    private:
};

#endif // TEXTURE_H
