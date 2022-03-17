// Eidmone Tagaca
// Source File for Project

#include <iostream>
#include "fonts.h"
#include <iostream>
using namespace std;

void et_PrintMsg() 
{
    cout << "Eidmone's file fired" <<endl;
}

void et_showCreditPage(Rect position, int defaultHeight, int color) {
  position.bot = defaultHeight;
  ggprint8b(&position, 16, color, "Eidmone Tagaca: ");
  ggprint8b(&position, 16, color, "Game Developer | Game Tester");
}

void et_showRulesPage(Rect position, int defaultHeight, int color) {
  position.bot = defaultHeight;
  ggprint8b(&position, 16, color, "Rule 4:");
  ggprint8b(&position, 16, color, "Once you exit the game, progress will NOT be saved.");
}