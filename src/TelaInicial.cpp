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
    vector<string> itensMenuInicial;
    vector<string> itensMenuEditar;
    char szNomeArq[100];
    unsigned int selecaoUsuario;

    itensMenuInicial.push_back("Ler tarefas de arquivo existente");
    itensMenuInicial.push_back("Criar novo arquivo de tarefas");

    itensMenuEditar.push_back("ID");
    itensMenuEditar.push_back("Nome");
    itensMenuEditar.push_back("Tempo mínimo de início");
    itensMenuEditar.push_back("Duração");
    itensMenuEditar.push_back("Estado de execução");
    itensMenuEditar.push_back("Adicionar requisito");
    itensMenuEditar.push_back("Remover requisito");


    UI_InicializaGUI();
    switch(UI_SelecionaOpcao("O que deseja fazer?", itensMenuInicial)) {
        case 0: //ler tarefas de arquivo existente
            // UI_LeEntradaTexto("Digite o nome do arquivo a ser lido", szNomeArq);
            try {
                grafo = OP_LerGrafo(/*szNomeArq*/ "RGrafo.txt");
            } catch (TS_Execao e) {
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
            break;
        case 1: //criar novo arquivo de tarefas
            grafo = ED_CriarGrafo();
            break;
    }

    hwndListaTarefas = UI_ListaTarefas(grafo);
    getch();
    delwin(hwndListaTarefas);

    mvprintw(2, 2, "Programa finalizado.");
    refresh();
    getch();
    OP_DeletarGrafo(grafo);
    UI_FinalizaPrograma();

    return 0;
}
