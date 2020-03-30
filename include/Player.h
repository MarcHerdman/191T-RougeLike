#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>


class Player : public Entity
{
    public:
        Player();
        virtual ~Player();

        void Init(char*,int,int);

    protected:

    private:
};

#endif // PLAYER_H
