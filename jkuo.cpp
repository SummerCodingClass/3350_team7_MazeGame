//Author: Jennifer K
//Individual Source File for Project


#include "fonts.h"
#include <iostream>
#include <cstring> //for strlen()
#include <GL/glx.h>
// #include <windows.h>
using namespace std;
// extern class Global gl;

// don't write classes yet

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




void jk_printMaze1(Rect position, int defaultHeight, int color) 
{

    const char* mazeName = "Maze 1";
    int rows = 31;
    int player[2] = {1, 29};

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
      "+  +  +  +--+--+--+--+  +--+  +  +--+--+--+--+  +  +--+--+--+  +",
      "|  |                       |  |     |  |  |     |        |  |  |",
      "+  +  +--+--+--+--+--+--+--+--+--+  +--+--+  +--+--+--+  +--+  +",
      "|  |        |     |  |        |  |  |  |              |  |     |",
      "+--+--+--+  +  +  +  +  +--+  +--+  +--+  +--+  +--+--+  +  +--+",
      "|     |     |  |  |  |  |  |        |  |  |     |     |  |     |",
      "+  +--+  +--+  +  +  +  +--+--+--+--+--+  +  +--+  +  +  +--+--+",
      "|           |  |  |  |                 |  |  |     |  |        |",
      "+--+--+--+  +--+  +  +--+--+--+--+--+  +  +  +--+--+--+--+--+  +",
      " X                |                 |     |              |      ",
      "+-----+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+"


    
    };



    jk_printMazeGrid(position, maze, rows, player, defaultHeight, color, 
                                                                    mazeName);


}


void jk_printMaze2(Rect position, int defaultHeight, int color) 
{
    const char* mazeName = "Maze 2";
    int rows = 27;
    int player[2] = {18, 23};

    
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

    

    jk_printMazeGrid(position, maze, rows, player, defaultHeight, color, 
                                                                    mazeName);




}


void jk_printMaze3(Rect position, int defaultHeight, int color) 
{
    const char* mazeName = "Maze 3";
    int rows = 23;
    int player[2] = {1, 22};


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

    
    jk_printMazeGrid(position, maze, rows, player, defaultHeight, color, 
                                                                    mazeName);
    


}


  void jk_page_transition(int& maze_state, char keyChecked) {
    //case XK_b;
    if (keyChecked == 'b') {
			if (maze_state == 0) {
				//do nothing
			} else if (maze_state > 0) {
				maze_state = 0;
      }
			
			return;
    }

		//case XK_s;
    if (keyChecked == 's') {
      if (maze_state == 0) {
        maze_state = 1;
      } else if (maze_state == 1) {
        maze_state = 2;
      } else if (maze_state == 2) {
        maze_state = 3;
      }

      return; 
    }

    if (keyChecked == 'r') {
      if (maze_state == 0) {
        maze_state = 11;
      }
    return; 
    }
    
    if (keyChecked == 'c') {
      if (maze_state == 0) {
        maze_state = 12;
      }
    return; 
    }
  }

// void jk_printMaze4(Rect position, int defaultHeight, int color) 
// {
   
    
//     jk_printMazeGrid(position, maze, rows, defaultHeight, color, mazeName);
    
//     // jk_printMazeGeneral(position, maze, rows, defaultHeight, color);
    


// }


void jk_showCreditPage(Rect position, int defaultHeight, int color) {
  position.bot = defaultHeight;
  ggprint8b(&position, 16, color, "Jennifer Kuo:");
  ggprint8b(&position, 16, color, "Game Designer | Game Programmer");
}


void jk_showRulesPage(Rect position, int defaultHeight, int color) {
  position.bot = defaultHeight;
  ggprint8b(&position, 16, color, "Rule 1:");
  ggprint8b(&position, 16, color, 
                              "Timer will start immediately upon game start.");
}



void jk_showWelcomePage(Rect position, int defaultHeight, int color) {
  position.bot = defaultHeight;
  
  ggprint13(&position, 16, color, "------------ Instructions ------------");
}



//will delete
void jk_showWelcomePageTitle(Rect position, int defaultHeight, int color) {
  position.bot = defaultHeight;
  
  ggprint40(&position, 16, color, "The MAze Game");
}







void jk_printMazeGrid(Rect position, const char* maze[], int rows,
    int startingPosition[2], int defaultHeight, int color, const char* mazeName) 
{   


    static int player[2];
    player[0] = startingPosition[0]; // x
    player[1] = startingPosition[1]; // y

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
        
        if (maze[i][j] == ' ') {
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


//if up arrow key is pressed
//position nextPosition = validate(); 
  // validate is going to return the next position if legit
  // return currentPosition if not legit

//if (legit movement and created a diff position) {
//   createMap();
// }


//note: update function call with current + next position;

Grid jk_traverseConstCharArray_CREATE(Rect position, const char* maze[], 
int rows, int startingPosition[2], int endingPosition[2], 
int currentPosition[2], 
int nextPosition[2], int defaultHeight, int color, const char* mazeName) 
{   

// could also pass "true/false" as argument
bool initialSetUp = false;

if (nextPosition[2] == [-1, -1]) {
  initialSetUp = true;
}

//determining player position

    static int player[2];
    player[0] = currentPosition[0]; // x
    player[1] = currentPosition[1]; // y

    ggprint8b(&position, 16, color, mazeName);
    

//determining columns
    int columns = strlen(maze[0]);
    for (int i = 1; i < rows; i++) {
      if ((int)strlen(maze[i]) > columns) {
        columns = strlen(maze[i]);
      }
    }


// creating actual grid
  Grid gridMaze = Grid(rows, columns);

  for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
          

          if (initialSetUp) {
              //setting x/y coord
              Grid[i][j] = GridCells.setXcoord();
              Grid[i][j] = GridCells.setYcoord();


              //setting wall + space property
              if (maze[i][j] == ' ') {
                Grid[i][j].setSpace(true);
                Grid[i][j].setWall(false);
              }
              else if (maze[i][j] == 'X') {
                Grid[i][j].setSpace(true);
                Grid[i][j].setWall(false);
              
              }
              else {
                Grid[i][j].setSpace(false);
                Grid[i][j].setWall(true);
              }


              // setting starting point of the maze
              if (i == startingPosition[1] && j == startingPosition[0]) {
                Grid[i][j].setStart(true);
              }
              else {
                Grid[i][j].setStart(false);
              }


              // setting end point of the maze
              if (i == endingPosition[1] && j == endingPosition[0]) {
                Grid[i][j].setEnd(true);
              }
              else {
                Grid[i][j].setEnd(false);
              }



          }

          // if it's not the initialSetUp of the map
          else {
            // check if the movement is allowed
                  // then update player movement + traveled
              int tempX = nextPosition[1];
              int tempY = nextPosition[0];
              if (Grid[tempX][tempY].isSpace) {
                Grid[i][j].setTraveled(true);
                Grid[tempX][tempY].setCurrent(true);
              }



// we paused here to 
              else {
                Grid[i][j].setEnd(false);
              }



              if (i == player[1] && j == player[0]) {
                Grid[i][j].setEnd(true);
              }
              else {
                Grid[i][j].setEnd(false);
              }







          }





    }
  }




  return gridMaze;

}



//Constructor's logic:
Grid(int rows = 0, int columns = 0);
