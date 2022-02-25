#ifndef _DEFS_H
#define _DEFS_H

typedef double Flt;
typedef double Vec[3];
typedef Flt	Matrix[4][4];

#define MakeVector(x, y, z, v) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)
#define VecNegate(a)	(a)[0]=(-(a)[0]); (a)[1]=(-(a)[1]); (a)[2]=(-(a)[2]);
#define VecDot(a,b)	((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecLen(a)	((a)[0]*(a)[0]+(a)[1]*(a)[1]+(a)[2]*(a)[2])
#define VecLenSq(a)	sqrtf((a)[0]*(a)[0]+(a)[1]*(a)[1]+(a)[2]*(a)[2])
#define VecCopy(a,b)	(b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2];
#define VecAdd(a,b,c) (c)[0]=(a)[0]+(b)[0]; (c)[1]=(a)[1]+(b)[1]; (c)[2]=(a)[2]+(b)[2]
#define VecSub(a,b,c) (c)[0]=(a)[0]-(b)[0]; (c)[1]=(a)[1]-(b)[1]; (c)[2]=(a)[2]-(b)[2]
#define VecS(A,a,b) (b)[0]=(A)*(a)[0]; (b)[1]=(A)*(a)[1]; (b)[2]=(A)*(a)[2]
#define VecAddS(A,a,b,c) (c)[0]=(A)*(a)[0]+(b)[0]; (c)[1]=(A)*(a)[1]+(b)[1]; (c)[2]=(A)*(a)[2]+(b)[2]
#define VecCross(a,b,c) (c)[0]=(a)[1]*(b)[2]-(a)[2]*(b)[1]; (c)[1]=(a)[2]*(b)[0]-(a)[0]*(b)[2]; (c)[2]=(a)[0]*(b)[1]-(a)[1]*(b)[0]
#define VecZero(v) (v)[0]=0.0;(v)[1]=0.0;v[2]=0.0
#define ABS(a) (((a)<0)?(-(a)):(a))
#define SGN(a) (((a)<0)?(-1):(1))
#define SGND(a) (((a)<0.0)?(-1.0):(1.0))

typedef struct t_rect {
	int left;
	int top;
	int right;
	int bot;
	int width;
	int height;
	int center;
	int centerx;
	int centery;
} Rect;

typedef struct t_mouse {
	int x,y;
	int lastx,lasty;
	int lbuttondown;
} Mouse;

typedef struct t_bsphere {
	Vec center;
	Flt radius;
	Flt radiusSqr;
} Bsphere;

typedef struct t_bbox {
	Flt min[3];
	Flt max[3];
} Bbox;

typedef struct t_texmap {
	int xres, yres;
	unsigned char *c;
	unsigned int *i;
} Texmap;

typedef struct t_screen {
	int x_res, y_res;
	int screen_x_res, screen_y_res;
	float gl_perspective_viewangle;
	Flt xcenter, ycenter;
	Flt fy_res, fx_res;
} Screen;

#define MAX_LIGHTS (4)
typedef struct t_lights {
	int onoff;
	int nlights;
	Vec light;
	float glAmb[4];
	float glDif[4];
	float glPos[4];
} Lights;

typedef struct t_keys {
	int autorepeatstate, shiftstate, ctrlstate, shiftlockstate;
} Keys;

typedef struct t_camera {
	Vec pos;
	Vec move;
	Vec dir;
	Vec rot;
	Flt ang;
	Flt tilt;
	Matrix m;
} Camera;

typedef struct t_mats {
	Matrix worldSpace;
	Matrix cameraSpace;
	Matrix playerSpace;
} Mats;

typedef struct t_frustum {
	Flt frontPlaneDistance;
	Vec frontPlaneNormal;
	Vec frontPlanePoint;
	Flt farPlaneDistance;
	Vec farPlanePoint;
	Flt farObjectPlaneDistance;
	Vec farObjectPlanePoint;
	Flt missile_view_distance2;
	//#1 is left   plane normal
	//#2 is right  plane normal
	//#3 is top    plane normal
	//#4 is bottom plane normal
	//#5 is front  plane normal
	//#6 is far    plane normal
	Vec planes[6];
	Flt glplanesd[6][4];
	float glplanesf[6][4];
	float glFarPlaneDistance;
	float glNearPlaneDistance;
	Vec save_planes[6];
} Frustum;

#endif

