#include "../include/read_file.h"
int row, col;

char** ReadData(char* file_name,int* count_str){
	char **text, temp_str[255];
	int real_size=0;
	FILE *fp;
	if((fp = fopen(file_name, "r")) == NULL){
		perror("fopen error");
		exit(-1);
	}
	if((text = malloc(sizeof(char*))) == NULL){
		perror("malloc error");
		exit(-1);
	}
	if((text[0] = malloc(255)) == NULL){
		perror("malloc error");
		exit(-1);
	}
	*count_str = 0;
	while((real_size = fread(temp_str, 1, 255, fp)) != 0){
		if(real_size!=255){
			temp_str[real_size]='\0';
			if((text = realloc(text, ((*count_str) + 1)*sizeof(char*)))==NULL){
				perror("realloc error");
				exit(-1);
			}
			if((text[*count_str] = realloc(text[*count_str], 256)) == NULL){
				perror("realloc error");
				exit(-1);
			}
			strcpy(text[*count_str], temp_str);
			(*count_str)++;
			break;
		}
		if((text = realloc(text, ((*count_str) + 1)*sizeof(char*))) == NULL){
			perror("realloc error");
			exit(-1);
		}
		if((text[*count_str] = realloc(text[*count_str], 256)) == NULL){
			perror("realloc error");
			exit(-1);
		}
		strcpy(text[*count_str], temp_str);
		(*count_str)++;
	}
	fclose(fp);
	return text;
}

void WriteData(char* file_name, char** text, int count){
	int i;
	FILE *fp;
	if((fp = fopen(file_name, "w")) == NULL){
		perror("fopen error");
		exit(-1);
	}
	for(i = 0; i < count; ++i){
		fwrite(text[i], 80, 1, fp);
	}
	fclose(fp);
}

void run(WINDOW* text_wnd, char* file_name){
	int ch =0, i = 0;
	int curr_pos_x = 0, curr_pos_y = 0, real_size = 0;
	char **text, temp[255];

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
				if((text = malloc((row-7)*sizeof(char*))) == NULL){
					perror("malloc error");
				}

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

				wprintw(text_wnd, "%c",ch);
				curr_pos_x++;
				break;
			}
			mvprintw(row-2, 0, "current cursor position\nrow: %d, col: %d",
													 curr_pos_y, curr_pos_x);
			move(curr_pos_y+4, curr_pos_x+1);
			wrefresh(text_wnd);
		}
}
