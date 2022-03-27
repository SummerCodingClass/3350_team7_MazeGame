
class Grid {

    
    public:
    int rows;
    int columns;
    GridCells currentPosition;
    GridCells startingPosition;
    GridCells endingPosition;

    GridCells maze[rows][columns];
    


    Grid(int rows = 0, int columns = 0);
    // int calculateColumns(); // this is a function used in the constructor.

    GridCells returnCurrentPosition();
    GridCells returnStartingPosition();
    GridCells returnEndingPosition();


   
    void printGrid();
    
    // there's a very high chance that we won't need resetGrid().
    bool resetGrid(); // reset everything, and also flag initial setup as false. 

    //if it hasnt been travelled, and it isn't a wall:
        // currentposition = "hastravelled"
        // next position = "player current"
    
    
  

};