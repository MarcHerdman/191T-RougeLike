#include "Scene.h"

Scene::Scene()
{
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    timer = new Timer();
    kBMs = new Inputs(timer);
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
    Init(screenWidth,screenHeight);
    timer->Start();
    return true;
}


GLint Scene::DrawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
    glLoadIdentity();
    Draw();
}

GLvoid Scene::ResizeScene(GLsizei width, GLsizei height)
{
    glViewport(0,0,width,height); //setting viewport
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,1,1,0); //Top Left is the origin point

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    ScreenResized(width, height);
}

int Scene::WinMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if(kBMs) kBMs->wParam = wParam;
    std::string action;         //Can't create variable in middle of switch. Good reason to use if\else
    //if(!(lParam & 0x40000000)) std::cout << "DOWN" << std::endl;
    switch(uMsg)
    {
        case WM_KEYDOWN:
            if(!timer->IsPaused() && !(lParam & 0x40000000)) kBMs->KeyPressed(); //ONLY RESPOND ONCE WHEN THE KEY IS FIRST PRESSED
            break;

        case WM_KEYUP:
            if(wParam == VK_ESCAPE) Action("KB_Esc");       //Escape is passed regardless of paused
            if(wParam == VK_RETURN) Action("KB_Enter");     //Enter is passed regardless of paused
            if(!timer->IsPaused())                          //Only pass other inputs if unpaused
            {
                if(kBMs) kBMs->KeyReleased();               //Pass Key Released to the Input
                if(wParam >= 'A' && wParam <= 'Z')
                {
                    char c = (char)(int)wParam;
                    std::string s = "KB_";
                    s+=c;
                    Action(s);
                }
            }
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
            kBMs->wParam = wParam;
            if(kBMs) action = kBMs->mouseEventUp();
            if(action != "") Action(action);
            break;

        case WM_MOUSEMOVE:
            //kBMs ->mouseMove(myModel,LOWORD(lParam),HIWORD(lParam));
            mouseX = LOWORD(lParam);
            mouseY = HIWORD(lParam);
            break;

        case WM_MOUSEWHEEL:
            break;
        }
}
