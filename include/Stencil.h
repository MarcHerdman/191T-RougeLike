#ifndef STENCIL_H
#define STENCIL_H
#include<Entity.h>
#include <math.h>

class Stencil
{
    public:
        Stencil();
        virtual ~Stencil();
        void drawMask(Entity*,float);
        void disableBuffer();

    protected:

    private:
};

#endif // STENCIL_H
