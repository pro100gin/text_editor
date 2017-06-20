#include "../include/init.h"
#include "../include/read_file.h"

void InitWnds(WINDOW** info_wnd_parent, WINDOW** main_wnd_parent,
                                 WINDOW** info_wnd, WINDOW** main_wnd){
    refresh();
    keypad(stdscr, TRUE);
    cbreak();
    start_color();
    noecho();
    curs_set(2);

    *info_wnd_parent = newwin(3, col, 0, 0);
    box(*info_wnd_parent, '|', '-');

    *info_wnd = derwin(*info_wnd_parent, 1, col-2, 1, 1);

    *main_wnd_parent = newwin(row-5, col, 3, 0);
    box(*main_wnd_parent, '|', '-');
    *main_wnd = derwin(*main_wnd_parent, row-7, col-2, 1, 1);

}

void InitDraw(char* file_name){
    int i;
    char dir[255];
    int count;
    char** text;

    WINDOW* info_wnd_parent,* main_wnd_parent;
    WINDOW* info_wnd,* main_wnd;

	initscr();
	getmaxyx(stdscr, row, col);

    InitWnds(&info_wnd_parent, &main_wnd_parent, &info_wnd, &main_wnd);

    wprintw(info_wnd,"%s/%s", getcwd(dir, 255), file_name);
    text = ReadData(file_name, &count);

    for(i = 0; i < count; ++i){
            wprintw(main_wnd,"%s", text[i]);
    }

    wmove(main_wnd,0,0);
    mvprintw(row-2, 0, "current cursor position\nrow: %d, col: %d", 0, 0);
    move(4,1);

    wrefresh(main_wnd_parent);
    wrefresh(info_wnd_parent);

    run(main_wnd, file_name);

    echo();
    endwin();
}
