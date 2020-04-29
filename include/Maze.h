//randomly generated maze, display minimap and draw rooms

#ifndef MAZE_H
#define MAZE_H

#include<vector>
#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<stack>
#include<utility>
#include<Texture.h>
#include<Util.h>
#include<bits/stdc++.h>

//using namespace std;

//abstract type to hold all info about a room
typedef struct{
    bool visited;
    unsigned short walls; //0=None, 1=West, 2=South, 3=W&S, 4=East, 5=W&E, 6=S&E, 7=W&S&E, 8=North, 9=W&N, 10=S&N, 11=W&S&N, 12=E&N, 13=W&E&N, 14=S&E&N, 15=ALL
    //Texture* tex;
} room;

//Define a simple ipair <-Move to the Util class
typedef std::pair<int,int> ipair;


class Maze
{
    public:
        Maze();
        virtual ~Maze();

        void GenerateMaze(int, int);        //Backtracking maze generating algorithm
        int GetNextDir(int);                //Supports maze generation
        int GetNeighbor(int,int);           //Supports maze generation
        void PrintMaze();                   //Printout of maze to the console

        //void Moving(int dir);

        //void PrepareToDrawMaze();
        void DrawMazeDisplay();             //Draw the minimap
        void DrawRoom();
        void DrawMazeBG();                  //Draw all things behind the player
        void DrawMazeFG();                  //Draw all things in front of the player

        std::string checkWallCollision(fpair);
        void movePlayer(std::string);

        int XYtoInt(ipair);                 //Convert X,Y to single array index     <-Move to Util class
        ipair IntToXY(int);                 //Convert single array index to X, Y    <-Move to Util class

        int GetRoomWalls();

        //int WallBits[4] = {1,2,4,8};
        int oppWallBits[4] = {4,8,1,2};     //The opposing room walls

        int mazeSizeX, mazeSizeY, mazeSize; //# of cells in X, Y and total;
        int plyLoc;                         //The index value of the cell player is in
        int exitLoc;                        // roll random number for exit location generation
        int exitCell;                       //Index value of the cell the exit will be generated in
        std::string exitD;                       // direction of exit in it's cell (N,E,S,W)
        int plyX;                           //Total number of pixel moved along the x axis
        int speed;                          //The number of pixels player moves per step

        std::vector<room> maze;             //The maze

        Texture* displayPieces;             //Textures for the minimap
        Texture* roomPieces;
        //Texture* westWall;                  //Textures for the room display
        //Texture* southWall;                 // ""                  ""
        //Texture* eastWall;                  // ""                  ""
        //Texture* northWall;                 // ""                  ""
        //Texture* floor;                     // ""                  ""

        float mapScreenPosX;                //Where to draw the map screen
        float mapScreenPosY;                //Where to draw the map screen
        //ipair instantaniousXY;              //The X and Y index of the cell the player is currently in

        void Rotate(int);                   //Rotate the maze

        void SetExit();                  //Generate exit location for this maze
        void ExitWall();

    protected:

    private:

};

#endif // MAZE_H
