// Author: Adam Nicholas
// File: Individual Contributions- Group Project

#include <iostream>
#include "fonts.h" 
#include "GridCells.h" 
#include "Grid.h"

using namespace std;

extern int getColumns (const char** maze, int rows);

void an_PrintMsg() {
    cout << "anicholas file worked!" << endl;
}

void an_showCreditPage(Rect position, int defaultHeight, int color) { 
    position.bot = defaultHeight;
    ggprint8b(&position, 16, color, "Adam Nicholas: ");
    ggprint8b(&position, 16, color, "Game Designer | Game Programmer");
}

void an_showRulesPage(Rect position, int defaultHeight, int color) { 
    position.bot = defaultHeight;
    ggprint8b(&position, 16, color, "Rule 5: ");
    ggprint8b(&position, 16, color, "Use arrow keys to move. Find the exit.");
}

void an_showWelcomePage(Rect position, int defaultHeight, int color) { 
    position.bot = defaultHeight;
    ggprint8b(&position, 16, color, "press 'R' to view rules page");
}

bool GridCells::isWall() {
    return wall;
}

bool GridCells::isStart() {
    return start;
}

bool GridCells::isEnd() {
    return end;
}

bool anicholas_Midterm(int value) {
    if (value > 0) {
        return true;
    } else {
        return false;
    }
}

void an_printMaze9(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                                int& maze_state)
{
    const char* mazeName = "Maze 9";            // 2. replace
    int rows = 15;                              // 3. replace: 
                                                //          start counting from 1
    int startingPosition[2] = {1, 1};          // 4. replace: 
                                                //          start counting from 0.
                                                //          1st number: left to right
                                                //          2nd number: top to bottom
                                                //  
    int endingPosition[2] = {2, 1};           // 5. replace: 
    //int endingPosition[2] = {5, 13};           // 5. replace: 
                                                //          same as #4.           
                                                //
    int wallColor[3] = {64, 235, 52};             // 6. replace:
                                                //          this is rgb color for wall. 
                                                //          don't forget #7

    // source: https://www.asciiart.eu/art-and-design/mazes
    // corridors need to be 1 space wide, or it will mess up the trail
 

    // 7. replace
    const char* maze[rows] = 
    {

        ".-.-.-.-.-.",
        "|   |     |",
        ": :-: : :-:",
        "|     | | |",
        ":-:-:-: : :",
        "|       | |",
        ": : :-: : :",
        "| |   |   |",
        ": :-:-:-: :",
        "| |     | |",
        ": : :-: : :",
        "|   |   | |",
        ": :-: :-: :",
        "|   | |   |",
        ":-:-:-:-:-:",
    
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

void an_printMaze10(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                                int& maze_state)
{
    const char* mazeName = "Maze 10";            // 2. replace
    int rows = 15;                              // 3. replace: 
                                                //          start counting from 1
    int startingPosition[2] = {1, 1};          // 4. replace: 
                                                //          start counting from 0.
                                                //          1st number: left to right
                                                //          2nd number: top to bottom
                                                //  
    int endingPosition[2] = {2, 1};           // 5. replace: 
    //int endingPosition[2] = {5, 13};           // 5. replace: 
                                                //          same as #4.           
                                                //
    int wallColor[3] = {102, 50, 168};             // 6. replace:
                                                //          this is rgb color for wall. 
                                                //          don't forget #7

    // source: https://www.asciiart.eu/art-and-design/mazes
    // corridors need to be 1 space wide, or it will mess up the trail
 

    // 7. replace
    const char* maze[rows] = 
    {

        ".-.-.-.-.-.",
        "|   |     |",
        ": :-: : :-:",
        "|     | | |",
        ":-:-:-: : :",
        "|       | |",
        ": : :-: : :",
        "| |   |   |",
        ": :-:-:-: :",
        "| |     | |",
        ": : :-: : :",
        "|   |   | |",
        ": :-: :-: :",
        "|   | |   |",
        ":-:-:-:-:-:",
    
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
