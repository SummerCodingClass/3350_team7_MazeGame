// Jeff Hicks
//
// Source File for Project
//
#include <iostream>
#include "fonts.h"
#include "GridCells.h"
using namespace std;

void jhicksMidtermFunction(bool test) {
    if (test == false) {
        cout << "Your test is not true."
    } else {
        cout << "Good Work!"
    }
}

void jh_PrintMsg() {
    cout << "Hello from Jeff's file!" << endl;
    return;
}


void jh_showCreditPage(Rect position, int defaultHeight, int color ) {
    position.bot = defaultHeight;
    ggprint8b(&position, 16, color, "Jeff Hicks:");
    ggprint8b(&position, 16, color, "Game Designer | Game Programmer");

}


void jh_showRulesPage(Rect position, int defaultHeight, int color) {
    position.bot = defaultHeight;
    ggprint8b(&position, 16, color, "Rule 2:");
    ggprint8b(&position, 16, color, "Timer will stop once you hit the exit.");
}


void jh_showWelcomePage(Rect position, int defaultHeight, int color) {
    position.bot = defaultHeight;
    ggprint8b(&position, 16, color, "right click to print msgs to console");
}

int GridCells:: setXcoord(int input) {
    xcoord = input;
    return xcoord;
}

int GridCells:: setYcoord(int input) {
    ycoord = input;
    return ycoord;
}

bool GridCells:: setSpace(bool input) {
    space = input;
    return space;
}

