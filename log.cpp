//log.cpp
//Author:  Gordon Griesel
//Date:    Summer 2014
//Purpose: Allow logging of messages to a file during program execution.
//
#include <stdio.h>
#include <stdarg.h>
#define FILENAME "x.x"
static FILE *fpxx;

void logOpen(void) { fpxx = fopen(FILENAME, "w"); }
void logClose(void) { fclose(fpxx); }

void Log(const char *fmt, ...)
{
	//This function works like printf()
	//The name Log is used because "log" is a standard C/C++ math function
	//usage:
	//Log("my numbers are: %i %i %f\n", num1, num2, fnum1);
	//
	va_list ap;
	if (fmt == NULL) return;
	va_start(ap, fmt);
	vfprintf(fpxx, fmt, ap);
	fflush(fpxx);
	va_end(ap);
}
