#include <ncurses.h>
#include <stdio.h>
#include <vector>
#include <string>
#include "GraphicalUserInterface.h"

using namespace std;

int main(void) {

    UI_InicializaGUI();

    mvprintw(2, 2, "Programa finalizado.");
    refresh();
    getch();
    endwin();

    return 0;
}
