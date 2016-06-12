#include "GraphicalUserInterface.h"
#include <ncurses.h>

using namespace std;

void UI_InicializaGUI() {
    initscr();
    start_color();

    /* Inicializa cores que serão utilizadas na interface */
    init_pair(cores_padrao, COLOR_WHITE, COLOR_BLACK);
    init_pair(cores_menu, COLOR_WHITE, COLOR_GREEN);
    init_pair(cores_nao_concluido,COLOR_RED,COLOR_WHITE);
    init_pair(cores_concluido,COLOR_GREEN,COLOR_WHITE);

    vector<string> itensMenuInicial;
    itensMenuInicial.push_back("item1");
    itensMenuInicial.push_back("item2");
    itensMenuInicial.push_back("item3");
    itensMenuInicial.push_back("item4");

    string titulo("titulo");

    UI_SelecionaOpcao(titulo, itensMenuInicial);

}

unsigned int    UI_SelecionaOpcao(string titulo, vector<string> itensMenu) {

    #define NLINES 30
    #define NCOLS 60

    char szTemp[100];
    unsigned int inx, lineOffset = 4;
    int currentInput;
    cbreak(); //desabilita line buffering
    noecho(); //não mostra a tecla digitada pelo usuário na tela

    WINDOW * hwndMenu = newwin(NLINES, NCOLS, 3, 3);


    box(hwndMenu, 0, 0); //cria bordas da janela
    wrefresh(hwndMenu);
    wbkgd(hwndMenu, COLOR_PAIR(cores_menu));

    wattron(hwndMenu, A_BOLD | A_STANDOUT | A_UNDERLINE);
    mvwprintw(hwndMenu, 1, 1, titulo.c_str());
    wattroff(hwndMenu, A_BOLD | A_STANDOUT | A_UNDERLINE);

    for (inx = 0; inx < itensMenu.size(); ++inx) {
        if (inx == 0) //primeiro item é destacado inicialmente
            wattron(hwndMenu, A_STANDOUT);
        else
            wattroff(hwndMenu, A_STANDOUT);
        sprintf(szTemp, "%-10s", itensMenu.at(inx).c_str());
        mvwprintw(hwndMenu, inx + lineOffset, 1, szTemp);
    }

    keypad(hwndMenu, TRUE);
    curs_set(0); //não mostra o cursor na tela

    inx = 0;
    currentInput = 0;
    do {
        mvwprintw(hwndMenu, inx + lineOffset, 1, szTemp);
        switch(currentInput) {
            case KEY_UP:
                inx = (inx < 1) ? itensMenu.size()-1 : inx - 1;
                break;
            case KEY_DOWN:
                inx = (inx >= itensMenu.size()-1) ? 0 : inx + 1;
                break;
        }
        wattron(hwndMenu, A_STANDOUT);
        sprintf(szTemp, "%-10s", itensMenu.at(inx).c_str());
        mvwprintw(hwndMenu, inx + lineOffset, 1, szTemp);
        wattroff(hwndMenu, A_STANDOUT);
    } while((currentInput = wgetch(hwndMenu)) != '\n'); /*o índice atual é selecionado
                                                        quando o usuário pressiona enter*/

    delwin(hwndMenu); //apaga a janela criada para mostrar o menu de opções
    return inx; //posição da opção selecionada pelo usuário

    #undef NLINES
    #undef NCOLS
}