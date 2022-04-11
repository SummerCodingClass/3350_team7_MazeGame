//Author: Jennifer K
//Individual Source File for Project


#include "fonts.h"
#include <iostream>
#include <cstring> //for strlen()
#include <GL/glx.h>
#include "GridCells.h"
#include "Grid.h"


using namespace std;







//functions that need prototypes
int getColumns (const char** maze, int rows);




bool jkuo_midterm_checkState(int mazeState, int desiredState) 
{
    // this test will test if we have a positive 
    // number of mazes in our collections

    if (mazeState == desiredState) {
        return true;
    }
    
    return false;
}





// void jkuo_midterm_function_wed(int maze_state) 
// {
//     // this test will fail on all pages aside from the map pages
//     // e.g. it will fail for welcome screen, but will pass for "maze 1" page
//     // it is testing the current maze_state constantly with each render
//     // no need for extra user input. 
    
//     cout << endl << endl;
//     cout << "====================================================" << endl;


//     if (maze_state < 1 || maze_state > 4) {
//         cout << endl << endl;
//         cout << "test FAILED." << endl
//              << "the inputted maze state is: " << maze_state << "." << endl
//              << "which is NOT within the range of 1 - 4." << endl 
//              << "this means you are NOT on a map page" << endl << endl;
//         cout << endl << endl;
//         return;
//     }
    
//     cout << endl << endl;
//     cout << "test PASSED. maze_state is: " << maze_state << endl
//          << "it IS within the range of 1 - 4" << endl
//          << "this means you ARE on a map page" << endl << endl;
//     cout << endl << endl;
//     return;
// }



// template <class T>
bool jkuo_midterm_function_mon(int& maze_state, int desired_state) 
{
    cout << endl << endl;

    if (desired_state <= 0 || desired_state >= 12) {
        // cout << "failed. please try a POSITIVE integer that's <= 4" << endl;
        return false;
    }
    


    // cout << "current maze_state: page" << maze_state << endl;
    // cout << "desired maze_state: page" << desired_state << endl;

    maze_state = desired_state;

    if (maze_state != desired_state) {

        // cout << endl;
        // cout << "results: page transition failed. returned false." << endl;
        // cout << endl << endl;

        return false;
    }

    // cout << endl;
    // cout << "results: page transition succeeded. returned true." << endl;
    // cout << endl << endl;

    return true;
}




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



void jk_printMazeTest(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                                int& maze_state)
{
    const char* mazeName = "Maze Tutorial";
    int rows = 5;
    int startingPosition[2] = {1, 3};
    // int endingPosition[2] = {1, 2}; 
    int endingPosition[2] = {2, 1}; 
    // column: count starting from 0, left being 0
    // row: also start from 0, but top being 0
    int wallColor[3] = {221, 160, 221};
    
    //  const char* maze[rows] = 
    // {
    
    //     "+-+-+-+-+-+",
    //     "|     |    ",
    //     "+ +-+ + +-+",
    //     "| --|   |--",
    //     "+-+-+-+-+-+"
    
    // };

     const char* maze[rows] = 
    {
    
        "+-+-",
        "|  .",
        "+ +-",
        "| --",
        "+-+-"
    
    };

    int columns = getColumns(maze, rows);

    if (firstRun) {
        player[0] = startingPosition[0]; // x
        player[1] = startingPosition[1]; // y
     
        mazeGrid = Grid(maze, rows, columns, player, endingPosition, 
                                                                wallColor);

        // mazeGrid.setWallColor(wallColor);
     
        mazeGrid.printGrid(position, rows, columns, player, defaultHeight, 
                                                color, mazeName, endReached);

        firstRun = false;
    } else if (endReached) {
        cout << "end reached" << endl; 
        mazeGrid.printGrid(position, rows, columns, player, defaultHeight, 
                                                color, mazeName, endReached);

        
        maze_state = -1 * maze_state;
        firstRun = true;
        endReached = false;
        

    } else {
        mazeGrid.printGrid(position, rows, columns, player, defaultHeight, 
                                                color, mazeName, endReached);
    }
}



