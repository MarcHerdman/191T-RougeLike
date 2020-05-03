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

fpair Entity::GetNextXY()
{
    float x = xPos;
    float y = yPos;
    if(movementFlag & 1) x-=walkSpeed;
    if(movementFlag & 2) y+=walkSpeed;
    if(movementFlag & 4) x+=walkSpeed;
    if(movementFlag & 8) y-=walkSpeed;
    return std::make_pair(x,y);
}

fpair Entity::MGetNextXY(fpair XYPlayer)
{
    float enemyX = xPos;
    float enemyY = yPos;

    float playerX = XYPlayer.first;
    float playerY = XYPlayer.second;

    float distanceX = playerX - enemyX;
    float distanceY = playerY - enemyY;

    float hypotenuse = sqrt((distanceX * distanceX) + (distanceY * distanceY));
//    std::cout << "Distance coordinates: " << distanceX << ", " << distanceY << std::endl;
//    std::cout << "Hypotenuse: " << hypotenuse << std::endl;
//    std::cout << "Player coordinates: " << playerX << ", " << playerY << std::endl;
    if(hypotenuse < .600)
    {
        enemyX += walkSpeed * (distanceX/hypotenuse);
        enemyY += walkSpeed * (distanceY/hypotenuse);
    }

//    std::cout << "Monster coordinates: " << enemyX << ", " << enemyY << std::endl;
    return std::make_pair(enemyX,enemyY);
}

//Set the entity's position based on the movement flag and walk speed.
void Entity::PositionEntity(fpair loc)
{
    xPos = loc.first;
    yPos = loc.second;
    /*
    float previousX = xPos;
    float previousY = yPos;
    if(movementFlag & 1) xPos-=walkSpeed;
    if(movementFlag & 2) yPos+=walkSpeed;
    if(movementFlag & 4) xPos+=walkSpeed;
    if(movementFlag & 8) yPos-=walkSpeed;
    //std::cout << xPos << ", " << yPos << std::endl;
    if(CheckCollision(room))
    {
        xPos = previousX;
        yPos = previousY;
    }
    */
}
