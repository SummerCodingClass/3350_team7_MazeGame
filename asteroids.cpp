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

class Global {
public:
	unsigned int textid;
	int xres, yres;
	char keys[65536];
	int maze_state;
	int player[2];
	bool firstRun;
	bool endReached;
	Grid mazeGrid;
	int maxMaze;
	

	Global() {
		xres = 960;
		yres = 600;
		memset(keys, 0, 65536);
		maze_state = 0;
		player[0] = 0;
		player[1] = 0;
		firstRun = true;
		endReached = false;
		// Grid mazeGrid = NULL;
		Grid mazeGrid;
		maxMaze = 3;

	}
} gl;

class Image {
    public:
    int width, height;
    unsigned char *data;
    Image(const char *fname) {
        if (fname[0] == '\0')
            return;
        int ppmFlag = 0;
        char name[40];
        strcpy(name, fname);
        int slen = strlen(name);
        char ppmname[80];
        if (strncmp(name+(slen -4), ".ppm",4) == 0)
            ppmFlag = 1;
        if (ppmFlag) {
            strcpy(ppmname, name);
        } else {
            name[slen -4] = '\0';
            sprintf(ppmname, "%s.ppm", name);
            char ts[100];
            sprintf(ts, "convert %s %s", fname, ppmname);
            system(ts);
        }
        FILE *fpi = fopen(ppmname, "r");
        if (fpi) {
            char line[200];
            fgets(line, 200, fpi);
            fgets(line, 200, fpi);
            while(line[0] == '#' || strlen(line) < 2)
                fgets(line, 200, fpi);
            sscanf(line, "%i %i", &width, &height);
            fgets(line, 200, fpi);
            int n = width * height * 3;
            data = new unsigned char[n];
            for (int i = 0; i < n; i++) {
                data[i] = fgetc(fpi);
            }
            fclose(fpi);
        } else {
            printf("ERROR opening image: %s\n", ppmname);
            exit(0);
        }
        if (!ppmFlag)
            unlink(ppmname);
		//~Image() {delete [] data;}
    }
} img("coder.png");


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
void physics();
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
			physics();
			physicsCountdown -= physicsRate;
		}
		render();
		x11.swapBuffers();
	}
	cleanup_fonts();
	logClose();
	return 0;
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
 
   glGenTextures(1, &gl.textid);
   glBindTexture(GL_TEXTURE_2D, gl.textid);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, img.width, img.height, 0,
       GL_RGB, GL_UNSIGNED_BYTE, img.data);
	glBindTexture(GL_TEXTURE_2D, 0);
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
											int (&player)[2], bool &firstRun);
extern void jk_printMaze3(Rect position, int defaultHeight, int color,
											int (&player)[2], bool &firstRun);
										
void jk_printMazeSecretMode1(Rect position, int defaultHeight, int color, 
                        int (&player)[2], bool &firstRun);
void jk_printMazeSecretMode2(Rect position, int defaultHeight, int color, 
                        int (&player)[2], bool &firstRun);
void jk_printMazeSecretMode3(Rect position, int defaultHeight, int color, 
                        int (&player)[2], bool &firstRun);

											
extern void jk_page_transition(int& maze_state, const char* keyChecked, 
                                                bool& firstRun, int maxMaze);