void jk_printMaze1(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                                int& maze_state)
{
    const char* mazeName = "Maze 1";
    int rows = 31;
    int startingPosition[2] = {1, 29};
    // int endingPosition[2] = {5, 29}; 
    int endingPosition[2] = {2, 29}; 
    // int endingPosition[2] = {41, 29}; 
    // int wallColor[3] = {0, 128, 0};
    int wallColor[3] = {139, 0, 0};

    // source: https://www.asciiart.eu/art-and-design/mazes
    // corridors need to be 1 space wide, or it will mess up the trail
 

    const char* maze[rows] = 
    {
    
        "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+",
        "|     |     |                             |",
        "+ +-+ + +-+-+ +-+-+-+-+-+-+-+-+-+ +-+-+-+ +",
        "|   |   |     |   |   |         |   |     |",
        "+-+ + +-+ +-+-+ + + + + +-+-+-+ +-+ + +-+-+",
        "|   | |   |     |   | |     | | |   |   | |",
        "+ +-+ + +-+ +-+-+-+-+-+-+ +-+-+ +-+-+-+ +-+",
        "| |   | | | |         | | |   |     | |   |",
        "+ +-+-+ +-+ + +-+-+-+ + + + + +-+ + +-+-+ +",
        "|     | |   |   |   | | |   |   | |       |",
        "+ +-+ + + +-+-+ +-+ + +-+-+-+-+ + +-+-+-+-+",
        "| |   | |     |   | |         | |       | |",
        "+ + +-+ +-+-+-+-+ + +-+-+-+-+ + +-+ +-+ +-+",
        "| | |             |         | |   | | |   |",
        "+ + + +-+-+-+-+-+-+-+ +-+-+ + +-+ + + +-+ +",
        "| |     |   |             | |   | |   |   |",
        "+ +-+-+ + + + +-+ +-+-+ +-+-+ + + +-+ + +-+",
        "| |     | | |   |     | |     | | | | |   |",
        "+ + +-+-+ + +-+ + +-+-+-+ +-+-+-+ + + +-+ +",
        "| | |     |   | |   |   |       | |   | | |",
        "+ + + +-+-+-+-+ +-+ + +-+-+ +-+ + +-+-+-+ +",
        "| |               | |     | |   |     | | |",
        "+ + +-+-+-+-+ +-+-+-+-+ + +-+ +-+-+-+ +-+ +",
        "| |     |   | |     | | | |         | |   |",
        "+-+-+-+ + + + + +-+ +-+ +-+ +-+ +-+-+ + +-+",
        "|   |   | | | | | |     | | |   |   | |   |",
        "+ +-+ +-+ + + + +-+-+-+-+-+ + +-+ + + +-+-+",
        "|       | | | |           | | |   | |     |",
        "+-+-+-+ +-+ + +-+-+-+-+-+ + + +-+-+-+-+-+ +",
        ".X          |           |   |         |   z",
        "+---+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"
    
    };

    int columns = getColumns(maze, rows);

    if (firstRun) {
        player[0] = startingPosition[0]; // x
        player[1] = startingPosition[1]; // y

        mazeGrid = Grid(maze, rows, columns, player, endingPosition, 
                                                                wallColor);

        // mazeGrid.setWallColor(wallColor);

        mazeGrid.printGrid(position, rows, columns, player, defaultHeight, 
                                                color, mazeName, endReached);

        firstRun = false;
    } else if (endReached) {
        cout << "end reached" << endl; 
        mazeGrid.printGrid(position, rows, columns, player, defaultHeight, 
                                                color, mazeName, endReached);

        
        maze_state = -1 * maze_state;
        firstRun = true;
        endReached = false;
        

    } else {
       
        mazeGrid.printGrid(position, rows, columns, player, defaultHeight, 
                                                color, mazeName, endReached);
    }
}



