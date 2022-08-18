#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ncurses.h>

//#include "sst/core/eli/elementinfo.h"

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

string navigation = "Navigate with arrow keys, enter, and escape (or '-').";

inline int positive_modulo(int i, int n) {
    return (i % n + n) % n;
}

void update_title_bar(WINDOW *win, int choice) {
    switch (choice) {
        case 0:
            //mvwprintw(win, 0, 15, "──────────────────");
            box(win, 0, 0);
            mvwprintw(win, 0, 2, "[SST-Curses]");
            break;
        case 1:
            box(win, 0, 0);
            mvwprintw(win, 0, 2, "[SST-Curses]");
            mvwprintw(win, 0, 15, "[sst-info]");
            break;
        case 2:
            box(win, 0, 0);
            mvwprintw(win, 0, 2, "[SST-Curses]");
            mvwprintw(win, 0, 15, "[Search by Tag]");
            break;
        case 3:
            box(win, 0, 0);
            mvwprintw(win, 0, 2, "[SST-Curses]");
            mvwprintw(win, 0, 15, "[Example Projects]");
            break;
        case 4:
            box(win, 0, 0);
            mvwprintw(win, 0, 2, "[SST-Curses]");
            mvwprintw(win, 0, 15, "[Project Builder]");
            break;

    }
    wrefresh(win);
}

int menu(WINDOW *win, int yoffset, int xoffset) {
    static int choice = 0;

    curs_set(0);

    update_title_bar(win, 0);
    noecho();
    keypad(win,true);
    mvwprintw(win, yoffset, xoffset, "Select an option:");

    int done = 0; // used for manual selection

    while (1) {
        for (int i = 0; i < menuchoices.size(); i++) {
            if (choice == i) {
                wattron(win, A_REVERSE);
            }
            mvwprintw(win, yoffset+2+i, xoffset, menuchoices[i].c_str());
            wattroff(win, A_REVERSE);
        }
        wrefresh(win);
        int c = wgetch(win);

        switch (c) {
            case KEY_UP:
            case 'k':
                choice = positive_modulo(choice-1, menuchoices.size());
                break;
            case 'j':
            case KEY_DOWN:
                choice = positive_modulo(choice+1, menuchoices.size());
                break;
            case KEY_ENTER:
            case 10:
                return choice+1;
            case '1':
                return 1;
            case '2':
                return 2;
            case '3':
                return 3;
            case '4':
                return 4;
        }
    }
    return choice;

}
void panel_sst_info(int maxy, int maxx) {
    WINDOW *sst_info = newwin(maxy-2, maxx-2, 1, 1);
    mvwprintw(sst_info, 2, 2, "Welcome to sst-info!");
    wrefresh(sst_info);

    keypad(sst_info, true);

    while(1) {
        int c = wgetch(sst_info);
        if (c == 27 || c == '-') { // ESC or '-'
            return;
        }
    }
}
void panel_search(int maxy, int maxx) {
    WINDOW *sst_info = newwin(maxy-2, maxx-2, 1, 1);
    mvwprintw(sst_info, 2, 2, "Welcome to the search tool!");
    wrefresh(sst_info);

    while(1) {
        int c = wgetch(sst_info);
        if (c == 27 || c == '-') { // ESC or '-'
            return;
        }
    }
}
void panel_example(int maxy, int maxx) {
    WINDOW *sst_info = newwin(maxy-2, maxx-2, 1, 1);
    mvwprintw(sst_info, 2, 2, "Welcome to the example project catalog!");
    wrefresh(sst_info);

    while(1) {
        int c = wgetch(sst_info);
        if (c == 27 || c == '-') { // ESC or '-'
            return;
        }
    }
}
void panel_builder(int maxy, int maxx) {
    WINDOW *sst_info = newwin(maxy-2, maxx-2, 1, 1);
    mvwprintw(sst_info, 2, 2, "Welcome to the interactive project builder!");
    wrefresh(sst_info);

    while(1) {
        int c = wgetch(sst_info);
        if (c == 27 || c == '-') { // ESC or '-'
            return;
        }
    }
}


int main(int argc, char **argv)
{
    initscr();
    cbreak();
    //noecho();

    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);
    WINDOW *win = newwin(maxy, maxx, 0, 0);
    //mvprintw(maxy, 10, "Navigation:");
    refresh();

    //wattron(win, A_REVERSE);
    box(win, 0, 0);
    //cchar_t verch, horch;
    //setcchar(&verch, L"o", 0, 0, NULL);
    //setcchar(&horch, L"o", 0, 0, NULL);
    //box_set(win, &verch, &horch);
    update_title_bar(win, 0);
    //mvwprintw(win, 0, 2, "[sst-curses]");
    mvwprintw(win, maxy-2, (maxx-navigation.length())/2, navigation.c_str());
    wrefresh(win);
    //wattroff(win, A_REVERSE);

    wrefresh(win);

    /*
    WINDOW *sstinfo = newwin(maxy-2, maxx-2, 1, 1);
    refresh();
    box(sstinfo, 0, 0);
    mvwprintw(sstinfo, 0, 3, "[ sst-info ]");
    wrefresh(sstinfo);
*/

    // main loop
    while (1) {
        logo(win, 2, (maxx-50) / 2);
        int choice = menu(win, (maxy-menuchoices.size())/2, (maxx-31)/2);
        update_title_bar(win, choice);
        //wclear(win);
        //wrefresh(win);
        switch (choice) {
            case 1:
                panel_sst_info(maxy, maxx);
                break;
            case 2:
                panel_search(maxy, maxx);
                break;
            case 3:
                panel_example(maxy, maxx);
                break;
            case 4:
                panel_builder(maxy, maxx);
                break;
        }
    }

    /*
    logo(win, 2, (maxx-50) / 2);
    int choice = menu(win, 7, 2);
    update_title_bar(win, choice);

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

    */

    endwin();
    return 0;
}
