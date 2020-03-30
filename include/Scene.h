#ifndef SCENE_H
#define SCENE_H

#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <Player.h>
#include <Inputs.h>

#include <Maze.h>

class Scene
{
    public:
        Scene();
        virtual ~Scene();

        GLint InitGL();             //initialize OpenGL
        GLint DrawScene();          //Renderer
        GLvoid ResizeScene(GLsizei, GLsizei);  //screen size changes
        int WinMsg(HWND, UINT, WPARAM, LPARAM);	// Callback of Inputs

        Player* ply;
        Inputs* kBMs;
        Maze* maze;
        float screenHeight, screenWidth; //To map background images

    protected:

    private:
};

#endif // SCENE_H