void jk_printMaze2(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                                int& maze_state)
{
    const char* mazeName = "Maze 2";
    int rows = 27;
    int startingPosition[2] = {7, 23};
    int endingPosition[2] = {8,23}; 
    // int endingPosition[2] = {13,25}; 
    int wallColor[3] = {220, 88, 42};

    
    // source: https://www.asciiart.eu/art-and-design/mazes
    
      const char* maze[rows] = 
    {
    
        ",-----------.-------------.",
        "|           |             |",
        "| . . ,---- | ----------. |",
        "| | | |     |           | |",
        "| | `-`-----! ,-------. | |",
        "| |           |       | | |",
        "| :-----.-----`-- ,---: | |",
        "| |     |         |   | | |",
        "| :---- | . ,---. | . | `-:",
        "| |     | | |   | | | |   |",
        "| | ----! | :-- | | | | . |",
        "| |       | |   | | | | | |",
        "| `-------! | --! | | | | |",
        "|           |     | | | | |",
        ":-----.---. :-----! | :-! |",
        "|     |   | |       | |   |",
        "| . . | . | | ,-----: `-- |",
        "| | | | | | | |     |     |",
        "| | | ` | | | | ----`---. |",
        "| | |   | | | |         | |",
        "| | `---`-! | | ,---. . | |",
        "| |         | | |   | | | |",
        "| :---.-----: | | . | | | |",
        "| |   |X    | | | | | | | |",
        "| ` . `---- | | `-! | `-! |",
        "|   |       | |     |     |",
        "`---`-------!.`-----`-----!"
    
    };


    int columns = getColumns(maze, rows);

    if (firstRun) {
        player[0] = startingPosition[0]; // x
        player[1] = startingPosition[1]; // y

        mazeGrid = Grid(maze, rows, columns, player, endingPosition, 
                                                                wallColor);

        // mazeGrid.setWallColor(wallColor);
   
        mazeGrid.printGrid(position, rows, columns, player, defaultHeight, 
                                                color, mazeName, endReached);

        firstRun = false;
    } else if (endReached) {
        cout << "end reached" << endl; 
        mazeGrid.printGrid(position, rows, columns, player, defaultHeight, 
                                                color, mazeName, endReached);

        
        maze_state = -1 * maze_state;
        firstRun = true;
        endReached = false;
        

    } else {
       
        mazeGrid.printGrid(position, rows, columns, player, defaultHeight, 
                                                color, mazeName, endReached);
    }

}


void jk_printMaze3(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                                int& maze_state)
{
    const char* mazeName = "Maze 3";
    int rows = 23;
    int startingPosition[2] = {1, 21};
    int endingPosition[2] = {1, 20}; 
    // int endingPosition[2] = {35, 1}; 
    int wallColor[3] = {246, 190, 0};


    // source: https://www.asciiart.eu/art-and-design/mazes
   
      const char* maze[rows] = 
    {
    
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaza",
      "8 8       8       8     8         8 8",
      "8 8 aaaaa 8 aaa aa8aa aa8 aaa aaa 8 8",
      "8       8   8 8     8     8 8 8   8 8",
      "8aaaa a 8aaa8 8aaaa 8aa a 8 8 8aaa8 8",
      "8   8 8       8     8 8 8 8 8     8 8",
      "8 a 8a8aaaa a 8 aaaa8 8a8 8 8aaaa 8 8",
      "8 8       8 8 8   8     8     8   8 8",
      "8 8aaaaaa 8a8 8aa 8 aaa 8aaaa 8 aa8 8",
      "8     8   8 8   8 8   8     8 8     8",
      "8 aaa 8aa 8 8aa 8 8aaa8 a a 8 8aaaaa8",
      "8   8   8 8 8   8   8   8 8 8   8   8",
      "8aaa8aa 8 8 8 aa8aa 8 aa8 8 8aa 8aa 8",
      "8     8 8     8   8 8   8 8   8     8",
      "8 aaa 8 8aaaa 8aa 8 8aa 8a8 aa8aaaa 8",
      "8 8   8     8     8   8 8 8       8 8",
      "8 8 aa8aa a 8aa aa8aa 8 8 8aaaaaa 8 8",
      "8 8     8 8 8 8 8     8       8 8   8",
      "8 8aaaa 8 8 8 8a8 8aaa8 aaaaa 8 8aaa8",
      "8 8   8 8 8     8     8 8   8       8",
      "8 8 aa8 8a8 aaa 8aaaa 8a8 a 8aaaa a 8",
      "8 8         8     8       8       8 8",
      "8.8aaaaaaaaa8aaaaa8aaaaaaa8aaaaaaa8a8",

    };

    
    int columns = getColumns(maze, rows);

    if (firstRun) {
        player[0] = startingPosition[0]; // x
        player[1] = startingPosition[1]; // y

        mazeGrid = Grid(maze, rows, columns, player, endingPosition, 
                                                                wallColor);

        // mazeGrid.setWallColor(wallColor);
   
        mazeGrid.printGrid(position, rows, columns, player, defaultHeight, 
                                                color, mazeName, endReached);

        firstRun = false;
    } else if (endReached) {
        cout << "end reached" << endl; 
        mazeGrid.printGrid(position, rows, columns, player, defaultHeight, 
                                                color, mazeName, endReached);

        
        maze_state = -1 * maze_state;
        firstRun = true;
        endReached = false;
        

    } else {
       
        mazeGrid.printGrid(position, rows, columns, player, defaultHeight, 
                                                color, mazeName, endReached);
    }


}




