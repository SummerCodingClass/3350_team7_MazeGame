
struct GridCells {
    
    int xcoord;
    int ycoord;
    bool space;
    bool wall;
    bool start;
    bool end;
    bool currentPosition;
    bool traveled;    

};



class Grid {



    
    public:
    int rows;
    int columns;
    GridCells maze[rows][columns];
    


    Grid(int rows = 0, int columns = 0);
    // int calculateColumns(); // this is a function used in the constructor.



    int setXcoord(int input);
    int setYcoord(int input);
    bool setSpace(bool input);
    bool setWall(bool input);
    bool setStart(bool input);
    bool setEnd (bool input);
    bool setCurrent(bool input);
    bool setTraveled(bool input);


    bool isSpace(GridCells cell);
    bool isWall(GridCells cell);
    bool isStart(GridCells cell);
    bool isEnd(GridCells cell);
    bool playerCurrent(GridCells cell);
    bool hasTraveled(GridCells cell);
    
    bool resetGrid(GridCells cell); // reset everything, and also flag initial setup as false.

    //if it hasnt been travelled, and it isn't a wall:
        // currentposition = "hastravelled"
        // next position = "player current"
    

    
    void printGrid();
  

};