//Team 7: Jennifer K, Jeff H, Eidmone T, Adam N, Jesus R
//Project: Maze
//Framework used: Asteroids from Professor Gordon
//start date: 2/24/2022

//lab 5 accomplishments: 
//- implemented simple testing functions from everyone's source files
//- clicking the right mouse button will print our msgs to the console



//
//program: asteroids.cpp
//author:  Gordon Griesel
//date:    2014 - 2021
//mod spring 2015: added constructors
//This program is a game starting point for a 3350 project.
//
//
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <ctime>
#include <cmath>
#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "log.h"
#include "fonts.h"

#include "GridCells.h"
#include "Grid.h"

#include "Global.h"
// #ifndef GLOBAL_H_
// #define GLOBAL_H_
// #include "Global.h"
// #endif //GLOBAL_H_


//for testing:
using namespace std;

//defined types
typedef float Flt;
typedef float Vec[3];
typedef Flt	Matrix[4][4];

//macros
#define rnd() (((Flt)rand())/(Flt)RAND_MAX)
#define random(a) (rand()%a)
#define VecZero(v) (v)[0]=0.0,(v)[1]=0.0,(v)[2]=0.0
#define MakeVector(x, y, z, v) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)
#define VecCopy(a,b) (b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2]
#define VecDot(a,b)	((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecSub(a,b,c) (c)[0]=(a)[0]-(b)[0]; \
						(c)[1]=(a)[1]-(b)[1]; \
						(c)[2]=(a)[2]-(b)[2]
//constants
const float timeslice = 1.0f;
const float gravity = -0.2f;
#define PI 3.141592653589793
#define ALPHA 1
const int MAX_BULLETS = 11;
const Flt MINIMUM_ASTEROID_SIZE = 60.0;

//-----------------------------------------------------------------------------
//Setup timers
const double physicsRate = 1.0 / 60.0;
const double oobillion = 1.0 / 1e9;
extern struct timespec timeStart, timeCurrent;
extern struct timespec timePause;
extern double physicsCountdown;
extern double timeSpan;
extern double timeDiff(struct timespec *start, struct timespec *end);
extern void timeCopy(struct timespec *dest, struct timespec *source);
//-----------------------------------------------------------------------------

// class Global {
// public:
// 	unsigned int textid[8];
// 	int xres, yres;
// 	char keys[65536];
// 	int maze_state;
// 	int current_time;
// 	int player[2];
// 	bool firstRun;
// 	bool endReached;
// 	Grid mazeGrid;
// 	bool showScores;
// 	int maxMaze;
// 	// int timeBeaten[];
// 	int timeBeaten[13];
// 	bool firstAttempt;
// 	bool newHighScore;
// 	int oldScore;
// 	int newScore;

	

// 	Global() {
// 		xres = 960;
// 		yres = 600;
// 		memset(keys, 0, 65536);
// 		maze_state = 0;
// 		player[0] = 0;
// 		player[1] = 0;
// 		firstRun = true;
// 		endReached = false;
// 		// Grid mazeGrid = NULL;
// 		Grid mazeGrid;
// 		showScores = false;
// 		maxMaze = 12;
// 		// timeBeaten[13] = {-1};
// 		for (int i = 0; i <= maxMaze; i++) {
// 			timeBeaten[i] = -1;
// 		}
// 		firstAttempt = false;
// 		newHighScore = false;
// 		oldScore = 0;
// 		newScore = 0;

// 	}
// } gl;

Global gl;


class Image {
public:
	int width, height;
	unsigned char *data;
	~Image() { delete [] data; }
	Image(const char *fname) {
		if (fname[0] == '\0')
			return;
		//printf("fname **%s**\n", fname);
		int ppmFlag = 0;
		char name[40];
		strcpy(name, fname);
		int slen = strlen(name);
		char ppmname[80];
		if (strncmp(name+(slen-4), ".ppm", 4) == 0)
			ppmFlag = 1;
		if (ppmFlag) {
			strcpy(ppmname, name);
		} else {
			name[slen-4] = '\0';
			//printf("name **%s**\n", name);
			sprintf(ppmname,"%s.ppm", name);
			//printf("ppmname **%s**\n", ppmname);
			char ts[100];
			//system("convert eball.jpg eball.ppm");
			sprintf(ts, "convert %s %s", fname, ppmname);
			system(ts);
		}
		//sprintf(ts, "%s", name);
		FILE *fpi = fopen(ppmname, "r");
		if (fpi) {
			char line[200];
			fgets(line, 200, fpi);
			fgets(line, 200, fpi);
			//skip comments and blank lines
			while (line[0] == '#' || strlen(line) < 2)
				fgets(line, 200, fpi);
			sscanf(line, "%i %i", &width, &height);
			fgets(line, 200, fpi);
			//get pixel data
			int n = width * height * 3;			
			data = new unsigned char[n];			
			for (int i=0; i<n; i++)
				data[i] = fgetc(fpi);
			fclose(fpi);
		} else {
			printf("ERROR opening image: %s\n",ppmname);
			exit(0);
		}
		if (!ppmFlag)
			unlink(ppmname);
	}
};
// Image img[5] = {"mazeTitle.png", "victoryTitle.png", "STAR.png", "cave.png",
// 													"star_grey.png"};

