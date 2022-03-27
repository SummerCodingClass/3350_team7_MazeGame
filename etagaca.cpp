// Eidmone Tagaca
// Source File for Project

#include <iostream>
#include "fonts.h"
#include <iostream>
#include "Grid.h"

using namespace std;

void et_PrintMsg() 
{
    cout << "Eidmone's file fired" <<endl;
}

void et_showCreditPage(Rect position, int defaultHeight, int color) {
  position.bot = defaultHeight;
  ggprint8b(&position, 16, color, "Eidmone Tagaca: ");
  ggprint8b(&position, 16, color, "Game Designer | Game Developer");
}

void et_showRulesPage(Rect position, int defaultHeight, int color) {
  position.bot = defaultHeight;
  ggprint8b(&position, 16, color, "Rule 4:");
  ggprint8b(&position, 16, color, "Once you exit the game, progress will NOT be saved.");
}

void et_showWelcomePage(Rect position, int defaultHeight, int color) {
  position.bot = defaultHeight;
  
  ggprint8b(&position, 16, color, "press 'C' to view credit page");
}

bool GridCells::setWall(bool input) {
  return wall;
}


bool GridCells::setStart(bool input) {
  return start;
}

bool GridCells::setEnd(bool input) {
  return end;
}


