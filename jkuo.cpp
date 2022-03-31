//Author: Jennifer K
//Individual Source File for Project


#include "fonts.h"
#include <iostream>
#include <cstring> //for strlen()
#include <GL/glx.h>
#include "GridCells.h"
#include "Grid.h"

// #include <windows.h>
using namespace std;
// extern class Global gl;

// don't write classes yet




//functions that need prototypes
int getColumns (const char** maze, int rows);












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





// void jk_printMazeGeneral(Rect position, const char* maze[], int rows, 
//                                                 int defaultHeight, int color) 
// {

//         for (int index = 0; index < rows; index++) {
//                 position.bot = defaultHeight - (index * 20);
//                 ggprint8b(&position, 16, color, maze[index]);
//             }

// }


void jk_printMazeGrid(Rect position, const char* maze[], int rows,
          int (&player)[2], int defaultHeight, int color, const char* mazeName) 
{   
    ggprint8b(&position, 16, color, mazeName);
    
    int columns = strlen(maze[0]);
    for (int i = 1; i < rows; i++) {
        if ((int)strlen(maze[i]) > columns) {
            columns = strlen(maze[i]);
        }
    }


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

            glColor3ub(200,50,50);
            // glColor3ub(20,20,20);
            
            if (maze[i][j] == ' ' || maze[i][j] == 'X') {
                glColor3ub(20,20,20);
            }
            
            if (i == player[1] && j == player[0]) {
                glColor3ub(255,250,250);
            }

            // i + 1 = down arrow key
            // if (i == player[1] + 1 && j == player[0]) { 
            //   glColor3ub(232,135,5); // orange // 
            // }

            // i - 1 = up arrow key
            // if (i == player[1] - 1 && j == player[0]) { 
            //   glColor3ub(232,135,5); // orange // 
            // }

            // j + 1 = right arrow key
            // if (i == player[1] && j == player[0] + 1) { 
            //     glColor3ub(232,135,5); // orange // 
            // }

          
            // j - 1 = left arrow key
            // if (i == player[1] && j == player[0] - 1) { 
            //     glColor3ub(232,135,5); // orange // 
            // }

            float w = 5.0f;
            glPushMatrix();
            glTranslatef(20+j*(w+1)*2, defaultHeight-50-i*(w+1)*2, 0);
            glBegin(GL_QUADS);
                glVertex2f(-w, -w);
                glVertex2f(-w,  w);
                glVertex2f( w,  w);
                glVertex2f( w, -w);
            glEnd();
            glPopMatrix();
       }
    }
}

