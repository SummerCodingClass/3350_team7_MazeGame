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
    int mazeEnd[2];
    int wallColor[3];
    // int currentPosition[2];

    
    // GridCells currentPosition;
    GridCells startingPosition;
    GridCells endingPosition;    
    vector <vector <GridCells>> mazeGrid; 
    
    int gridPlayer[2];
    
    // ref for 2d vectors:
    // https://www.geeksforgeeks.org/vector-of-vectors-in-c-stl-with-examples/
    
    void setWallColor(int colorChoice[3]);



    Grid() 
    {
        rows = 0;
        columns = 0;
    }


    // default wall color is green if unspecified
    Grid(const char** maze, int inputRows, int inputColumns, int player[2], 
                                                int end[2]) 
    {
        rows = inputRows;
        columns = inputColumns;
        gridPlayer[1] = player[1];
        gridPlayer[0] = player[0];

        int colorChoice[3] = {0, 128, 0};
        setWallColor(colorChoice);

     
        for (int i = 0; i < rows; i++) {
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
    
        
            mazeGrid.push_back(v1);
        }


        
    }

    
  

    // can specify wall color
    Grid(const char** maze, int inputRows, int inputColumns, int player[2], 
                                                int end[2], int colorChoice[3]) 
    {
        rows = inputRows;
        columns = inputColumns;
        gridPlayer[1] = player[1];
        gridPlayer[0] = player[0];
        setWallColor(colorChoice);

        // cout << "test";

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
                temp.setXcoord(j);
                temp.setYcoord(i);
                
                // bool isCurrent = false;
                if (i == end[1] && j == end[0]) {
                    // cout << "end point at j: " << j << ", i: " << i << endl;
                    temp.setEnd(true);
                    mazeEnd[1] = i;
                    mazeEnd[0] = j;

                } else {
                    temp.setEnd(false);
                }



                if (i == gridPlayer[1] && j == gridPlayer[0]) {
                    temp.setCurrent(true);
                    temp.setTraveled(false);
                    // currentPosition[0] = j;
                    // currentPosition[1] = i;
                    // isCurrent = true;

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

    
    GridCells returnStartingPosition();
    GridCells returnEndingPosition();



vector <vector <GridCells>> GridGetter() 
{
    return mazeGrid;
}





   
void printGrid(Rect position, int rows, int columns,
        int (&player)[2], int defaultHeight, int color, const char* mazeName,
                                                            bool& endReached) 
{

    ggprint8b(&position, 16, color, mazeName);

    // DON'T FORGET TO REMOVE!!!!
    // cout << "in printGrid: " << endl;
    // cout << "player: " << player[0] << ",  " << player[1] << endl;
    // cout << "mazeEnd: " << mazeEnd[0] << ",  " << mazeEnd[1] << endl;
    
    if (player[1] == mazeEnd[1] && player[0] == mazeEnd[0]) {
            
            cout << "in printGrid, endReached marked true" << endl;
            endReached = true;
            
    }



    // ==============================
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

            
            
            //color of wall
            // glColor3ub(200,50,50);
            // glColor3ub(0,128,0);
            glColor3ub(wallColor[0],wallColor[1], wallColor[2]);

            if(mazeGrid[i][j].isSpace()) {
                glColor3ub(20,20,20);
            }


            
            if(mazeGrid[i][j].isEnd()) {
                glColor3ub(128,128,128);
            }




            if(mazeGrid[i][j].playerCurrent()) {
                glColor3ub(255,250,250);
                // cout << "is player current: " <<
                // mazeGrid[i][j].playerCurrent() << endl;
            }



            if(mazeGrid[i][j].hasTraveled()) {
                // glColor3ub(255,255,0); // yellow
                glColor3ub(0,255,255);
            }

            // -----------------alternative: this works too-----------------
            // if(i == player[1] && j == player[0]) {
            //     glColor3ub(255,250,250);
            //     mazeGrid[i][j].setTraveled(true);
            // }
            // // ---------------------------------------------------
            


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

