//remove
#include <GL/glx.h>
#include "fonts.h"


//keep
#include <vector>
using namespace std;


class Grid {

    
    public:
    int rows;
    int columns;
    GridCells currentPosition;
    GridCells startingPosition;
    GridCells endingPosition;    
    vector <vector <GridCells> > mazeGrid; 
// ref: https://www.geeksforgeeks.org/vector-of-vectors-in-c-stl-with-examples/
    


    Grid() {
        rows = 0;
        columns = 0;
    }

    Grid(const char** maze, int inputRows = 0, int inputColumns = 0) {
        rows = inputRows;
        columns = inputColumns;
        //mazeGrid = mazeGrid[];

    
    // for (int i = 0; i < rows; i++) { 
    //     for (int j = 0; j < columns; j++) {
    //         printf("%c\n", maze[i][j]);
            
    //     }
            
    // }



    // Inserting elements into vector
    for (int i = 0; i < rows; i++) {
        // Vector to store column elements
        vector <GridCells> v1;
  
        for (int j = 0; j < columns; j++) {
            
            GridCells temp;

            if (maze[i][j] == ' ') {
                temp.setSpace(true);
                temp.setWall(false);
            } else if (maze[i][j] == 'X') {
                temp.setSpace(true);
                temp.setWall(false);
            } else {
                temp.setSpace(false);
                temp.setWall(true);
            }


            v1.push_back(temp);
        }
  
        // Pushing back above 1D vector
        // to create the 2D vector
        mazeGrid.push_back(v1);
    }


        
    }
    // int calculateColumns(); // this is a function used in the constructor.

    GridCells returnCurrentPosition();
    GridCells returnStartingPosition();
    GridCells returnEndingPosition();


   
    void printGrid(Rect position, int rows, int columns,
        int (&player)[2], int defaultHeight, int color, const char* mazeName) 
  {

       ggprint8b(&position, 16, color, mazeName);

        // DON'T FORGET TO REMOVE!!!!
        player[0] = 0;
        player[1] = 1;

        // ==============================

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                glColor3ub(200,50,50);
                if(mazeGrid[i][j].isSpace()) {
                    glColor3ub(20,20,20);

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
    
    // there's a very high chance that we won't need resetGrid().
    bool resetGrid(); // reset everything, and also flag initial setup as false. 

    //if it hasnt been travelled, and it isn't a wall:
        // currentposition = "hastravelled"
        // next position = "player current"
    
    
  

};