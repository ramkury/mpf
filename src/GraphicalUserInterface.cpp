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

vector<string> itensMenuEditar;
vector<string> itensMenuConfirmacao;

void UI_InicializaGUI() {

    itensMenuEditar.push_back("ID");
    itensMenuEditar.push_back("Nome");
    itensMenuEditar.push_back("Tempo minimo de inicio");
    itensMenuEditar.push_back("Duracao");
    itensMenuEditar.push_back("Estado de execucao");
    itensMenuEditar.push_back("Adicionar requisito");
    itensMenuEditar.push_back("Remover requisito");
    itensMenuEditar.push_back("Excluir tarefa");
    itensMenuEditar.push_back("Voltar");

    itensMenuConfirmacao.push_back("Nao");
    itensMenuConfirmacao.push_back("Sim");

    initscr();
    start_color();
    curs_set(0); //não mostra o cursor na tela
    cbreak(); //desabilita line buffering
    noecho(); //não mostra a tecla digitada pelo usuário na tela

    /* Inicializa cores que serão utilizadas na interface */
    init_pair(cores_padrao, COLOR_WHITE, COLOR_BLACK);
    init_pair(cores_menu, COLOR_WHITE, COLOR_CYAN);
    init_pair(cores_nao_concluido,COLOR_WHITE,COLOR_RED);
    init_pair(cores_concluido,COLOR_WHITE,COLOR_GREEN);
    init_pair(cores_erro,COLOR_WHITE,COLOR_RED);

    bkgd(COLOR_PAIR(cores_padrao));

    mvprintw(NLINES+5, 2, "Pressione enter para editar a tarefa selecionada ou M para abrir o menu.");
    refresh();
}

void UI_LeEntradaTexto(string titulo, char *szEntrada) {
    WINDOW * hwndMenu = UI_CriaJanelaEntrada(titulo.c_str(), cores_menu);
    wrefresh(hwndMenu);
    curs_set(1);
    echo();
    mvwgetstr(hwndMenu, NLINES/2, 3, szEntrada);
    delwin(hwndMenu);
}

void UI_FinalizaPrograma() {
    endwin();
    exit(0);
}

unsigned int    UI_SelecionaOpcao(string titulo, vector<string> itensMenu) {

    WINDOW * hwndMenu = UI_CriaJanelaEntrada(titulo.c_str(), cores_menu);

    keypad(hwndMenu, TRUE);
    curs_set(0);
    cbreak();
    noecho();

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
        sprintf(szTemp, "%s", itensMenu.at(inx).c_str());
        mvwprintw(hwndMenu, inx + LN_OFFSET, 1, szTemp);
    }

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

    curs_set(0);
    noecho();

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

    redrawwin(hwndMenu);

    return hwndMenu;
}

tpElementoGrafo* UI_ListaTarefas(pGrafo grafo) {
    int intUserInput;
    bool shouldRebuildList = false;
    int inx = 0;
    vector<tpElementoGrafo*> v;
    tpElementoGrafo * elemAtual;

    WINDOW *hwndLista = UI_CriaJanelaEntrada("Lista de tarefas", cores_padrao);
    keypad(hwndLista, true);
    curs_set(0);
    noecho();   

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

    if (v.size() == 0) {
        wgetch(hwndLista);
        delwin(hwndLista);
        return NULL;
    }

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
            case 'M':
            case 'm':
                delwin(hwndLista);
                return NULL;
            case '\n':
                shouldRebuildList = true;
        }
    } while(!shouldRebuildList);

    delwin(hwndLista);
    return v.at(inx);

}

