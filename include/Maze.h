#ifndef MAZE_H
#define MAZE_H

#include<vector>
#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<stack>
#include<utility>
#include<Texture.h>

typedef struct{
    bool visited;
    unsigned short walls; //0=None, 1=West, 2=South, 3=W&S, 4=East, 5=W&E, 6=S&E, 7=W&S&E, 8=North, 9=W&N, 10=S&N, 11=W&S&N, 12=E&N, 13=W&E&N, 14=S&E&N, 15=ALL
    //Texture* tex;
} room;

typedef std::pair<int,int> ipair;



class Maze
{
    public:
        Maze();
        virtual ~Maze();

        void GenerateMaze(int, int);
        int GetNextDir(int);
        int GetNeighbor(int,int);
        void PrintMaze();

        void Moving(int dir);

        void PrepareToDrawMaze();
        void DrawMazeDisplay();
        void DrawMazeBG();
        void DrawMazeFG();
        int XYtoInt(ipair);
        ipair IntToXY(int);

        //int WallBits[4] = {1,2,4,8};
        int oppWallBits[4] = {4,8,1,2};

        int mazeSizeX, mazeSizeY, mazeSize; //# of cells in X, Y and total;
        int plyLoc; //The index value of the cell player is in
        int plyX; //Total number of pixel moved along the x axis
        int speed; //The number of pixels player moves per step
        std::vector<room> maze;

        Texture* displayPieces;
        Texture* westWall;
        Texture* southWall;
        Texture* eastWall;
        Texture* northWall;
        Texture* floor;

        float mapScreenPosX; //Where to draw the map screen
        float mapScreenPosY; //Where to draw the map screen
        ipair instantaniousXY;//The X and Y index of the cell the player is currently in


        //Testing a mechanic - Can be removed
        void Rotate(int);

    protected:

    private:

};

#endif // MAZE_H