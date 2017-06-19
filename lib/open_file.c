#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <curses.h>
#include <dirent.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>

char** ReadData(char* file_name,int* count_str){
	char **text, temp_str[255];
	text = malloc(sizeof(char*));
	text[0] = malloc(255);
	FILE *fp = fopen(file_name, "r");
	int real_size=0;
	*count_str = 0;
	while(real_size = fread(temp_str, 1, 255, fp)){
		if(real_size!=255){
			temp_str[real_size]='\0';
			text = realloc(text, ((*count_str) + 1)*sizeof(char*));
			text[*count_str] = realloc(text[*count_str], 256);
			strcpy(text[*count_str], temp_str);
			(*count_str)++;
			 break;
		}
		//temp_str[strlen(temp_str)-1] = '\0';
		text = realloc(text, ((*count_str) + 1)*sizeof(char*));
		text[*count_str] = realloc(text[*count_str], 256);
		strcpy(text[*count_str], temp_str);
		(*count_str)++;
	}
	fclose(fp);
	return text;
}

void WriteData(char* file_name, char** text, int count){
	FILE *fp = fopen(file_name, "w");
	for(int i = 0; i < count; ++i){
		fwrite(text[i], 80, 1, fp);
	}
	//fwrite(text, sizeof(text), 1, fp);
	fclose(fp);
}

void run(WINDOW* text_wnd, char* file_name, int row, int col, int count){
	int ch =0;
	int curr_pos_x = 0, curr_pos_y = 0;
	while((ch = getch()) != 'q'){
		switch(ch){
			case KEY_LEFT:
				if(curr_pos_x>0){
					wmove(text_wnd, curr_pos_y, --curr_pos_x);
					move(curr_pos_y+4, curr_pos_x+1);
				}
				break;
			case KEY_RIGHT:
				if(curr_pos_x<col-3){
					wmove(text_wnd, curr_pos_y, ++curr_pos_x);
					move(curr_pos_y+4, curr_pos_x+1);
				}
				break;
			case KEY_UP:
			 	if(curr_pos_y>0){
					wmove(text_wnd, --curr_pos_y, curr_pos_x);
					move(curr_pos_y+4, curr_pos_x+1);
				}
			 	break;
			case KEY_DOWN:
				if(curr_pos_y<row-8){
					wmove(text_wnd, ++curr_pos_y, curr_pos_x);
					move(curr_pos_y+4, curr_pos_x+1);
				}
				break;
			case 25:
				curr_pos_x;
				char **text, temp[255];
				text = malloc((row-7)*sizeof(char*));

				int i=0, real_size=0;
				while((real_size = mvwinnstr(text_wnd, i, 0, temp, 80)) != ERR){
					text[i] = malloc(80);
					strcpy(text[i], temp);
					text[i][79] = '\n';
					i++;
					if(i>row-7) break;
				}
				WriteData(file_name, text, row-7);
				return;
			default:
				if(curr_pos_x>col-3){
					curr_pos_x=0;
					curr_pos_y++;
					wmove(text_wnd, curr_pos_y, curr_pos_x);
					move(curr_pos_y+4, curr_pos_x+1);
				}

				count = curr_pos_y > count ? curr_pos_y : count;

				wprintw(text_wnd, "%c",ch);
				curr_pos_x++;
				break;
			}
			mvprintw(row-2, 0, "current cursor position\nrow: %d, col: %d", curr_pos_y, curr_pos_x);
			move(curr_pos_y+4, curr_pos_x+1);
			wrefresh(text_wnd);
		}
}

void InitDraw(char* file_name){
    initscr();
    int ch;
    int row, col;
    WINDOW* info_wnd_parent,* main_wnd_parent;
    WINDOW* info_wnd,* main_wnd;
    refresh();
    keypad(stdscr, TRUE);
    cbreak();
    start_color();
    noecho();
    curs_set(2);
    getmaxyx(stdscr, row, col);

    info_wnd_parent = newwin(3, col, 0, 0);
    box(info_wnd_parent, '|', '-');

	info_wnd = derwin(info_wnd_parent, 1, col-2, 1, 1);

    main_wnd_parent = newwin(row-5, col, 3, 0);
    box(main_wnd_parent, '|', '-');
    main_wnd = derwin(main_wnd_parent, row-7, col-2, 1, 1);
	char dir[255];
	wprintw(info_wnd,"%s", getcwd(dir, 255));
	wprintw(info_wnd,"/%s", file_name);
	int count;
	char** text = ReadData(file_name, &count);
	for(int i = 0; i < count; ++i){
		wprintw(main_wnd,"%s", text[i]);
	}
    

    wmove(main_wnd,0,0);
    mvprintw(row-2, 0, "current cursor position\nrow: %d, col: %d", 0, 0);
    move(4,1);
	wrefresh(main_wnd_parent);
    wrefresh(info_wnd_parent);
    run(main_wnd, file_name, row, col, count);
    attroff(COLOR_PAIR(1));
    echo();
    endwin();
}





int main(){
	char *file_name = "text";
	InitDraw(file_name);

	return 0;
}
