#include "Entity.h"

Entity::Entity()
{
    tex = new Texture();
}

Entity::~Entity()
{
    //dtor
}

//Draw the entity to the screen
//Requires Push Matrix be call before and Pop Matrix be called after
void Entity::DrawEntity()
{
    tex->TextureBinder();
    //tex->Draw(0.5 - tex->widthPercentage,0.5 - tex->heightPercentage, 3.0, 3.0);
    tex->Draw(xPos,yPos,3.0,3.0);
}

//Set the entity's position based on the movement flag and walk speed.
void Entity::PositionEntity(int room)
{
    if(movementFlag & 1) xPos-=walkSpeed;
    if(movementFlag & 2) yPos+=walkSpeed;
    if(movementFlag & 4) xPos+=walkSpeed;
    if(movementFlag & 8) yPos-=walkSpeed;

    //std::cout << "X: " << xPos << ", Y: " << yPos << std::endl;

    if(room & 1) if(xPos < 0.3) xPos+=walkSpeed;
    //else if(xPos<0.2) Action("ChangeRoomLeft");
    if(room & 4) if(xPos > 0.7) xPos-=walkSpeed;
    //else if(xPos>0.8) Action("ChangeRoomRight");
    if(room & 2) if(yPos > 0.6) yPos-=walkSpeed;
    //else if(yPos<0.62 && xPos > 0.45 && xPos < 0.55) Action("ChangeRoomDown");
    if(room & 8) if(yPos < 0.4) yPos+=walkSpeed;
    //else if(yPos<0.38 && xPos > 0.55 && xPos < 0.55 ) Action("ChangeRoomUp");

}
