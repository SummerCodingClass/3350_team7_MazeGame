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

    int rows = 12;
  // source: https://www.asciiart.eu/art-and-design/mazes
    const char* maze[rows] = 
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

    
    jk_printMazeGeneral(position, maze, rows, defaultHeight, color);

    // for (int index = 0; index < 12; index++) {
    //     position.bot = defaultHeight - (index * 20);
    //     //position.left = 10;
    //     ggprint8b(&position, 16, color, maze1[index]);
    // }



}


void jk_printMaze2(Rect position, int defaultHeight, int color) 
{

    int rows = 27;
  // source: https://www.asciiart.eu/art-and-design/mazes
    const char* maze[rows] = 
    {
    
    "    ,-----------------------------.----------------------------------.",
    "|                             |                                  |    ",
    "|    .    .    ,---------     |     ------------------------.    |    ",
    "|    |    |    |              |                             |    |    ",
    "|    |    `----`--------------!    ,-------------------.    |    |    ",
    "|    |                             |                   |    |    |    ",
    "|    :--------------.--------------`----     ,---------:    |    |    ",
    "|    |              |                        |         |    |    |    ",
    "|    :---------     |    .    ,---------.    |    .    |    `----:    ",
    "|    |              |    |    |         |    |    |    |         |    ",
    "|    |     ---------!    |    :----     |    |    |    |    .    |    ",
    "|    |                   |    |         |    |    |    |    |    |    ",
    "|    `-------------------!    |     ----!    |    |    |    |    |    ",
    "|                             |              |    |    |    |    |    ",
    ":--------------.---------.    :--------------!    |    :----!    |    ",
    "|              |         |    |                   |    |         |    ",
    "|    .    .    |    .    |    |    ,--------------:    `----     |    ",
    "|    |    |    |    |    |    |    |              |              |    ",
    "|    |    |    `    |    |    |    |     ---------`---------.    |    ",
    "|    |    |         |    |    |    |                        |    |    ",
    "|    |    `---------`----!    |    |    ,---------.    .    |    |    ",
    "|    |                        |    |    |         |    |    |    |    ",
    "|    :---------.--------------:    |    |    .    |    |    |    |    ",
    "|    |         | X            |    |    |    |    |    |    |    |    ",
    "|    `    .    `---------     |    |    `----!    |    `----!    |    ",
    "|         |                   |    |              |              |    ",
    "`---------`-------------------!    `--------------`--------------!"
    
    };

    
    jk_printMazeGeneral(position, maze, rows, defaultHeight, color);


}


void jk_printMaze3(Rect position, int defaultHeight, int color) 
{

    int rows = 23;
  // source: https://www.asciiart.eu/art-and-design/mazes
    const char* maze[rows] = 
    {
    
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa   a",
    "8   8               8               8           8                   8   8",
    "8   8   aaaaaaaaa   8   aaaaa   aaaa8aaaa   aaaa8   aaaaa   aaaaa   8   8",
    "8               8       8   8           8           8   8   8       8   8",
    "8aaaaaaaa   a   8aaaaaaa8   8aaaaaaaa   8aaaa   a   8   8   8aaaaaaa8   8",
    "8       8   8               8           8   8   8   8   8           8   8",
    "8   a   8aaa8aaaaaaaa   a   8   aaaaaaaa8   8aaa8   8   8aaaaaaaa   8   8",
    "8   8               8   8   8       8           8           8       8   8",
    "8   8aaaaaaaaaaaa   8aaa8   8aaaa   8   aaaaa   8aaaaaaaa   8   aaaa8   8",
    "8           8       8   8       8   8       8           8   8           8",
    "8   aaaaa   8aaaa   8   8aaaa   8   8aaaaaaa8   a   a   8   8aaaaaaaaaaa8",
    "8       8       8   8   8       8       8       8   8   8       8       8",
    "8aaaaaaa8aaaa   8   8   8   aaaa8aaaa   8   aaaa8   8   8aaaa   8aaaa   8",
    "8           8   8           8       8   8       8   8       8           8",
    "8   aaaaa   8   8aaaaaaaa   8aaaa   8   8aaaa   8aaa8   aaaa8aaaaaaaa   8",
    "8   8       8           8           8       8   8   8               8   8",
    "8   8   aaaa8aaaa   a   8aaaa   aaaa8aaaa   8   8   8aaaaaaaaaaaa   8   8",
    "8   8           8   8   8   8   8           8               8   8       8",
    "8   8aaaaaaaa   8   8   8   8aaa8   8aaaaaaa8   aaaaaaaaa   8   8aaaaaaa8",
    "8   8       8   8   8           8           8   8       8               8",
    "8   8   aaaa8   8aaa8   aaaaa   8aaaaaaaa   8aaa8   a   8aaaaaaaa   a   8",
    "8   8                   8           8               8               8   8",
    "8   8aaaaaaaaaaaaaaaaaaa8aaaaaaaaaaa8aaaaaaaaaaaaaaa8aaaaaaaaaaaaaaa8aaa8",

    };

    
    jk_printMazeGeneral(position, maze, rows, defaultHeight, color);


}