void jk_printMaze1(Rect position, int defaultHeight, int color, 
                             int (&player)[2], bool &firstRun, Grid& mazeGrid)
{
    const char* mazeName = "Maze 1";
    int rows = 31;
    int startingPosition[2] = {1, 29};

    // source: https://www.asciiart.eu/art-and-design/mazes
    const char* maze[rows] = 
    {
    
        "+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+",
        "|        |        |                                            |",
        "+  +--+  +  +--+--+  +--+--+--+--+--+--+--+--+--+  +--+--+--+  +",
        "|     |     |        |     |     |              |     |        |",
        "+--+  +  +--+  +--+--+  +  +  +  +  +--+--+--+  +--+  +  +--+--+",
        "|     |  |     |        |     |  |        |  |  |     |     |  |",
        "+  +--+  +  +--+  +--+--+--+--+--+--+  +--+--+  +--+--+--+  +--+",
        "|  |     |  |  |  |              |  |  |     |        |  |     |",
        "+  +--+--+  +--+  +  +--+--+--+  +  +  +  +  +--+  +  +--+--+  +",
        "|        |  |     |     |     |  |  |     |     |  |           |",
        "+  +--+  +  +  +--+--+  +--+  +  +--+--+--+--+  +  +--+--+--+--+",
        "|  |     |  |        |     |  |              |  |           |  |",
        "+  +  +--+  +--+--+--+--+  +  +--+--+--+--+  +  +--+  +--+  +--+",
        "|  |  |                    |              |  |     |  |  |     |",
        "+  +  +  +--+--+--+--+--+--+--+  +--+--+  +- +--+  +  +  +--+  +",
        "|  |        |     |                    |  |     |  |     |     |",
        "+  +--+--+  +  +  +  +--+  +--+--+  +--+--+  +  +  +--+  +  +--+",
        "|  |        |  |  |     |        |  |        |  |  |  |  |     |",
        "+  +  +--+--+  +  +--+  +  +--+--+--+  +--+--+--+  +  +  +--+  +",
        "|  |  |        |     |  |     |     |           |  |     |  |  |",
        "+  +  +  +--+--+--+--+  +--+  +  +--+--+  +--+  +  +--+--+--+  +",
        "|  |                       |  |        |  |     |        |  |  |",
        "+  +  +--+--+--+--+  +--+--+--+--+  +  +--+  +--+--+--+  +--+  +",
        "|  |        |     |  |        |  |  |  |              |  |     |",
        "+--+--+--+  +  +  +  +  +--+  +--+  +--+  +--+  +--+--+  +  +--+",
        "|     |     |  |  |  |  |  |        |  |  |     |     |  |     |",
        "+  +--+  +--+  +  +  +  +--+--+--+--+--+  +  +--+  +  +  +--+--+",
        "|           |  |  |  |                 |  |  |     |  |        |",
        "+--+--+--+  +--+  +  +--+--+--+--+--+  +  +  +--+--+--+--+--+  +",
        " X                |                 |     |              |      ",
        "+-----+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+"
    
    };

    int columns = getColumns(maze, rows);

    if (firstRun) {
        player[0] = startingPosition[0]; // x
        player[1] = startingPosition[1]; // y
        // jk_printMazeGrid(position, maze, rows, player, defaultHeight, color, 
                                                            // mazeName);
        // Grid(rows, columns);
        // printGrid();
        cout << "before Grid";
        mazeGrid = Grid(maze, rows, columns, player);
        cout << "after Grid";
        mazeGrid.printGrid(position, rows, columns, player, defaultHeight, 
                                                               color, mazeName);

        firstRun = false;
    }
    
    else {
        // jk_printMazeGrid(position, maze, rows, player, defaultHeight, color, 
                                                          // mazeName);
        mazeGrid.printGrid(position, rows, columns, player, defaultHeight, 
                                                              color, mazeName);                                                          
    }
}


void jk_printMaze2(Rect position, int defaultHeight, int color, 
                                             int (&player)[2], bool& firstRun)
{
    const char* mazeName = "Maze 2";
    int rows = 27;
    int startingPosition[2] = {17, 23};

    
    // source: https://www.asciiart.eu/art-and-design/mazes
    const char* maze[rows] = 
    {
    
        ",-----------------------------.----------------------------------.",
        "|                             |                                  |",
        "|    .    .    ,---------     |     ------------------------.    |",
        "|    |    |    |              |                             |    |",
        "|    |    `----`--------------!    ,-------------------.    |    |",
        "|    |                             |                   |    |    |",
        "|    :--------------.--------------`----     ,---------:    |    |",
        "|    |              |                        |         |    |    |",
        "|    :---------     |    .    ,---------.    |    .    |    `----:",
        "|    |              |    |    |         |    |    |    |         |",
        "|    |     ---------!    |    :----     |    |    |    |    .    |",
        "|    |                   |    |         |    |    |    |    |    |",
        "|    `-------------------!    |     ----!    |    |    |    |    |",
        "|                             |              |    |    |    |    |",
        ":--------------.---------.    :--------------!    |    :----!    |",
        "|              |         |    |                   |    |         |",
        "|    .    .    |    .    |    |    ,--------------:    `----     |",
        "|    |    |    |    |    |    |    |              |              |",
        "|    |    |    `    |    |    |    |     ---------`---------.    |",
        "|    |    |         |    |    |    |                        |    |",
        "|    |    `---------`----!    |    |    ,---------.    .    |    |",
        "|    |                        |    |    |         |    |    |    |",
        "|    :---------.--------------:    |    |    .    |    |    |    |",
        "|    |         | X            |    |    |    |    |    |    |    |",
        "|    `    .    `---------     |    |    `----!    |    `----!    |",
        "|         |                   |    |              |              |",
        "`---------`-------------------!    `--------------`--------------!"
    
    };


     if (firstRun) {
        player[0] = startingPosition[0]; // x
        player[1] = startingPosition[1]; // y
        jk_printMazeGrid(position, maze, rows, player, defaultHeight, color, 
                                                                    mazeName);
        firstRun = false;
    }
    
    else {
        jk_printMazeGrid(position, maze, rows, player, defaultHeight, color, 
                                                                    mazeName);
    }


}