Image img[8] = {
				"img_unused_ver/mazeTitle.png", //0
				"img_used/victoryTitle.png", 	//1
				"img_unused_ver/STAR.png", 		//2
				"img_used/cave.png",			//3
				"img_used/star_black.png", 		//4
				"img_used/newTitlePage.png",	//5
				"img_used/exit_key_black.png", 	//6
				"img_used/mazeWall.png"			//7
				};

class Ship {
public:
	Vec pos;
	Vec dir;
	Vec vel;
	Vec acc;
	float angle;
	float color[3];
public:
	Ship() {
		pos[0] = (Flt)(gl.xres/2);
		pos[1] = (Flt)(gl.yres/2);
		pos[2] = 0.0f;
		VecZero(dir);
		VecZero(vel);
		VecZero(acc);
		angle = 0.0;
		color[0] = color[1] = color[2] = 1.0;
	}
};

class Bullet {
public:
	Vec pos;
	Vec vel;
	float color[3];
	struct timespec time;
public:
	Bullet() { }
};

class Asteroid {
public:
	Vec pos;
	Vec vel;
	int nverts;
	Flt radius;
	Vec vert[8];
	float angle;
	float rotate;
	float color[3];
	struct Asteroid *prev;
	struct Asteroid *next;
public:
	Asteroid() {
		prev = NULL;
		next = NULL;
	}
};

class Game {
public:
	Ship ship;
	Asteroid *ahead;
	Bullet *barr;
	int nasteroids;
	int nbullets;
	struct timespec bulletTimer;
	struct timespec mouseThrustTimer;
	bool mouseThrustOn;
public:
	Game() {
		ahead = NULL;
		barr = new Bullet[MAX_BULLETS];
		nasteroids = 0;
		nbullets = 0;
		mouseThrustOn = false;
		//build 10 asteroids...
		for (int j=0; j<10; j++) {
			Asteroid *a = new Asteroid;
			a->nverts = 8;
			a->radius = rnd()*80.0 + 40.0;
			Flt r2 = a->radius / 2.0;
			Flt angle = 0.0f;
			Flt inc = (PI * 2.0) / (Flt)a->nverts;
			for (int i=0; i<a->nverts; i++) {
				a->vert[i][0] = sin(angle) * (r2 + rnd() * a->radius);
				a->vert[i][1] = cos(angle) * (r2 + rnd() * a->radius);
				angle += inc;
			}
			a->pos[0] = (Flt)(rand() % gl.xres);
			a->pos[1] = (Flt)(rand() % gl.yres);
			a->pos[2] = 0.0f;
			a->angle = 0.0;
			a->rotate = rnd() * 4.0 - 2.0;
			a->color[0] = 0.8;
			a->color[1] = 0.8;
			a->color[2] = 0.7;
			a->vel[0] = (Flt)(rnd()*2.0-1.0);
			a->vel[1] = (Flt)(rnd()*2.0-1.0);
			//std::cout << "asteroid" << std::endl;
			//add to front of linked list
			a->next = ahead;
			if (ahead != NULL)
				ahead->prev = a;
			ahead = a;
			++nasteroids;
		}
		clock_gettime(CLOCK_REALTIME, &bulletTimer);
	}
	~Game() {
		delete [] barr;
	}
} g;

