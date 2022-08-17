#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ncurses.h>

using namespace std;

void logo(WINDOW *win, int yoffset, int xoffset) {
    mvwprintw(win, yoffset  , xoffset, ",---.,---.|---      ,---..   .,---.,---.,---.,---.");
    mvwprintw(win, yoffset+1, xoffset, "`---.`---.|     --- |    |   ||    `---.|---'`---.");
    mvwprintw(win, yoffset+2, xoffset, "`---'`---'`---'     `---'`---'`    `---'`---'`---'");
    wrefresh(win);
}

vector<string> menuchoices = {
    "(1) sst-info",
    "(2) Search components by tag",
    "(3) Create example project",
    "(4) Interactive project builder"
};

inline int positive_modulo(int i, int n) {
    return (i % n + n) % n;
}

int menu(WINDOW *win, int yoffset, int xoffset) {
    static int choice = 0;

    noecho();
    keypad(win,true);
    mvwprintw(win, yoffset, xoffset, "Select an option:");

    int done = 0; // used for manual selection

    while (1) {
        for (int i = 0; i < menuchoices.size(); i++) {
            if (choice == i) {
                wattron(win, A_REVERSE);
            }
            mvwprintw(win, yoffset+1+i, xoffset, menuchoices[i].c_str());
            wattroff(win, A_REVERSE);
        }
        wrefresh(win);

        int c = wgetch(win);

        switch (c) {
            case KEY_UP:
                choice = positive_modulo(choice-1, menuchoices.size());
                break;
            case KEY_DOWN:
                choice = positive_modulo(choice+1, menuchoices.size());
                break;
            case KEY_ENTER:
            case 10:
                return choice;
            case '1':
                return 0;
            case '2':
                return 1;
            case '3':
                return 2;
            case '4':
                return 3;
        }
    }
    return choice;

}

int main(int argc, char **argv)
{
    initscr();
    cbreak();
    //noecho();

    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);
    WINDOW *win = newwin(maxy, maxx, 0, 0);
    refresh();

    box(win, 0, 0);
    wrefresh(win);

    logo(win, 2, (maxx-50) / 2);
    int choice = menu(win, 7, 2);


    WINDOW *input = newwin(3, maxx-4, maxy-4, 2);
    box(input,0,0);
    wrefresh(input);

    wmove(input, 0, 0);
    refresh();
    mvwprintw(input, 1, 2, "You selected %d.", choice+1);
    wrefresh(input);

    keypad(input,true);

    while(1) {
        int c = wgetch(input);
        if (c == 27) {
            wclear(input);
            wrefresh(input);
            menu(win, 7, 2);
        }
    }


    endwin();
    return 0;
}