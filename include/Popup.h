#ifndef POPUP_H
#define POPUP_H

#include<Buttons.h>
#include<Texture.h>

class Popup
{
    public:
        Popup();
        virtual ~Popup();

        void Init(int,int,int);
        void SetActive(bool);
        void Draw(int,int);

        Buttons* btns;
        Texture* msg;

        bool isActive;

    protected:

    private:
};

#endif // POPUP_H
