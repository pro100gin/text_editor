#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <curses.h>
#include <dirent.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>

int row, col;

void InitWnds(WINDOW** , WINDOW** , WINDOW** , WINDOW** );
void InitDraw(char* );

#endif