void jk_printMaze3(Rect position, int defaultHeight, int color, 
                                              int (&player)[2], bool& firstRun)
{
    const char* mazeName = "Maze 3";
    int rows = 23;
    int startingPosition[2] = {1, 22};


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

    
   if (firstRun) {
        player[0] = startingPosition[0]; // x
        player[1] = startingPosition[1]; // y
        jk_printMazeGrid(position, maze, rows, player, defaultHeight, color, 
                                                                   mazeName);
        firstRun = false;
    }
    
    else {
        jk_printMazeGrid(position, maze, rows, player, defaultHeight, color, 
                                                                    mazeName);
    }


}


void jk_page_transition(int& maze_state, const char* keyChecked, 
                                                               bool& firstRun) 
{
    //case XK_b;
    if (strcmp(keyChecked, "b") == 0) {
        if (maze_state == 0) {
            //do nothing
        } else if (maze_state > 230) {
            maze_state = 23;
        } else if (maze_state > 0) {
            maze_state = 0;
        }
        
        return;
    }

		//case XK_s;
    if (strcmp(keyChecked, "s") == 0) {
        if (maze_state == 0) {
            firstRun = true;
            maze_state = 1;
        } else if (maze_state == 1) {
            firstRun = true;
            maze_state = 2;
        } else if (maze_state == 2) {
            firstRun = true;
            maze_state = 3;
        } else if (maze_state == 3) {
            firstRun = true;
            maze_state = 0;
        } else if (maze_state == 23) {
            firstRun = true;
            maze_state = 231;
        } else if (maze_state == 231) {
            firstRun = true;
            maze_state = 232;
        } else if (maze_state == 232) {
            firstRun = true;
            maze_state = 233;
        } else if (maze_state == 233) {
            firstRun = true;
            maze_state = 23;
        }

        return; 
    }

    if (strcmp(keyChecked, "r") == 0) {
        if (maze_state == 0) {
            maze_state = 11;
        } else if(maze_state == 22) {
            maze_state = 23;
        }
        return; 
    }
    
    if (strcmp(keyChecked, "c") == 0) {
        if (maze_state == 0) {
            maze_state = 12;
        }
        return; 
    }

    if (strcmp(keyChecked, "q") == 0) {
        if(maze_state == 11 || maze_state == 12) {
            maze_state = 20;
        }
        return; 
    }

    if (strcmp(keyChecked, "w") == 0) {
        if(maze_state == 20) {
            maze_state = 21;
        }
        return; 
    }

    if (strcmp(keyChecked, "e") == 0) {
        if(maze_state == 21) {
            maze_state = 22;
        }
        return; 
    }


    // if (strcmp(keyChecked, "up") == 0) {
    //   if (maze_state == 1 || maze_state == 2 || maze_state == 3) {
        
    //   }
    // return; 
    // }


}


// void jk_printMaze4(Rect position, int defaultHeight, int color) 
// {
   
    
//     jk_printMazeGrid(position, maze, rows, defaultHeight, color, mazeName);
    
//     // jk_printMazeGeneral(position, maze, rows, defaultHeight, color);
    


// }




//----------------------------------------------------------------------------
// printing texts - general
//----------------------------------------------------------------------------

