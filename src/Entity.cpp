#include "Entity.h"

Entity::Entity()
{
    tex = new Texture();

    verticies[0].x=0.0; verticies[0].y=0.0; verticies[0].z=-8.0;
    verticies[1].x=1.0; verticies[1].y=0.0; verticies[1].z=-8.0;
    verticies[2].x=1.0; verticies[2].y=1.0; verticies[2].z=-8.0;
    verticies[3].x=0.0; verticies[3].y=1.0; verticies[3].z=-8.0;

    runSpeed = 0;
    jumpSpeed = 0;

    xPos = 0.0;
    yPos = 0.0;
    zPos = 5.0;

    xSize = 2.0;    //X Y scaling
    ySize = 2.0;

    xRotation = 0.0;    //Rotations of the player
    yRotation = 0.0;
    zRotation = 0.0;

    action = 0;

    frames = 7;
    xMin = 0.0;
    yMin = 0.0;
    xMax = 1.0/frames;
    yMax = 1.0/4;
}

Entity::~Entity()
{
    //dtor
}

void Entity::DrawEntity()
{

    tex->TextureBinder();
    glTranslatef(0.5 - tex->widthPercentage,0.5 - tex->heightPercentage,0);
    glScalef(3.0,3.0,0.0);
    tex->Draw();
}
