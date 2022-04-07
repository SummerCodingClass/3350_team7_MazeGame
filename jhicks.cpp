// Jeff Hicks
//
// Source File for Project
//
#include <iostream>
#include <GL/glx.h>
#include "fonts.h"
#include "GridCells.h"
#include "Grid.h"

//determines if the maze state is the home page
bool jhicks_midterm_function(int& maze_state)
{
    if (maze_state == 0)
    	cout << "HOME SCREEN" << endl;
    else
	    cout << "NOT HOME SCREEN" << endl;
    return (maze_state == 0);
}


void jh_PrintMsg()
{   
    cout << "Hello from Jeff's file!" << endl;
    return;
}


void jh_showCreditPage(Rect position, int defaultHeight, int color)
{
    position.bot = defaultHeight;
    ggprint8b(&position, 16, color, "Jeff Hicks:");
    ggprint8b(&position, 16, color, "Game Designer | Game Programmer");
}

void jh_Image(int xres, int yres, unsigned int textid)
{
    glPushMatrix();
    glTranslatef(xres/2, yres/2, 0);
    float w = 50.0;
    glColor3ub(255, 255, 255);
    glBindTexture(GL_TEXTURE_2D, textid);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-w,-w);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-w,w);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(w,w);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(w,-w);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

void jh_showRulesPage(Rect position, int defaultHeight, int color)
{
    position.bot = defaultHeight;
    ggprint8b(&position, 16, color, "Rule 2:");
    ggprint8b(&position, 16, color, 
        "Timer will stop once you hit the exit.");
}


void jh_showWelcomePage(Rect position, int defaultHeight, int color)
{
    position.bot = defaultHeight;
    ggprint8b(&position, 16, color, 
        "right click to print msgs to console");
}

int GridCells:: setXcoord(int input)
{
    xcoord = input;
    return xcoord;
}

int GridCells:: setYcoord(int input)
{
    ycoord = input;
    return ycoord;
}

bool GridCells:: setSpace(bool input)
{
    space = input;
    return space;
}


