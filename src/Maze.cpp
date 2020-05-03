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
    mazeFrame = new Texture();

    displayPieces->CreateTexture("images/RL_MapPieces.png", 4,5);
    roomPieces->CreateTexture("images/RL_TopDown.png",4,2);
    mazeFrame->CreateTexture("images/RL_frame.jpg",1,1,1,0);

    mazeSizeX = x;
    mazeSizeY = y;
    mazeSize = x*y;
    for(int i = 0; i < mazeSize; ++i) //For every space in the maze...
    {
        pathToPlayer.push_back(make_pair(INT_MAX,-1)); //Set up a path array with all max distance from player and not visited
    }

    mapScreenPosX = 0.5415;//0.5 + displayPieces->widthPercentage * mazeSizeX / 2;   //Where to put the map readout
    mapScreenPosY = 0.015;//displayPieces->heightPercentage * mazeSizeY;      //Where to put the map readout

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
    runDijkstra(false);
    SetExit();
    do
    {
        monsterLoc = rand() % mazeSize;
    }
    while(pathToPlayer[monsterLoc].first < 5);
    //plyLoc = 40;
    //exitLoc = rand() % 32;
    //ExitWall();

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
            if(maze[loc].walls & 2){
                if (loc == exitCell) {cout << "E";}     //Upper E = Wall underneath
                else {std::cout << "_";}
            }
            else if (loc == exitCell){cout << "e";}     //Lower e = no Wall underneath
            else {std::cout << " ";}

            if(maze[loc].walls & 4){ std::cout << "|";}else std::cout << " ";
        }
        std::cout << std::endl;
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


void Maze::DrawMazeDisplay()
{
    //glPushMatrix();
    mazeFrame->TextureBinder();
    mazeFrame->Draw(1,0);
    displayPieces->TextureBinder();
    for(int i = 0; i < maze.size(); ++i)
    {
        displayPieces->curFrame = maze[i].walls;
        ipair pos = IntToXY(i);
        float locX = mapScreenPosX + displayPieces->widthPercentage*pos.first;
        float locY = mapScreenPosY + displayPieces->heightPercentage*pos.second;
        if(maze[i].visited) displayPieces->Draw(locX,locY,1.0,1.0);
        //displayPieces->Draw(locX,locY,1.0,1.0);
        if(i == exitCell)
        {
            displayPieces->curFrame = 16;
            displayPieces->Draw(locX,locY,1.0,1.0);
        }
        else if(i == monsterLoc)
        {
            displayPieces->curFrame = 18;
            displayPieces->Draw(locX,locY,1.0,1.0);
        }
        if(i == plyLoc)
        {
            displayPieces->curFrame = 17;
            displayPieces->Draw(locX,locY,1.0,1.0);
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
            if(x == 0) //Left Row
            {
                curFrame = 1;
                if(y == 3 && !(maze[plyLoc].walls & 1)) curFrame = 3;
                if(exitD == "West"){
                        if(y == 3 && (plyLoc == exitCell)) curFrame = 5;
                }
            }
            else if(x == cells-1) //Right Row
            {
                curFrame = 1;
                mirror = true;
                if(y == 3 && !(maze[plyLoc].walls & 4)) curFrame = 3;
                if(exitD == "East"){
                        if(y == 3 && (plyLoc == exitCell)) curFrame = 5;
                }
            }

            if(y == 0)//top row
            {
                curFrame = 0;
                if(x == 0 || x == cells-1) curFrame = 6;
                else if(x == 3 && !(maze[plyLoc].walls & 8)) curFrame = 2;
                if(exitD == "North"){
                        if(x == 3 && (plyLoc == exitCell)) curFrame = 4;
                }
            }
            else if(y == cells-1)//Bottom row
            {
                curFrame = 0;
                flip = true;
                if(x == 0 || x == cells-1) curFrame = 6; //Bottom corners
                else if(x == 3 && !(maze[plyLoc].walls & 2)) curFrame = 2;//bottom middle
                if(exitD == "South"){
                        if(x == 3 && (plyLoc == exitCell)) curFrame = 4;
                }
            }
            roomPieces->curFrame = curFrame;
            roomPieces->Draw(x*roomPieces->widthPercentage,y*roomPieces->heightPercentage,1.0,1.0,mirror, flip);
        }
    }
}

int Maze::GetRoomWalls()
{
    return maze[plyLoc].walls;
}

