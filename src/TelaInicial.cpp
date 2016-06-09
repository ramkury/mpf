#include <ncurses.h>
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

int main(void)
{

	enum TS_cores
	{
		TS_cores_padrao,
		TS_cores_menu,
		TS_cores_concluido,
		TS_cores_nao_concluido
	};

	WINDOW * w;
	vector<string> menu;
	menu.push_back("item1");
	menu.push_back("item2");
	menu.push_back("item3");
	menu.push_back("item4");

	char str[10];
	int n_itens = 4;
	int inx, ch;

	initscr();
	cbreak();
	start_color();
	noecho();

	init_pair(TS_cores_padrao, COLOR_WHITE, COLOR_BLACK);
	init_pair(TS_cores_menu, COLOR_WHITE, COLOR_GREEN);
	init_pair(TS_cores_nao_concluido,COLOR_RED,COLOR_WHITE);
	init_pair(TS_cores_concluido,COLOR_GREEN,COLOR_WHITE);

	bkgd(COLOR_PAIR(TS_cores_padrao));

	w = newwin(30, 60, 3, 3);
	box(w, 0, 0);
	wbkgd(w, COLOR_PAIR(TS_cores_menu));
	for (inx = 1; inx <= menu.size(); ++inx)
	{
		if (inx == 1)
			wattron(w, A_STANDOUT);
		else
			wattroff(w, A_STANDOUT);
		sprintf(str, "%-10s", menu.at(inx-1).c_str());
		mvwprintw(w, inx, 1, str);
	}

	keypad(w, TRUE);
	curs_set(0);

	inx = 1;
	ch = 0;
	unsigned int def = 10;
	do
	{
		mvwprintw(w, inx, 1, str);
		switch(ch)
		{
			case KEY_UP:
				inx = (inx <= 1) ? menu.size() : inx - 1;
				break;
			case KEY_DOWN:
				inx = (inx >= menu.size()) ? 1 : inx + 1;
				break;
			default:
				mvwprintw(w, def++, 2, "default");
		}
		wattron(w, A_STANDOUT);
		sprintf(str, "%-10s", menu.at(inx-1).c_str());
		mvwprintw(w, inx, 1, str);
		wattroff(w, A_STANDOUT);
		// wrefresh(w);
	} while((ch = wgetch(w)) != '\n');

	wrefresh(w);

	delwin(w);
	mvprintw(2, 2, "hi");
	refresh();
	getch();

	endwin();

	return 0;
}