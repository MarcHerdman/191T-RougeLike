#ifndef ENTITY_H
#define ENTITY_H

#include<GL/gl.h>
#include<Texture.h>

typedef struct
{
    float x;
    float y;
    float z;
}vec3;

class Entity
{
    public:
        Entity();
        virtual ~Entity();

        void DrawEntity();
        void PositionEntity();

        virtual void Init(char*, int, int) = 0; //Force all child classes to have an Init function

        float scale[3] = {1.0,1.0,1.0};
        vec3 verticies[4];

        float xPos;     //x position of the player
        float yPos;     //y position of the player
        float zPos;     //z position of the player

        float xSize;    //X Y scaling
        float ySize;

        float xRotation;    //Rotations of the player
        float yRotation;
        float zRotation;

        float runSpeed;
        float jumpSpeed;

        float xMax,xMin,yMax,yMin;

        int action;
        int frames;
        Texture* tex;

    protected:

    private:
};

#endif // ENTITY_H