// --------------------------------------------------------------------------
// start of template for new maze
// --------------------------------------------------------------------------
// 1. replace function name as well

void jk_printMazeTemplate(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                                int& maze_state)
{
    const char* mazeName = "Maze Template";    // 2. replace
    int rows = 31;                      // 3. replace: 
                                        //          start counting from 1
    int startingPosition[2] = {1, 29};  // 4. replace: 
                                        //          start counting from 0.
                                        //          1st number: left to right
                                        //          2nd number: top to bottom
                                        //  
    int endingPosition[2] = {42, 29};   // 5. replace: 
                                        //          same as #4.           
                                        //
    int wallColor[3] = {0, 128, 0}; // 6. replace:
                                        //          this is rgb color for wall. 
                                        //          don't forget #7

    // source: https://www.asciiart.eu/art-and-design/mazes
    // corridors need to be 1 space wide, or it will mess up the trail
 

    // 7. replace
    const char* maze[rows] = 
    {
    
        "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+",
        "|     |     |                             |",
        "+ +-+ + +-+-+ +-+-+-+-+-+-+-+-+-+ +-+-+-+ +",
        "|   |   |     |   |   |         |   |     |",
        "+-+ + +-+ +-+-+ + + + + +-+-+-+ +-+ + +-+-+",
        "|   | |   |     |   | |     | | |   |   | |",
        "+ +-+ + +-+ +-+-+-+-+-+-+ +-+-+ +-+-+-+ +-+",
        "| |   | | | |         | | |   |     | |   |",
        "+ +-+-+ +-+ + +-+-+-+ + + + + +-+ + +-+-+ +",
        "|     | |   |   |   | | |   |   | |       |",
        "+ +-+ + + +-+-+ +-+ + +-+-+-+-+ + +-+-+-+-+",
        "| |   | |     |   | |         | |       | |",
        "+ + +-+ +-+-+-+-+ + +-+-+-+-+ + +-+ +-+ +-+",
        "| | |             |         | |   | | |   |",
        "+ + + +-+-+-+-+-+-+-+ +-+-+ + +-+ + + +-+ +",
        "| |     |   |             | |   | |   |   |",
        "+ +-+-+ + + + +-+ +-+-+ +-+-+ + + +-+ + +-+",
        "| |     | | |   |     | |     | | | | |   |",
        "+ + +-+-+ + +-+ + +-+-+-+ +-+-+-+ + + +-+ +",
        "| | |     |   | |   |   |       | |   | | |",
        "+ + + +-+-+-+-+ +-+ + +-+-+ +-+ + +-+-+-+ +",
        "| |               | |     | |   |     | | |",
        "+ + +-+-+-+-+ +-+-+-+-+ + +-+ +-+-+-+ +-+ +",
        "| |     |   | |     | | | |         | |   |",
        "+-+-+-+ + + + + +-+ +-+ +-+ +-+ +-+-+ + +-+",
        "|   |   | | | | | |     | | |   |   | |   |",
        "+ +-+ +-+ + + + +-+-+-+-+-+ + +-+ + + +-+-+",
        "|       | | | |           | | |   | |     |",
        "+-+-+-+ +-+ + +-+-+-+-+-+ + + +-+-+-+-+-+ +",
        " X          |           |   |         |    ",
        "+---+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"
    
    };

    int columns = getColumns(maze, rows);

    if (firstRun) {
        player[0] = startingPosition[0]; // x
        player[1] = startingPosition[1]; // y

        mazeGrid = Grid(maze, rows, columns, player, endingPosition, 
                                                                wallColor);
   
        mazeGrid.printGrid(position, rows, columns, player, defaultHeight, 
                                                color, mazeName, endReached);

        firstRun = false;
    } else if (endReached) {
        cout << "end reached" << endl; 
        mazeGrid.printGrid(position, rows, columns, player, defaultHeight, 
                                                color, mazeName, endReached);

        
        maze_state = -1 * maze_state;
        firstRun = true;
        endReached = false;
        

    } else {
       
        mazeGrid.printGrid(position, rows, columns, player, defaultHeight, 
                                                color, mazeName, endReached);
    }
}