void jk_showCreditPage(Rect position, int defaultHeight, int color) 
{
    position.bot = defaultHeight;
    ggprint8b(&position, 16, color, "Jennifer Kuo:");
    ggprint8b(&position, 16, color, "Game Designer | Game Programmer");
}


void jk_showRulesPage(Rect position, int defaultHeight, int color) 
{
    position.bot = defaultHeight;
    ggprint8b(&position, 16, color, "Rule 1:");
    ggprint8b(&position, 16, color, 
                              "Timer will start immediately upon game start.");
}



void jk_showWelcomePage(Rect position, int defaultHeight, int color) 
{
    position.bot = defaultHeight;
  
    ggprint13(&position, 16, color, "------------ Instructions ------------");
}


//could be replaced by picture logo
void jk_showWelcomePageTitle(Rect position, int defaultHeight, int color) 
{
    position.bot = defaultHeight;
  
    ggprint40(&position, 16, color, "The MAze Game");
}





//----------------------------------------------------------------------------
// printing texts - secret page related
//----------------------------------------------------------------------------
void jk_showWelcomePage2(Rect position, int defaultHeight, int color) 
{
    position.bot = defaultHeight;
  
    ggprint8b(&position, 16, color, "how to enter secret mode:");
    ggprint8b(&position, 16, color, "under either rules page or credit page,");
    ggprint8b(&position, 16, color, "type qwer in order");
}

// test page
void jk_showSecretMode(Rect position, int defaultHeight, int color) 
{
    position.bot = defaultHeight;
  
    ggprint40(&position, 16, color, "Welcome to Secret Mode");
}

void jk_showSecretModeMessage(Rect position, int defaultHeight, int color) 
{
    position.bot = defaultHeight;
  
    ggprint13(&position, 48, color, "------------ Instructions ------------");
    ggprint8b(&position, 32, color, "press s to start games in FREELO MODE");
    ggprint8b(&position, 32, color, "press b to go back to the main page");
}
//----------------------------------------------------------------------------









//----------------------------------------------------------------------------
// helper functions for the maze
//----------------------------------------------------------------------------


//for secrete mode
void jk_playerMovementForSecretMode(char* keys, int (&player)[2]) 
{
    //player[0] = column = "j"
    //player[1] = row = "i"

    //up
    if (keys[XK_Up]) {
        player[1] = player[1] - 1;
    }

    //down
    if (keys[XK_Down]) {
        player[1] = player[1] + 1;
    }
  
    //left
    if (keys[XK_Left]) {
        player[0] = player[0] - 1;
    }

    //right
    if (keys[XK_Right]) {
        player[0] = player[0] + 1;
    }
}



void checkWall(int (&player)[2], int nextMove[2], Grid& grid) 
{
        int i = nextMove[1];
        int j = nextMove[0];
        
        vector <vector <GridCells>> tempGrid = grid.GridGetter();
       
        cout << "i: " << i << " j: " << j << endl;
        cout << "before isWall()." << endl;
        if ( tempGrid[i][j].isWall() ) {
            cout << "this is a wall" << endl;
            return;
            // do nothing, return player[2] as is
        }
        else {
            cout << "NOT a wall" << endl;
            cout << "before: " << player[0] << ", " << player[1] << endl;
            player[0] = nextMove[0];
            player[1] = nextMove[1];
            cout << "after: " << player[0] << ", " << player[1] << endl;
            return;
        }
}


//for normal mode
void jk_playerMovement(char* keys, int (&player)[2], Grid& grid) 
{
    //player[0] = column = "j"
    //player[1] = row = "i"

    // if (i == player[1] + 1 && j == player[0]) { 

    int nextMove[2];

    //up
    if (keys[XK_Up]) {
        nextMove[1] = player[1] - 1;
        nextMove[0] = player[0];
        checkWall(player, nextMove, grid);
       
    }

    //down
    if (keys[XK_Down]) {
        nextMove[1] = player[1] + 1;
        nextMove[0] = player[0];
        checkWall(player, nextMove, grid);
        
    }
  
    //left
    if (keys[XK_Left]) {
        nextMove[0] = player[0] - 1;
        nextMove[1] = player[1];
        checkWall(player, nextMove, grid);

    }

    //right
    if (keys[XK_Right]) {
        nextMove[0] = player[0] + 1;
        nextMove[1] = player[1];
        checkWall(player, nextMove, grid);
    }
}





