#include <vector>
using namespace std;


class Grid {

    
    public:
        int rows;
        int columns;
        int mazeEnd[2];
        int wallColor[3];
        int gridPlayer[2];
        vector <vector <GridCells>> mazeGrid; 




        Grid();

        // default wall color is green if unspecified
        // Grid(const char** maze, int inputRows, int inputColumns, int player[2], 
        //                                                             int end[2]); 
        // // can specify wall color
        Grid(const char** maze, int inputRows, int inputColumns, int player[2], 
                                                int end[2], int colorChoice[3]); 

        vector <vector <GridCells>> GridGetter(); 
                                                    
        void setWallColor(int colorChoice[3]);

        void printGrid(Rect position, int rows, int columns,
        int (&player)[2], int defaultHeight, int color, const char* mazeName,
                                                            bool& endReached);

};


// ref for 2d vectors:
// https://www.geeksforgeeks.org/vector-of-vectors-in-c-stl-with-examples/