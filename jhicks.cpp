// Jeff Hicks
//
// Source File for Project
//
#include <iostream>
#include <GL/glx.h>
#include "fonts.h"
#include "GridCells.h"
#include "Grid.h"

//determines if the maze state is the home page
bool jhicks_midterm_function(int& maze_state)
{
    /*
    if (maze_state == 0)
    	cout << "HOME SCREEN" << endl;
    else
	    cout << "NOT HOME SCREEN" << endl;
    */
    return (maze_state == 0);
}


void jh_PrintMsg()
{   
    cout << "Hello from Jeff's file!" << endl;
    return;
}


void jh_showCreditPage(Rect position, int defaultHeight, int color)
{
    position.bot = defaultHeight;
    ggprint8b(&position, 16, color, "Jeff Hicks:");
    ggprint8b(&position, 16, color, "Game Designer | Game Programmer");
}

void jh_showRulesPage(Rect position, int defaultHeight, int color)
{
    position.bot = defaultHeight;
    ggprint8b(&position, 16, color, "Rule 2:");
    ggprint8b(&position, 16, color, 
        "Timer will stop once you hit the exit.");
}


void jh_showWelcomePage(Rect position, int defaultHeight, int color)
{
    position.bot = defaultHeight;
    ggprint8b(&position, 16, color, 
        "right click to print msgs to console");
}

int GridCells:: setXcoord(int input)
{
    xcoord = input;
    return xcoord;
}

int GridCells:: setYcoord(int input)
{
    ycoord = input;
    return ycoord;
}

bool GridCells:: setSpace(bool input)
{
    space = input;
    return space;
}

void jh_Image(int xres, int yres, unsigned int textid)
{
    glPushMatrix();
    glTranslatef(xres/2, yres/2, 0);
    float w = 200.0;
    glColor3ub(255, 255, 255);
    glBindTexture(GL_TEXTURE_2D, textid);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-w,-w);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-w,w);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(w,w);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(w,-w);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

extern int getColumns (const char** maze, int rows);

void jh_printMaze5(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                                int& maze_state)
{
    const char* mazeName = "Maze 5";    
    int rows = 13;                     
                                        
    int startingPosition[2] = {1, 12};  // 4. replace: 
                                        //          start counting from 0.
                                        //          1st number: left to right
                                        //          2nd number: top to bottom
                                        //  
    int endingPosition[2] = {10, 0};   // 5. replace: 
                                        //          same as #4. 
                                        //          don't forget #6
    int wallColor[3] = {240,248,255};
    // source: https://www.asciiart.eu/art-and-design/mazes

    // 6. replace
    const char* maze[rows] = 
    {
    
        ".--.--.--.  .--.--.",
        "|     |        |  |",
        ":  :--:  :  :  :  :",
        "|  |     |  |     |",
        ":  :  :  :--:--:--:",
        "|  |  |           |",
        ":  :  :--:--:--:  :",
        "|  |        |  |  |",
        ":  :--:--:  :  :  :",
        "|     |     |  |  |",
        ":--:  :  :--:  :  :",
        "|        |        |",
        ":X :--:--:--:--:--:"
    
    };

    int columns = getColumns(maze, rows);

    if (firstRun) {
        player[0] = startingPosition[0]; // x
        player[1] = startingPosition[1]; // y

        mazeGrid = Grid(maze, rows, columns, player, endingPosition, wallColor);
   
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


void jh_printMaze6(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                                int& maze_state)
{
    const char* mazeName = "Maze 6";   
    int rows = 10;                    
                                        //          start counting from 1
    int startingPosition[2] = {1, 29};  // 4. replace: 
                                        //          start counting from 0.
                                        //          1st number: left to right
                                        //          2nd number: top to bottom
                                        //  
    int endingPosition[2] = {42, 29};   // 5. replace: 

    int wallColor[3] = {135,206,250};
    // source: https://www.asciiart.eu/art-and-design/mazes

    const char* maze[rows] = 
    {
                    
        "┌─┬─────────────────────┬─┐", 
        "│ └───┐ ╶─────┐ ╶───┬─╴ ╵ │", 
        "├───┐ ├───╴ ┌─┴─┐ ╷ └─┬─┐ │", 
        "│ ╷ │ │ ╶─┬─┘ ╷ │ └─┐ │ ╵ │", 
        "│ ├─┘ ├───┤ ┌─┤ └───┤ └─┐ │", 
        "│ │ ┌─┘ ╷ ╵ │ └───╴ │ ╷ │ │", 
        "│ │ ╵ ┌─┼───┤ ┌─────┤ │ │ │", 
        "│ └───┘ ╵ ╷ ╵ ╵ ┌─╴ └─┘ │ │", 
        "└─────────┴─────┴───────┴─┘ "
    
    };

    int columns = getColumns(maze, rows);

    if (firstRun) {
        player[0] = startingPosition[0]; // x
        player[1] = startingPosition[1]; // y

        mazeGrid = Grid(maze, rows, columns, player, endingPosition,wallColor);
   
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