// --------------------------------------------------------------------------
// end of template for new maze
// --------------------------------------------------------------------------








//----------------------------------------------------------------------------
// midterm functions for group
//----------------------------------------------------------------------------


extern bool jhicks_midterm_function(int maze_state);
extern bool jrojas_midterm_func(int value);
extern bool anicholas_Midterm(int value);
// extern bool etagaca_midterm(int& current_time); called in main


// // void printTimerWarning(int& current_time, Rect position, 
//                                                 int defaultHeight, int color)
// {
//     if(etagaca_midterm(current_time)) {
//         ggprint8b(position, 16, 0x00b19cd9, "1 minutes have passed");
//     }
// }













void jk_page_transition(int& maze_state, const char* keyChecked, 
                                                    bool& firstRun, int maxMaze) 
{

    //for midterm
    // if (strcmp(keyChecked, "5") == 0) {
    //     //true
    //     if (maze_state == 0) {
    //         firstRun = true;
    //         bool success = jkuo_midterm_function(maze_state, 30);
    //         cout << "test done. success =  " << success << endl; 
    //         return;
    //     }
    // }

    // if (strcmp(keyChecked, "6") == 0) {

    //     if (maze_state == 30) {
    //         bool success = jkuo_midterm_function(maze_state, 
    //         100000000000000000000000000000000000000000000000000000000000000);
    //         cout << "test done. success =  " << success << endl;
    //         return;
    //     }

    // }

    
    //case XK_b;
    if (strcmp(keyChecked, "b") == 0) {
        
        if (jhicks_midterm_function(maze_state)) {
        // if (maze_state == 0) {
            //do nothing
            // firstRun = true;
        } else if (maze_state == 1000 || maze_state == 404) {
            maze_state = 0;
        } else if (maze_state > 230) {
            maze_state = 23;
        // } else if (maze_state > 0) {
        } else if (anicholas_Midterm(maze_state)) {
            maze_state = 0;
            // firstRun = true;
        }
        
        return;
    }

    if (strcmp(keyChecked, "p") == 0) {
        if (maze_state >= 1 && maze_state <= maxMaze) {
            maze_state = maze_state * 405000; // dedicated pause page 
            return; 
        }
    }

    if (strcmp(keyChecked, "u") == 0) {
        if (maze_state >= 405000) {
            maze_state = maze_state / 405000; 
                                        // restoring from dedicated pause page
            return; 
        }
    }

		//case XK_s;
    if (strcmp(keyChecked, "s") == 0) {
        // if (jhicks_midterm_function(maze_state)) {
        if (maze_state == 0) {
            firstRun = true;

            //for midterm:

            // case for success:
            bool success = jkuo_midterm_function_mon(maze_state, 1);

            // case for failure:
            // bool success = jkuo_midterm_function(maze_state, -1);

            if (!success) {
                cout << "test returned false" << endl;
            }

            // maze_state = 1;
        } else if (maze_state == -4 ) {
            cout << "in maze_state -4" << endl;
            firstRun = true;
            maze_state = 1;
        
        } else if (jrojas_midterm_func(maze_state)) {
        // } else if (maze_state < 0 ) {
            firstRun = true;

            if (maze_state == -3) {
                maze_state = (maze_state* -1) + 2;
            } else if (maze_state > (-1 * maxMaze)) {
                maze_state = (maze_state* -1) + 1;
            } else {
                maze_state = 1000; // congrats on beating everything
            }
             
        } else if (maze_state == 1) {
            firstRun = true;
            maze_state = 2;
        } else if (maze_state == 2) {
            firstRun = true;
            maze_state = 3;
        } else if (maze_state == 3) {
            firstRun = true;
            maze_state = 5;
        } else if (maze_state == 4) {
            firstRun = true;
            maze_state = 1;
        } else if (maze_state == 5) {
            firstRun = true;
            maze_state = 6;
        } else if (maze_state == 6) {
            firstRun = true;
            maze_state = 7;
        } else if (maze_state == 7) {
            firstRun = true;
            maze_state = 8;
        } else if (maze_state == 8) {
            firstRun = true;
            maze_state = 9;
        } else if (maze_state == 9) {
            firstRun = true;
            maze_state = 10;
        } else if (maze_state == 10) {
            firstRun = true;
            maze_state = 11;
        } else if (maze_state == 11) {
            firstRun = true;
            maze_state = 12;
        } else if (maze_state == 12) {
            firstRun = true;
            maze_state = 0;
        } else if (maze_state == 230) {
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
            maze_state = 110;
        } else if(maze_state == 22) {
            maze_state = 230;
        }
        return; 
    }
    
    if (strcmp(keyChecked, "c") == 0) {
        if (maze_state == 0) {
            maze_state = 120;
        }
        return; 
    }

    if (strcmp(keyChecked, "q") == 0) {
        if(maze_state == 110 || maze_state == 120) {
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

    if (strcmp(keyChecked, "z") == 0) {
        if(maze_state == 0) {
            firstRun = true;
            maze_state = 4; //test mode
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
    ggprint8b(&position, 16, color, 
                              "You have 1000 seconds max per stage.");
}



void jk_showWelcomePage(Rect position, int defaultHeight, int color) 
{
    position.bot = defaultHeight;
  
    ggprint13(&position, 16, color, "------------ Instructions ------------");
}

void jk_showWelcomePage3(Rect position, int defaultHeight, int color) 
{
    position.bot = defaultHeight;
  
    ggprint8b(&position, 16, color, "press 'Z' to start from tutorial stage");
}

//could be replaced by picture logo
void jk_showWelcomePageTitle(Rect position, int defaultHeight, int color) 
{
    position.bot = defaultHeight;
  
    // ggprint40(&position, 16, color, "The MAze Game");
    ggprint40(&position, 16, color, "Placeholder for Adam");
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



void jkuo_checkWall(int (&player)[2], int nextMove[2], Grid& grid) 
{
    int orig_i = player[1];
    int orig_j = player[0];
    int i = nextMove[1];
    int j = nextMove[0];
    
    vector <vector <GridCells>> tempGrid = grid.GridGetter();
    
    // cout << "i: " << i << " j: " << j << endl;
    // cout << "before isWall()." << endl;

    

    if (tempGrid[i][j].isWall()) {
    
    // if ( tempGrid[i][j].isWall() || 
    //         player[1] >= (grid.rows-1) || player[0] >= (grid.columns-1)) {
    // // cout << "rows: " << grid.rows << " columns: " << grid.columns << endl;
        // cout << "this is a wall" << endl;
        return;
        // do nothing, return player[2] as is
    }
    else {

        // cout << "is it entering here?" << endl;
        // cout << "NOT a wall" << endl;
        // cout << "before: " << player[0] << ", " << player[1] << endl;
        // tempGrid[i][j].setCurrent(true);

        // set present to NOT current
        grid.mazeGrid[orig_i][orig_j].setCurrent(false);
        // grid.mazeGrid[orig_i][orig_j].setTraveled(true);
        // set next as current
        grid.mazeGrid[i][j].setCurrent(true);

        if (grid.mazeGrid[i][j].hasTraveled() == true) {
            grid.mazeGrid[i][j].setTraveled(false);
            grid.mazeGrid[orig_i][orig_j].setTraveled(false);
        } else {
            grid.mazeGrid[orig_i][orig_j].setTraveled(true);
        }

        

        
        player[0] = nextMove[0];
        player[1] = nextMove[1];
        

        // if (tempGrid[i][j].isEnd()) {
        
        // }
        // cout << "after: " << player[0] << ", " << player[1] << endl;
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
        jkuo_checkWall(player, nextMove, grid);
       
    }

    //down
    if (keys[XK_Down]) {
        nextMove[1] = player[1] + 1;
        nextMove[0] = player[0];
        jkuo_checkWall(player, nextMove, grid);
        
    }
  
    //left
    if (keys[XK_Left]) {
        nextMove[0] = player[0] - 1;
        nextMove[1] = player[1];
        jkuo_checkWall(player, nextMove, grid);

    }

    //right
    if (keys[XK_Right]) {
        nextMove[0] = player[0] + 1;
        nextMove[1] = player[1];
        jkuo_checkWall(player, nextMove, grid);
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

int GridCells::getXcoord() 
{
    return xcoord;
}

int GridCells::getYcoord() 
{
    return ycoord;
}





//----------------------------------------------------------------------------
// class functions for Grid.h
//----------------------------------------------------------------------------


void Grid::setWallColor(int colorChoice[3]) 
{
    wallColor[0] = colorChoice[0];
    wallColor[1] = colorChoice[1];
    wallColor[2] = colorChoice[2];
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



