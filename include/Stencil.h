#ifndef STENCIL_H
#define STENCIL_H
#include <math.h>
#include<GL/gl.h>
#include<Texture.h>


class Stencil
{
    public:
        Stencil();
        virtual ~Stencil();
        void drawMask();
        void disableBuffer();
        Texture* tex;


    protected:

    private:
};

#endif // STENCIL_H
