// Author: Adam Nicholas
// File: Individual Contributions- Group Project

#include <iostream>
#include "fonts.h" 
#include "GridCells.h" 

using namespace std;

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

void anicholasPrint(int num) {
    cout << "Enter 1 to display my Odin username: ";
    cin >> num;

    if (num == 1) {
        cout << "Odin Username: anicholas" << endl;
    } else {
        cout << "Cannot display username!" << endl;
    }
}