int getColumns (const char** maze, int rows) 
{
    int columns = strlen(maze[0]);
    for (int i = 1; i < rows; i++) {
        if ((int)strlen(maze[i]) > columns) {
            columns = strlen(maze[i]);
        }
    }

    return columns;
}



//----------------------------------------------------------------------------
// class functions for GridCells.h
//----------------------------------------------------------------------------


bool GridCells::playerCurrent() 
{
    return currentPosition;
}


bool GridCells::hasTraveled() 
{
    return traveled;
}



















//----------------------------------------------------------------------------
//
// maze printing for secrete mode: 
//   - free movement
//   - limitless transition between stages
//   - print maze using const char arrays instead of grid
//
//----------------------------------------------------------------------------

void jk_printMazeSecretMode1(Rect position, int defaultHeight, int color, 
                        int (&player)[2], bool &firstRun)
{
    const char* mazeName = "Maze 1";
    int rows = 31;
    int startingPosition[2] = {1, 29};

    // source: https://www.asciiart.eu/art-and-design/mazes
    const char* maze[rows] = 
    {
    
        "+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+",
        "|        |        |                                            |",
        "+  +--+  +  +--+--+  +--+--+--+--+--+--+--+--+--+  +--+--+--+  +",
        "|     |     |        |     |     |              |     |        |",
        "+--+  +  +--+  +--+--+  +  +  +  +  +--+--+--+  +--+  +  +--+--+",
        "|     |  |     |        |     |  |        |  |  |     |     |  |",
        "+  +--+  +  +--+  +--+--+--+--+--+--+  +--+--+  +--+--+--+  +--+",
        "|  |     |  |  |  |              |  |  |     |        |  |     |",
        "+  +--+--+  +--+  +  +--+--+--+  +  +  +  +  +--+  +  +--+--+  +",
        "|        |  |     |     |     |  |  |     |     |  |           |",
        "+  +--+  +  +  +--+--+  +--+  +  +--+--+--+--+  +  +--+--+--+--+",
        "|  |     |  |        |     |  |              |  |           |  |",
        "+  +  +--+  +--+--+--+--+  +  +--+--+--+--+  +  +--+  +--+  +--+",
        "|  |  |                    |              |  |     |  |  |     |",
        "+  +  +  +--+--+--+--+--+--+--+  +--+--+  +- +--+  +  +  +--+  +",
        "|  |        |     |                    |  |     |  |     |     |",
        "+  +--+--+  +  +  +  +--+  +--+--+  +--+--+  +  +  +--+  +  +--+",
        "|  |        |  |  |     |        |  |        |  |  |  |  |     |",
        "+  +  +--+--+  +  +--+  +  +--+--+--+  +--+--+--+  +  +  +--+  +",
        "|  |  |        |     |  |     |     |           |  |     |  |  |",
        "+  +  +  +--+--+--+--+  +--+  +  +--+--+  +--+  +  +--+--+--+  +",
        "|  |                       |  |        |  |     |        |  |  |",
        "+  +  +--+--+--+--+  +--+--+--+--+  +  +--+  +--+--+--+  +--+  +",
        "|  |        |     |  |        |  |  |  |              |  |     |",
        "+--+--+--+  +  +  +  +  +--+  +--+  +--+  +--+  +--+--+  +  +--+",
        "|     |     |  |  |  |  |  |        |  |  |     |     |  |     |",
        "+  +--+  +--+  +  +  +  +--+--+--+--+--+  +  +--+  +  +  +--+--+",
        "|           |  |  |  |                 |  |  |     |  |        |",
        "+--+--+--+  +--+  +  +--+--+--+--+--+  +  +  +--+--+--+--+--+  +",
        " X                |                 |     |              |      ",
        "+-----+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+"

    };

    // int columns = getColumns(maze, rows);

    if (firstRun) {
        player[0] = startingPosition[0]; // x
        player[1] = startingPosition[1]; // y
        jk_printMazeGrid(position, maze, rows, player, defaultHeight, color, 
                                                                    mazeName);
        // // Grid(rows, columns);
        // // printGrid();

        // mazeGrid = Grid(maze, rows, columns); // just to avoid warning
        // mazeGrid.printGrid(position, rows, columns, player, defaultHeight, 
                              // color, mazeName);
        

        firstRun = false;
    }
    
    else {
        jk_printMazeGrid(position, maze, rows, player, defaultHeight, color, 
                                                                    mazeName);
        // mazeGrid.printGrid(position, rows, columns, player, defaultHeight, 
                              // color, mazeName);                                                          
    }
}


