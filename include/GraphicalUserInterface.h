#ifndef GRAPHICAL_USER_INTERFACE
#define GRAPHICAL_USER_INTERFACE

#include <vector>
#include <string>

enum TS_cores
{
	cores_padrao,
	cores_menu,
	cores_concluido,
	cores_nao_concluido
};

/**
 * Mostra um menu de opções em que o usuário navega e seleciona a opção desejada
 * utilizando as setas do teclado.
 * @param itensMenu opções que podem ser escolhidas pelo usuário
 * @return índice da opção selecionada pelo usuário (contagem começando em 1)
 */
unsigned int UI_SelecionaOpcao(std::vector<std::string> itensMenu);

#endif