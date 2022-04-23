#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <ctime>
#include <cmath>
#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "log.h"
#include "fonts.h"

#include "GridCells.h"
#include "Grid.h"


#include "Global.h"
// #ifndef GLOBAL_H_
// #define GLOBAL_H_
// #include "Global.h"
// #endif //GLOBAL_H_


Global::Global() {
    xres = 960;
    yres = 600;
    memset(keys, 0, 65536);
    maze_state = 0;
    player[0] = 0;
    player[1] = 0;
    firstRun = true;
    endReached = false;
    // Grid mazeGrid = NULL;
    Grid mazeGrid;
    showScores = false;
    maxMaze = 12;
    // timeBeaten[13] = {-1};
    for (int i = 0; i <= maxMaze; i++) {
        timeBeaten[i] = -1;
    }
    firstAttempt = false;
    newHighScore = false;
    oldScore = 0;
    newScore = 0;
}