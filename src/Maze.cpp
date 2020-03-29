#include "Maze.h"

Maze::Maze()
{
    //ctor
    srand (time(NULL));
    plyLoc = 0;
    plyX = 512;
    speed = 8;
}

Maze::~Maze()
{
    //dtor
}

void Maze::GenerateMaze(int x, int y)
{
    displayPieces = new Texture();
    westWall = new Texture();
    southWall = new Texture();
    eastWall = new Texture();
    northWall = new Texture();
    floor = new Texture();

    displayPieces->CreateTexture("images/RL_MapPieces.png", 4,4);
    westWall->CreateTexture("images/RL_WestWall.png", 1, 1);
    southWall->CreateTexture("images/RL_SouthWall.png", 1, 2);
    eastWall->CreateTexture("images/RL_EastWall.png", 1, 1);
    northWall->CreateTexture("images/RL_NorthWall.png", 1, 2);
    floor->CreateTexture("images/RL_Floor.png", 1, 1);

    mazeSizeX = x;
    mazeSizeY = y;
    mazeSize = x*y;

    mapScreenPosX = 0.5 - displayPieces->widthPercentage * mazeSizeX / 2;
    mapScreenPosY = 1.0 - displayPieces->heightPercentage * mazeSizeY;

    for(int i = 0; i< mazeSize; ++i)
    {
            room r;
            r.visited = false;
            r.walls = 15; //Bitfield 1=LeftWall, 2=SouthWall, 4=RightWall, 8=NorthWall
            //r.tex = new Texture();
            //r.tex->CreateTexture("images/MazeWalls.png", 4, 4);
            maze.push_back(r);
    }
    std::stack<int> progress; //Stack up rooms as we traverse to allow backtracking
    int start = rand() % mazeSize; //Pick a random room to start in
    maze[start].visited = true; //Mark that room as visited
    progress.push(start); //Add the start room to the stack
    while(!progress.empty()) //Keep searching until all room have no valid paths
    {
        int dir = GetNextDir(progress.top()); //Decide on a direction to go
        if(dir == -1) //If no valid directions...
        {
            progress.pop();//...Remove this room from the stack
        }
        else
        {
            maze[progress.top()].walls = maze[progress.top()].walls ^ (1 << dir);//Break the wall in the direction we want to go
            int newRoom = GetNeighbor(progress.top(),dir); //Get the location of the next room
            maze[newRoom].visited = true; //Mark the next room as visited
            int knockWall = oppWallBits[dir]; //Get the bit# of the adjoining wall in the new room
            maze[newRoom].walls = maze[newRoom].walls ^ knockWall; //Knock down the adjoing wall
            progress.push(newRoom); //Push the new room to the stack
        }
    }
    for(int i = 0; i < maze.size(); ++i)
    {
        maze[i].visited=false;
    }
    PrintMaze(); //Draw maze in console
}

int Maze::GetNextDir(int curLoc)
{
    unsigned short thisRoomWalls = maze[curLoc].walls; //Get the walls as they stand now
    ipair thisRoom = IntToXY(curLoc); //Get X Y coords for this room

    //Remove ability to pick wall that leads to visited room or out of maze
    if(thisRoom.first > 0) //Not against west edge
    {
        int westNeighbor = XYtoInt(std::make_pair(thisRoom.first - 1, thisRoom.second));
        if(maze[westNeighbor].visited) //West neighbor has been visited
        {
            thisRoomWalls = thisRoomWalls & ~1; //Remove ability to pick west wall
        }
    }
    else //Against west edge
    {
        thisRoomWalls = thisRoomWalls & ~1; //Remove ability to pick west wall
    }

    if(thisRoom.first < mazeSizeX-1) //Not against east edge
    {
        int eastNeighbor = XYtoInt(std::make_pair(thisRoom.first + 1, thisRoom.second));
        if(maze[eastNeighbor].visited) //East neighbor has been visited
        {
            thisRoomWalls = thisRoomWalls & ~4; //Remove ability to pick east wall
        }
    }
    else //Against west edge
    {
        thisRoomWalls = thisRoomWalls & ~4; //Remove ability to pick east wall
    }

    if(thisRoom.second > 0) //Not against north edge
    {
        int northNeighbor = XYtoInt(std::make_pair(thisRoom.first, thisRoom.second - 1));
        if(maze[northNeighbor].visited) //North neighbor has been visited
        {
            thisRoomWalls = thisRoomWalls & ~8; //Remove ability to pick west wall
        }
    }
    else //Against north edge
    {
        thisRoomWalls = thisRoomWalls & ~8; //Remove ability to pick north wall
    }

    if(thisRoom.second < mazeSizeY-1) //Not against south edge
    {
        int southNeighbor = XYtoInt(std::make_pair(thisRoom.first, thisRoom.second + 1));
        if(maze[southNeighbor].visited) //South neighbor has been visited
        {
            thisRoomWalls = thisRoomWalls & ~2; //Remove ability to pick east wall
        }
    }
    else //Against south edge
    {
        thisRoomWalls = thisRoomWalls & ~2; //Remove ability to pick south wall
    }

    if(thisRoomWalls == 0) return -1; //No valid options so return -1

    unsigned short proposedDir;
    unsigned short proposedWall;
    do //While the prosed wall to remove is not valid for this room keep trying.
    {
        proposedDir = rand() % 4; //Select a number between 0-3
        proposedWall = 1 << proposedDir; //Turn it into a bitmask 1,2,4, or 8
    }while(!(thisRoomWalls & proposedWall));
    return (int)proposedDir;
}

