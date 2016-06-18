#include "GraphicalUserInterface.h"
#include <ncurses.h>
#include <cstring>

#define NLINES 35
#define NCOLS 130

#define LN_OFFSET 3

#define COL_ID 1
#define COL_NOME COL_ID + 11
#define COL_DUR COL_NOME + 80
#define COL_INIC COL_DUR + 10
#define COL_QTD_REQ COL_INIC + 15

using namespace std;

void UI_InicializaGUI() {

    initscr();
    start_color();
    curs_set(0); //não mostra o cursor na tela
    cbreak(); //desabilita line buffering
    noecho(); //não mostra a tecla digitada pelo usuário na tela

    /* Inicializa cores que serão utilizadas na interface */
    init_pair(cores_padrao, COLOR_WHITE, COLOR_BLACK);
    init_pair(cores_menu, COLOR_WHITE, COLOR_GREEN);
    init_pair(cores_nao_concluido,COLOR_WHITE,COLOR_RED);
    init_pair(cores_concluido,COLOR_WHITE,COLOR_GREEN);
    init_pair(cores_erro,COLOR_WHITE,COLOR_RED);

    bkgd(COLOR_PAIR(cores_padrao));


}

void UI_LeEntradaTexto(string titulo, char *szEntrada) {
    WINDOW * hwndMenu = UI_CriaJanelaEntrada(titulo.c_str(), cores_menu);
    redrawwin(hwndMenu);
    getstr(szEntrada);
    delwin(hwndMenu);
}

void UI_FinalizaPrograma() {
    endwin();
    exit(0);
}

unsigned int    UI_SelecionaOpcao(string titulo, vector<string> itensMenu) {

    WINDOW * hwndMenu = UI_CriaJanelaEntrada(titulo.c_str(), cores_menu);

    char szTemp[100];
    unsigned int inx;
    int currentInput;

    for (inx = 0; inx < itensMenu.size(); ++inx) {
        if (inx == 0) { //primeiro item é destacado inicialmente
            wattron(hwndMenu, A_STANDOUT);
        }
        else {
            wattroff(hwndMenu, A_STANDOUT);
        }
        sprintf(szTemp, "%-10s", itensMenu.at(inx).c_str());
        mvwprintw(hwndMenu, inx + LN_OFFSET, 1, szTemp);
    }

    keypad(hwndMenu, TRUE);

    inx = 0;
    currentInput = 0;
    do {
        mvwprintw(hwndMenu, inx + LN_OFFSET, 1, szTemp);
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
        mvwprintw(hwndMenu, inx + LN_OFFSET, 1, szTemp);
        wattroff(hwndMenu, A_STANDOUT);
    } while((currentInput = wgetch(hwndMenu)) != '\n'); /*o índice atual é selecionado
                                                        quando o usuário pressiona enter*/

    delwin(hwndMenu); //apaga a janela criada para mostrar o menu de opções
    return inx; //posição da opção selecionada pelo usuário

}

void UI_MostraMsg(string titulo, string mensagem, TS_cores colorPair) {
    WINDOW *hwndMsg = UI_CriaJanelaEntrada(titulo.c_str(), colorPair);
    int nLinhas, nColunas;
    getmaxyx(hwndMsg, nLinhas, nColunas); //mede as dimensões da janela
    wattron(hwndMsg, A_BOLD); //mensagem é mostrada em negrito
    mvwprintw(hwndMsg, nLinhas/2, (nColunas-mensagem.size())/2, mensagem.c_str());
    //mostra mensagem no centro da janela
    wattroff(hwndMsg, A_BOLD);
    mvwprintw(hwndMsg, nLinhas-2, 2, "Pressione qualquer tecla para continuar.");
    wgetch(hwndMsg);
    delwin(hwndMsg);
}

