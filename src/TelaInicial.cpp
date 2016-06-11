#include <ncurses.h>
#include <stdio.h>
#include <vector>
#include <string>
#include "GraphicalUserInterface.h"

using namespace std;

int main(void)
{

	initscr();
	start_color();

	init_pair(cores_padrao, COLOR_WHITE, COLOR_BLACK);
	init_pair(cores_menu, COLOR_WHITE, COLOR_GREEN);
	init_pair(cores_nao_concluido,COLOR_RED,COLOR_WHITE);
	init_pair(cores_concluido,COLOR_GREEN,COLOR_WHITE);

	WINDOW * hwndMenu;
	vector<string> itensMenu;
	itensMenu.push_back("item1");
	itensMenu.push_back("item2");
	itensMenu.push_back("item3");
	itensMenu.push_back("item4");

	UI_SelecionaOpcao(itensMenu);

	
	mvprintw(2, 2, "hi");
	refresh();
	getch();

	endwin();

	return 0;
}