void Maze::runDijkstra(bool debug)
{
    for(int i = 0; i < mazeSize; ++i) //For every space in the maze...
    {
        pathToPlayer[i] = make_pair(INT_MAX,-1); //Set up a path array with all max distance from player and not visited
    }
    priority_queue< ipair, vector <ipair>, greater<ipair> > pq; //Make a prioity queue that will priotitize low values
    pathToPlayer[plyLoc] = make_pair(0,plyLoc);	//Set the players spot to "no steps required to get here" and "came here from here"
    pq.push(make_pair(0,plyLoc));				//Push that same info to the priority queue
    while (!pq.empty())						//As long as something is in the queue we have not exhausted all options
    {
        int thisVert = pq.top().second;			//Get the location index you are at
        pq.pop();								//And pop this room from the queue
        //neighbors n = W->getAdjacent(thisVert);	//Get all square around this one
        if(debug) std::cout << "This vert is " << thisVert << std::endl;
        for(int i = 0; i < 4; ++i)				//Process each square
        {
            bool canPass = false;
            ipair neighborXY = IntToXY(thisVert); 											//get that squares info
            if(i==0 && !(maze[thisVert].walls & 1))
            {
                if(debug) std::cout << "Checking West" << std::endl;
                canPass = true;
                neighborXY.first -= 1;
            }
            else if(i==1 && !(maze[thisVert].walls & 2))
            {
                if(debug) std::cout << "Checking South" << std::endl;
                canPass = true;
                neighborXY.second += 1;
            }
            else if(i==2 && !(maze[thisVert].walls & 4))
            {
                if(debug) std::cout << "Checking East" << std::endl;
                canPass = true;
                neighborXY.first += 1;
            }
            else if(i==3 && !(maze[thisVert].walls & 8))
            {
                if(debug) std::cout << "Checking North" << std::endl;
                canPass = true;
                neighborXY.second -= 1;
            }
            if(canPass)
            {
                int neighbor = XYtoInt(neighborXY);
                if(debug) std::cout << "At " << neighbor << " whos distance value is " << pathToPlayer[neighbor].first << std::endl;
                if (pathToPlayer[neighbor].first > pathToPlayer[thisVert].first + 1)	//If the distance value stored there is greater than the path the current square + 1...
                {
                    pathToPlayer[neighbor].first = pathToPlayer[thisVert].first + 1;	//Update that squares distance value
                    pathToPlayer[neighbor].second = thisVert;							//Update that squares "came from" value to be the square we were just on
                    pq.push(make_pair(pathToPlayer[neighbor].first, neighbor));			//Push the new square to the queue to be processed
                    if(debug) std::cout << "Updated" << std::endl;
                }
            }
        }
        if(debug)
        {
            std::cout << "----------------------------------" << std::endl;
            PrintPathToPlayer();
            //std::string s;
            //cin >> s;
        }

    }
}

void Maze::PrintPathToPlayer()
{
    for(int y = 0; y < mazeSizeY; y++)
    {
        for(int x = 0; x < mazeSizeX; x++)
        {
            if(pathToPlayer[y*mazeSizeX + x].first == INT_MAX) std::cout << "X";
            else std::cout << pathToPlayer[y*mazeSizeX + x].first;
            std::cout << "\t";
        }
        std::cout << std::endl;
    }
}

std::string Maze::checkWallCollision(fpair loc)
{
    //std::cout << "PLYLOC: " << plyLoc << " WALLS " << maze[plyLoc].walls << " XY: " << loc.first << ", " << loc.second << std::endl;
    float westBase = 0.07;
    float northBase = 0.03;
    float eastBase = 0.4;
    float southBase = 0.65;

    int onDoorFlag = 0;
    int onExitFlag = 0;

    if(loc.second > 0.32 && loc.second < 0.38)
    {
        if(!(maze[plyLoc].walls & 1) || ((plyLoc == exitCell) && (exitD == "West")))
        {
            westBase = 0.03;
            onDoorFlag +=1;
        }
        if(!(maze[plyLoc].walls & 4) || ((plyLoc == exitCell) && (exitD == "East")))
        {
            eastBase = 0.44;
            onDoorFlag +=4;
        }
    }
    if(loc.first > 0.22 && loc.first < 0.26)
    {
        if(!(maze[plyLoc].walls & 2) || ((plyLoc == exitCell) && (exitD == "South")))
        {
            southBase = 0.7;
            onDoorFlag +=2;
        }
        if(!(maze[plyLoc].walls & 8) || ((plyLoc == exitCell) && (exitD == "North")))
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

void Maze::SetExit()
{
    int validCells[] = {0,1,2,3,4,5,6,7,8, 9,17, 18,26, 27,35, 36,44, 45,53, 54,62, 63,71, 72,73,74,75,76,77,78,79,80};
    exitCell = validCells[rand() % 30];
    while(pathToPlayer[exitCell].first < 5)
    {
        exitCell = validCells[rand() % 30];
    }

    if (exitCell > 71){
        exitD = "South";
    }
    else if (exitCell < 9){
        exitD = "North";
    }
    else if (exitCell%9 == 8){
        exitD = "East";
    }
    else{
        exitD = "West";
    }
}


