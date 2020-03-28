#include "Maze.h"

Maze::Maze()
{
    //ctor
    srand (time(NULL));
}

Maze::~Maze()
{
    //dtor
}

void Maze::GenerateMaze(int x, int y)
{
    mazeSizeX = x;
    mazeSizeY = y;
    mazeSize = x*y;
    for(int i = 0; i< mazeSize; ++i)
    {
            room r;
            r.visited = false;
            r.walls = 15; //Bitfield 1=LeftWall, 2=SouthWall, 4=RightWall, 8=NorthWall
            r.tex = new Texture();
            r.tex->CreateTexture("images/MazeWalls.png", 4, 4);
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
    SetMaze(); //Set room's texture to know what frame to display
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

void Maze::SetMaze()
{
    for(int i = 1; i < maze.size(); ++i)
    {
        maze[i].tex->curFrame = maze[i].walls;
    }
}

int Maze::XYtoInt(ipair ip)
{
    return(ip.second * mazeSizeX + ip.first);
}

ipair Maze::IntToXY(int i)
{
    return std::make_pair(i%mazeSizeX, i/mazeSizeX);
}

void Maze::DrawMaze()
{
    maze[0].tex->TextureBinder();
    glPushMatrix();
    for(int i = 0; i < maze.size(); ++i)
    {
        ipair pos = IntToXY(i);
        //glTranslatef(100+16*pos.first,100+16*pos.second,5.0);
        //glScalef(2.0,2.0,1.0);

        maze[i].tex->Draw();
    }
    glPopMatrix();
}
