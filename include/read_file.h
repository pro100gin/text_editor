#ifndef READ_FILE_H
#define READ_FILE_H
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

char** ReadData(char* ,int* );
void WriteData(char* , char** , int );
void run(WINDOW* , char* );

#endif