void jk_printMazeSecretMode2(Rect position, int defaultHeight, int color, 
                                          int (&player)[2], bool& firstRun)
{
    const char* mazeName = "Maze 2";
    int rows = 27;
    int startingPosition[2] = {17, 23};

    
    // source: https://www.asciiart.eu/art-and-design/mazes
    const char* maze[rows] = 
    {
    
        ",-----------------------------.----------------------------------.",
        "|                             |                                  |",
        "|    .    .    ,---------     |     ------------------------.    |",
        "|    |    |    |              |                             |    |",
        "|    |    `----`--------------!    ,-------------------.    |    |",
        "|    |                             |                   |    |    |",
        "|    :--------------.--------------`----     ,---------:    |    |",
        "|    |              |                        |         |    |    |",
        "|    :---------     |    .    ,---------.    |    .    |    `----:",
        "|    |              |    |    |         |    |    |    |         |",
        "|    |     ---------!    |    :----     |    |    |    |    .    |",
        "|    |                   |    |         |    |    |    |    |    |",
        "|    `-------------------!    |     ----!    |    |    |    |    |",
        "|                             |              |    |    |    |    |",
        ":--------------.---------.    :--------------!    |    :----!    |",
        "|              |         |    |                   |    |         |",
        "|    .    .    |    .    |    |    ,--------------:    `----     |",
        "|    |    |    |    |    |    |    |              |              |",
        "|    |    |    `    |    |    |    |     ---------`---------.    |",
        "|    |    |         |    |    |    |                        |    |",
        "|    |    `---------`----!    |    |    ,---------.    .    |    |",
        "|    |                        |    |    |         |    |    |    |",
        "|    :---------.--------------:    |    |    .    |    |    |    |",
        "|    |         | X            |    |    |    |    |    |    |    |",
        "|    `    .    `---------     |    |    `----!    |    `----!    |",
        "|         |                   |    |              |              |",
        "`---------`-------------------!    `--------------`--------------!"
    
    };

    

    if (firstRun) {
        player[0] = startingPosition[0]; // x
        player[1] = startingPosition[1]; // y
        jk_printMazeGrid(position, maze, rows, player, defaultHeight, color, 
                                                                    mazeName);
        firstRun = false;
    }
    
    else {
        jk_printMazeGrid(position, maze, rows, player, defaultHeight, color, 
                                                                    mazeName);
    }
}


void jk_printMazeSecretMode3(Rect position, int defaultHeight, int color, 
                                          int (&player)[2], bool& firstRun)
{
    const char* mazeName = "Maze 3";
    int rows = 23;
    int startingPosition[2] = {1, 22};


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

    
   if (firstRun) {
        player[0] = startingPosition[0]; // x
        player[1] = startingPosition[1]; // y
        jk_printMazeGrid(position, maze, rows, player, defaultHeight, color, 
                                                                    mazeName);
        firstRun = false;
    }
    
    else {
        jk_printMazeGrid(position, maze, rows, player, defaultHeight, color, 
                                                                    mazeName);
    }
}
