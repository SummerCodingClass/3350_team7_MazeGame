//Author: Jennifer K
//Individual Source File for Project


#include "fonts.h"
#include <iostream>
#include <cstring> //for strlen()
#include <GL/glx.h>
#include "GridCells.h"
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
        // glColor3ub(20,20,20);
        
        if (maze[i][j] == ' ' || maze[i][j] == 'X') {
          glColor3ub(20,20,20);
        }
        
        if (i == player[1] && j == player[0]) {
          glColor3ub(255,250,250);
        }

        // if (i == player[1] + 1 && j == player[0]) { // i + 1 = down arrow key
        //   glColor3ub(232,135,5); // orange // 
        // }

        // if (i == player[1] - 1 && j == player[0]) { // i - 1 = up arrow key
        //   glColor3ub(232,135,5); // orange // 
        // }

        // if (i == player[1] && j == player[0] + 1) { // j + 1 = right arrow key
        //     glColor3ub(232,135,5); // orange // 
        // }

      
        // if (i == player[1] && j == player[0] - 1) { // j - 1 = left arrow key
        //     glColor3ub(232,135,5); // orange // 
        // }



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

void jk_printMaze1(Rect position, int defaultHeight, int color, 
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


void jk_printMaze2(Rect position, int defaultHeight, int color, 
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


void jk_printMaze3(Rect position, int defaultHeight, int color, 
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


  void jk_page_transition(int& maze_state, const char* keyChecked, 
                                                        bool& firstRun) 
{
    //case XK_b;
    if (strcmp(keyChecked, "b") == 0) {
			if (maze_state == 0) {
				//do nothing
			} else if (maze_state > 0) {
				maze_state = 0;
      }
			
			return;
    }

		//case XK_s;
    if (strcmp(keyChecked, "s") == 0) {
      if (maze_state == 0) {
        firstRun = true;
        maze_state = 1;
      } else if (maze_state == 1) {
        firstRun = true;
        maze_state = 2;
      } else if (maze_state == 2) {
        firstRun = true;
        maze_state = 3;
      }

      return; 
    }

    if (strcmp(keyChecked, "r") == 0) {
      if (maze_state == 0) {
        maze_state = 11;
      }
    return; 
    }
    
    if (strcmp(keyChecked, "c") == 0) {
      if (maze_state == 0) {
        maze_state = 12;
      }
    return; 
    }

    // if (strcmp(keyChecked, "up") == 0) {
    //   if (maze_state == 1 || maze_state == 2 || maze_state == 3) {
        
    //   }
    // return; 
    // }


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



//could be replaced by picture logo
void jk_showWelcomePageTitle(Rect position, int defaultHeight, int color) {
  position.bot = defaultHeight;
  
  ggprint40(&position, 16, color, "The MAze Game");
}


void jk_playerMovement(char* keys, int (&player)[2]) {
  
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


bool GridCells::playerCurrent() {
  return currentPosition;
}


bool GridCells::hasTraveled() {
  return traveled;
}