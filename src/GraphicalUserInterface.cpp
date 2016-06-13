#include "GraphicalUserInterface.h"
#include <ncurses.h>

#define NLINES 30
#define NCOLS 130

using namespace std;

void UI_InicializaGUI() {

    unsigned int opcaoSelecionada;

    initscr();
    start_color();

    /* Inicializa cores que serão utilizadas na interface */
    init_pair(cores_padrao, COLOR_WHITE, COLOR_BLACK);
    init_pair(cores_menu, COLOR_WHITE, COLOR_GREEN);
    init_pair(cores_nao_concluido,COLOR_RED,COLOR_WHITE);
    init_pair(cores_concluido,COLOR_GREEN,COLOR_WHITE);
    init_pair(cores_erro,COLOR_WHITE,COLOR_RED);

    bkgd(COLOR_PAIR(cores_padrao));

    vector<string> itensMenuInicial;
    itensMenuInicial.push_back("Ler tarefas de arquivo existente");
    itensMenuInicial.push_back("Criar novo arquivo de tarefas");

    opcaoSelecionada = UI_SelecionaOpcao("Escolha uma ação:", itensMenuInicial);

    UI_MostraMsg("Título Erro", "Mensagem de erro", cores_nao_concluido);

    char szEntrada[100];

    switch (opcaoSelecionada) {
        case 0:
            // Recebe a entrada do usuário com o nome do arquivo a ser aberto
            UI_LeEntradaTexto("Digite o nome do arquivo a ser lido", szEntrada);
            mvprintw(3, 3, szEntrada);
            // Le o arquivo com o nome informado pelo usuário
            // Abre tela de visualização de tarefas
            break;
        case 1:
            // Recebe a entrada do usuário com o nome do arquivo a ser criado
            UI_LeEntradaTexto("Digite o nome do arquivo a ser criado", szEntrada);
            // Cria o arquivo com o nome informado pelo usuário
            // Abre tela de visualização de tarefas
            break;
    }

}

void UI_LeEntradaTexto(string titulo, char *szEntrada) {
    WINDOW * hwndMenu = UI_CriaJanelaEntrada(titulo.c_str(), cores_menu);
    getstr(szEntrada);
    wrefresh(hwndMenu);
    delwin(hwndMenu);
}

void UI_FinalizaPrograma() {
    endwin();
}

unsigned int    UI_SelecionaOpcao(string titulo, vector<string> itensMenu) {

    WINDOW * hwndMenu = UI_CriaJanelaEntrada(titulo.c_str(), cores_menu);

    char szTemp[100];
    unsigned int inx, lineOffset = 4;
    int currentInput;
    cbreak(); //desabilita line buffering
    noecho(); //não mostra a tecla digitada pelo usuário na tela

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

}

void UI_MostraMsg(std::string titulo, std::string mensagem, TS_cores colorPair) {
    WINDOW *hwndMsg = UI_CriaJanelaEntrada(titulo.c_str(), colorPair);
    int nLinhas, nColunas;
    getmaxyx(hwndMsg, nLinhas, nColunas); //mede as dimensões da janela
    wattron(hwndMsg, A_BOLD); //mensagem é mostrada em negrito
    mvwprintw(hwndMsg, nLinhas/2, (nColunas-mensagem.size())/2, mensagem.c_str());
    //mostra mensagem no centro da janela
    wattroff(hwndMsg, A_BOLD);
    mvwprintw(hwndMsg, nLinhas-2, 2, "Pressione qualquer tecla para continuar.");
    wgetch(hwndMsg);
}

WINDOW *UI_CriaJanelaEntrada(const char *szTitulo, TS_cores colorPair) {
    WINDOW * hwndMenu = newwin(NLINES, NCOLS, 3, 3);

    box(hwndMenu, 0, 0); //cria bordas da janela
    wbkgd(hwndMenu, COLOR_PAIR(colorPair));

    wattron(hwndMenu, A_BOLD | A_STANDOUT | A_UNDERLINE);
    mvwprintw(hwndMenu, 1, 1, szTitulo); //imprime o título da janela
    wattroff(hwndMenu, A_BOLD | A_STANDOUT | A_UNDERLINE);

    return hwndMenu;
}

#undef NLINES
#undef NCOLS