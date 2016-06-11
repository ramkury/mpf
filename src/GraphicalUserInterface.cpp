#include "GraphicalUserInterface.h"
#include <ncurses.h>

unsigned int UI_SelecionaOpcao(std::vector<std::string> itensMenu)
{
	char szTemp[100];
	unsigned int inx;
	int currentInput;
	cbreak();
	noecho();

	WINDOW * hwndMenu = newwin(30, 60, 3, 3);

	box(hwndMenu, 0, 0);
	wrefresh(hwndMenu);
	wbkgd(hwndMenu, COLOR_PAIR(cores_menu));
	for (inx = 1; inx <= itensMenu.size(); ++inx)
	{
		if (inx == 1)
			wattron(hwndMenu, A_STANDOUT);
		else
			wattroff(hwndMenu, A_STANDOUT);
		sprintf(szTemp, "%-10s", itensMenu.at(inx-1).c_str());
		mvwprintw(hwndMenu, inx, 1, szTemp);
	}

	keypad(hwndMenu, TRUE);
	curs_set(0);

	inx = 1;
	currentInput = 0;
	do
	{
		mvwprintw(hwndMenu, inx, 1, szTemp);
		switch(currentInput)
		{
			case KEY_UP:
				inx = (inx <= 1) ? itensMenu.size() : inx - 1;
				break;
			case KEY_DOWN:
				inx = (inx >= itensMenu.size()) ? 1 : inx + 1;
				break;
		}
		wattron(hwndMenu, A_STANDOUT);
		sprintf(szTemp, "%-10s", itensMenu.at(inx-1).c_str());
		mvwprintw(hwndMenu, inx, 1, szTemp);
		wattroff(hwndMenu, A_STANDOUT);
	} while((currentInput = wgetch(hwndMenu)) != '\n');

	delwin(hwndMenu);
	return inx;
}