void UI_ImprimeTarefa(WINDOW *hwndLista, tpElementoGrafo* tarefa, int coluna, bool selecionado = false) {
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

void UI_NovaTarefa(pGrafo pCabeca) {
    char szEntradaUsuario[100];
    tpElementoGrafo novaTarefa;
    int numPreReq;

    UI_LeEntradaTexto("Digite o ID da tarefa", szEntradaUsuario);
    novaTarefa.id = atoi(szEntradaUsuario);
    UI_LeEntradaTexto("Digite o nome da tarefa", szEntradaUsuario);
    strcpy(novaTarefa.szNome, szEntradaUsuario);
    UI_LeEntradaTexto("A tarefa ja foi executada? (0 para não, 1 para sim)", szEntradaUsuario);
    novaTarefa.executado = atoi(szEntradaUsuario);
    UI_LeEntradaTexto("Digite o tempo de duracao da tarefa", szEntradaUsuario);
    novaTarefa.tempoDuracao = atoi(szEntradaUsuario);
    UI_LeEntradaTexto("Digite o tempo minimo de inicio da tarefa", szEntradaUsuario);
    novaTarefa.tempoInicMin = atoi(szEntradaUsuario);

    try {
        OP_CriarTarefa(pCabeca, novaTarefa);
    } catch(TS_Execao e) {
        if (e == TS_ExcecaoTrfInval) {
            UI_MostraMsg("Erro!", "Tarefa invalida!", cores_erro);
            return;
        }
        else {
            throw e;
        }
    }

    UI_LeEntradaTexto("Digite o numero de pre requisitos da tarefa", szEntradaUsuario);
    numPreReq = atoi(szEntradaUsuario);

    try {
        for (int i = 1; i <= numPreReq; ++i) {
            char szTitulo[100];
            sprintf(szTitulo, "Digite o ID do %do pre requisito", i);
            UI_LeEntradaTexto(string(szTitulo), szEntradaUsuario);
            OP_CriarRequisito(pCabeca, novaTarefa.id, atoi(szEntradaUsuario));
        }
    } catch(TS_Execao e) {
        switch (e) {
            case TS_ExcecaoIdReqInval:
                UI_MostraMsg("Erro!", "ID da tarefa invalido!", cores_erro);
                return;
            case TS_ExcecaoReqCirc:
                UI_MostraMsg("Erro!", "Pre requisito cria caminho circular!", cores_erro);
                return;
            default:
                throw e;
        }
    }
}

void UI_EditarTarefa(pGrafo grafo, tpElementoGrafo *tarefa) {
    unsigned int opcaoSelecionada;

    if (tarefa != NULL) {
        opcaoSelecionada = UI_SelecionaOpcao(string(tarefa->szNome), itensMenuEditar);
        switch (opcaoSelecionada) {
            case 0: //ID
                UI_EditarID(grafo, tarefa);
                break;
            case 1: //Nome
                UI_EditarNome(grafo, tarefa);
                break;
            case 2: //Tempo mínimo de início
                UI_EditarInicMin(grafo, tarefa);
                break;
            case 3: //Duração
                UI_EditarDuracao(grafo, tarefa);
                break;
            case 4: //Estado de execução
                UI_EditarEstadoExec(grafo, tarefa);
                break;
            case 5: //Adicionar requisito
                UI_CriarRequisito(grafo, tarefa);
                break;
            case 6: //Remover requisito
                UI_ExcluirRequisito(grafo, tarefa);
                break;
            case 7: //Excluir tarefa
                UI_ExcluirTarefa(grafo, tarefa);
                break;
        }
    }
}

void UI_EditarID(pGrafo grafo, tpElementoGrafo *tarefa) {
    char szEntradaUsuario[100];
    unsigned int novoId;

    UI_LeEntradaTexto("Digite o novo ID da tarefa:", szEntradaUsuario);
    novoId = atoi(szEntradaUsuario);
    try {
        OP_EditarId(grafo, tarefa->id, novoId);
    } catch(TS_Execao e) {
        switch (e) {
            case TS_ExcecaoIdJahExiste:
                UI_MostraMsg("Erro!", "Esse ID jah existe!", cores_erro);
                return;
            case TS_ExcecaoIdTrfInval:
                UI_MostraMsg("Erro!", "ID invalido!", cores_erro);
                return;
            default:
                throw e;
        }
    }
}

void UI_EditarNome(pGrafo grafo, tpElementoGrafo *tarefa) {
    char szEntradaUsuario[100];

    UI_LeEntradaTexto("Digite o novo nome da tarefa:", szEntradaUsuario);
    OP_EditarNome(grafo, tarefa->id, szEntradaUsuario);
}

void UI_EditarInicMin(pGrafo grafo, tpElementoGrafo *tarefa) {
    char szEntradaUsuario[100];
    int tempoInicMin;

    UI_LeEntradaTexto("Digite o novo tempo minimo de inicio da tarefa:", szEntradaUsuario);
    tempoInicMin = atoi(szEntradaUsuario);
    try {
        OP_EditarInicMin(grafo, tarefa->id, tempoInicMin);
    } catch(TS_Execao e) {
        if (e == TS_ExcecaoTmpNgtv) {
            UI_MostraMsg("Erro!", "O tempo minimo de execucao nao pode ser um valor negativo", cores_erro);
            return;
        }
        else {
            throw e;
        }
    }
}

void UI_EditarDuracao(pGrafo grafo, tpElementoGrafo *tarefa) {
    char szEntradaUsuario[100];
    int novaDuracao;

    UI_LeEntradaTexto("Digite o novo tempo de duracao da tarefa:", szEntradaUsuario);
    novaDuracao = atoi(szEntradaUsuario);
    try {
        OP_EditarDuracao(grafo, tarefa->id, novaDuracao);
    } catch (TS_Execao e) {
        if (e == TS_ExcecaoDurNgtv) {
            UI_MostraMsg("Erro!", "A duracao de uma tarefa nao pode ser um valor negativo!", cores_erro);
            return;
        }
        else {
            throw e;
        }
    }
}

void UI_EditarEstadoExec(pGrafo grafo, tpElementoGrafo *tarefa) {
    char szEntradaUsuario[10];
    bool novoEstadoExecucao;

    UI_LeEntradaTexto("Digite 1 para executado e 0 para nao executado:", szEntradaUsuario);
    novoEstadoExecucao = atoi(szEntradaUsuario);

    OP_EditarEstadoExec(grafo, tarefa->id, novoEstadoExecucao);
}

void UI_CriarRequisito(pGrafo grafo, tpElementoGrafo *tarefa) {
    char szEntradaUsuario[100];
    unsigned int idRequisito;

    UI_LeEntradaTexto("Digite o ID da tarefa a ser adicionada como pre requisito", szEntradaUsuario);
    idRequisito = atoi(szEntradaUsuario);

    try {
        OP_CriarRequisito(grafo, tarefa->id, idRequisito);
    } catch(TS_Execao e) {
        switch (e) {
            case TS_ExcecaoIdReqInval:
                UI_MostraMsg("Erro!", "Nao existe nenhuma tarefa com esse ID!", cores_erro);
                return;
            case TS_ExcecaoReqCirc:
                UI_MostraMsg("Erro!", "Adicionar esse requisito cria um caminho circular!", cores_erro);
                return;
            default:
                throw e;
        }
    }
}

void UI_ExcluirRequisito(pGrafo grafo, tpElementoGrafo *tarefa) {
    char szEntradaUsuario[100];
    unsigned int idRequisito;

    UI_LeEntradaTexto("Digite o ID do pre requisito a ser removido", szEntradaUsuario);
    idRequisito = atoi(szEntradaUsuario);

    try {
        OP_ExcluirRequisito(grafo, tarefa->id, idRequisito);
    } catch(TS_Execao e) {
        switch (e) {
            case TS_ExcecaoIdReqInval:
                UI_MostraMsg("Erro!", "Nao existe nenhuma tarefa com esse ID!", cores_erro);
                return;
            default:
                throw e;
        }
    } 
}

void UI_ExcluirTarefa(pGrafo grafo, tpElementoGrafo *tarefa) {
    int selecaoUsuario;
    selecaoUsuario = UI_SelecionaOpcao("Tem certeza que deseja excluir essa tarefa?", itensMenuConfirmacao);
    if (selecaoUsuario == 1) {
        OP_ExcluirTarefa(grafo, tarefa->id);
    }
}

void UI_EscreverGrafo(pGrafo grafo) {
    char szEntradaUsuario[100];

    UI_LeEntradaTexto("Digite o nome do arquivo a ser escrito", szEntradaUsuario);
    OP_SalvarGrafo(grafo, szEntradaUsuario);
}

void UI_DefinirTempo(pGrafo grafo) {
    char szEntradaUsuario[100];
    int tempo;

    UI_LeEntradaTexto("Digite o novo tempo", szEntradaUsuario);
    tempo = atoi(szEntradaUsuario);
    try {
        OP_AtualizarGrafo(grafo, tempo);
    } catch(TS_Execao e) {
        if (e == TS_ExcecaoTmpNgtv) {
            UI_MostraMsg("Erro", "O tempo nao pode ser negativo!", cores_erro);
        } else {
            throw e;
        }
    }
}

#undef NLINES
#undef NCOLS