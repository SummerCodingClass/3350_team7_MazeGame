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
    // this test will test if the current maze state is a certain value
    if (mazeState == desiredState) {
        return true;
    }
    
    return false;
}



bool jkuo_midterm_function_mon(int& maze_state, int desired_state) 
{
    if (desired_state <= 0 || desired_state >= 12) {
        return false;
    }

    maze_state = desired_state;

    if (maze_state != desired_state) {
        return false;
    }
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



void jk_printMazeGeneral(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
            int& maze_state, const char* mazeName, int rows, 
            int startingPosition[2], int endingPosition[2], int wallColor[3],
            const char* maze[])
{

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



void jk_printMazeTest(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                                int& maze_state)
{
    const char* mazeName = "Tutorial Stage: Maze 4";
    int rows = 5;
    int startingPosition[2] = {1, 3};
    int endingPosition[2] = {1, 2}; 
    // int endingPosition[2] = {9, 1}; 
     
    
    int wallColor[3] = {221, 160, 221};
    
    const char* maze[rows] = 
    {
    
        "+-+-+-+-+-+",
        "|     |   z",
        "+ +-+ + +-+",
        "| --|   |--",
        "+-+-+-+-+-+"
    
    };

    jk_printMazeGeneral(position, defaultHeight, color, player, firstRun,
            endReached, mazeGrid, maze_state, mazeName, rows, startingPosition,
            endingPosition, wallColor, maze);
}



void jk_printMaze1(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                                int& maze_state)
{
    const char* mazeName = "Maze 1";
    int rows = 31;
    int startingPosition[2] = {1, 29};
    
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

    jk_printMazeGeneral(position, defaultHeight, color, player, firstRun,
            endReached, mazeGrid, maze_state, mazeName, rows, startingPosition,
            endingPosition, wallColor, maze);
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


    jk_printMazeGeneral(position, defaultHeight, color, player, firstRun,
            endReached, mazeGrid, maze_state, mazeName, rows, startingPosition,
            endingPosition, wallColor, maze);
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

    jk_printMazeGeneral(position, defaultHeight, color, player, firstRun,
            endReached, mazeGrid, maze_state, mazeName, rows, startingPosition,
            endingPosition, wallColor, maze);
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



void jk_page_transition(int& maze_state, const char* keyChecked, 
                                bool& firstRun, int maxMaze, bool& showScores) 
{
    //case XK_b;
    if (strcmp(keyChecked, "b") == 0) {        
        // if (maze_state == 0) {
        if (jhicks_midterm_function(maze_state)) { 
            //do nothing
        } else if (maze_state == 1000 || maze_state == 404) {
            maze_state = 0;
        } else if (maze_state > 230) {
            maze_state = 230;
        // } else if (maze_state > 0) {
        } else if (anicholas_Midterm(maze_state)) {
            maze_state = 0;
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
        if (maze_state == 0) {
            firstRun = true;

            bool success = jkuo_midterm_function_mon(maze_state, 1);

            if (!success) {
                cout << "test returned false" << endl;
            }

            // maze_state = 1;
        } else if (maze_state == -4 ) {
            firstRun = true;
            maze_state = 1;
        
        } else if (jrojas_midterm_func(maze_state)) {
        // } else if (maze_state < 0 ) {
            firstRun = true;

            if (maze_state == -3) {
                maze_state = (maze_state* -1) + 2;
            } else if (maze_state > (-1 * maxMaze)) {
                maze_state = (maze_state* -1) + 1;
            } else if (maze_state == (-1 * maxMaze)) {
                maze_state = 0;
            }
            // } else {
                // maze_state = 1000; // congrats on beating everything
            // }
        } else if (maze_state == 3) {
            firstRun = true;
            maze_state = 5;
        } else if (maze_state == 4) {
            firstRun = true;
            maze_state = 1;
        } else if (maze_state == 12) {
            firstRun = true;
            maze_state = 0;
        } else if (maze_state == 1 || maze_state == 2 || maze_state == 5 ||
                   maze_state == 6 || maze_state == 7 || maze_state == 8 ||
                   maze_state == 9 || maze_state == 10 || maze_state == 11) {
            firstRun = true;
            maze_state++;
        } else if (maze_state == 230 || maze_state == 231 
                                     || maze_state == 232) {
            firstRun = true;
            maze_state++;
        } else if (maze_state == 233) {
            firstRun = true;
            maze_state = 230;
        }        
        return; 
    }

    
    if (strcmp(keyChecked, "a") == 0) {
        if (showScores) {
            showScores = false;
            return; 
        }
        showScores = true;
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
}





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
    ggprint8b(&position, 16, color, 
                              "The grey square represents the exit.");
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

void jk_showWelcomePage4(Rect position, int defaultHeight, int color) 
{
    position.bot = defaultHeight;
  
    ggprint8b(&position, 16, color, "press 'A' any time for scoreboard");
}



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



void jkuo_checkWall(int (&player)[2], int nextMove[2], Grid& grid) 
{
    int orig_i = player[1];
    int orig_j = player[0];
    int i = nextMove[1];
    int j = nextMove[0];
    
    vector <vector <GridCells>> tempGrid = grid.GridGetter();
    

    if (tempGrid[i][j].isWall()) {

        // do nothing, return player[2] as is
        return;

    } else {

        grid.mazeGrid[orig_i][orig_j].setCurrent(false);
        grid.mazeGrid[i][j].setCurrent(true);

        if (grid.mazeGrid[i][j].hasTraveled() == true) {

            grid.mazeGrid[i][j].setTraveled(false);
            grid.mazeGrid[orig_i][orig_j].setTraveled(false);

        } else {

            grid.mazeGrid[orig_i][orig_j].setTraveled(true);

        }

        player[0] = nextMove[0];
        player[1] = nextMove[1];
        
        return;
    }
}



void jk_playerMovement(char* keys, int (&player)[2], Grid& grid) 
{
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



//for secrete mode
void jk_playerMovementForSecretMode(char* keys, int (&player)[2]) 
{
    //player[0] = column = "j"
    //player[1] = row = "i"

    // if (i == player[1] + 1 && j == player[0]) { 

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



GridCells::GridCells() 
{

    xcoord = 0;
    ycoord = 0;
    space = true;
    wall = true;
    start = true;
    end = true;
    currentPosition = true;
    traveled = true;

}



GridCells::GridCells(int x, int y, bool uspace, bool uwall, 
                bool ustart, bool uend, bool ucurrent, bool utravel) 
{

    xcoord = x;
    ycoord = y;
    space = uspace;
    wall = uwall;
    start = ustart;
    end = uend;
    currentPosition = ucurrent;
    traveled = utravel;

}





//----------------------------------------------------------------------------
//
// maze printing for secrete mode: 
//   - free movement
//   - limitless transition between stages
//   - print maze using const char arrays instead of grid
//
//----------------------------------------------------------------------------

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
            
            if (maze[i][j] == ' ' || maze[i][j] == 'X') {
                glColor3ub(20,20,20);
            }
            
            if (i == player[1] && j == player[0]) {
                glColor3ub(255,250,250);
            }

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





//----------------------------------------------------------------------------
// nonessential class functions for Grid.h
//----------------------------------------------------------------------------

void Grid::setWallColor(int colorChoice[3]) 
{
    wallColor[0] = colorChoice[0];
    wallColor[1] = colorChoice[1];
    wallColor[2] = colorChoice[2];
}



vector <vector <GridCells>> Grid::GridGetter() 
{
    return mazeGrid;
}



//----------------------------------------------------------------------------
// essential functions for Grid.h - developed together in group meetings
//----------------------------------------------------------------------------


Grid::Grid() 
{
    rows = 0;
    columns = 0;
}


Grid::Grid(const char** maze, int inputRows, int inputColumns, 
                                int player[2], int end[2], int colorChoice[3]) 
{
    rows = inputRows;
    columns = inputColumns;
    gridPlayer[1] = player[1];
    gridPlayer[0] = player[0];
    setWallColor(colorChoice);

    // Inserting elements into vector
    for (int i = 0; i < rows; i++) {
        // Vector to store column elements
        vector <GridCells> v1;

        for (int j = 0; j < columns; j++) {
            
            GridCells temp;
            temp.setXcoord(j);
            temp.setYcoord(i);
            
            if (i == end[1] && j == end[0]) {
                temp.setEnd(true);
                mazeEnd[1] = i;
                mazeEnd[0] = j;
            } else {
                temp.setEnd(false);
            }

            if (i == gridPlayer[1] && j == gridPlayer[0]) {
                temp.setCurrent(true);
                temp.setTraveled(false);
            } else if (maze[i][j] == ' ') {
                temp.setSpace(true);
                temp.setWall(false);
                temp.setCurrent(false);
                temp.setTraveled(false);
                
            } else if (maze[i][j] == 'X') {
                temp.setSpace(true);
                temp.setWall(false);
                temp.setCurrent(false);
                temp.setTraveled(false);
            } else {
                temp.setSpace(false);
                temp.setWall(true);
                temp.setCurrent(false);
                temp.setTraveled(false);
            }


            v1.push_back(temp);
            
        }

        // Pushing back above 1D vector
        // to create the 2D vector
        mazeGrid.push_back(v1);
    }


    
}


   
void Grid::printGrid(Rect position, int rows, int columns,
        int (&player)[2], int defaultHeight, int color, const char* mazeName,
                                                            bool& endReached) 
{

    ggprint8b(&position, 16, color, mazeName);

    
    // player reached the ending position
    if (player[1] == mazeEnd[1] && player[0] == mazeEnd[0]) {

            endReached = true;
            
    }
    


    // ========================== start of for loops ========================
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

            
            
            //color of wall
            glColor3ub(wallColor[0],wallColor[1], wallColor[2]);

            if(mazeGrid[i][j].isSpace()) {
                glColor3ub(20,20,20);
            }
            
            if(mazeGrid[i][j].isEnd()) {
                glColor3ub(128,128,128);
            }

            if(mazeGrid[i][j].playerCurrent()) {
                glColor3ub(255,250,250);
            }

            if(mazeGrid[i][j].hasTraveled()) {
                glColor3ub(0,255,255);
            }

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
    // ========================== end of for loops ========================

}
    



// scene construction:

// void jk_stageSetUp(Rect msgPosition, Rect timerPosition, int defaultHeight, 
//             int color, int maze_state, int firstRun, int current_time) 
// {

//     glClear(GL_COLOR_BUFFER_BIT);
	
// 	ggprint8b(&r, 16, 0x00ffffff, "press s to switch to next maze");
// 	ggprint8b(&r, 16, 0x00ffffff, "press b to return to home");
// 	ggprint8b(&r, 16, 0x00ffffff, "press p to pause game");
// 	ggprint8b(&r, 16, 0x00ffffff, "HOLD down the arrowkeys to move about");

// 	et_timer(et_message, gl.yres-120, 0x00B24BF3, gl.maze_state, 
// 											gl.firstRun, gl.current_time);

// 	jk_playerMovement(gl.keys, gl.player, gl.mazeGrid);

// }






//============================================================================
// Scoreboard
//============================================================================

bool jk_allStagesBeaten(int timeBeaten[], int maxMaze)
{
    
    for (int i = 1; i <= maxMaze; i++) {
        if (i == 4) {
            //do nothing. tutorial stage doesn't count against progress
        } else {
            if(timeBeaten[i] == -1) {   
                return false;
            }
        }
    }

    return true;
}

void jk_displayScore(int timeBeaten[], int maxMaze, Rect position1, 
                                   Rect position2, int defaultHeight, int color)
{
    position1.bot = defaultHeight;
    position2.bot = defaultHeight;
    

    for (int level = 1; level <= maxMaze; level++) {

        string mazeLevel = "Maze " + to_string(level) + ": ";
        const char *name = mazeLevel.c_str();

        // ggprint13(&position1, 16, color, "Maze 1: ");
        ggprint13(&position1, 35, color, name);
    
        if (timeBeaten[level] == -1) {
            ggprint13(&position2, 35, 0x00FF8C00, "no attempt yet");
        } else {
    
            int time = timeBeaten[level];
            string mazeTime = "completed in " + to_string(time) + " seconds";
            const char *highScore = mazeTime.c_str();
            ggprint13(&position2, 35, color, highScore);
        }    
    }


}



void highScoreMessages(int& maze_state, int (&timeBeaten)[13], int current_time, 
        bool& firstAttempt, bool& newHighScore, int& oldScore, int& newScore,
        Rect r, int maxMaze)
{
    int levelBeaten = maze_state * -1;

    if (timeBeaten[levelBeaten] == -1) {
        timeBeaten[levelBeaten] = current_time;
        firstAttempt = true;


    } else if (current_time < timeBeaten[levelBeaten]) {

        newHighScore = true;
        oldScore = timeBeaten[levelBeaten];
        timeBeaten[levelBeaten] = current_time;
        newScore = timeBeaten[levelBeaten];
    }

    
    if (firstAttempt) {
        string record = "current high score: " 
                + to_string(timeBeaten[levelBeaten]) + " seconds";
        const char *recordChar = record.c_str();			
        ggprint8b(&r, 16, 0x00ffffff, recordChar);

    } else if (newHighScore) {
        ggprint8b(&r, 16, 0x00ffffff, 
                            "Congratulations! You beated the record!");
        
        string record = "record beaten: " 
                + to_string(oldScore) + " seconds";
        const char *recordChar = record.c_str();			
        ggprint8b(&r, 16, 0x00ffffff, recordChar);


        
        record = "new high score: " 
                + to_string(newScore) + " seconds";
        recordChar = record.c_str();			
        ggprint8b(&r, 16, 0x00ffffff, recordChar);


        ggprint8b(&r, 16, 0x00ffffff, 
                            "The new high score has been recorded");	
    } else {
        string record = "high score: " 
                + to_string(timeBeaten[levelBeaten]) + " seconds";
        const char *recordChar = record.c_str();			
        ggprint8b(&r, 16, 0x00ffffff, recordChar);
    }




    bool allBeaten = jk_allStagesBeaten(timeBeaten, maxMaze);

    if (allBeaten == true) {
    	maze_state = 1000;
    }
}