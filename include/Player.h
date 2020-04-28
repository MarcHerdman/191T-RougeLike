//The player entity

#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>


class Player : public Entity
{
    public:
        Player();
        virtual ~Player();

        void Init(char*,int,int);   //Initialize the player
        void Action(int);           //Handle inputs

        void Teleport(std::string);

    protected:

    private:
};

#endif // PLAYER_H
