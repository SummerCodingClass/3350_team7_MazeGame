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
bool jhicks_midterm_function(int maze_state)
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
    float w = 300.0;
    glTranslatef(xres/2, yres -250, 0);
    glColor3ub(255, 255, 255);
    glBindTexture(GL_TEXTURE_2D, textid);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-w,  w);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( w,  w);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( w, -w);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-w, -w);
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
                                        
    int startingPosition[2] = {4, 1};  // 4. replace: 
                                        //          start counting from 0.
                                        //          1st number: left to right
                                        //          2nd number: top to bottom
                                        //  
    int endingPosition[2] = {3, 1};   // 5. replace: 
    //int endingPosition[2] = {6, 1};
                                        //          same as #4. 
                                        //          don't forget #6
    int wallColor[3] = {0, 53, 148};
    // source: https://www.asciiart.eu/art-and-design/mazes

    // 6. replace
    const char* maze[rows] = 
    {
    
        ".-.--.--.--.--.-.",
        "|    |       -| |",
        ": :--:--: -: -: :",
        "| |    -| -|    |",
        ": : -: -:--:--: :",
        "| | -|        | |",
        ": : -:--:--:- : :",
        "| |        |- | |",
        ": :--:--:- :- : :",
        "|    |     |- | |",
        ":-:- :- :--:- : :",
        "|       |       |",
        ":--:--:--:--:--::"
    
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
    int rows = 23;                    
                                        //          start counting from 1
    int startingPosition[2] = {1, 21};  // 4. replace: 
                                        //          start counting from 0.
                                        //          1st number: left to right
                                        //          2nd number: top to bottom
                                        // 
    int endingPosition[2] = {1, 20};                                      
    //int endingPosition[2] = {19, 1};   // 5. replace: 

    int wallColor[3] = {70, 255, 0};
    // source: https://www.asciiart.eu/art-and-design/mazes

    const char* maze[rows] = 
    {
    
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
      "8 8       8       8     8         8 8",
      "8 8 aaaaa 8 aaa aa8aa aa8 aaa aaa 8 8",
      "8       8   8 8     8     8 8 8   8 8",
      "8 aaa a 8aaa8 8aaaa 8aa a 8 8 8aaa8 8",
      "8 8 8 8       8     8 8 8 8 8     8 8",
      "8 a 8a8aaaa a 8 aaaa8 8a8 8 8aaaa 8 8",
      "8 8       8 8 8   8     8     8   8 8",
      "8 8aaaaaa 8a8 8aa 8 aaa 8aaaa 8 aa8 8",
      "8     8   8 8   8 8   8     8 8     8",
      "8 aaa 8aa 8 8aa 8 8aaa8 a a 8 8aaaaa8",
      "8   8   8 8 8   8   8   8 8 8   8   8",
      "8 aa8aa 8 8 8 aa8aa 8 aa8 8 8aa 8aa 8",
      "8 8   8 8     8   8 8   8 8   8     8",
      "8 aaa 8 8aaaa 8aa 8 8aa 8a8 aa8aaaa 8",
      "8 8   8     8     8   8 8 8       8 8",
      "8 8 aa8aa a 8aa aa8aa 8 8 8aaaaaa 8 8",
      "8 8     8 8 8 8 8     8       8 8   8",
      "8 8aaaa 8 8 8 8a8 8aaa8 aaaaa 8 8aaa8",
      "8 8   8 8 8     8     8 8   8       8",
      "8 8 aa8 8a8 aaa 8aaaa 8a8 a 8aaaa a 8",
      "8 8         8     8       8       8 8",
      "888aaaaaaaaa8aaaaa8aaaaaaa8aaaaaaa8a8",

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
