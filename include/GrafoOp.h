#ifndef GRAFO_OP
#define GRAFO_OP

#include "GrafoED.h"

/** @file GrafoOp.h
*   @brief Arquivo de cabeçalho com as funções lógicas para manipulação do grafo
*   @sa GrafoED.h
*/

/** @enum TS_Excecao
*	@brief Enumeration que agrupa as exeções previstas nas assertivas de GrafoOp.h.
*	@var TS_ExcecaoFlhFopen Reporta falha na função fopen
*	@var TS_ExcecaoTrfInval Reporta que a tarefa é inválida
*	@var TS_ExcecaoReqCirc Reporta que um requisito circular foi encontrado
*	@var TS_ExcecaoGrafoInval Reporta que um grafo inválido foi passado de parâmetro
*	@var TS_ExcecaoIdJahExiste Reporta que o novo id já existe
*	@var TS_ExcecaoIdTrfInval Reporta que o Id da tarefa é inválido
*	@var TS_ExcecaoDurNgtv Reporta que a duração fornecida é negativa
*	@var TS_ExcecaoTmpNgtv Reporta que o tempo mínimo fornecido é negativo
*   @var TS_ExcecaoIdReqInval Reporta que o Id do requisito é inválido
*/
	enum TS_Execao{
		TS_ExcecaoFlhFopen,
		TS_ExcecaoTrfInval,
		TS_ExcecaoReqCirc,
		TS_ExcecaoGrafoInval,
		TS_ExcecaoIdJahExiste,
		TS_ExcecaoIdTrfInval,
		TS_ExcecaoDurNgtv,
		TS_ExcecaoTmpNgtv,
		TS_ExcecaoIdReqInval,
	};

/** @fn pGrafo OP_LerGrafo(char *)
*   @brief A partir de um arquivo .txt gera o grafo do gerenciador.
*   @param string com o nome do arquivo de onde o arquivo será lido
*/
   pGrafo OP_LerGrafo(char *);

/** @fn void OP_SalvarGrafo(pGrafo, char *)
*   @brief Escreve o grafo em um .txt.
*   @param ponteiro para cabeça do grafo
*   @param string com o nome do arquivo onde o grafo será escrito
*/
   void   OP_SalvarGrafo(pGrafo, char *);

/** @fn void OP_DeletarGrafo(pGrafo)
*   @brief Deleta o grafo.
*   @param ponteiro para cabeça do grafo
*/
   void   OP_DeletarGrafo(pGrafo);

/** @fn int  OP_CalcularTempMinExec(pGrafo, unsigned int)
*   @brief Calcula o menor tempo necessário para a tarefa ser executada.
*   @param ponteiro para cabeça do grafo
*   @param id da tarefa
*/
   int    OP_CalcularTempoMinExec(pGrafo, unsigned int);

/** @fn void  OP_EditarId(pGrafo, unsigned int, unsigned int)
*   @brief Edita o Id da tarefa.
*   @param ponteiro para cabeça do grafo
*   @param antigo id da tarefa
*   @param novo id da tarefa
*/
   void   OP_EditarId(pGrafo, unsigned int, unsigned int);	// verificar se novo id já não existe

/** @fn void  OP_EditarNome(pGrafo, unsigned int, unsigned int)
*   @brief Edita o nome da tarefa.
*   @param ponteiro para cabeça do grafo
*   @param id da tarefa
*   @param novo nome da tarefa
*/
   void   OP_EditarNome(pGrafo, unsigned int, char *);

/** @fn void  OP_EditarEstadoExec(pGrafo, unsigned int, unsigned int)
*   @brief Edita o estado de execução da tarefa.
*   @param ponteiro para cabeça do grafo
*   @param id da tarefa
*   @param verdadeiro se a tarefa já tiver sido executada, se não, falso.
*/
   void   OP_EditarEstadoExec(pGrafo, unsigned int, bool);

/** @fn void  OP_EditarDuracao(pGrafo, unsigned int, unsigned int)
*   @brief Edita o tempo de duração da execução da tarefa.
*   @param ponteiro para cabeça do grafo
*   @param id da tarefa
*   @param novo tempo de execução da tarefa
*/
   void   OP_EditarDuracao(pGrafo, unsigned int, int);

/** @fn void  OP_EditarInicMin(pGrafo, unsigned int, unsigned int)
*   @brief Edita o tempo mínio para a tarefa estar passível de ser executada.
*   @param ponteiro para cabeça do grafo
*   @param id da tarefa
*   @param novo tempo mínimo de espera até a tarefa poder ser executada
*/
   void   OP_EditarInicMin(pGrafo, unsigned int, int);

/** @fn void  OP_ExcluirTarefa(pGrafo, unsigned int)
*   @brief Exclui a tarefa.
*   @param ponteiro para cabeça do grafo
*   @param id da tarefa
*/
   void   OP_ExcluirTarefa(pGrafo, unsigned int);

/** @fn void  OP_CriarTarefa(pGrafo, tpElementoGrafo)
*   @brief Cria a tarefa, sem a lista de requisitos (eles devem ser inseridos um a um).
*   @param ponteiro para cabeça do grafo
*   @param struct com as informações da tarefa
*/
   void   OP_CriarTarefa(pGrafo, tpElementoGrafo); // controlar para não permitir ids repetidos

/** @fn void  OP_CriarRequisito(pGrafo, unsigned int, unsigned int)
*   @brief Cria novos requisitos para tarefas.
*   @param ponteiro para cabeça do grafo
*   @param id da tarefa
*   @param id do requisito a ser adicionado
*/
   void   OP_CriarRequisito(pGrafo, unsigned int, unsigned int);
   
/** @fn void  OP_ExcluirRequisito(pGrafo, unsigned int, unsigned int)
*   @brief Exclui requisito da tarefa.
*   @param ponteiro para cabeça do grafo
*   @param id da tarefa
*   @param id do requisito a ser retirado
*/
   void   OP_ExcluirRequisito(pGrafo, unsigned int, unsigned int);

/** @fn bool OP_EhGrafoValido(pGrafo)
*   @brief Verifica se o grafo é válido, função de apoio para as assertivas.
*   @param ponteiro para cabeça do grafo
*/
    bool  OP_EhGrafoValido(pGrafo);

/** @fn void OP_VerificarReq(pGrafo pCabeca)
*   @brief Verifica se os pré-requisitos das funções são ids válidos e caso inválidos os exclui.
*   @param ponteiro para cabeça do grafo
*/
   void   OP_VerificarReq(pGrafo);

/** @fn bool OP_EhTarefaValida(pGrafo, tpElementoGrafo *)
*   @brief Verifica se a tarefa é válida, função de apoio para as assertivas.
*   @param ponteiro para cabeça do grafo
*   @param ponteiro para tarefa a ser validada
*/
    bool  OP_EhTarefaValida(pGrafo, tpElementoGrafo *);

/** @fn bool OP_TemOrigem(pGrafo)
*   @brief Verifica se o grafo tem origens, ou seja, verifica a existência de tarefas sem pré-requisitos.
*   @param ponteiro para cabeça do grafo
*/
    bool   OP_TemOrigem(pGrafo);

/** @fn bool OP_TemReqCircular(pGrafo pCabeca)
*   @brief Verifica se o grafo tem requisitos circulares, ou seja, se uma tarefa é pré-requisito de algum pré-requisito.
*   @param ponteiro para cabeça do grafo
*/
    bool   OP_TemReqCircular(pGrafo);

#endif
