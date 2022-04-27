// Jesus Rojas
// Individual Source File for 3350 Group Project

#include <iostream>
#include "fonts.h"
#include "GridCells.h"
#include "Grid.h"

using namespace std;

extern int getColumns (const char** maze, int rows);

/* Jesus Rojas 
* CMPS 3350
* Midterm
* Date Written: 04/04/2022
**************************
* This function will test if an input
* is greater than zero
* If is less than zero
* a response is displayed
*/
void jrojas(int userInput)
{
    int maxNumber = 0;
    /* Test if user input
     * is greater than zero*/
    if (userInput > 0) {
        // maxNumber will be assigned userInput
        maxNumber = userInput;
        // Increment maxNumber for temp use
        maxNumber++;
    } else {
        printf("Please an enter a number greater than zero!\n");
    }
}

bool jrojas_midterm_func(int value) 
{
    /*Test value if negative return true
    otherwise false */
    if (value < 0)
        return true;
    else
        return false;
}

void jr_PrintMsg()
{
    cout << "jrojas -testing this out! Hello there!" << endl;
}

void jr_showCreditPage(Rect position, int defaultHeight, int color) 
{
  position.bot = defaultHeight;
  ggprint8b(&position, 16, color, "Jesus Rojas:");
  ggprint8b(&position, 16, color, "Game Designer | Game Programmer");
}

void jr_showRulesPage(Rect position, int defaultHeight, int color) 
{
  position.bot = defaultHeight;
  ggprint8b(&position, 16, color, "Rule 3:");
  ggprint8b(&position, 16, color, "You could pause game and resume.");
}

void jr_showWelcomePage(Rect position, int defaultHeight, int color) 
{
  position.bot = defaultHeight;
  ggprint8b(&position, 16, color, "press 'S' to start from Maze 1");
}

bool GridCells::setCurrent(bool input) 
{
    currentPosition = input;
    return currentPosition;
}

bool GridCells::setTraveled(bool input) 
{
    traveled = input;
    return traveled;
}

bool GridCells::isSpace() 
{
    return space;
}

/*-------------------------------------------------------------------------
* jr_printMaze7
*-------------------------------------------------------------------------*/
void jr_printMaze7(Rect position, int defaultHeight, int color, 
        int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                            int& maze_state)
{
    const char* mazeName = "Maze 7";
    int rows = 31;                      // Row Count
    
    //Original Starting Points
    int startingPosition[2] = {17, 20}; // (Starting Position)
    int endingPosition[2] = {29, 29};   // (Ending Position)
    
    //Test Starting Points
    //int endingPosition[2] = {17, 21};

    int wallColor[3] = {239, 66, 245};  // **PINK COLOR**

    // Maze source: https://www.asciiart.eu/art-and-design/mazes
    const char* maze[rows] = 
    {    
        "+++++++++++++++++++++++++++++++",
        "|         |                   |",  
        "| +++++++++++++++++ +++++ + + |",  
        "|       |           |     | + |",  
        "| +++++ | +++++++++++++++++ + |",  
        "| | +   |       | |         + |",  
        "| | + | | +++++ | | +++++++++ |",  
        "| | | | | | |   | | | |     | |",  
        "| | + | | + ++++++| + +   + | |",  
        "| |   | |         |       | | |",  
        "| ++++| + +++++++++++++++++++ |",  
        "|   | |   |         |         |",  
        "| + | +++++++++++++ +++++++ + |",  
        "| | |             |       | | |",  
        "| | | +++++++++++ | +++++ | | |", 
        "| | |   |   |   | | |   |   | |",  
        "| | | + +++ +++ | | | +++ ++++|",  
        "|   | |         | | |         |",  
        "|++ | | ++++++++| | | ++++++++|",  
        "| | | | | |   | |+| | |       |",  
        "| | | | | + ++| |X| | | +++++ |",  
        "| | | | | +   | | | | | |   | |",  
        "| | | | | + +++ | | |   | + | |",  
        "| | | | |       | | |+| | | | |",  
        "| | | | +++++++++ | | |+++++| |",  
        "|   | |           | |       | |",  
        "| ++++| +++++++++ ++| +++++ | |",  
        "| |   | |     |     |   |     |",  
        "| +++ | +++++ | +++ + ++++++++|",  
        "|       |        |  |         |",  
        "+++++++++++++++++++++++++++++++"
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

/*-------------------------------------------------------------------------
* jr_printMaze8
*-------------------------------------------------------------------------*/
void jr_printMaze8(Rect position, int defaultHeight, int color, 
        int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                            int& maze_state)
{
    const char* mazeName = "Maze 8";
    int rows = 26;                      // Row Count
    //Original Starting Points
    int startingPosition[2] = {15, 24}; // (Starting Position)
    int endingPosition[2] = {29, 1};    // (Ending Position)    
                                        //          Counting from 0.
                                        //          1st number: left to right
                                        //          2nd number: top to bottom
    //Test Starting Points
    //int endingPosition[2] = {13, 24};    // (Ending Position)    
    
    int wallColor[3] = {3, 107, 252};   // **BLUE COLOR**

    // Maze source: https://www.asciiart.eu/art-and-design/mazes

    const char* maze[rows] = 
    {    
        "+-+-+-+-+-+-+-+++-+-+-+-+-+-+-+",
        "|             | |             |",
        "| |-| |-|-|-| | | | | |-|-| |-|",
        "| | | | |-| | |-| |-|-| | | | |",
        "| |   | |   |     |   | | | | |",
        "| | |-| | |-|-|-|-| | | | |-| |",
        "| |   | | |         |   |   | |",
        "| | |-| |-| |-|-|-|-| |-| | | |",
        "| |   |     |       |   | |   |",
        "| |-| | |-|-| |-|-| |-| |-|-| |",
        "| |   |       |     | |       |",
        "| | |-|-|-|-| | |-|-| | |-|-| |",
        "| |   |   |   | |   |   |   | |",
        "| |-| | | | |-| | |-| |-| | |-|",
        "| |   | | |   |   |   |   |   |",
        "| |-|-| | | | |-|-| |-| |-|-| |",
        "| |     | | | |   | |     |   |",
        "| | | |-| | | | | | |-|-| | |-|",
        "|   |   | | | | | |       | | |",
        "| |-|-| | | | | |-| |-|-|-| | |",
        "|   |   |   | | |   |     | | |",
        "|-|-|-|-| | |-|-|-|-| | | | | |",
        "| | |   | |   |   |   | | |   |",
        "| | | |-|-|-|-| | | | |-| | |-|",
        "|              X|   | |       |",
        "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+",
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