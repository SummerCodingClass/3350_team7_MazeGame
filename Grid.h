#include <vector>
using namespace std;


class Grid {

    
    public:
        int rows;
        int columns;
        int mazeEnd[2];
        int wallColor[3];
        int gridPlayer[2];
        // bool movingNext;
        bool gridFirstRun;
        vector <vector <GridCells>> mazeGrid; 

        Grid();

        Grid(const char** maze, int inputRows, int inputColumns, int player[2], 
                                                int end[2], int colorChoice[3]); 

        vector <vector <GridCells>> GridGetter(); 
                                                    
        void setWallColor(int colorChoice[3]);

        void printGrid(Rect position, int rows, int columns,

        int (&player)[2], int defaultHeight, int color, const char* mazeName,
                                                            bool& endReached);

        void exitImage(int i, int j);

        void wallImage(int i, int j, int r, int g, int b);

        void playerImage (int yres, unsigned int textid, int player[2]);
};


// ref for 2d vectors:
// https://www.geeksforgeeks.org/vector-of-vectors-in-c-stl-with-examples/