#include <ncurses.h>
#include <stdio.h>
#include <vector>
#include <string>
#include "GraphicalUserInterface.h"
#include "GrafoOp.h"

using namespace std;

void TrataExcecao(TS_Execao e);

vector<string> itensMenuInicial;

int main(void) {

    pGrafo grafo;
    tpElementoGrafo *tarefaSelecionada;
    char szNomeArq[100];
    unsigned int selecaoUsuario;

    itensMenuInicial.push_back("Ler tarefas de arquivo existente");
    itensMenuInicial.push_back("Criar novo arquivo de tarefas");

    UI_InicializaGUI();
    
    switch(UI_SelecionaOpcao("O que deseja fazer?", itensMenuInicial)) {
        case 0: //ler tarefas de arquivo existente
            UI_LeEntradaTexto("Digite o nome do arquivo a ser lido", szNomeArq);
            try {
                grafo = OP_LerGrafo(szNomeArq);
            } catch (TS_Execao e) {
                TrataExcecao(e);
            } catch (...) {
                UI_FinalizaPrograma();
            }
            break;
        case 1: //criar novo arquivo de tarefas
            grafo = ED_CriarGrafo();
            UI_NovaTarefa(grafo);
            break;
    }

    tarefaSelecionada = UI_ListaTarefas(grafo);
    UI_EditarTarefa(grafo, tarefaSelecionada);

    mvprintw(2, 2, "Programa finalizado.");
    refresh();
    getch();
    OP_DeletarGrafo(grafo);
    UI_FinalizaPrograma();

    return 0;
}

void TrataExcecao(TS_Execao e) {
    string msg;
    switch (e) {
        case TS_ExcecaoFlhFopen:
            msg = "Falha na abertura do arquivo";
            break;
        case TS_ExcecaoTrfInval:
            msg = "Tarefa invalida";
            break;
        default:
            msg = "Outra excecao";
    }
    UI_MostraMsg("Excecao", msg, cores_erro);
    UI_FinalizaPrograma();
}