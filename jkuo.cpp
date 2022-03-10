//Author: Jennifer K
//Individual Source File for Project


#include "fonts.h"
#include <iostream>
using namespace std;

// don't write classes yet

void jk_PrintMsg() 
{
    cout << endl << endl;
    cout << "Hello!" << endl;
    cout << "Each of the following msgs came from a member's file:" << endl;
    cout << endl;
    cout << "Test message from jk" << endl;
}



Rect jk_createRect(int yres, int height, int left, int center) 
{
    Rect results;
    results.bot = yres - height;
    results.left = left;
    results.center = center;

    return results;
}


// void jk_printMaze(const char* maze, int rows, int color, Rect position, 
//                      int defaultHeight) {
//     for (int index = 0; index < rows; index++) {
//         position.bot = defaultHeight - (rows * 20);
//         //position.left = 10;
//         ggprint8b(&position, 16, color, maze[index][1]);
//     }

// }



void jk_printMazeGeneral(Rect position, const char* maze[], int rows, 
                                                int defaultHeight, int color) 
{

        for (int index = 0; index < rows; index++) {
                position.bot = defaultHeight - (index * 20);
                ggprint8b(&position, 16, color, maze[index]);
            }

}

void jk_printMaze1(Rect position, int defaultHeight, int color) 
{


  // source: https://www.asciiart.eu/art-and-design/mazes
    const char* maze1[12] = 
    {
    
     "___________________________________  " ,
     "| _____ |   | ___ | ___ ___ | |   | |" ,
     "| |   | |_| |__ | |_| __|____ | | | |" ,
     "| | | |_________|__ |______ |___|_| |" ,
     "| |_|   | _______ |______ |   | ____|" ,
     "| ___ | |____ | |______ | |_| |____ |" ,
     "|___|_|____ | |   ___ | |________ | |" ,
     "|   ________| | |__ | |______ | | | |" ,
     "| | | ________| | __|____ | | | __| |" ,
     "|_| |__ |   | __|__ | ____| | |_| __|" ,
     "|   ____| | |____ | |__ |   |__ |__ |" ,
     "| |_______|_______|___|___|___|_____|"
    
    };

    
    jk_printMazeGeneral(position, maze1, 12, defaultHeight, color);

    // for (int index = 0; index < 12; index++) {
    //     position.bot = defaultHeight - (index * 20);
    //     //position.left = 10;
    //     ggprint8b(&position, 16, color, maze1[index]);
    // }



}
