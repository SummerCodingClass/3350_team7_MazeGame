//Jesus Rojas
//Group Project Source file

#include <iostream>
#include "fonts.h"

using namespace std;

/*Comment until future use
class jrojas_test {
    private:
        string jr_name;

    public:
        void PrintName(string jr_name) 
        {
            cout << jrojas_test;
            return;
        }
};
*/

void jr_PrintMsg()
{
    cout << "jrojas -testing this out! Hello there!" << endl;
}

void jr_showCreditPage(Rect position, int defaultHeight, int color) {
  position.bot = defaultHeight;
  ggprint8b(&position, 16, color, "Jesus Rojas:");
  ggprint8b(&position, 16, color, "Game Designer | Game Programmer");
}

void jr_showRulesPage(Rect position, int defaultHeight, int color) {
  position.bot = defaultHeight;
  ggprint8b(&position, 16, color, "Rule 3:");
  ggprint8b(&position, 16, color, "You could pause game and resume.");
}

void jr_showWelcomePage(Rect position, int defaultHeight, int color) {
  position.bot = defaultHeight;
  ggprint8b(&position, 16, color, "press 'S' to start game");
}
