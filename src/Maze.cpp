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
    roomPieces = new Texture();
    //westWall = new Texture();
    //southWall = new Texture();
    //eastWall = new Texture();
    //northWall = new Texture();
    //floor = new Texture();

    displayPieces->CreateTexture("images/RL_MapPieces.png", 4,4);
    roomPieces->CreateTexture("images/RL_TopDown.png",4,2);
    //westWall->CreateTexture("images/RL_WestWall.png", 1, 1,0.0,0.0);
    //southWall->CreateTexture("images/RL_SouthWall.png", 1, 2,0.5,0.0);
    //eastWall->CreateTexture("images/RL_EastWall.png", 1, 1,1.0,0.0);
    //northWall->CreateTexture("images/RL_NorthWall.png", 1, 2,0.5,0.0);
    //floor->CreateTexture("images/RL_Floor.png", 1, 1,0.5,0.0);

    mazeSizeX = x;
    mazeSizeY = y;
    mazeSize = x*y;

    mapScreenPosX = 0.5 + displayPieces->widthPercentage * mazeSizeX / 2;   //Where to put the map readout
    mapScreenPosY = 0.01;//displayPieces->heightPercentage * mazeSizeY;      //Where to put the map readout

    for(int i = 0; i< mazeSize; ++i)
    {
            room r;
            r.visited = false;
            r.walls = 15; //Bitfield 1=LeftWall, 2=SouthWall, 4=RightWall, 8=NorthWall
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
    plyLoc = rand() % mazeSize;
    maze[plyLoc].visited = true;
    PrintMaze(); //Draw maze in console
}

