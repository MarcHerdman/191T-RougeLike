#include "Scene.h"

Entity* ply = new Entity();
Inputs* kBMs = new Inputs(ply);

Scene::Scene()
{
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    maze = new Maze();
    maze->GenerateMaze(10,10);
}

Scene::~Scene()
{
    //dtor
}
GLint Scene::InitGL()
{
    glShadeModel(GL_SMOOTH); // to make graphics nicer
    glClearDepth(1.0f);  //Depth Clearance
    glEnable(GL_DEPTH_TEST); //
    glDepthFunc(GL_LEQUAL);


    //glEnable(GL_COLOR_MATERIAL);
    //_glLight light(GL_LIGHT0);


    //myModel->initModel("images/metal.jpg");

    //plx->parallaxInit("images/Flower.jpg");

    ply->InitEntity("images/prof.png", 9, 4);
    ply->AddAnimation("WalkUp", 0, 9);
    ply->AddAnimation("WalkLeft", 9, 9);
    ply->AddAnimation("WalkDown", 18, 9);
    ply->AddAnimation("WalkRight", 27, 9);
    ply->AddAnimation("IdleUp", 0, 1);
    ply->AddAnimation("IdleLeft", 9, 1);
    ply->AddAnimation("IdleDown", 18, 1);
    ply->AddAnimation("IdleRight", 27, 1);
    ply->tex->SetAnimation("IdleDown",true,false,0);
    return true;
}

GLint Scene::DrawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
    glLoadIdentity();

    glTranslated(0,0,-10.0);         //placing objects
    glPushMatrix();
        //ply->Actions();
        ply->DrawEntity();
    glPopMatrix();

    maze->DrawMaze();
}

GLvoid Scene::ResizeScene(GLsizei width, GLsizei height)
{
    GLfloat aspectRatio = (GLfloat) width/(GLfloat) height; //ratio for window mode
    glViewport(0,0,width,height); //setting viewport
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,aspectRatio,0.1,100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int Scene::WinMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {

        case WM_KEYDOWN:
            kBMs ->wParam = wParam;
            //kBMs->keyPressed(myModel); //Handling model movement
            //kBMs->keyEnv(plx, 0.005);
            kBMs->KeyPressed();
            break;

        case WM_KEYUP:
            kBMs->wParam = wParam;
            kBMs->KeyReleased();
            break;

        case WM_LBUTTONDOWN:
            //kBMs ->wParam = wParam;
            //kBMs->mouseEventDown(myModel,LOWORD(lParam),HIWORD(lParam));
            break;

        case WM_RBUTTONDOWN:
            //kBMs ->wParam = wParam;
            //kBMs->mouseEventDown(myModel,LOWORD(lParam),HIWORD(lParam));
            break;

        case WM_MBUTTONDOWN:
            //kBMs ->wParam = wParam;
            //kBMs->mouseEventDown(myModel,LOWORD(lParam),HIWORD(lParam));
            break;

        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
            //kBMs ->wParam = wParam;
            //kBMs->mouseEventUp();
            break;

        case WM_MOUSEMOVE:
            //kBMs ->mouseMove(myModel,LOWORD(lParam),HIWORD(lParam));
            break;

        case WM_MOUSEWHEEL:
            break;
    }
}
