#include "Level.h"

Level::Level(std::stack<Scene*>* s)
{
    //timer = new Timer;
    sceneStack = s;
    //ctor
    mon = new Monster();
    ply = new Player();
    maze = new Maze();
    popup = new Popup;
    //btns = new Buttons();
    kBMs = new Inputs(timer);
    kBMs->SetPlayer(ply);
    kBMs->SetMonster(mon);
    kBMs->SetMaze(maze);
    kBMs->SetBtns(popup->btns);
    //question = new Texture();

}

Level::~Level()
{
    //dtor
}

//Initialize this scene
//Must be called before all other functions
void Level::Init(int screenWidth, int screenHeight)
{
    ply->Init("images/prof.png", 9, 4);
    mon->Init("images/vampire.png", 12, 8);
    ply->PositionEntity(std::make_pair(0.2, 0.2));
    mon->PositionEntity(std::make_pair(0.1, 0.6));
    maze->GenerateMaze(9,9);
    popup->Init(screenWidth, screenHeight);
    //btns->Init("images/RL_Buttons_1024.png", 4, 8);
    //btns->AddButton("Accept", ACCEPT, 0.4, 0.33, false, screenWidth, screenHeight);
    //btns->AddButton("Decline", DECLINE, 0.6, 0.33, false, screenWidth, screenHeight);
    //question->CreateTexture("images/RL_Exit.png",1,1,0.5,0.0);
    //timer->Start();
}

//Draw this scene to the screen
void Level::Draw()
{
    fpair newXY = ply->GetNextXY();
    fpair newMXY = mon->MGetNextXY(newXY);
    std::string coll = maze->checkWallCollision(newXY);
    std::string enemyColl = maze->checkWallCollision(newMXY);
    std::string enemyPlayerColl = mon->EnemyCollisionWithPlayer(newMXY, newXY);
    std::cout << coll << std::endl;
    if(coll == "COLL_NONE")
    {
        ply->PositionEntity(newXY);
    }

    if(enemyColl == "COLL_NONE")
    {
        mon->PositionEntity(newMXY);

    }
    //enemy collision with player
    if(enemyPlayerColl == "COLL_W_PLAYER")
    {
        std::cout << "YOU ARE DEAD..." << std::endl;
        //timer->Pause();
        //popup->SetActive(true);
    }

    if(coll.substr(0,5) == "TRANS")
    {
        std::string dir = coll.substr(6,1);
        std::cout << dir << std::endl;
        ply->Teleport(dir);
        mon->Teleport(dir);
        maze->movePlayer(dir);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
    glLoadIdentity();

    //Push and Pop Matrix Located inside DrawMaze()
    //maze->PrepareToDrawMaze();
    glPushMatrix();
    maze->DrawMazeDisplay();
    //maze->DrawMazeBG();
    maze->DrawRoom();

        //ply->PositionEntity(maze->GetRoomWalls());
    ply->DrawEntity();
    mon->DrawEntity();
    glPopMatrix();
    //maze->DrawMazeFG();
    if(timer->IsPaused())
    {
        popup->Draw(mouseX,mouseY);
    }
}

//Collect user inputs relevant to this scene and act on them
void Level::Action(std::string action)
{
    std::cout << action << std::endl;
    if(action == "KB_Esc" || action == "Decline") //Decline can only happen if paused
    {
        if(timer->IsPaused())
        {
            std::cout << "UNPAUSE" << std::endl;
            //btns->SetActive(false);
            popup->SetActive(false);
            timer->Resume();
        }
        else
        {
            std::cout << "PAUSE" << std::endl;
            timer->Pause();
            //btns->SetActive(true);
            popup->SetActive(true);
        }
    }
    else if(action == "Accept" || "KB_Enter")
    {
        sceneStack->pop();
    }
}
//Recalculate the button edges each time screen is resized
void Level::ScreenResized(int screenWidth, int screenHeight)
{
    popup->btns->CalculateBorders(screenWidth, screenHeight);
}
