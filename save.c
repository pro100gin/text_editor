#include "readData.h"



char** readData(char *dir, int *fileCount){
    struct dirent **entry;
    char **names;
    (*fileCount)=0;
    (*fileCount) = scandir(dir, &entry, 0, alphasort);
    names = (char**)malloc((*fileCount)*sizeof(char*));
    for(int i=1; i <(*fileCount); ++i){
       names[i-1] = malloc(255);
       strcpy(names[i-1], entry[i]->d_name);
    }
    (*fileCount)--;
    return names;
}


void printFiles(direct *curr, int colorBG){
	wclear(curr->workWnd);
	for(int i=0; i<curr->countNames; ++i){
		if(i == curr->currPos){
			wattron(curr->workWnd, COLOR_PAIR(colorBG));
			wprintw(curr->workWnd, "%40.40s\n", curr->names[i]);
			wattroff(curr->workWnd, COLOR_PAIR(colorBG));
		}
		else
			wprintw(curr->workWnd, "%40.40s\n", curr->names[i]);
	}
	wrefresh(curr->workWnd);
}

void run(direct *left, direct *right, direct *current){ 
	int ch =0;
	while((ch = getch()) != 'q'){
		switch(ch){
			case KEY_LEFT:
				if(current->workWnd == right->workWnd){
					printFiles(current, 2);
					right->currPos = current->currPos;
					current = left;
					printFiles(current, 1);
				}
				break;
			case KEY_RIGHT:
				if(current->workWnd == left->workWnd){
					printFiles(current, 2);
					left->currPos = current->currPos;
					current = right;
					printFiles(current, 1);
				}
				break;
			case KEY_UP:
			 	if(current->currPos > 0) current->currPos--;
				printFiles(current, 1);
				break;
			case KEY_DOWN:
				if(current->currPos < current->countNames - 1) current->currPos++;
				printFiles(current, 1);
				break;
			case 10: //enter
				if(!chdir(current->path)){
					if(!chdir(current->names[current->currPos])){
						free(current->names);
						current->names=NULL;
						current->names = readData(".", &current->countNames);
						current->currPos = 0;
						getcwd(current->path, MAXDIR);
						printFiles(current, 1);
						if(current->workWnd == left->workWnd) left = current;
						else right = current;
					}
				}
				break;
			}
			wrefresh(current->workWnd);
		}
}

void initDraw(){
	initscr();
	direct *right = malloc(sizeof(direct));
	direct *left = malloc(sizeof(direct));
	direct *current = malloc(sizeof(direct));
	left->names = readData(getenv("PWD"), &left->countNames);
	right->names = readData(getenv("HOME"), &right->countNames);
	strcpy(left->path,getenv("PWD"));
	strcpy(right->path,getenv("HOME"));
	
	int ch;
	int row, col;

	curs_set(0);
	refresh();
	keypad(stdscr, TRUE);
	cbreak();
	start_color();
	noecho();
	getmaxyx(stdscr, row, col);

	left->parentWnd = newwin(row, col/2-1, 0, 0);
	box(left->parentWnd, '|', '-');
	left->workWnd = derwin(left->parentWnd, row-2, col/2-3, 1, 1);
	
	right->parentWnd = newwin(row, col/2, 0, col/2);
	box(right->parentWnd, '|', '-');
	right->workWnd = derwin(right->parentWnd, row-2, col/2-2, 1, 1);

	init_pair(1, COLOR_WHITE, COLOR_CYAN);
	init_pair(2, COLOR_WHITE, COLOR_BLUE);

	printFiles(left, 1);
	printFiles(right, 2);

	wrefresh(left->parentWnd);
	wrefresh(right->parentWnd);
	
	current = left;
	

	run(left, right, current);
	
	echo();
	endwin();
}




int main(){
   drawInterface();
   return 0;
}
