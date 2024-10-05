#include <ncurses.h>

int main() {
    initscr();
    start_color();
    raw();
    noecho();
    nodelay(stdscr,TRUE);

    printw("Ncurses run!\n");
    while(ERR == getch());

    endwin();
    return 0;
}