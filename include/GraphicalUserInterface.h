#ifndef GRAPHICAL_USER_INTERFACE
#define GRAPHICAL_USER_INTERFACE

#include "GrafoOp.h"
#include "GrafoED.h"
#include <vector>
#include <string>
#include <ncurses.h>

enum TS_cores {
    cores_padrao,
    cores_menu,
    cores_concluido,
    cores_nao_concluido,
    cores_erro
};

vector<string> itensMenuInicial;
vector<string> itensMenuEditar;

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
unsigned int    UI_SelecionaOpcao(std::string titulo, std::vector<std::string> itensMenu);

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
 * @return ponteiro para a janela criada
 */
WINDOW* UI_ListaTarefas(pGrafo grafo);

#endif