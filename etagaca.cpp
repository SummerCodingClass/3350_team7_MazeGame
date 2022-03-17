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
  ggprint8b(&position, 16, color, "Eidmone: ");
}

