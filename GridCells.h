
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

    int setXcoord(int input);
    int setYcoord(int input);
    bool setSpace(bool input);
    bool setWall(bool input);
    bool setStart(bool input);
    bool setEnd(bool input);
    bool setCurrent(bool input);
    bool setTraveled(bool input);


    bool isSpace();
    bool isWall();
    bool isStart();
    bool isEnd();
    bool playerCurrent();
    bool hasTraveled();

};