int Maze::GetNeighbor(int curLoc, int dir)
{
    if(dir == 0) //West
    {
        return curLoc - 1;
    }
    else if(dir == 1) //South
    {
        return curLoc + mazeSizeX;
    }
    else if(dir == 2) //East
    {
        return curLoc + 1;
    }
    else if(dir == 3) //North
    {
        return curLoc - mazeSizeX;
    }
}

void Maze::PrintMaze()
{
    std::cout << " ";
    for(int i = 0; i < mazeSizeX; ++i)
    {
        std::cout << "_ ";
    }
    std::cout << std::endl;
    for(int y = 0; y < mazeSizeY; ++y)
    {
        std::cout << "|";
        for(int x = 0; x < mazeSizeX; ++x)
        {
            int loc = XYtoInt(std::make_pair(x,y));
            if(maze[loc].walls & 2){ std::cout << "_";} else std::cout << " ";
            if(maze[loc].walls & 4){ std::cout << "|";} else std::cout << " ";
        }
        std::cout << std::endl;
    }
}


void Maze::Moving(int dir)
{
    if(dir == 0) plyX -= speed;
    else if(dir == 2) plyX += speed;
    int locX = plyX / 1024;
    ipair loc = IntToXY(plyLoc);
    plyLoc = XYtoInt(std::make_pair(locX, loc.second));
    //std::cout << "PLYX: " << plyX << "PLYLOC: " << locX << std::endl;
}


int Maze::XYtoInt(ipair ip)
{
    return(ip.second * mazeSizeX + ip.first);
}

ipair Maze::IntToXY(int i)
{
    return std::make_pair(i%mazeSizeX, i/mazeSizeX);
}

void Maze::PrepareToDraw()
{
    instantaniousXY = IntToXY(plyLoc);
}

void Maze::DrawMazeDisplay()
{
    displayPieces->TextureBinder();
    for(int i = 0; i < maze.size(); ++i)
    {
        displayPieces->curFrame = maze[i].walls;
        ipair pos = IntToXY(i);
        float locX = mapScreenPosX + displayPieces->widthPercentage*pos.first;
        float locY = mapScreenPosY + displayPieces->heightPercentage*pos.second;
        glPushMatrix();
            glTranslatef(locX,locY,0);
            displayPieces->Draw();
            if(i == plyLoc)
            {
                displayPieces->curFrame = 15;
                displayPieces->Draw();
            }
        glPopMatrix();
    }
}

void Maze::DrawMazeBG()
{
    northWall->TextureBinder();
    northWall->curFrame = !((maze[plyLoc].walls & 8) >> 3);
    //std::cout << "NW " << northWall->curFrame << std::endl;
    float modifier = (plyX - (instantaniousXY.first * northWall->width)) / 1920.0;
    //std::cout << "Base: " << base << std::endl;
    float startX = 0.5 - modifier;
    glPushMatrix();
        glTranslatef(startX,0,0);
        northWall->Draw();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(startX,northWall->heightPercentage,0);
        floor->TextureBinder();
        floor->Draw();
    glPopMatrix();
}

void Maze::testRotate(int dir)
{
    //This code rotates the rightmost 4 bits by n
    //& 0xF ensures the all bits but the last 4 are reset to 0s
    int n = 1;
    if(dir == 1) //Clockwise
        test = ((test >> n) | (test << (4-n))) & 0xF;
    else//Counterclockwise
        test = ((test << n) | (test >> (4-n))) & 0xF;
    std::cout << "Test " << test << std::endl;
}

void Maze::DrawMazeFG()
{
    southWall->curFrame = !((maze[plyLoc].walls & 2) >> 1);
    //std::cout << "SW " << southWall->curFrame << std::endl;

    ipair loc = IntToXY(plyLoc);
    float base = (plyX - (loc.first * southWall->width)) / 1920.0;
    float startX = 0.5 - base;
    if(maze[plyLoc].walls & 1) //West Wall exists
    {
        glPushMatrix();
            westWall->TextureBinder();
            glTranslatef(startX,0,0);
            westWall->Draw();
        glPopMatrix();
    }
    if(maze[plyLoc].walls & 4) //East Wall exists
    {
        glPushMatrix();
            eastWall->TextureBinder();
            glTranslatef(startX+eastWall->widthPercentage*7,0,0);
            eastWall->Draw();
        glPopMatrix();
    }
    glPushMatrix();
        glTranslatef(startX,northWall->heightPercentage + southWall->heightPercentage,0);
        southWall->TextureBinder();
        southWall->Draw();
    glPopMatrix();
}