void check_mouse(XEvent *e)
{
	//Did the mouse move?
	//Was a mouse button clicked?
	static int savex = 0;
	static int savey = 0;
	//
	static int ct=0;
	//std::cout << "m" << std::endl << std::flush;
	if (e->type == ButtonRelease) {
		return;
	}
	if (e->type == ButtonPress) {
		if (e->xbutton.button==1) {
			//Left button is down
			//a little time between each bullet
			struct timespec bt;
			clock_gettime(CLOCK_REALTIME, &bt);
			double ts = timeDiff(&g.bulletTimer, &bt);
			if (ts > 0.1) {
				timeCopy(&g.bulletTimer, &bt);
				//shoot a bullet...
				if (g.nbullets < MAX_BULLETS) {
					Bullet *b = &g.barr[g.nbullets];
					timeCopy(&b->time, &bt);
					b->pos[0] = g.ship.pos[0];
					b->pos[1] = g.ship.pos[1];
					b->vel[0] = g.ship.vel[0];
					b->vel[1] = g.ship.vel[1];
					//convert ship angle to radians
					Flt rad = ((g.ship.angle+90.0) / 360.0f) * PI * 2.0;
					//convert angle to a vector
					Flt xdir = cos(rad);
					Flt ydir = sin(rad);
					b->pos[0] += xdir*20.0f;
					b->pos[1] += ydir*20.0f;
					b->vel[0] += xdir*6.0f + rnd()*0.1;
					b->vel[1] += ydir*6.0f + rnd()*0.1;
					b->color[0] = 1.0f;
					b->color[1] = 1.0f;
					b->color[2] = 1.0f;
					++g.nbullets;
				}
			}
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
	//keys[XK_Up] = 0;
	if (savex != e->xbutton.x || savey != e->xbutton.y) {
		//Mouse moved
		int xdiff = savex - e->xbutton.x;
		int ydiff = savey - e->xbutton.y;
		if (++ct < 10)
			return;		
		//std::cout << "savex: " << savex << std::endl << std::flush;
		//std::cout << "e->xbutton.x: " << e->xbutton.x << std::endl <<
		//std::flush;
		if (xdiff > 0) {
			//std::cout << "xdiff: " << xdiff << std::endl << std::flush;
			g.ship.angle += 0.05f * (float)xdiff;
			if (g.ship.angle >= 360.0f)
				g.ship.angle -= 360.0f;
		}
		else if (xdiff < 0) {
			//std::cout << "xdiff: " << xdiff << std::endl << std::flush;
			g.ship.angle += 0.05f * (float)xdiff;
			if (g.ship.angle < 0.0f)
				g.ship.angle += 360.0f;
		}
		if (ydiff > 0) {
			//apply thrust
			//convert ship angle to radians
			Flt rad = ((g.ship.angle+90.0) / 360.0f) * PI * 2.0;
			//convert angle to a vector
			Flt xdir = cos(rad);
			Flt ydir = sin(rad);
			g.ship.vel[0] += xdir * (float)ydiff * 0.01f;
			g.ship.vel[1] += ydir * (float)ydiff * 0.01f;
			Flt speed = sqrt(g.ship.vel[0]*g.ship.vel[0]+
												g.ship.vel[1]*g.ship.vel[1]);
			if (speed > 10.0f) {
				speed = 10.0f;
				normalize2d(g.ship.vel);
				g.ship.vel[0] *= speed;
				g.ship.vel[1] *= speed;
			}
			g.mouseThrustOn = true;
			clock_gettime(CLOCK_REALTIME, &g.mouseThrustTimer);
		}
		x11.set_mouse_position(100,100);
		savex = 100;
		savey = 100;
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
			gl.maze_state = 1;
			break;
		case XK_2:
			gl.maze_state = 2;
			break;
		case XK_3:
			gl.maze_state = 3;
			break;

		case XK_b:
			jk_page_transition(gl.maze_state, "b", gl.firstRun, gl.maxMaze);
			break;
		
		case XK_s:
			jk_page_transition(gl.maze_state, "s", gl.firstRun, gl.maxMaze);
			break;

		case XK_c:
			jk_page_transition(gl.maze_state, "c", gl.firstRun, gl.maxMaze);
			break;
		
		case XK_r:
			jk_page_transition(gl.maze_state, "r", gl.firstRun, gl.maxMaze);
			break;
		
		case XK_q:
			jk_page_transition(gl.maze_state, "q", gl.firstRun, gl.maxMaze);
			break;

		case XK_w:
			jk_page_transition(gl.maze_state, "w", gl.firstRun, gl.maxMaze);
			break;

		case XK_e:
			jk_page_transition(gl.maze_state, "e", gl.firstRun, gl.maxMaze);
			break;

		case XK_z:
			jk_page_transition(gl.maze_state, "z", gl.firstRun, gl.maxMaze);
			break;
		
		case XK_5:
			jk_page_transition(gl.maze_state, "z", gl.firstRun, gl.maxMaze);
			break;

		case XK_6:
			jk_page_transition(gl.maze_state, "z", gl.firstRun, gl.maxMaze);
			break;


		case XK_Escape:
			return 1;
		case XK_f:
			break;
		// case XK_s:
		// 	break;
		case XK_Down:
			break;
		case XK_equal:
			break;
		case XK_minus:
			break;


	// // Rect jk_t = jk_createRect(gl.yres, 100, 10, 0);

	// 	case XK_1:
	// 		glClear(GL_COLOR_BUFFER_BIT);
	// 		jk_printMaze1(jk_t, gl.yres-100, 0x0040e0d0);
	// 		break;
	// 	case XK_2:
	// 		glClear(GL_COLOR_BUFFER_BIT);
	// 		jk_printMaze2(jk_t, gl.yres-100, 0x0040e0d0);
	// 		break;
	// 	case XK_3:
	// 		glClear(GL_COLOR_BUFFER_BIT);
	// 		jk_printMaze3(jk_t, gl.yres-100, 0x0040e0d0);
	// 		break;
	}
	return 0;
}

void deleteAsteroid(Game *g, Asteroid *node)
{
	//Remove a node from doubly-linked list
	//Must look at 4 special cases below.
	if (node->prev == NULL) {
		if (node->next == NULL) {
			//only 1 item in list.
			g->ahead = NULL;
		} else {
			//at beginning of list.
			node->next->prev = NULL;
			g->ahead = node->next;
		}
	} else {
		if (node->next == NULL) {
			//at end of list.
			node->prev->next = NULL;
		} else {
			//in middle of list.
			node->prev->next = node->next;
			node->next->prev = node->prev;
		}
	}
	delete node;
	node = NULL;
}

void buildAsteroidFragment(Asteroid *ta, Asteroid *a)
{
	//build ta from a
	ta->nverts = 8;
	ta->radius = a->radius / 2.0;
	Flt r2 = ta->radius / 2.0;
	Flt angle = 0.0f;
	Flt inc = (PI * 2.0) / (Flt)ta->nverts;
	for (int i=0; i<ta->nverts; i++) {
		ta->vert[i][0] = sin(angle) * (r2 + rnd() * ta->radius);
		ta->vert[i][1] = cos(angle) * (r2 + rnd() * ta->radius);
		angle += inc;
	}
	ta->pos[0] = a->pos[0] + rnd()*10.0-5.0;
	ta->pos[1] = a->pos[1] + rnd()*10.0-5.0;
	ta->pos[2] = 0.0f;
	ta->angle = 0.0;
	ta->rotate = a->rotate + (rnd() * 4.0 - 2.0);
	ta->color[0] = 0.8;
	ta->color[1] = 0.8;
	ta->color[2] = 0.7;
	ta->vel[0] = a->vel[0] + (rnd()*2.0-1.0);
	ta->vel[1] = a->vel[1] + (rnd()*2.0-1.0);
	//std::cout << "frag" << std::endl;
}

void physics()
{
	Flt d0,d1,dist;
	//Update ship position
	g.ship.pos[0] += g.ship.vel[0];
	g.ship.pos[1] += g.ship.vel[1];
	//Check for collision with window edges
	if (g.ship.pos[0] < 0.0) {
		g.ship.pos[0] += (float)gl.xres;
	}
	else if (g.ship.pos[0] > (float)gl.xres) {
		g.ship.pos[0] -= (float)gl.xres;
	}
	else if (g.ship.pos[1] < 0.0) {
		g.ship.pos[1] += (float)gl.yres;
	}
	else if (g.ship.pos[1] > (float)gl.yres) {
		g.ship.pos[1] -= (float)gl.yres;
	}
	//
	//
	//Update bullet positions
	struct timespec bt;
	clock_gettime(CLOCK_REALTIME, &bt);
	int i = 0;
	while (i < g.nbullets) {
		Bullet *b = &g.barr[i];
		//How long has bullet been alive?
		double ts = timeDiff(&b->time, &bt);
		if (ts > 2.5) {
			//time to delete the bullet.
			memcpy(&g.barr[i], &g.barr[g.nbullets-1],
				sizeof(Bullet));
			g.nbullets--;
			//do not increment i.
			continue;
		}
		//move the bullet
		b->pos[0] += b->vel[0];
		b->pos[1] += b->vel[1];
		//Check for collision with window edges
		if (b->pos[0] < 0.0) {
			b->pos[0] += (float)gl.xres;
		}
		else if (b->pos[0] > (float)gl.xres) {
			b->pos[0] -= (float)gl.xres;
		}
		else if (b->pos[1] < 0.0) {
			b->pos[1] += (float)gl.yres;
		}
		else if (b->pos[1] > (float)gl.yres) {
			b->pos[1] -= (float)gl.yres;
		}
		++i;
	}
	//
	//Update asteroid positions
	Asteroid *a = g.ahead;
	while (a) {
		a->pos[0] += a->vel[0];
		a->pos[1] += a->vel[1];
		//Check for collision with window edges
		if (a->pos[0] < -100.0) {
			a->pos[0] += (float)gl.xres+200;
		}
		else if (a->pos[0] > (float)gl.xres+100) {
			a->pos[0] -= (float)gl.xres+200;
		}
		else if (a->pos[1] < -100.0) {
			a->pos[1] += (float)gl.yres+200;
		}
		else if (a->pos[1] > (float)gl.yres+100) {
			a->pos[1] -= (float)gl.yres+200;
		}
		a->angle += a->rotate;
		a = a->next;
	}
	//
	//Asteroid collision with bullets?
	//If collision detected:
	//     1. delete the bullet
	//     2. break the asteroid into pieces
	//        if asteroid small, delete it
	a = g.ahead;
	while (a) {
		//is there a bullet within its radius?
		int i=0;
		while (i < g.nbullets) {
			Bullet *b = &g.barr[i];
			d0 = b->pos[0] - a->pos[0];
			d1 = b->pos[1] - a->pos[1];
			dist = (d0*d0 + d1*d1);
			if (dist < (a->radius*a->radius)) {
				//std::cout << "asteroid hit." << std::endl;
				//this asteroid is hit.
				if (a->radius > MINIMUM_ASTEROID_SIZE) {
					//break it into pieces.
					Asteroid *ta = a;
					buildAsteroidFragment(ta, a);
					int r = rand()%10+5;
					for (int k=0; k<r; k++) {
						//get the next asteroid position in the array
						Asteroid *ta = new Asteroid;
						buildAsteroidFragment(ta, a);
						//add to front of asteroid linked list
						ta->next = g.ahead;
						if (g.ahead != NULL)
							g.ahead->prev = ta;
						g.ahead = ta;
						g.nasteroids++;
					}
				} else {
					a->color[0] = 1.0;
					a->color[1] = 0.1;
					a->color[2] = 0.1;
					//asteroid is too small to break up
					//delete the asteroid and bullet
					Asteroid *savea = a->next;
					deleteAsteroid(&g, a);
					a = savea;
					g.nasteroids--;
				}
				//delete the bullet...
				memcpy(&g.barr[i], &g.barr[g.nbullets-1], sizeof(Bullet));
				g.nbullets--;
				if (a == NULL)
					break;
			}
			i++;
		}
		if (a == NULL)
			break;
		a = a->next;
	}
	//---------------------------------------------------
	//check keys pressed now
	if (gl.keys[XK_Left]) {
		// g.ship.angle += 4.0;
		// if (g.ship.angle >= 360.0f)
		// 	g.ship.angle -= 360.0f;
		// gl.player[0] = gl.player[1] - 1;
	}
	if (gl.keys[XK_Right]) {
		// g.ship.angle -= 4.0;
		// if (g.ship.angle < 0.0f)
		// 	g.ship.angle += 360.0f;

		// gl.player[0] = gl.player[1] + 1;
	}
	if (gl.keys[XK_Up]) {
		//apply thrust
		//convert ship angle to radians
		// Flt rad = ((g.ship.angle+90.0) / 360.0f) * PI * 2.0;
		// //convert angle to a vector
		// Flt xdir = cos(rad);
		// Flt ydir = sin(rad);
		// g.ship.vel[0] += xdir*0.02f;
		// g.ship.vel[1] += ydir*0.02f;
		// Flt speed = sqrt(g.ship.vel[0]*g.ship.vel[0]+
		// 		g.ship.vel[1]*g.ship.vel[1]);
		// if (speed > 10.0f) {
		// 	speed = 10.0f;
		// 	normalize2d(g.ship.vel);
		// 	g.ship.vel[0] *= speed;
		// 	g.ship.vel[1] *= speed;
		// }

		// gl.player[1] = gl.player[1] - 1;
	}
	if (gl.keys[XK_space]) {
		//a little time between each bullet
		struct timespec bt;
		clock_gettime(CLOCK_REALTIME, &bt);
		double ts = timeDiff(&g.bulletTimer, &bt);
		if (ts > 0.1) {
			timeCopy(&g.bulletTimer, &bt);
			if (g.nbullets < MAX_BULLETS) {
				//shoot a bullet...
				//Bullet *b = new Bullet;
				Bullet *b = &g.barr[g.nbullets];
				timeCopy(&b->time, &bt);
				b->pos[0] = g.ship.pos[0];
				b->pos[1] = g.ship.pos[1];
				b->vel[0] = g.ship.vel[0];
				b->vel[1] = g.ship.vel[1];
				//convert ship angle to radians
				Flt rad = ((g.ship.angle+90.0) / 360.0f) * PI * 2.0;
				//convert angle to a vector
				Flt xdir = cos(rad);
				Flt ydir = sin(rad);
				b->pos[0] += xdir*20.0f;
				b->pos[1] += ydir*20.0f;
				b->vel[0] += xdir*6.0f + rnd()*0.1;
				b->vel[1] += ydir*6.0f + rnd()*0.1;
				b->color[0] = 1.0f;
				b->color[1] = 1.0f;
				b->color[2] = 1.0f;
				g.nbullets++;
			}
		}
	}

	// Rect jk_t = jk_createRect(gl.yres, 100, 10, 0);
	// if (gl.keys[XK_1]) {
	// 	glClear(GL_COLOR_BUFFER_BIT);
	// 	jk_printMaze1(jk_t, gl.yres-100, 0x0040e0d0);
	// }
	// if (gl.keys[XK_2]) {
	// 	glClear(GL_COLOR_BUFFER_BIT);
	// 	jk_printMaze2(jk_t, gl.yres-100, 0x0040e0d0);
	// }
	// if (gl.keys[XK_3]) {
	// 	glClear(GL_COLOR_BUFFER_BIT);
	// 	jk_printMaze3(jk_t, gl.yres-100, 0x0040e0d0);
	// }



	if (g.mouseThrustOn) {
		//should thrust be turned off
		struct timespec mtt;
		clock_gettime(CLOCK_REALTIME, &mtt);
		double tdif = timeDiff(&mtt, &g.mouseThrustTimer);
		//std::cout << "tdif: " << tdif << std::endl;
		if (tdif < -0.3)
			g.mouseThrustOn = false;
	}
}



extern void jk_showCreditPage(Rect position, int defaultHeight, int color);
extern void jh_showCreditPage(Rect position, int defaultHeight, int color, int xres, int yres, unsigned int textid);
extern void jr_showCreditPage(Rect position, int defaultHeight, int color);
extern void et_showCreditPage(Rect position, int defaultHeight, int color);
extern void an_showCreditPage(Rect position, int defaultHeight, int color);

extern void jk_showRulesPage(Rect position, int defaultHeight, int color);
extern void jh_showRulesPage(Rect position, int defaultHeight, int color);
extern void jr_showRulesPage(Rect position, int defaultHeight, int color);
extern void et_showRulesPage(Rect position, int defaultHeight, int color);
extern void an_showRulesPage(Rect position, int defaultHeight, int color);

// can be replaced by picture logo
extern void jk_showWelcomePageTitle(Rect position, int defaultHeight, 
																int color);

extern void jk_showWelcomePage(Rect position, int defaultHeight, int color);
extern void jh_showWelcomePage(Rect position, int defaultHeight, int color);
extern void jr_showWelcomePage(Rect position, int defaultHeight, int color);
extern void et_showWelcomePage(Rect position, int defaultHeight, int color);
extern void an_showWelcomePage(Rect position, int defaultHeight, int color);
extern void jk_showWelcomePage2(Rect position, int defaultHeight, int color);
extern void jk_showWelcomePage3(Rect position, int defaultHeight, int color);
extern void jk_showSecretMode(Rect position, int defaultHeight, int color);
extern void jk_showSecretModeMessage(Rect position, int defaultHeight, 
																	int color);
extern void jk_playerMovement(char* keys, int (&player)[2], Grid& grid);
extern void jk_playerMovementForSecretMode(char* keys, int (&player)[2]);

//Jennifer's Midterm
extern void jkuo_midterm_function_wed (int maze_state);

//Jeff's Midterm
extern bool jhicks_midterm_function(int& maze_state);

//Jesus's Midterm
extern void jr_MidtermFunc(int value);

//Adam's Midterm
extern void anicholasPrint(int num);

//Eidmone's Midterm
extern void etagaca_midterm(string name);


void render()
{

//Jennifer's Midterm
jkuo_midterm_function_wed(gl.maze_state);

//Jeff's Midterm
if (jhicks_midterm_function(gl.maze_state))
	cout << "HOME SCREEN" << endl;
else
	cout << "NOT HOME SCREEN" << endl;

//Jesus's Midterm
jr_MidtermFunc(55);
jr_MidtermFunc(-108);

//Adam's Midterm
anicholasPrint(1);

//Eidmone's Midterm
etagaca_midterm("C++");
etagaca_midterm("Cobol");





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


	if (gl.maze_state == 0) {
		
		glClear(GL_COLOR_BUFFER_BIT);
		ggprint8b(&r, 16, 0x00ff0000, "3350 - MAze");

		// will delete
		jk_showWelcomePageTitle(jk_welcomeTitlePlaceHolder, 
											gl.yres - (gl.yres/2), 0x00FF0000);


		jk_showWelcomePage(jk_welcomeMessage, gl.yres - 400, 0x00CC593F);
		jh_showWelcomePage(jk_welcomeMessage, gl.yres - 490, 0x00CC593F);
		jr_showWelcomePage(jk_welcomeMessage, gl.yres - 450, 0x00CC593F);
		et_showWelcomePage(jk_welcomeMessage, gl.yres - 470, 0x00CC593F);
		an_showWelcomePage(jk_welcomeMessage, gl.yres - 430, 0x00CC593F);
		jk_showWelcomePage3(jk_welcomeMessage, gl.yres - 530, 0x00FF0050);
		jk_showWelcomePage2(jk_welcomeMessage, gl.yres - 550, 0x00FF0050);

		//should display "level" and "timer" instead... 
		//and maybe even "highest score" 
		// ggprint8b(&r, 16, 0x00ffff00, "n bullets: %i", g.nbullets);
		// ggprint8b(&r, 16, 0x00ffff00, "n asteroids: %i", g.nasteroids);
		// ggprint8b(&r, 16, 0x00ffffff, " ");



		//ggprint8b(&r, 16, 0x00ffffff, "Instructions:");
		//ggprint8b(&r, 16, 0x00ffffff, "right click to print msgs to console");
		//ggprint8b(&r, 16, 0x00ffffff, "press s to switch between maps");
		//ggprint8b(&r, 16, 0x00ffffff, "press c to view credit page");
		//ggprint8b(&r, 16, 0x00ffffff, "press r to view rules page ");
		//ggprint8b(&r, 16, 0x00ffffff, "press b to return to this page");



		

	}

	Rect jk_t = jk_createRect(gl.yres, 100, 10, 0);
	Rect jk_message = jk_createRect(gl.yres+50, 100, 10, 0); 
	Rect jk_titles = jk_createRect(gl.yres+50, 100, 10, 0);
	
	jk_titles.left = gl.xres / 2;
	jk_titles.center = 1;

	jk_message.left = 50;

	if (gl.maze_state == 11) {
		glClear(GL_COLOR_BUFFER_BIT);
		ggprint13(&jk_titles, 16, 0x00ffffff, "Rules Page");
		ggprint8b(&jk_titles, 16, 0x00ffffff, "press b to return to home");



		jk_showRulesPage(jk_message, gl.yres-120, 0x0040e0d0);
		jh_showRulesPage(jk_message, gl.yres-220, 0x0024AAFA);
		jr_showRulesPage(jk_message, gl.yres-320, 0x0051f542);
		et_showRulesPage(jk_message, gl.yres-420, 0x00B24BF3);
		an_showRulesPage(jk_message, gl.yres-520, 0x00FF7025);

	}





	if (gl.maze_state == 12) {
		glClear(GL_COLOR_BUFFER_BIT);
		// load_ggfont(17); // arial 140
		ggprint13(&jk_titles, 16, 0x00ffffff, "CREDIT Page");
		ggprint8b(&jk_titles, 16, 0x00ffffff, "press b to return to home");


		jk_showCreditPage(jk_message, gl.yres-20, 0x0040e0d0);
		jk_showCreditPage(jk_message, gl.yres-120, 0x0040e0d0);
		jh_showCreditPage(jk_message, gl.yres-220, 0x0024AAFA, gl.xres, gl.yres, gl.textid);
		jr_showCreditPage(jk_message, gl.yres-320, 0x0051f542);
		et_showCreditPage(jk_message, gl.yres-420, 0x00B24BF3);
		an_showCreditPage(jk_message, gl.yres-520, 0x00FF7025);
		
	}
	

	if (gl.maze_state == 1) {
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		ggprint8b(&r, 16, 0x00ffffff, "press s to switch to next maze");
		ggprint8b(&r, 16, 0x00ffffff, "press b to return to home");
		ggprint8b(&r, 16, 0x00ffffff, "HOLD down the arrowkeys to move about");


		jk_playerMovement(gl.keys, gl.player, gl.mazeGrid);
		jk_printMaze1(jk_t, gl.yres-100, 0x0040e0d0, gl.player, gl.firstRun, 
									gl.endReached, gl.mazeGrid, gl.maze_state);
	}
	if (gl.maze_state == 2) {
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		ggprint8b(&r, 16, 0x00ffffff, "press s to switch to next maze");
		ggprint8b(&r, 16, 0x00ffffff, "press b to return to home");
		ggprint8b(&r, 16, 0x00ffffff, "HOLD down the arrowkeys to move about");

		jk_playerMovement(gl.keys, gl.player, gl.mazeGrid);
		jk_printMaze2(jk_t, gl.yres-100, 0x0040e0d0, gl.player, gl.firstRun);
	}
	if (gl.maze_state == 3) {
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		ggprint8b(&r, 16, 0x00ffffff, "press s to switch to next maze");
		ggprint8b(&r, 16, 0x00ffffff, "press b to return to home");
		ggprint8b(&r, 16, 0x00ffffff, "HOLD down the arrowkeys to move about");

		jk_playerMovement(gl.keys, gl.player, gl.mazeGrid);
		jk_printMaze3(jk_t, gl.yres-100, 0x0040e0d0, gl.player, gl.firstRun);
	}
	if (gl.maze_state == 4) {
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		ggprint8b(&r, 16, 0x00ffffff, "press s to switch to next maze");
		ggprint8b(&r, 16, 0x00ffffff, "press b to return to home");
		ggprint8b(&r, 16, 0x00ffffff, "HOLD down the arrowkeys to move about");

		jk_playerMovement(gl.keys, gl.player, gl.mazeGrid);
		jk_printMazeTest(jk_t, gl.yres-100, 0x0040e0d0, gl.player, gl.firstRun, 
									gl.endReached, gl.mazeGrid, gl.maze_state);
	}



	if (gl.maze_state < 0) {

		glClear(GL_COLOR_BUFFER_BIT);
		ggprint8b(&r, 16, 0x00ffffff, "victory!");
		ggprint8b(&r, 16, 0x00ffffff, "press s to start the next level");

	}

	
// gl.maze_state = 1000;
	if (gl.maze_state == 1000) {

		glClear(GL_COLOR_BUFFER_BIT);
		ggprint8b(&r, 16, 0x00ffffff, "congrats on beating everything!");
		ggprint8b(&r, 16, 0x00ffffff, "press b to return to homepage");

	}







	//secret mode
	if (gl.maze_state == 23) {
		glClear(GL_COLOR_BUFFER_BIT);
		ggprint8b(&r, 16, 0x00ff0000, "3350 - MAze");

		// will delete
		jk_showSecretMode(jk_welcomeTitlePlaceHolder, 
											gl.yres - (gl.yres/2), 0x00FF0050);

		jk_showSecretModeMessage(jk_welcomeMessage, gl.yres - 400, 0x00CC5050);

	}

	//zen mode stages

	if (gl.maze_state == 231) {
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		ggprint8b(&r, 16, 0x00ffffff, "press s to switch to next maze");
		ggprint8b(&r, 16, 0x00ffffff, "press b to return to secret home");
		ggprint8b(&r, 16, 0x00ffffff, "HOLD down the arrowkeys to move about");

		jk_playerMovementForSecretMode(gl.keys, gl.player);
		jk_printMazeSecretMode1(jk_t, gl.yres-100, 0x0040e0d0, gl.player, 
												gl.firstRun);
	}
	if (gl.maze_state == 232) {
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		ggprint8b(&r, 16, 0x00ffffff, "press s to switch to next maze");
		ggprint8b(&r, 16, 0x00ffffff, "press b to return to secret home");
		ggprint8b(&r, 16, 0x00ffffff, "HOLD down the arrowkeys to move about");

		jk_playerMovementForSecretMode(gl.keys, gl.player);
		jk_printMazeSecretMode2(jk_t, gl.yres-100, 0x0040e0d0, gl.player, 
												gl.firstRun);
	}
	if (gl.maze_state == 233) {
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		ggprint8b(&r, 16, 0x00ffffff, "press s to switch to next maze");
		ggprint8b(&r, 16, 0x00ffffff, "press b to return to secret home");
		ggprint8b(&r, 16, 0x00ffffff, "HOLD down the arrowkeys to move about");

		jk_playerMovementForSecretMode(gl.keys, gl.player);
		jk_printMazeSecretMode3(jk_t, gl.yres-100, 0x0040e0d0, gl.player, 
												   gl.firstRun);
												// gl.firstRun, gl.mazeGrid);
	}


//for midterm
	if (gl.maze_state == 30) {
		glClear(GL_COLOR_BUFFER_BIT);
		ggprint8b(&r, 16, 0x00ff0000, "3350 - MAze");
		ggprint8b(&r, 16, 0x00ff0000, "transition succeeded.");		
		ggprint8b(&r, 16, 0x00ff0000, "press 6 to see a failed case.");		
		
		// jk_showSecretMode(jk_welcomeTitlePlaceHolder, 
		// 									gl.yres - (gl.yres/2), 0x00FF0050);

		// jk_showSecretModeMessage(jk_welcomeMessage, gl.yres - 400, 0x00CC5050);

	}



	// if (gl.keys[XK_1] ) {
	// 	glClear(GL_COLOR_BUFFER_BIT);
	// 	jk_printMaze1(jk_t, gl.yres-100, 0x0040e0d0);
	// }
	// if (gl.keys[XK_2] ) {
	// 	glClear(GL_COLOR_BUFFER_BIT);
	// 	jk_printMaze2(jk_t, gl.yres-100, 0x0040e0d0);
		
	// }
	// if (gl.keys[XK_3] ) {
		
	// }



	



/*
	//-------------------------------------------------------------------------
	//Draw the ship
	glColor3fv(g.ship.color);
	glPushMatrix();
	glTranslatef(g.ship.pos[0], g.ship.pos[1], g.ship.pos[2]);
	//float angle = atan2(ship.dir[1], ship.dir[0]);
	glRotatef(g.ship.angle, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	//glVertex2f(-10.0f, -10.0f);
	//glVertex2f(  0.0f, 20.0f);
	//glVertex2f( 10.0f, -10.0f);
	glVertex2f(-12.0f, -10.0f);
	glVertex2f(  0.0f,  20.0f);
	glVertex2f(  0.0f,  -6.0f);
	glVertex2f(  0.0f,  -6.0f);
	glVertex2f(  0.0f,  20.0f);
	glVertex2f( 12.0f, -10.0f);
	glEnd();
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex2f(0.0f, 0.0f);
	glEnd();
	glPopMatrix();
	if (gl.keys[XK_Up] || g.mouseThrustOn) {
		int i;
		//draw thrust
		Flt rad = ((g.ship.angle+90.0) / 360.0f) * PI * 2.0;
		//convert angle to a vector
		Flt xdir = cos(rad);
		Flt ydir = sin(rad);
		Flt xs,ys,xe,ye,r;
		glBegin(GL_LINES);
		for (i=0; i<16; i++) {
			xs = -xdir * 11.0f + rnd() * 4.0 - 2.0;
			ys = -ydir * 11.0f + rnd() * 4.0 - 2.0;
			r = rnd()*40.0+40.0;
			xe = -xdir * r + rnd() * 18.0 - 9.0;
			ye = -ydir * r + rnd() * 18.0 - 9.0;
			glColor3f(rnd()*.3+.7, rnd()*.3+.7, 0);
			glVertex2f(g.ship.pos[0]+xs,g.ship.pos[1]+ys);
			glVertex2f(g.ship.pos[0]+xe,g.ship.pos[1]+ye);
		}
		glEnd();
	}
	//-------------------------------------------------------------------------
	//Draw the asteroids
	// {
	// 	Asteroid *a = g.ahead;
	// 	while (a) {
	// 		//Log("draw asteroid...\n");
	// 		glColor3fv(a->color);
	// 		glPushMatrix();
	// 		glTranslatef(a->pos[0], a->pos[1], a->pos[2]);
	// 		glRotatef(a->angle, 0.0f, 0.0f, 1.0f);
	// 		glBegin(GL_LINE_LOOP);
	// 		//Log("%i verts\n",a->nverts);
	// 		for (int j=0; j<a->nverts; j++) {
	// 			glVertex2f(a->vert[j][0], a->vert[j][1]);
	// 		}
	// 		glEnd();
	// 		//glBegin(GL_LINES);
	// 		//	glVertex2f(0,   0);
	// 		//	glVertex2f(a->radius, 0);
	// 		//glEnd();
	// 		glPopMatrix();
	// 		glColor3f(1.0f, 0.0f, 0.0f);
	// 		glBegin(GL_POINTS);
	// 		glVertex2f(a->pos[0], a->pos[1]);
	// 		glEnd();
	// 		a = a->next;
	// 	}
	// }
	//-------------------------------------------------------------------------
	//Draw the bullets
	for (int i=0; i<g.nbullets; i++) {
		Bullet *b = &g.barr[i];
		//Log("draw bullet...\n");
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_POINTS);
		glVertex2f(b->pos[0],      b->pos[1]);
		glVertex2f(b->pos[0]-1.0f, b->pos[1]);
		glVertex2f(b->pos[0]+1.0f, b->pos[1]);
		glVertex2f(b->pos[0],      b->pos[1]-1.0f);
		glVertex2f(b->pos[0],      b->pos[1]+1.0f);
		glColor3f(0.8, 0.8, 0.8);
		glVertex2f(b->pos[0]-1.0f, b->pos[1]-1.0f);
		glVertex2f(b->pos[0]-1.0f, b->pos[1]+1.0f);
		glVertex2f(b->pos[0]+1.0f, b->pos[1]-1.0f);
		glVertex2f(b->pos[0]+1.0f, b->pos[1]+1.0f);
		glEnd();
	}

*/


}



