#ifndef GRAPHICAL_USER_INTERFACE
#define GRAPHICAL_USER_INTERFACE

#include "GrafoOp.h"
#include "GrafoED.h"
#include <vector>
#include <string>
#include <ncurses.h>

using namespace std;

enum TS_cores {
    cores_padrao,
    cores_menu,
    cores_concluido,
    cores_nao_concluido,
    cores_erro
};

/**
 * Realiza as operações necessárias para inicializar a interface de usuário
 * e mostra o menu inicial.
 */
void UI_InicializaGUI();

/**
 * Finaliza a interface gráfica e sai do programa.
 */
void UI_FinalizaPrograma();

/**
 * Abre uma janela que pede uma entrada de texto para o usuário.
 * @param titulo título da janela que será aberta
 * @param szEntrada ponteiro para o espaço de memória em que a entrada do usuário
 * será armazenada como uma string terminada em zero.
 */
void UI_LeEntradaTexto(std::string titulo, char *szEntrada);

/**
 * Mostra um menu de opções em que o usuário navega e seleciona a opção desejada
 * utilizando as setas do teclado.
 * @param titulo título da janela que será aberta
 * @param itensMenu opções que podem ser escolhidas pelo usuário
 * @return índice da opção selecionada pelo usuário (contagem começando em 0)
 */
unsigned int UI_SelecionaOpcao(std::string titulo, std::vector<std::string> itensMenu);

/**
 * Mostra mensagem na tela e aguarda o usuário pressionar uma tecla
 * @param titulo Título da janela que será aberta com a mensagem de erro
 * @param mensagem Mensagem a ser mostrada para o usuário
 * @param colorPair cores a serem usadas como background da janela
 */
void UI_MostraMsg(std::string titulo, std::string mensagem, TS_cores colorPair);

/**
 * Cria uma janela genérica para entrada do usuário.
 * @param szTitulo título da janela a ser criada
 * @param colorPair cores a serem usadas como background da janela
 * @return referência para a janela criada
 */
WINDOW* UI_CriaJanelaEntrada(const char *szTitulo, TS_cores colorPair);

/**
 * Cria janela para mostrar lista de tarefas
 * @param grafo Cabeça do grafo contendo a lista de tarefas a serem listadas
 * @return ponteiro para a tarefa selecionada
 */
tpElementoGrafo* UI_ListaTarefas(pGrafo grafo);

/**
 * Imprime os dados relativos a uma tarefa na linha e janela escolhidas
 * @param hwndLista janela em que será impressa a tarefa
 * @param tarefa Tarefa a ser impressa na tela
 * @param linha Linha em que será impressa a tarefa
 * @param selecionado Define se o cursor está posicionado na linha dessa tarefa
 */
void UI_ImprimeTarefa(WINDOW *hwndLista, tpElementoGrafo* tarefa, int linha, bool selecionado);

/**
 * Pede ao usuário informações necessárias para criação de uma nova tarefa,
 * cria o objeto de tarefa com as informações obtidas do usuário e insere
 * a tarefa no grafo.
 * @param pCabeca ponteiro para a cabeça do grafo no qual a tarefa será inserida
 */
void UI_NovaTarefa(pGrafo pCabeca);

/**
 * Mostra um menu para o usuário com todos os dados da tarefa que podem ser alterados
 * e chama a função de edição do atributo selecionado.
 * @param grafo Grafo contendo a tarefa que deve ser editada
 * @param tarefa Tarefa que está sendo editada
 */
void UI_EditarTarefa(pGrafo grafo, tpElementoGrafo *tarefa);

/**
 * Abre uma janela de entrada de texto e pede que o usuário digite o novo ID da tarefa.
 * Se possível, atualiza o ID da tarefa. Se não, mostra mensagem de erro ao usuário.
 * @param grafo Grafo contendo a tarefa a ser editada
 * @param tarefa Tarefa a ser editada
 */
void UI_EditarID(pGrafo grafo, tpElementoGrafo *tarefa);

