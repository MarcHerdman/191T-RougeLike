#ifndef MONSTER_H
#define MONSTER_H

#include <Entity.h>
#include <Player.h>
//#include <Level.h>

class Monster : public Entity
{
    public:
        Monster();
        virtual ~Monster();

        void Init(char *, int, int);
        void Action(int);
        void Teleport(std::string);
        std::string EnemyCollisionWithPlayer(fpair, fpair);

        bool hasCaught = false;
    protected:

    private:
};

#endif // MONSTER_H