//X Windows variables
class X11_wrapper {
private:
	Display *dpy;
	Window win;
	GLXContext glc;
public:
	X11_wrapper() { }
	X11_wrapper(int w, int h) {
		GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
		//GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
		XSetWindowAttributes swa;
		setup_screen_res(gl.xres, gl.yres);
		dpy = XOpenDisplay(NULL);
		if (dpy == NULL) {
			std::cout << "\n\tcannot connect to X server" << std::endl;
			exit(EXIT_FAILURE);
		}
		Window root = DefaultRootWindow(dpy);
		XWindowAttributes getWinAttr;
		XGetWindowAttributes(dpy, root, &getWinAttr);
		int fullscreen = 0;
		gl.xres = w;
		gl.yres = h;
		if (!w && !h) {
			//Go to fullscreen.
			gl.xres = getWinAttr.width;
			gl.yres = getWinAttr.height;
			//When window is fullscreen, there is no client window
			//so keystrokes are linked to the root window.
			XGrabKeyboard(dpy, root, False,
				GrabModeAsync, GrabModeAsync, CurrentTime);
			fullscreen=1;
		}
		XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
		if (vi == NULL) {
			std::cout << "\n\tno appropriate visual found\n" << std::endl;
			exit(EXIT_FAILURE);
		} 
		Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
		swa.colormap = cmap;
		swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
			PointerMotionMask | MotionNotify | ButtonPress | ButtonRelease |
			StructureNotifyMask | SubstructureNotifyMask;
		unsigned int winops = CWBorderPixel|CWColormap|CWEventMask;
		if (fullscreen) {
			winops |= CWOverrideRedirect;
			swa.override_redirect = True;
		}
		win = XCreateWindow(dpy, root, 0, 0, gl.xres, gl.yres, 0,
			vi->depth, InputOutput, vi->visual, winops, &swa);
		//win = XCreateWindow(dpy, root, 0, 0, gl.xres, gl.yres, 0,
		//vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
		set_title();
		glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
		glXMakeCurrent(dpy, win, glc);
		show_mouse_cursor(0);
	}
	~X11_wrapper() {
		XDestroyWindow(dpy, win);
		XCloseDisplay(dpy);
	}
	void set_title() {
		//Set the window title bar.
		XMapWindow(dpy, win);
		XStoreName(dpy, win, "Asteroids template");
	}
	void check_resize(XEvent *e) {
		//The ConfigureNotify is sent by the
		//server if the window is resized.
		if (e->type != ConfigureNotify)
			return;
		XConfigureEvent xce = e->xconfigure;
		if (xce.width != gl.xres || xce.height != gl.yres) {
			//Window size did change.
			reshape_window(xce.width, xce.height);
		}
	}
	void reshape_window(int width, int height) {
		//window has been resized.
		setup_screen_res(width, height);
		glViewport(0, 0, (GLint)width, (GLint)height);
		glMatrixMode(GL_PROJECTION); glLoadIdentity();
		glMatrixMode(GL_MODELVIEW); glLoadIdentity();
		glOrtho(0, gl.xres, 0, gl.yres, -1, 1);
		set_title();
	}
	void setup_screen_res(const int w, const int h) {
		gl.xres = w;
		gl.yres = h;
	}
	void swapBuffers() {
		glXSwapBuffers(dpy, win);
	}
	bool getXPending() {
		return XPending(dpy);
	}
	XEvent getXNextEvent() {
		XEvent e;
		XNextEvent(dpy, &e);
		return e;
	}
	void set_mouse_position(int x, int y) {
		XWarpPointer(dpy, None, win, 0, 0, 0, 0, x, y);
	}
	void show_mouse_cursor(const int onoff) {
		if (onoff) {
			//this removes our own blank cursor.
			XUndefineCursor(dpy, win);
			return;
		}
		//vars to make blank cursor
		Pixmap blank;
		XColor dummy;
		char data[1] = {0};
		Cursor cursor;
		//make a blank cursor
		blank = XCreateBitmapFromData (dpy, win, data, 1, 1);
		if (blank == None)
			std::cout << "error: out of memory." << std::endl;
		cursor = XCreatePixmapCursor(dpy, blank, blank, &dummy, &dummy, 0, 0);
		XFreePixmap(dpy, blank);
		//this makes the cursor. then set it using this function
		XDefineCursor(dpy, win, cursor);
		//after you do not need the cursor anymore use this function.
		//it will undo the last change done by XDefineCursor
		//(thus do only use ONCE XDefineCursor and then XUndefineCursor):
	}
} x11(gl.xres, gl.yres);
// ---> for fullscreen x11(0, 0);

//function prototypes
void init_opengl(void);
void check_mouse(XEvent *e);
int check_keys(XEvent *e);
// void physics();
void render();

//==========================================================================
// M A I N
//==========================================================================
int main()
{
	logOpen();
	init_opengl();
	srand(time(NULL));
	clock_gettime(CLOCK_REALTIME, &timePause);
	clock_gettime(CLOCK_REALTIME, &timeStart);
	x11.set_mouse_position(100,100);
	int done=0;
	while (!done) {
		while (x11.getXPending()) {
			XEvent e = x11.getXNextEvent();
			x11.check_resize(&e);
			check_mouse(&e);
			done = check_keys(&e);
		}
		clock_gettime(CLOCK_REALTIME, &timeCurrent);
		timeSpan = timeDiff(&timeStart, &timeCurrent);
		timeCopy(&timeStart, &timeCurrent);
		physicsCountdown += timeSpan;
		while (physicsCountdown >= physicsRate) {
			// physics();
			physicsCountdown -= physicsRate;
		}
		render();
		x11.swapBuffers();
	}
	cleanup_fonts();
	logClose();
	return 0;
}

unsigned char *buildAlphaData(Image *img)
{
	//Add 4th component to an RGB stream...
	//RGBA
	//When you do this, OpenGL is able to use the A component to determine
	//transparency information.
	//It is used in this application to erase parts of a texture-map from view.
	int i;
	int a,b,c;
	unsigned char *newdata, *ptr;
	unsigned char *data = (unsigned char *)img->data;
	newdata = (unsigned char *)malloc(img->width * img->height * 4);
	ptr = newdata;
	for (i=0; i<img->width * img->height * 3; i+=3) {
		a = *(data+0);
		b = *(data+1);
		c = *(data+2);
		*(ptr+0) = a;
		*(ptr+1) = b;
		*(ptr+2) = c;
		//-----------------------------------------------
		//get largest color component...
		//*(ptr+3) = (unsigned char)((
		//		(int)*(ptr+0) +
		//		(int)*(ptr+1) +
		//		(int)*(ptr+2)) / 3);
		//d = a;
		//if (b >= a && b >= c) d = b;
		//if (c >= a && c >= b) d = c;
		//*(ptr+3) = d;
		//-----------------------------------------------
		//this code optimizes the commented code above.
		//code contributed by student: Chris Smith
		//
		// *(ptr+3) = ((255-a)|(255-b)|(255-c));
		*(ptr+3) = (a|b|c);
		//-----------------------------------------------
		ptr += 4;
		data += 3;
	}
	return newdata;
}

