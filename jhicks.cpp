// Jeff Hicks
//
// Source File for Project
//
#include <iostream>
#include "fonts.h"
using namespace std;



void jh_PrintMsg()
{
    cout << "Hello from Jeff's file!" << endl;
    return;
}


void jh_showCreditPage(Rect position, int defaultHeight, int color )
{
    position.bot = defaultHeight;
    ggprint8b(&position, 16, color, "Jeff Hicks");

}
