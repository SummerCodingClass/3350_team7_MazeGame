//Jesus Rojas
//Group Project Source file

#include <iostream>
#include "fonts.h"
#include "GridCells.h"

using namespace std;

/*Comment until future use
class jrojas_test {
    private:
        string jr_name;

    public:
        void PrintName(string jr_name) 
        {
            cout << jrojas_test;
            return;
        }
};
*/

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

void jr_midterm_func(int value) {
    /*Test value if postive, negative or invalid input*/
    if (value >= 0)
        cout << "The value: " << value << " is a postive number";
    else if (value < 0)
        cout << "The value: " << value << " is a negative number";
    else
        cout << "The value input is INVALID, try again!\n";
    cout << "\n";
}

void jr_PrintMsg()
{
    cout << "jrojas -testing this out! Hello there!" << endl;
}

void jr_showCreditPage(Rect position, int defaultHeight, int color) {
  position.bot = defaultHeight;
  ggprint8b(&position, 16, color, "Jesus Rojas:");
  ggprint8b(&position, 16, color, "Game Designer | Game Programmer");
}

void jr_showRulesPage(Rect position, int defaultHeight, int color) {
  position.bot = defaultHeight;
  ggprint8b(&position, 16, color, "Rule 3:");
  ggprint8b(&position, 16, color, "You could pause game and resume.");
}

void jr_showWelcomePage(Rect position, int defaultHeight, int color) {
  position.bot = defaultHeight;
  ggprint8b(&position, 16, color, "press 'S' to start game");
}

bool GridCells::setCurrent(bool input) {
    currentPosition = input;
    return currentPosition;
}

bool GridCells::setTraveled(bool input) {
    traveled = input;
    return traveled;
}

bool GridCells::isSpace() {
    return space;
}

// --------------------------------------------------------------------------
// start of template for new maze
// --------------------------------------------------------------------------
/*
void jk_printMaze1(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                                int& maze_state)
{
    const char* mazeName = "Maze 1";
    int rows = 31;
    int startingPosition[2] = {1, 29};
    int endingPosition[2] = {42, 29}; 

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
        " X          |           |   |         |    ",
        "+---+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"
    
    };

    int columns = getColumns(maze, rows);

    if (firstRun) {
        player[0] = startingPosition[0]; // x
        player[1] = startingPosition[1]; // y

        mazeGrid = Grid(maze, rows, columns, player, endingPosition);
   
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
*/
// --------------------------------------------------------------------------
// end of template for new maze
// --------------------------------------------------------------------------