#ifndef SQUARE_H
#define SQUARE_H

#include<GL/gl.h>
#include<Texture.h>

class Square
{
    public:
        Square();
        virtual ~Square();
        void DrawSquare(float,float,float,float);
        void Init(char*);   //Initialize the player



        Texture* tex;

    protected:

    private:
};

#endif // SQUARE_H
