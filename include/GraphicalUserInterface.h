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

unsigned int UI_SelecionaOpcao(std::vector<std::string> itensMenu);

#endif