#include <ncurses.h>
#include <stdio.h>
#include <vector>
#include <string>
#include "GraphicalUserInterface.h"
#include "GrafoOp.h"

using namespace std;

int main(void) {

    pGrafo grafo;
    WINDOW * hwndListaTarefas;

    UI_InicializaGUI();
    grafo = OP_LerGrafo("RGrafo.txt");
    hwndListaTarefas = UI_ListaTarefas(grafo);
    wgetch(hwndListaTarefas);
    delwin(hwndListaTarefas);

    mvprintw(2, 2, "Programa finalizado.");
    refresh();
    getch();
    OP_DeletarGrafo(grafo);
    UI_FinalizaPrograma();

    return 0;
}