/**
 * Abre uma janela de entrada de texto e pede que o usuário digite o novo nome da tarefa.
 * Se possível, atualiza o nome da tarefa. Se não, mostra mensagem de erro ao usuário.
 * @param grafo Grafo contendo a tarefa a ser editada
 * @param tarefa Tarefa a ser editada
 */
void UI_EditarNome(pGrafo grafo, tpElementoGrafo *tarefa);

/**
 * Abre uma janela de entrada de texto e pede que o usuário digite o novo tempo 
 * mínimo de início  da tarefa.
 * Se possível, atualiza o atributo da tarefa. Se não, mostra mensagem de erro ao usuário.
 * @param grafo Grafo contendo a tarefa a ser editada
 * @param tarefa Tarefa a ser editada
 */
void UI_EditarInicMin(pGrafo grafo, tpElementoGrafo *tarefa);

/**
 * Abre uma janela de entrada de texto e pede que o usuário digite o novo tempo 
 * de duração da tarefa
 * Se possível, atualiza o atributo da tarefa. Se não, mostra mensagem de erro ao usuário.
 * @param grafo Grafo contendo a tarefa a ser editada
 * @param tarefa Tarefa a ser editada
 */
void UI_EditarDuracao(pGrafo grafo, tpElementoGrafo *tarefa);

/**
 * Abre uma janela de entrada de texto e pede que o usuário digite o novo estado
 * de execução da tarefa
 * Se possível, atualiza o atributo da tarefa. Se não, mostra mensagem de erro ao usuário.
 * @param grafo Grafo contendo a tarefa a ser editada
 * @param tarefa Tarefa a ser editada
 */
void UI_EditarEstadoExec(pGrafo grafo, tpElementoGrafo *tarefa);

/**
 * Abre uma janela de entrada de texto e pede que o usuário digite o ID da tarefa a ser
 * adicionada como pré requisito. Se possível, adiciona a tarefa na lista de pré requisitos.
 * Se não, mostra mensagem de erro ao usuário.
 * @param grafo Grafo contendo a tarefa a ser editada
 * @param tarefa Tarefa a ser editada
 */
void UI_CriarRequisito(pGrafo grafo, tpElementoGrafo *tarefa);

/**
 * Abre uma janela de entrada de texto e pede que o usuário digite o ID da tarefa a ser
 * removida da lista de pré requisitos. Se possível, remove a tarefa da lista de pré requisitos.
 * Se não, mostra mensagem de erro ao usuário.
 * @param grafo Grafo contendo a tarefa a ser editada
 * @param tarefa Tarefa a ser editada
 */
void UI_ExcluirRequisito(pGrafo grafo, tpElementoGrafo *tarefa);

/**
 * Exclui a tarefa escolhida do grafo.
 * @param grafo Grafo contendo a tarefa a ser excluída
 * @param tarefa Tarefa a ser excluída
 */
void UI_ExcluirTarefa(pGrafo grafo, tpElementoGrafo *tarefa);

/**
 * Abre uma janela de entrada de texto e pede que o usuário digite o nome do arquivo
 * de texto a ser criado com as informações do grafo.
 * @param grafo Grafo a ser escrito no arquivo
 */
void UI_EscreverGrafo(pGrafo grafo);

/**
 * Abre uma janela de entrada de texto e pede que o usuário digite o instante de tempo
 * para o qual o estado das tarefas deve ser calculado. Computa e altera o estado de execução
 * de todas as tarefas do grafo para o tempo escolhido.
 * @param grafo Grafo a ser atualizado de acordo com o tempo escolhido
 */
void UI_DefinirTempo(pGrafo grafo);

/**
 * Abre uma janela e mostra os IDs de todos os pre requisitos da tarefa. Caso a tarefa não
 * possua pré requisitos, mostra uma mensagem para o usuário.
 * @param tarefa Tarefa cujos pre requisitos são listados.
 */
void UI_ListaPreReq(tpElementoGrafo *tarefa);

#endif