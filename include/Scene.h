//Abstract class for all screens of the game
//including the levels and menus

#ifndef SCENE_H
#define SCENE_H
#include<Shader.h>

#include <windows.h>
#include <GL/glut.h>
#include <vector>
#include <stack>

#include <Scene.h>
#include <Texture.h>
#include <iostream>
#include <Player.h>
#include <Inputs.h>
#include <Maze.h>
#include <Stencil.h>
#include<Sound.h>
//#include <Button.h>
#include <Timer.h>
#include <Util.h>

class Scene
{
    public:
        Scene();
        virtual ~Scene();

        GLint InitGL();                                 //initialize OpenGL
        GLint DrawScene();                              //Renderer
        GLvoid ResizeScene(GLsizei, GLsizei);           //screen size changes
        int WinMsg(HWND, UINT, WPARAM, LPARAM);	        //Callback of Inputs

        virtual void Init(int, int) = 0;                //Force all scenes to have an Init function
        virtual void Draw() = 0;                        //Force all scenes to have a Draw function
        virtual void Action(std::string action) = 0;    //Force all scenes to have an Action function
        virtual void ScreenResized(int,int) = 0;

        Inputs* kBMs;                                   //Input handler
        float screenHeight, screenWidth;                //Keep track of the screen height and width
        float aspectRatio;
        int mouseX, mouseY;                             //Current mouse position

        std::stack<Scene*>* sceneStack;                 //The scene stack
        Timer* timer;                                   //The timer for this scene

    protected:

    private:
};

#endif // SCENE_H
