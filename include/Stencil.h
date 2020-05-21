#ifndef STENCIL_H
#define STENCIL_H
#include<GL/gl.h>
#include <math.h>
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