int Maze::GetNextDir(int curLoc)
{
    int validSelections=0;
    ipair curLocXY = IntToXY(curLoc);
    if(curLocXY.first - 1 >= 0) //West
    {
        int neightbor = XYtoInt(std::make_pair(curLocXY.first - 1,curLocXY.second));
        if(!maze[neightbor].visited) validSelections+=1;

    }
    if(curLocXY.first + 1 < mazeSizeX) //East
    {
        int neightbor = XYtoInt(std::make_pair(curLocXY.first + 1,curLocXY.second));
        if(!maze[neightbor].visited) validSelections+=4;
    }
    if(curLocXY.second - 1 >= 0) //North
    {
        int neightbor = XYtoInt(std::make_pair(curLocXY.first,curLocXY.second -1));
        if(!maze[neightbor].visited) validSelections+=8;
    }
    if(curLocXY.second + 1 < mazeSizeY) //South
    {
        int neightbor = XYtoInt(std::make_pair(curLocXY.first,curLocXY.second+1));
        if(!maze[neightbor].visited) validSelections+=2;

    }
    if(!validSelections) return -1;
    int proposedDir = 0;
    int proposedWall = 0;
    do
    {
        proposedDir = rand() % 4; //Select a number between 0-3
        proposedWall = 1 << proposedDir; //Turn it into a bitmask 1,2,4, or 8
    }while(!(validSelections & proposedWall));
    return proposedDir;
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

/*
void Maze::Moving(int dir)
{
    int localX = plyX % 1024;
    //std::cout << localX << std::endl;
    ipair cell = IntToXY(plyLoc);
    if(dir == 0) //Left
    {
        if(!(maze[plyLoc].walls & 1 && localX < 128))
        {
            plyX -= speed;
        }
    }
    else if(dir == 2) //Right
    {
        if(!(maze[plyLoc].walls & 4 && localX > 768))
        {
            plyX += speed;
        }
    }
    else if(dir == 1 && localX > 392 && localX < 576) //Down
    {
        if(!(maze[plyLoc].walls & 2))
        {
            std::cout << "Move Down" << std::endl;
            cell.second += 1;
        }
    }
    else if(dir == 3 && localX > 392 && localX < 576) //Up
    {
        if(!(maze[plyLoc].walls & 8))
        {
            std::cout << "Move Up" << std::endl;
            cell.second -= 1;
        }
    }
    int cellX = plyX / 1024;
    plyLoc = XYtoInt(std::make_pair(cellX, cell.second));
    maze[plyLoc].visited = true;
    //std::cout << "PLYX: " << plyX << "PLYLOC: " << locX << std::endl;
}
*/

int Maze::XYtoInt(ipair ip)
{
    return(ip.second * mazeSizeX + ip.first);
}

ipair Maze::IntToXY(int i)
{
    return std::make_pair(i%mazeSizeX, i/mazeSizeX);
}

/*
void Maze::PrepareToDrawMaze()
{
    //std::cout << plyLoc << std::endl;
    instantaniousXY = IntToXY(plyLoc);
}
*/

void Maze::DrawMazeDisplay()
{
    //glPushMatrix();
    displayPieces->TextureBinder();
    for(int i = 0; i < maze.size(); ++i)
    {
        if(maze[i].visited)
        {
            displayPieces->curFrame = maze[i].walls;
            ipair pos = IntToXY(i);
            float locX = mapScreenPosX + displayPieces->widthPercentage*pos.first*2;
            float locY = mapScreenPosY + displayPieces->heightPercentage*pos.second*2;

            displayPieces->Draw(locX,locY,2.0,2.0);
            if(i == plyLoc)
            {
                displayPieces->curFrame = 15;
                displayPieces->Draw(locX,locY,2.0,2.0);
            }
        }
    }
    //glPopMatrix();
}

void Maze::Rotate(int dir)
{
    //This code rotates the rightmost 4 bits by n
    //& 0xF ensures the all bits but the last 4 are reset to 0s
    //int n = 1;
    //if(dir == 1) //Clockwise
    //    test = ((test >> n) | (test << (4-n))) & 0xF;
    //else//Counterclockwise
    //    test = ((test << n) | (test >> (4-n))) & 0xF;
    //std::cout << "Test " << test << std::endl;
    int N = mazeSizeX;
    for(int x = 0; x < N / 2; ++x)
    {
        for(int y = x; y < N-x-1; ++y)
        {
            int first = XYtoInt(std::make_pair(x,y));
            int second = XYtoInt(std::make_pair(y,N-1-x));
            int third = XYtoInt(std::make_pair(N-1-x,N-1-y));
            int forth = XYtoInt(std::make_pair(N-1-y,x));
            if(dir == 1)
            {
                room temp = maze[first];
                maze[first] = maze[second];
                maze[second] = maze[third];
                maze[third] = maze[forth];
                maze[forth] = temp;
                maze[first].walls = ((maze[first].walls >> 1) | (maze[first].walls << (3))) & 0xF;
                maze[second].walls = ((maze[second].walls >> 1) | (maze[second].walls << (3))) & 0xF;
                maze[third].walls = ((maze[third].walls >> 1) | (maze[third].walls << (3))) & 0xF;
                maze[forth].walls = ((maze[forth].walls >> 1) | (maze[forth].walls << (3))) & 0xF;
            }
            else if(dir == -1)
            {
                room temp = maze[forth];
                maze[forth] = maze[third];
                maze[third] = maze[second];
                maze[second] = maze[first];
                maze[first] = temp;
                maze[first].walls = ((maze[first].walls << 1) | (maze[first].walls >> (3))) & 0xF;
                maze[second].walls = ((maze[second].walls << 1) | (maze[second].walls >> (3))) & 0xF;
                maze[third].walls = ((maze[third].walls << 1) | (maze[third].walls >> (3))) & 0xF;
                maze[forth].walls = ((maze[forth].walls << 1) | (maze[forth].walls >> (3))) & 0xF;
            }
        }
    }
    if(mazeSize % 2)
    {
        int i = (mazeSize - 1) / 2;
        std::cout << "i: " << i << std::endl;
        if(dir == 1) maze[i].walls = ((maze[i].walls >> 1) | (maze[i].walls << (3))) & 0xF;
        else if(dir == -1) maze[i].walls = ((maze[i].walls << 1) | (maze[i].walls >> (3))) & 0xF;
    }
}

void Maze::DrawRoom()
{
    int cells = 7;
    roomPieces->TextureBinder();
    for(int y = 0; y < cells; ++y)
    {
        for(int x = 0; x < cells; ++x)
        {
            bool mirror = false;
            bool flip = false;
            int curFrame = 7;
            if(x == 0)
            {
                curFrame = 1;
                if(y == 3 && !(maze[plyLoc].walls & 1)) curFrame = 3;
            }
            else if(x == cells-1)
            {
                curFrame = 1;
                mirror = true;
                if(y == 3 && !(maze[plyLoc].walls & 4)) curFrame = 3;
            }

            if(y == 0)
            {
                curFrame = 0;
                if(x == 0 || x == cells-1) curFrame = 6;
                else if(x == 3 && !(maze[plyLoc].walls & 8)) curFrame = 2;
            }
            else if(y == cells-1)
            {
                curFrame = 0;
                flip = true;
                if(x == 0 || x == cells-1) curFrame = 6;
                else if(x == 3 && !(maze[plyLoc].walls & 2)) curFrame = 2;
            }
            roomPieces->curFrame = curFrame;
            roomPieces->Draw(x*roomPieces->widthPercentage,y*roomPieces->heightPercentage,1.0,1.0,mirror, flip);
        }
    }
}
/*
void Maze::DrawMazeBG()
{

    northWall->curFrame = !((maze[plyLoc].walls & 8) >> 3); //Create a 1 or 0 for north door present or not
    //float modifier = (plyX - (instantaniousXY.first * northWall->width)) / (float)defaultScreenSizeX;
    //float startX = 0.5 - modifier;
    glPushMatrix();
        northWall->TextureBinder();
        //northWall->Draw(startX,0);
        northWall->Draw(0.5,0);
    //glPopMatrix();
    //glPushMatrix();
        floor->TextureBinder();
        //floor->Draw(startX,northWall->heightPercentage);
        floor->Draw(0.5,northWall->heightPercentage);
            if(maze[plyLoc].walls & 1) //West Wall exists
    {
        //glPushMatrix();
            westWall->TextureBinder();
            //westWall->Draw(startX,0);
            westWall->Draw(0.233,0);
        //glPopMatrix();
    }
    if(maze[plyLoc].walls & 4) //East Wall exists
    {
        //glPushMatrix();
            eastWall->TextureBinder();
            //eastWall->Draw(startX+eastWall->widthPercentage*7,0);
            eastWall->Draw(0.766,0);
        //glPopMatrix();
    }
    glPopMatrix();
}

void Maze::DrawMazeFG()
{
    glPushMatrix();
    southWall->curFrame = !((maze[plyLoc].walls & 2) >> 1); //Create a 1 or 0 for south door present or not
    //float modifier = (plyX - (instantaniousXY.first * northWall->width)) / (float)defaultScreenSizeX;
    //float startX = 0.5 - modifier;
    //glPushMatrix();
        southWall->TextureBinder();
        //southWall->Draw(startX,northWall->heightPercentage + southWall->heightPercentage);
        southWall->Draw(0.5,northWall->heightPercentage + southWall->heightPercentage);
    glPopMatrix();
}
*/
int Maze::GetRoomWalls()
{
    return maze[plyLoc].walls;
}


std::string Maze::checkWallCollision(fpair loc)
{
    std::cout << "PLYLOC: " << plyLoc << " WALLS " << maze[plyLoc].walls << " XY: " << loc.first << ", " << loc.second << std::endl;
    float westBase = 0.07;
    float northBase = 0.03;
    float eastBase = 0.4;
    float southBase = 0.65;

    int onDoorFlag = 0;

    if(loc.second > 0.32 && loc.second < 0.38)
    {
        if(!(maze[plyLoc].walls & 1))
        {
            westBase = 0.03;
            onDoorFlag +=1;
        }
        if(!(maze[plyLoc].walls & 4))
        {
            eastBase = 0.44;
            onDoorFlag +=4;
        }
    }
    if(loc.first > 0.22 && loc.first < 0.26)
    {
        if(!(maze[plyLoc].walls & 2))
        {
            southBase = 0.7;
            onDoorFlag +=2;
        }
        if(!(maze[plyLoc].walls & 8))
        {
            northBase = 0.01;
            onDoorFlag +=8;
        }
    }

    if(loc.first < westBase)
    {
        if(onDoorFlag & 1) return "TRANS_W";
        return "COLL_W";
    }
    if(loc.first > eastBase)
    {
        if(onDoorFlag & 4) return "TRANS_E";
        return "COLL_E";
    }
    if(loc.second < northBase)
    {
        if(onDoorFlag & 8) return "TRANS_N";
        return "COLL_N";
    }
    if(loc.second > southBase)
    {
        if(onDoorFlag & 2) return "TRANS_S";
        return "COLL_S";
    }
    return "COLL_NONE";
}

void Maze::movePlayer(std::string dir)
{
    if(dir == "N") plyLoc -= mazeSizeX;
    else if(dir == "S") plyLoc += mazeSizeX;
    else if(dir == "W") plyLoc--;
    else if(dir == "E") plyLoc++;
    maze[plyLoc].visited = true;
}