WINDOW *UI_CriaJanelaEntrada(const char *szTitulo, TS_cores colorPair) {
    WINDOW * hwndMenu = newwin(NLINES, NCOLS, 3, 3);

    box(hwndMenu, 0, 0); //cria bordas da janela
    wbkgd(hwndMenu, COLOR_PAIR(colorPair));

    wattron(hwndMenu, A_BOLD | A_STANDOUT | A_UNDERLINE);
    mvwprintw(hwndMenu, 1, (NCOLS - strlen(szTitulo))/2, szTitulo); //imprime o título da janela
    wattroff(hwndMenu, A_BOLD | A_STANDOUT | A_UNDERLINE);

    return hwndMenu;
}

WINDOW* UI_ListaTarefas(pGrafo grafo) {
    int intUserInput;
    bool shouldRebuildList = false;
    int inx = 0;
    vector<tpElementoGrafo*> v;
    tpElementoGrafo * elemAtual;

    WINDOW *hwndLista = UI_CriaJanelaEntrada("Lista de tarefas", cores_padrao);
    keypad(hwndLista, true);

    elemAtual = grafo->org;
    while(elemAtual != NULL) { //adiciona todas as tarefas no vector v
        v.push_back(elemAtual);
        elemAtual = elemAtual->prox;
    }
    
    wattron(hwndLista, A_BOLD | A_UNDERLINE);

    mvwprintw(hwndLista, LN_OFFSET-1, COL_ID, "%-128s", "ID");
    mvwprintw(hwndLista, LN_OFFSET-1, COL_NOME, "Nome da Tarefa");
    mvwprintw(hwndLista, LN_OFFSET-1, COL_DUR, "Duracao");
    mvwprintw(hwndLista, LN_OFFSET-1, COL_INIC, "T. Inic. Min");
    mvwprintw(hwndLista, LN_OFFSET-1, COL_QTD_REQ, "Qtd.PreReq");

    wattroff(hwndLista, A_BOLD | A_UNDERLINE);

    for(int i = 0; i < v.size(); ++i) {
        tpElementoGrafo * atual = v.at(i);
        UI_ImprimeTarefa(hwndLista, atual, i+LN_OFFSET, i == 0);
    }

    do {
        switch(wgetch(hwndLista)) {
            case KEY_UP:
                UI_ImprimeTarefa(hwndLista, v.at(inx), inx+LN_OFFSET, false);
                inx = (inx <= 0 ? v.size() - 1 : inx - 1);
                UI_ImprimeTarefa(hwndLista, v.at(inx), inx+LN_OFFSET, true);
                break;
            case KEY_DOWN:
                UI_ImprimeTarefa(hwndLista, v.at(inx), inx+LN_OFFSET, false);
                inx = (inx >= v.size() - 1 ? 0 : inx + 1);
                UI_ImprimeTarefa(hwndLista, v.at(inx), inx+LN_OFFSET, true);
                break;
            default:
                shouldRebuildList = true;
        }
    } while(!shouldRebuildList);

    return hwndLista;
    
}

void UI_ImprimeTarefa(WINDOW *hwndLista, tpElementoGrafo* tarefa, int coluna, bool selecionado) {
    selecionado ? wattron(hwndLista, A_STANDOUT) : wattroff(hwndLista, A_STANDOUT);
    if (tarefa->executado) {
        wattron(hwndLista, COLOR_PAIR(cores_concluido));
    }
    else {
        wattron(hwndLista, COLOR_PAIR(cores_nao_concluido));
    }
    mvwprintw(hwndLista, coluna, COL_ID, "%-128u", tarefa->id);
    mvwprintw(hwndLista, coluna, COL_NOME, "%s", tarefa->szNome);
    mvwprintw(hwndLista, coluna, COL_DUR, "%d", tarefa->tempoDuracao);
    mvwprintw(hwndLista, coluna, COL_INIC, "%d", tarefa->tempoInicMin);
    mvwprintw(hwndLista, coluna, COL_QTD_REQ, "%d", tarefa->qtdPreReq);
}

#undef NLINES
#undef NCOLS