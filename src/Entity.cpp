#include "Entity.h"

Entity::Entity()
{
    tex = new Texture();

    verticies[0].x=0.0; verticies[0].y=0.0; verticies[0].z=-1.0;
    verticies[1].x=1.0; verticies[1].y=0.0; verticies[1].z=-1.0;
    verticies[2].x=1.0; verticies[2].y=1.0; verticies[2].z=-1.0;
    verticies[3].x=0.0; verticies[3].y=1.0; verticies[3].z=-1.0;

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
    //glColor3f(1.0,0.0,0.0);
    tex->TextureBinder();

    glTranslatef(xPos,yPos,zPos);

    glRotatef(xRotation,1.0,0.0,0.0);
    glRotatef(yRotation,0.0,1.0,0.0);
    glRotatef(zRotation,0.0,0.0,1.0);

    glScalef(xSize,ySize,1);

    glBegin(GL_QUADS);
        glTexCoord2f(xMin,yMax);
        glVertex3f(verticies[0].x,verticies[0].y,verticies[0].z);

        glTexCoord2f(xMax,yMax);
        glVertex3f(verticies[1].x,verticies[1].y,verticies[1].z);

        glTexCoord2f(xMax,yMin);
        glVertex3f(verticies[2].x,verticies[2].y,verticies[2].z);

        glTexCoord2f(xMin,yMin);
        glVertex3f(verticies[3].x,verticies[3].y,verticies[3].z);
    glEnd();
}

void Entity::PositionEntity()
{

}

void Entity::InitEntity(char* filename)
{
    tex->CreateTexture(filename);
}

void Entity::Actions()
{
    switch(action)
    {
        case 0: xMin+=1.0/frames;
                xMax+=1.0/frames;
                yMin=0.5;
                yMax=0.75;
                if(xMax>=1) {xMin=0.0; xMax=1.0/frames;}
        break;
    }
}
