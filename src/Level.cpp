#include "Level.h"
//float a = 0.0;
Level::Level(std::stack<Scene*>* s)
{

    timer = new Timer;
    sceneStack = s;
    help = new HelpScreen(sceneStack);
    mon = new Monster();
    ply = new Player();
    maze = new Maze();
    popup = new Popup;
    sound = new Sound();
    square = new Square();
    shader = new Shader();
    alphaSquare = new Square();
    mask = new Stencil();
    kBMs = new Inputs(timer);
    kBMs->SetPlayer(ply);
    kBMs->SetMonster(mon);
    kBMs->SetMaze(maze);
    kBMs->SetBtns(popup->btns);
    kBMs->SetSound(sound);

    footstepSpacer = 0;
    maskRandomizer = 0.0;
    playerInMonsterRoom = false;
}

Level::~Level()
{
    //dtor
}

//Initialize this scene
//Must be called before all other functions
void Level::Init(int screenWidth, int screenHeight)
{
    help->Init(screenWidth,screenHeight);
    ply->Init("images/prof.png", 9, 4);
    mon->Init("images/vampire.png", 12, 8);
    ply->PositionEntity(std::make_pair(0.2, 0.2));
    mon->PositionEntity(std::make_pair(0.1, 0.6));
    maze->GenerateMaze(9,9);
    popup->Init(screenWidth, screenHeight);
    sound->initSounds();
    shader->initShader("vert.vs","frag.fs",shader->program);
    square->Init("images/noise.png");
    alphaSquare->Init("images/foghelper.png");
    mask->tex->CreateTexture("images/Idontwantatextureonthisobjectbutprogramkeepscrashing.png",1,1);
    sound->playMusic("sounds/Haunted.mp3");
    //btns->Init("images/RL_Buttons_1024.png", 4, 8);
    //btns->AddButton("Accept", ACCEPT, 0.4, 0.33, false, screenWidth, screenHeight);
    //btns->AddButton("Decline", DECLINE, 0.6, 0.33, false, screenWidth, screenHeight);
    //question->CreateTexture("images/RL_Exit.png",1,1,0.5,0.0);
    timer->Start();
}
void Level::CalculateChanges()
{
    maze->runDijkstra(false);
    fpair newXY = ply->GetNextXY();
    std::string coll = maze->checkWallCollision(newXY);
    if(maze->plyLoc == maze->monsterLoc)
    {
        if(!playerInMonsterRoom)//First frame they are together
        {
            mon->PositionEntity(make_pair(0.25,.25));
            playerInMonsterRoom = true;
        }
    }
    else
    {
        playerInMonsterRoom = false;
    }
    if(coll == "COLL_NONE")
    {
        ply->PositionEntity(newXY);
    }
    if(playerInMonsterRoom)
    {
        fpair newMXY = mon->MGetNextXY(newXY);
        std::string enemyColl = maze->checkWallCollision(newMXY);
        std::string enemyPlayerColl = mon->EnemyCollisionWithPlayer(newMXY, newXY);
        if(enemyColl == "COLL_NONE")
        {
            mon->PositionEntity(newMXY);
        }
        if(enemyPlayerColl == "COLL_W_PLAYER")
        {
            std::cout << "YOU ARE DEAD..." << std::endl;
            timer->Pause();
            popup->SetActive(true);
        }
    }
    else
    {
        if(mon->hasWaited > mon->waitInRoomTime)
        {
            maze->monsterLoc = maze->pathToPlayer[maze->monsterLoc].second;
            mon->hasWaited = 0;
        }
        else
        {
            mon->hasWaited++;
        }
    }
    if(coll.substr(0,5) == "TRANS")
    {
        std::string dir = coll.substr(6,1);
        //std::cout << dir << std::endl;
        if((maze->plyLoc == maze->exitCell) && (dir == maze->exitD.substr(0,1)))
        {
            NewLevel();                  //move to next level

        }
        else
        {
            ply->Teleport(dir);
            maze->movePlayer(dir);
        }
    }
        if(ply->movementFlag!=0){
            if (footstepSpacer == 0) {
            footstepSpacer =5;
            if(sound) sound->playSound("sounds/walking.mp3");
            }
            else {
                footstepSpacer--;
            }
    }
    maskRandomizer += 0.1;
}
//Draw this scene to the screen
void Level::Draw()
{
    if(!timer->IsPaused())
    {
        CalculateChanges();
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
    glLoadIdentity();
    glPushMatrix();
        maze->DrawMazeDisplay();
        maze->DrawRoom();

        ply->DrawEntity();
        if(playerInMonsterRoom) mon->DrawEntity();
    glPopMatrix();
    if(timer->IsPaused())
    {
        popup->Draw(mouseX,mouseY);
    }
    else
    {
        alphaSquare->DrawSquare(0,0,2,2);

        glPushMatrix();
            mask->drawMask();
        glPopMatrix();

        glUseProgram(shader->program);
        GLuint loc = glGetUniformLocation(shader->program,"iTime");

        if(loc != -1)
        {
            glUniform1f(loc, maskRandomizer);
        }
        square->DrawSquare(-1,-.75,5,5);
        glRotated(90,0,0,1);
        square->DrawSquare(-1,-.75,5,5);
        glUseProgram(0);
        mask->disableBuffer();
    }
}

//Collect user inputs relevant to this scene and act on them
void Level::Action(std::string action)
{
    std::cout << "Action: "  << action << std::endl;
    if(action == "KB_Esc" || action == "Decline") //Decline can only happen if paused
    {
        if(timer->IsPaused())
        {
            std::cout << "UNPAUSE" << std::endl;
            //btns->SetActive(false);

            popup->SetActive(false);
            sound->resumeMusic();

            timer->Resume();
        }
        else
        {
            std::cout << "PAUSE" << std::endl;
            timer->Pause();
            sound->pauseMusic();
            //btns->SetActive(true);
            popup->SetActive(true);
        }
    }
    else if(action == "Accept" || action == "KB_Enter")
    {
        sceneStack->pop();
    }
    else if(action == "InGameHelp")
    {
        std::cout << "In Help" << std::endl;
        sceneStack->push(help);
    }
}
//Recalculate the button edges each time screen is resized
void Level::ScreenResized(int screenWidth, int screenHeight)
{
    popup->btns->CalculateBorders(screenWidth, screenHeight);
}
void Level::NewLevel()
{
    delete maze;
    maze = new Maze();
    maze->GenerateMaze(9,9);
    ply->Teleport("M");
}