void init_opengl(void)
{
   //OpenGL initialization
   glViewport(0, 0, gl.xres, gl.yres);
   //Initialize matrices
   glMatrixMode(GL_PROJECTION); glLoadIdentity();
   glMatrixMode(GL_MODELVIEW); glLoadIdentity();
   //This sets 2D mode (no perspective)
   glOrtho(0, gl.xres, 0, gl.yres, -1, 1);
   //
   glDisable(GL_LIGHTING);
   glDisable(GL_DEPTH_TEST);
   glDisable(GL_FOG);
   glDisable(GL_CULL_FACE);
   //
   //Clear the screen to black
   glClearColor(0.0, 0.0, 0.0, 1.0);
   //Do this to allow fonts
   glEnable(GL_TEXTURE_2D);
   initialize_fonts();
 
   glGenTextures(1, &gl.textid[0]);
   glBindTexture(GL_TEXTURE_2D, gl.textid[0]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, img[0].width, img[0].height, 0,
       GL_RGB, GL_UNSIGNED_BYTE, img[0].data);
   glBindTexture(GL_TEXTURE_2D, 0);

   glGenTextures(1, &gl.textid[1]);
   glBindTexture(GL_TEXTURE_2D, gl.textid[1]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, img[1].width, img[1].height, 0,
       GL_RGB, GL_UNSIGNED_BYTE, img[1].data);
   glBindTexture(GL_TEXTURE_2D, 0);
	
   glGenTextures(1, &gl.textid[2]);
   glBindTexture(GL_TEXTURE_2D, gl.textid[2]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, img[2].width, img[2].height, 0,
       GL_RGB, GL_UNSIGNED_BYTE, img[2].data);
   glBindTexture(GL_TEXTURE_2D, 0);

   glGenTextures(1, &gl.textid[3]);
   glBindTexture(GL_TEXTURE_2D, gl.textid[3]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, img[3].width, img[3].height, 0,
       GL_RGB, GL_UNSIGNED_BYTE, img[3].data);
	glBindTexture(GL_TEXTURE_2D, 0);


// --------------testing: success-----------------


// #4. star_black.png
   glGenTextures(1, &gl.textid[4]);
   glBindTexture(GL_TEXTURE_2D, gl.textid[4]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   unsigned char *silhouetteData = buildAlphaData(&img[4]);	
   int w = img[4].width;
   int h = img[4].height;
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
   							GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
   free(silhouetteData);	   
//    glBindTexture(GL_TEXTURE_2D, 0);

// #5. newTitlePage.png
   glGenTextures(1, &gl.textid[5]);
   glBindTexture(GL_TEXTURE_2D, gl.textid[5]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   silhouetteData = buildAlphaData(&img[5]);	
   w = img[5].width;
   h = img[5].height;
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
   							GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
   free(silhouetteData);	   
//    glBindTexture(GL_TEXTURE_2D, 0);

// #6. exit_key_black.png
   glGenTextures(1, &gl.textid[6]);
   glBindTexture(GL_TEXTURE_2D, gl.textid[6]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   silhouetteData = buildAlphaData(&img[6]);	
   w = img[6].width;
   h = img[6].height;
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
   							GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
   free(silhouetteData);	   
//    glBindTexture(GL_TEXTURE_2D, 0);

// #7. mazeWall.png
   glGenTextures(1, &gl.textid[7]);
   glBindTexture(GL_TEXTURE_2D, gl.textid[7]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, img[7].width, img[7].height, 0,
       GL_RGB, GL_UNSIGNED_BYTE, img[7].data);
//    glBindTexture(GL_TEXTURE_2D, 0);




}


void normalize2d(Vec v)
{
	Flt len = v[0]*v[0] + v[1]*v[1];
	if (len == 0.0f) {
		v[0] = 1.0;
		v[1] = 0.0;
		return;
	}
	len = 1.0f / sqrt(len);
	v[0] *= len;
	v[1] *= len;
}


// -------------------simple testing functions from lab 5:
//when the right mouse button is pressed, print msgs to the console
extern void jk_PrintMsg();
extern void jh_PrintMsg();
extern void jr_PrintMsg();
extern void et_PrintMsg();
extern void an_PrintMsg();

extern Rect jk_createRect(int yres, int height, int left, int center);

extern void jk_printMazeTest(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                            int& maze_state);

extern void jk_printMaze1(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                            int& maze_state);
extern void jk_printMaze2(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                            int& maze_state);
extern void jk_printMaze3(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                            int& maze_state);
extern void jh_printMaze5(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                            int& maze_state);
extern void jh_printMaze6(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                            int& maze_state);	
extern void jr_printMaze7(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                            int& maze_state);	
extern void jr_printMaze8(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                            int& maze_state);	
extern void an_printMaze9(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                            int& maze_state);	
extern void an_printMaze10(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                            int& maze_state);	
extern void et_printMaze11(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                            int& maze_state);

extern void et_printMaze12(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid, 
                                                            int& maze_state);
void jk_printMazeSecretMode1(Rect position, int defaultHeight, int color, 
                        int (&player)[2], bool &firstRun);
void jk_printMazeSecretMode2(Rect position, int defaultHeight, int color, 
                        int (&player)[2], bool &firstRun);
void jk_printMazeSecretMode3(Rect position, int defaultHeight, int color, 
                        int (&player)[2], bool &firstRun);

											
extern void jk_page_transition(int& maze_state, const char* keyChecked, 
                                bool& firstRun, int maxMaze, bool& showScores); 


void check_mouse(XEvent *e)
{
	//Did the mouse move?
	//Was a mouse button clicked?

	if (e->type == ButtonRelease) {
		return;
	}
	if (e->type == ButtonPress) {
		if (e->xbutton.button==1) {
			//Left button is down
		}
		if (e->xbutton.button==3) {
			//Right button is down
		

		// -------------------simple testing functions from lab 5:
		//when the right mouse button is pressed, print msgs to the console
			jk_PrintMsg();
			jh_PrintMsg();
			jr_PrintMsg();
			et_PrintMsg();
			an_PrintMsg();


		}
	}
}


int check_keys(XEvent *e)
{
	static int shift=0;
	if (e->type != KeyRelease && e->type != KeyPress) {
		//not a keyboard event
		return 0;
	}
	int key = (XLookupKeysym(&e->xkey, 0) & 0x0000ffff);
	//Log("key: %i\n", key);
	if (e->type == KeyRelease) {
		gl.keys[key] = 0;
		if (key == XK_Shift_L || key == XK_Shift_R)
			shift = 0;
		return 0;
	}
	if (e->type == KeyPress) {
		//std::cout << "press" << std::endl;
		gl.keys[key]=1;
		if (key == XK_Shift_L || key == XK_Shift_R) {
			shift = 1;
			return 0;
		}
	}

	// Rect jk_t = jk_createRect(gl.yres, 100, 10, 0);

	(void)shift;
	switch (key) {
		case XK_1:
			// gl.maze_state = 1;
			break;
		case XK_2:
			// gl.maze_state = 2;
			break;
		case XK_3:
			// gl.maze_state = 3;
			break;

		case XK_b:
			jk_page_transition(gl.maze_state, "b", gl.firstRun, gl.maxMaze, 
															gl.showScores);
			break;
		
		case XK_s:
			jk_page_transition(gl.maze_state, "s", gl.firstRun, gl.maxMaze, 
															gl.showScores);
			break;

		case XK_c:
			jk_page_transition(gl.maze_state, "c", gl.firstRun, gl.maxMaze, 
															gl.showScores);
			break;
		
		case XK_r:
			jk_page_transition(gl.maze_state, "r", gl.firstRun, gl.maxMaze, 
															gl.showScores);
			break;
		
		case XK_q:
			jk_page_transition(gl.maze_state, "q", gl.firstRun, gl.maxMaze, 
															gl.showScores);
			break;

		case XK_w:
			jk_page_transition(gl.maze_state, "w", gl.firstRun, gl.maxMaze, 
															gl.showScores);
			break;

		case XK_e:
			jk_page_transition(gl.maze_state, "e", gl.firstRun, gl.maxMaze, 
															gl.showScores);
			break;

		case XK_z:
			jk_page_transition(gl.maze_state, "z", gl.firstRun, gl.maxMaze, 
															gl.showScores);
			break;
		
		case XK_u:
			jk_page_transition(gl.maze_state, "u", gl.firstRun, gl.maxMaze, 
															gl.showScores);
			break;

		case XK_p:
			jk_page_transition(gl.maze_state, "p", gl.firstRun, gl.maxMaze, 
															gl.showScores);
			break;
		
		case XK_a:
			jk_page_transition(gl.maze_state, "a", gl.firstRun, gl.maxMaze, 
															gl.showScores);
			break;


		// I couldn't tell what this was trying to do. 
		// lemme know if you want to keep it and we'll see if we can get
		// what you needed implemented

		// case XK_5:
		// 	jk_page_transition(gl.maze_state, "z", gl.firstRun, gl.maxMaze);
		// 	break;

		// case XK_6:
		// 	jk_page_transition(gl.maze_state, "z", gl.firstRun, gl.maxMaze);
		// 	break;


		case XK_Escape:
			return 1;
		case XK_f:
			break;
		case XK_Down:
			break;
		case XK_equal:
			break;
		case XK_minus:
			break;
	}
	return 0;
}


extern void jk_showCreditPage(Rect position, int defaultHeight, int color);
extern void jh_showCreditPage(Rect position, int defaultHeight, int color);
extern void jr_showCreditPage(Rect position, int defaultHeight, int color);
extern void et_showCreditPage(Rect position, int defaultHeight, int color);
extern void an_showCreditPage(Rect position, int defaultHeight, int color);

extern void jk_showRulesPage(Rect position, int defaultHeight, int color);
extern void jh_showRulesPage(Rect position, int defaultHeight, int color);
extern void jr_showRulesPage(Rect position, int defaultHeight, int color);
extern void et_showRulesPage(Rect position, int defaultHeight, int color);
extern void an_showRulesPage(Rect position, int defaultHeight, int color);

// now called in secret page
extern void jk_showWelcomePageTitle(Rect position, int defaultHeight, 
																int color);

extern void jk_showWelcomePage(Rect position, int defaultHeight, int color);
extern void jh_showWelcomePage(Rect position, int defaultHeight, int color);
extern void jr_showWelcomePage(Rect position, int defaultHeight, int color);
extern void et_showWelcomePage(Rect position, int defaultHeight, int color);
extern void an_showWelcomePage(Rect position, int defaultHeight, int color);
extern void jk_showWelcomePage2(Rect position, int defaultHeight, int color);
extern void jk_showWelcomePage3(Rect position, int defaultHeight, int color);
extern void jk_showWelcomePage4(Rect position, int defaultHeight, int color);
extern void jk_showSecretMode(Rect position, int defaultHeight, int color);
extern void jk_showSecretModeMessage(Rect position, int defaultHeight, 
																	int color);
extern void jk_playerMovement(char* keys, int (&player)[2], Grid& grid);
extern void jk_playerMovementForSecretMode(char* keys, int (&player)[2]);
extern void jh_Image(int xres, int yres, unsigned int textid);
extern void playerImage(int yres, unsigned int textid, int player[2]);
extern void backgroundImageWelcome(int xres, int yres, unsigned int textid);
extern void backgroundImageMap (int xres, int yres, unsigned int textid);

extern void et_timer(Rect position, int defaultHeight, int color, 
						int& maze_state,  bool& firstRun, int & current_time);

extern bool jkuo_midterm_checkState(int mazeState, int desiredState);
extern bool etagaca_midterm(int& current_time);


extern void jk_displayScore(int timeBeaten[], int maxMaze, Rect position1, 
								Rect position2, int defaultHeight, int color);
extern void highScoreMessages(int& maze_state, int (&timeBeaten)[13], 
        int current_time, bool& firstAttempt, bool& newHighScore, 
							int& oldScore, int& newScore, Rect r, int maxMaze);



void jk_stageSetUp(Rect r, Rect timerPosition) 
{
	glClear(GL_COLOR_BUFFER_BIT);
	backgroundImageMap(gl.xres, gl.yres,gl.textid[3]);
	ggprint8b(&r, 16, 0x00ffffff, 
				"press s to switch to next maze. press b to return to home");
	ggprint8b(&r, 16, 0x00ffffff, "press p to pause game");
	ggprint8b(&r, 16, 0x00ffffff, "press a any time to view scoreboard");
	ggprint8b(&r, 16, 0x00ffffff, "HOLD down the arrowkeys to move about");

	et_timer(timerPosition, gl.yres-120, 0x00B24BF3, gl.maze_state, 
											gl.firstRun, gl.current_time);
	if(etagaca_midterm(gl.current_time)) {
		ggprint8b(&r, 16, 0x00b19cd9, 
						"5 seconds have passed. Let's get started!");
	}											

	jk_playerMovement(gl.keys, gl.player, gl.mazeGrid);
	
}

void printTheRightMaze(Rect position, int defaultHeight, int color, 
            int (&player)[2], bool &firstRun, bool& endReached, Grid& mazeGrid,
																int& maze_state)
{
	switch (maze_state) {
		case 1:
			jk_printMaze1(position, defaultHeight, color, player, firstRun, 
								 endReached, mazeGrid, maze_state);
			break;
		case 2:
			jk_printMaze2(position, defaultHeight, color, player, firstRun, 
								 endReached, mazeGrid, maze_state);
			break;
		case 3:
			jk_printMaze3(position, defaultHeight, color, player, firstRun, 
								 endReached, mazeGrid, maze_state);
			break;
		case 4:
			jk_printMazeTest(position, defaultHeight, color, player, 
					 firstRun, endReached, mazeGrid, maze_state);
			break;
		case 5:
			jh_printMaze5(position, defaultHeight, color, player, firstRun, 
								 endReached, mazeGrid, maze_state);
			break;
		case 6:
			jh_printMaze6(position, defaultHeight, color, player, firstRun, 
								 endReached, mazeGrid, maze_state);
			break;
		case 7:
			jr_printMaze7(position, defaultHeight, color, player, firstRun, 
								 endReached, mazeGrid, maze_state);
			break;
		case 8:
			jr_printMaze8(position, defaultHeight, color, player, firstRun, 
								 endReached, mazeGrid, maze_state);
			break;
		case 9:
			an_printMaze9(position, defaultHeight, color, player, firstRun, 
								 endReached, mazeGrid, maze_state);
			break;
		case 10:
			an_printMaze10(position, defaultHeight, color, player, 
					 firstRun, endReached, mazeGrid, maze_state);
			break;
		case 11:
			et_printMaze11(position, defaultHeight, color, player, 
					 firstRun, endReached, mazeGrid, maze_state);
			break;	
		case 12:
			et_printMaze12(position, defaultHeight, color, player, 
					 firstRun, endReached, mazeGrid, maze_state);
			break;	
		default:
			cout << "error printing the right maze" << endl;
			break;
	}
}


// gonna move to Jeff's

void testBackgroundImage (int xres, int yres, unsigned int textid)
{
    glPushMatrix();
    float w = 300;

    glTranslatef(xres/2, yres - 300, 0);

    // glColor3ub(255, 255, 255);
    glBindTexture(GL_TEXTURE_2D, textid);

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-w,  w);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( w,  w);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( w, -w);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-w, -w);
    glEnd();
    // glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
	glDisable(GL_ALPHA_TEST);
}





void render()
{


	Rect r;

	r.bot = gl.yres - 20;
	r.left = 10;
	r.center = 0;

	// Rect jk_welcomeScreen = jk_createRect(gl.yres+50, 100, 10, 0); 
	
	Rect jk_welcomeMessage = jk_createRect(gl.yres, 100, 10, 0);
	jk_welcomeMessage.left = gl.xres / 2;
	jk_welcomeMessage.center = 1;

	
	Rect jk_welcomeTitlePlaceHolder = jk_createRect(gl.yres, 100, 10, 0);
	jk_welcomeTitlePlaceHolder.left = gl.xres / 2;
	jk_welcomeTitlePlaceHolder.center = 1;
	
	Rect jk_titles = jk_createRect(gl.yres+50, 100, 10, 0);
	jk_titles.left = gl.xres / 2;
	jk_titles.center = 1;

	Rect jk_message = jk_createRect(gl.yres+50, 100, 10, 0); 
	jk_message.left = 50;

	Rect jk_t = jk_createRect(gl.yres, 100, 10, 0);
	
	Rect jk_scoreColumn1 = jk_createRect(gl.yres, 100, 10, 0);
	jk_scoreColumn1.left = gl.xres/3 + 50;
	
	Rect jk_scoreColumn2 = jk_createRect(gl.yres, 100, 10, 0);
	jk_scoreColumn2.left = gl.xres/3 + 160;
	




	if (gl.showScores) {
		glClear(GL_COLOR_BUFFER_BIT);
		ggprint13(&jk_titles, 16, 0x00ffffff, "Scoreboard");
		ggprint8b(&jk_titles, 16, 0x00ffffff, "scores are erased upon exit");
		ggprint8b(&jk_titles, 16, 0x00ffffff, "press a again to resume");

		jk_displayScore(gl.timeBeaten, gl.maxMaze, jk_scoreColumn1, 
								jk_scoreColumn2, gl.yres - 150, 0x00e3a90b);



	} else {

		if (jkuo_midterm_checkState(gl.maze_state, 0)) {
		// if (gl.maze_state == 0) {
			
			gl.firstAttempt = false;
			gl.newHighScore = false;

			glClear(GL_COLOR_BUFFER_BIT);

			backgroundImageWelcome(gl.xres, gl.yres,gl.textid[3]);
			// jh_Image(gl.xres, gl.yres,gl.textid[0]);
			testBackgroundImage(gl.xres, gl.yres, gl.textid[5]);
			jk_showWelcomePage(jk_welcomeMessage, gl.yres - 380, 0x00CC593F);
			jh_showWelcomePage(jk_welcomeMessage, gl.yres - 510, 0x00CC593F);
			jr_showWelcomePage(jk_welcomeMessage, gl.yres - 450, 0x00CC593F);
			et_showWelcomePage(jk_welcomeMessage, gl.yres - 490, 0x00CC593F);
			an_showWelcomePage(jk_welcomeMessage, gl.yres - 470, 0x00CC593F);
			jk_showWelcomePage3(jk_welcomeMessage, gl.yres - 430, 0x00e3a90b);
			// jk_showWelcomePage2(jk_welcomeMessage, gl.yres - 550, 0x00FF0050);
			jk_showWelcomePage2(jk_welcomeMessage, gl.yres - 150, 0x00FF0050);
			jk_showWelcomePage4(jk_welcomeMessage, gl.yres - 410, 0x00e3a90b);

		}




		if (jkuo_midterm_checkState(gl.maze_state, 110)) {
		// if (gl.maze_state == 11) {
			glClear(GL_COLOR_BUFFER_BIT);
			ggprint13(&jk_titles, 16, 0x00ffffff, "Rules Page");
			ggprint8b(&jk_titles, 16, 0x00ffffff, "press b to return to home");

			jk_showRulesPage(jk_message, gl.yres-120, 0x0040e0d0);
			jh_showRulesPage(jk_message, gl.yres-220, 0x0024AAFA);
			jr_showRulesPage(jk_message, gl.yres-320, 0x0051f542);
			et_showRulesPage(jk_message, gl.yres-420, 0x00B24BF3);
			an_showRulesPage(jk_message, gl.yres-520, 0x00FF7025);
		}




		if (jkuo_midterm_checkState(gl.maze_state, 120)) {
		// if (gl.maze_state == 12) {
			glClear(GL_COLOR_BUFFER_BIT);
			// load_ggfont(17); // arial 140
			ggprint13(&jk_titles, 16, 0x00ffffff, "CREDIT Page");
			ggprint8b(&jk_titles, 16, 0x00ffffff, "press b to return to home");

			//jh_Image(gl.xres, gl.yres, gl.textid);
			jk_showCreditPage(jk_message, gl.yres-120, 0x0040e0d0);
			jh_showCreditPage(jk_message, gl.yres-220, 0x0024AAFA);
			jr_showCreditPage(jk_message, gl.yres-320, 0x0051f542);
			et_showCreditPage(jk_message, gl.yres-420, 0x00B24BF3);
			an_showCreditPage(jk_message, gl.yres-520, 0x00FF7025);
		}





		if (gl.maze_state < 0) {
			glClear(GL_COLOR_BUFFER_BIT);
			//ggprint8b(&r, 16, 0x00ffffff, "victory!");
			ggprint8b(&r, 16, 0x00ffffff, "press s to start next level");
			jh_Image(gl.xres, gl.yres -50, gl.textid[1]);

			
			string paused_time = "Completed in: " + to_string(gl.current_time) 
																  + " seconds";
			const char *p = paused_time.c_str();
			ggprint8b(&r, 16, 0x00ffffff, p);

			highScoreMessages(gl.maze_state, gl.timeBeaten, gl.current_time,
				gl.firstAttempt, gl.newHighScore, gl.oldScore, gl.newScore, r,
																gl.maxMaze);

		}





		Rect et_message = jk_createRect(gl.yres+50, 100, 10, 0); 


		// maze 1 - 12
		if (gl.maze_state >= 1 && gl.maze_state <= 12) {
			gl.firstAttempt = false;
			gl.newHighScore = false;

			jk_stageSetUp(r, et_message);
			// backgroundImageWelcome(gl.xres, gl.yres,gl.textid[3]);
			printTheRightMaze(jk_t, gl.yres-100, 0x0040e0d0, 
									gl.player, gl.firstRun, gl.endReached, 
									gl.mazeGrid, gl.maze_state);
			// playerImage (gl.yres - 100, gl.textid[2], gl.player);
			playerImage (gl.yres - 100, gl.textid[4], gl.player);
		}




		// gl.maze_state = 1000;

		if (jkuo_midterm_checkState(gl.maze_state, 1000)) {
		// if (gl.maze_state == 1000) {

			glClear(GL_COLOR_BUFFER_BIT);
			ggprint13(&jk_titles, 16, 0x00ffffff, 
									"congrats on beating everything!");
			ggprint8b(&jk_titles, 16, 0x00ffffff, 
									"press b to return to homepage");
			ggprint8b(&jk_titles, 16, 0x00ffffff, 
									"scores are erased upon exit");
			ggprint8b(&jk_titles, 16, 0x00ffffff, 
									"maze 4 is an optional tutorial stage");

			Rect jk_scoreColumn3 = jk_createRect(gl.yres, 100, 10, 0);
			jk_scoreColumn3.left = 50;
			
			Rect jk_scoreColumn4 = jk_createRect(gl.yres, 100, 10, 0);
			jk_scoreColumn4.left = 130;

			jk_displayScore(gl.timeBeaten, gl.maxMaze, jk_scoreColumn3, 
								jk_scoreColumn4, gl.yres - 150, 0x00e3a90b);


		}



		if (jkuo_midterm_checkState(gl.maze_state, 404)) {
		// if (gl.maze_state == 404) {

			glClear(GL_COLOR_BUFFER_BIT);
			ggprint8b(&r, 16, 0x00ffffff, "Timer is up, please Try again");
			ggprint8b(&r, 16, 0x00ffffff, "press b to return to homepage");

		}


		
		// if (jkuo_midterm_checkState(gl.maze_state, 405)) {
		if (gl.maze_state >= 405000) {

			glClear(GL_COLOR_BUFFER_BIT);
			ggprint8b(&r, 16, 0x00ffffff, "THE GAME IS PAUSED");
			ggprint8b(&r, 16, 0x00ffffff, "press u to return to game");
			string paused_time = "Elapsed Time: " + to_string(gl.current_time);
			const char *p = paused_time.c_str();
			ggprint8b(&r, 16, 0x00ffffff, p);
		}


		//secret mode

		if (jkuo_midterm_checkState(gl.maze_state, 230)) {
		// if (gl.maze_state == 230) {
			glClear(GL_COLOR_BUFFER_BIT);
			ggprint8b(&r, 16, 0x00ff0000, "3350 - MAze");

			jk_showWelcomePageTitle(jk_welcomeTitlePlaceHolder, 
											gl.yres - (gl.yres/2), 0x00FF0000);
			jk_showSecretMode(jk_welcomeTitlePlaceHolder, 
								gl.yres - (gl.yres/2 - gl.yres/4), 0x00FF0050);

			jk_showSecretModeMessage(jk_welcomeMessage, gl.yres - 400, 
																	0x00CC5050);

		}

		//zen mode stages

		if (jkuo_midterm_checkState(gl.maze_state, 231)) {
		// if (gl.maze_state == 231) {
			
			glClear(GL_COLOR_BUFFER_BIT);
			
			ggprint8b(&r, 16, 0x00ffffff, "press s to switch to next maze");
			ggprint8b(&r, 16, 0x00ffffff, "press b to return to secret home");
			ggprint8b(&r, 16, 0x00ffffff, 
									"HOLD down the arrowkeys to move about");

			jk_playerMovementForSecretMode(gl.keys, gl.player);
			jk_printMazeSecretMode1(jk_t, gl.yres-100, 0x0040e0d0, gl.player, 
													gl.firstRun);
		}

		if (jkuo_midterm_checkState(gl.maze_state, 232)) {
		// if (gl.maze_state == 232) {
			
			glClear(GL_COLOR_BUFFER_BIT);
			
			ggprint8b(&r, 16, 0x00ffffff, "press s to switch to next maze");
			ggprint8b(&r, 16, 0x00ffffff, "press b to return to secret home");
			ggprint8b(&r, 16, 0x00ffffff, 
									"HOLD down the arrowkeys to move about");

			jk_playerMovementForSecretMode(gl.keys, gl.player);
			jk_printMazeSecretMode2(jk_t, gl.yres-100, 0x0040e0d0, gl.player, 
													gl.firstRun);
		}

		if (jkuo_midterm_checkState(gl.maze_state, 233)) {
		// if (gl.maze_state == 233) {
			
			glClear(GL_COLOR_BUFFER_BIT);
			
			ggprint8b(&r, 16, 0x00ffffff, "press s to switch to next maze");
			ggprint8b(&r, 16, 0x00ffffff, "press b to return to secret home");
			ggprint8b(&r, 16, 0x00ffffff, 
									"HOLD down the arrowkeys to move about");

			jk_playerMovementForSecretMode(gl.keys, gl.player);
			jk_printMazeSecretMode3(jk_t, gl.yres-100, 0x0040e0d0, gl.player, 
													gl.firstRun);
													
		}


	}


}



