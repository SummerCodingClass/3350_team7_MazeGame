//wasn't the most helpful but gave some ideas:
// https://stackoverflow.com/questions/1433204/
                // how-do-i-use-extern-to-share-variables-between-source-files
// namely, at least it got me thinking about using a header file so jkuo.cpp 
// could recognize the class "Global"
// once it does recognize the class, then I was able to extern the 
// gl variable... finally!


class Global {
public:
	unsigned int textid[10];
	int xres, yres;
	char keys[65536];
	int maze_state;
	int current_time;
	int player[2];
	bool firstRun;
	bool endReached;
	Grid mazeGrid;
	bool showScores;
	int maxMaze;
	// int timeBeaten[];
	int timeBeaten[13];
	bool firstAttempt;
	bool newHighScore;
	int oldScore;
	int newScore;

	

	Global();
};

