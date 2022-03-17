// Author: Adam Nicholas
// File: Individual Contributions- Group Project

#include <iostream>
#include "fonts.h"

using namespace std;

void an_PrintMsg() {
    cout << "anicholas file worked!" << endl;
}

void an_showCreditPage(Rect position, int defaultHeight, int color) { 
    position.bot = defaultHeight;
    ggprint8b(&position, 16, color, "Adam Nicholas: ");
    ggprint8b(&position, 16, color, "Game Designer | Game Programmer | Sound Designer");
}

void an_showRulesPage(Rect position, int defaultHeight, int color) { 
    position.bot = defaultHeight;
    ggprint8b(&position, 16, color, "Rule 5: ");
    ggprint8b(&position, 16, color, "Use arrow keys to move. Find the exit.");
}
