// Created by: Eidmone Tagaca
// Source File for Project 3350

#include <iostream>
#include "fonts.h"
#include <iostream>
#include "GridCells.h"
// These are for the timers
#include <ctime>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include "Grid.h"

using namespace std;

extern int getColumns(const char** maze, int rows);

void et_PrintMsg() {
    cout << "Eidmone's file fired" <<endl;
}

void et_showCreditPage(Rect position, int defaultHeight, int color) {
  position.bot = defaultHeight;
  ggprint8b(&position, 16, color, "Eidmone Tagaca: ");
  ggprint8b(&position, 16, color, "Game Designer | Game Developer");
}

void et_showRulesPage(Rect position, int defaultHeight, int color) {
  position.bot = defaultHeight;
  ggprint8b(&position, 16, color, "Rule 4:");
  ggprint8b(&position, 16, color,
     "Once you exit the game, progress will NOT be saved.");
}

void et_showWelcomePage(Rect position, int defaultHeight, int color) {
  position.bot = defaultHeight;
  ggprint8b(&position, 16, color, "press 'C' to view credit page");
}

bool GridCells::setWall(bool input) {
  wall = input;
  return wall;
}

bool GridCells::setStart(bool input) {
  start = input;
  return start;
}

bool GridCells::setEnd(bool input) {
  end = input;
  return end;
}

// ===> Added function for the midterm <===
// Info: receives a string input and outputs it to terminal
void etagaca_midterm(string name) {
  // If the input name is an empty string
  // then we display error to terminal
  if (name == "Kotlin" || name == "Lisp" || name == "Cobol") {
    cout << name << " is not that great" << endl;
  } else {
    // If the input is valid then output this
    cout << name << " is awesome!";
  }
}

int count = 0;
// 1 2
void et_timer(Rect position, int defaultHeight, int color, int& maze_state,  
                                        bool& firstRun, int& current_time) {
    position.bot = defaultHeight;

    if (firstRun == true) {
      count = 0;
    }

    string temp = "Time: " + to_string(count);
    const char *c = temp.c_str();

    ggprint8b(&position, 16, color, c);

    count++;
    current_time = count;
    sleep(1);

    if (count == 1000) {
      maze_state = 404;
    }
}

void et_printMaze11(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                                int& maze_state)
{
    const char* mazeName = "Maze 11";    
    int rows = 23;                                               
    int startingPosition[2] = {22, 21};                                                        
    int endingPosition[2] = {29, 1};                                                              
    int wallColor[3] = {220, 88, 42};
                                                                       
    const char* maze[rows] = 
    {
      "-----------------------------",
      "|     |     |                ",
      "| --- - ----- --------------|",
      "|   |   |     |   |   |     |",
      "--- | --- ----- | | | | ----|",
      "|   | |   |     |   | |     |",
      "| --- | --- ------------- --|",
      "| |   | | | |         | | | |",
      "| ----| | |   ------- | | | |",
      "|     | |   |   |     | |   |",
      "- --- - - ---- ---- - ------|",
      "|     | |         | |       |",
      "- - --- ----- --- - --------|",
      "| | |             |         |",
      "- - - -------- ------ ----- |",
      "| |     |   |             | |",
      "- ----- - - - --- ----- ----|",
      "| |     | | |   |     | |   |",
      "- - ----- - --- - ------- --|",
      "| | |     |   | |       |   |",
      "- - - --------- --- - ----- |",
      "| |               | | X   | |",
      "-----------------------------"
    };

    int columns = getColumns(maze, rows);

    if (firstRun) {
        player[0] = startingPosition[0];
        player[1] = startingPosition[1];

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

void et_printMaze12(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                                int& maze_state)
{
    const char* mazeName = "Maze 12";    
    int rows = 19;                                               
    int startingPosition[2] = {9, 17};                                                        
    int endingPosition[2] = {0, 1};                                                              
    int wallColor[3] = {220, 88, 42};
                                                                       
    const char* maze[rows] = 
    {
      "-----------------------------",
      "      |     |               |",
      "| --- - ----- --------------|",
      "|   |   |     |   |   |     |",
      "|-- | --- ----- | | | | ----|",
      "|   | |   |     |   | |     |",
      "| --- | --- ------------- --|",
      "| | | | | | |    |    | | | |",
      "| | --| | |   ------- | | | |",
      "| |   | |   |   |     | | | |",
      "| --- | | ----  --- - --- --|",
      "|     | |         | |       |",
      "| - --- ----- --- - --------|",
      "| | |   |   |     |         |",
      "| - | ------- ------- ----- |",
      "| | |   |   |             | |",
      "| | |--   - - --- ----- ----|",
      "| |     |X| |   |     | |   |",
      "-----------------------------"
    };

    int columns = getColumns(maze, rows);

    if (firstRun) {
        player[0] = startingPosition[0];
        player[1] = startingPosition[1];

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