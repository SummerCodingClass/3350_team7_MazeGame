
class GridCells {
    public:
    int xcoord;
    int ycoord;
    bool space;
    bool wall;
    bool start;
    bool end;
    bool currentPosition;
    bool traveled;    


    // GridCells() {
    //     xcoord = 0;
    //     ycoord = 0;
    //     space = true;
    //     wall = true;
    //     start = true;
    //     end = true;
    //     currentPosition = true;
    //     traveled = true;
    // }

    // GridCells(int x, int y, bool uspace, bool uwall, 
    //             bool ustart, bool uend, bool ucurrent, bool utravel) {

    //     xcoord = x;
    //     ycoord = y;
    //     space = uspace;
    //     wall = uwall;
    //     start = ustart;
    //     end = uend;
    //     currentPosition = ucurrent;
    //     traveled = utravel;


    // }

    GridCells();
    GridCells(int x, int y, bool uspace, bool uwall, 
                bool ustart, bool uend, bool ucurrent, bool utravel);

    int setXcoord(int input);
    int setYcoord(int input);
    bool setSpace(bool input);
    bool setWall(bool input);
    bool setStart(bool input);
    bool setEnd(bool input);
    bool setCurrent(bool input);
    bool setTraveled(bool input);

    int getXcoord();
    int getYcoord();
    bool isSpace();
    bool isWall();
    bool isStart();
    bool isEnd();
    bool playerCurrent();
    bool hasTraveled();

};


