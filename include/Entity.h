//Abstract class to provide common functionality to things that must move on the screen
//Mainly intended to be used for the player and enemies

#ifndef ENTITY_H
#define ENTITY_H

#include<GL/gl.h>
#include<Texture.h>
#include<Util.h>

class Entity
{
    public:
        Entity();
        virtual ~Entity();

        void DrawEntity();
        fpair GetNextXY();
        void PositionEntity(fpair);

        virtual void Init(char*, int, int) = 0; //Force all child classes to have an Init function
        virtual void Action(int) = 0;           //Force all child classes to have an Action function
        //virtual bool CheckCollision(int) = 0;

        float xPos;                             //x position of the entity
        float yPos;                             //y position of the entity

        int movementFlag;                       //bitflag of current directions entity is moving (W=1,S=2,E=4,N=8)
        std::string whenIdle;                   //what idle animation to play if no longer moving

        float walkSpeed;                        //Movement speed in terms of percentage of screen moved per frame

        Texture* tex;                           //Texture information for the entity

    protected:

    private:
};

#endif // ENTITY_H
