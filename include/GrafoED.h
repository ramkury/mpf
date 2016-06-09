#ifndef GRAFO_ED
#define GRAFO_ED

#include <cstdlib>
#include <cstdio>
#include <cstring>

/** @file GrafoED.h
*   @brief Arquivo de cabeçalho com as funções que interagem diretamente com o grafo, executando inserções, exclusões e edições na estrutura de dados
*   @sa GrafoOp.h
*/

/** @enum TS_fCondRet
*   @brief Enumeration com os possíveis retornos das funções (TS_fCondRetOk ou TS_fCondRetErro)
*/
   enum TS_fCondRet {
        TS_CondRetOk,
        TS_CondRetErro};

/** @typedef struct tpElementoReq tgElementoReq
*   @brief Tipo que armazena as informações dos requisitos.
*   @see tgElementoGrafo
*/
/** @struct tgElementoReq
*   @brief Estrutura que armazena as informações dos requisitos.
*   @var unsigned int id
*   @brief ID do requisito
*   @var struct tgElementoReq * prox
*   @brief Ponteiro para o próximo pré-requisito
*/
   typedef struct tgElementoReq{
	   unsigned int id;
	   struct tgElementoReq *prox;
   }tpElementoReq;

/** @typedef struct tgElementoGrafo tpElementoGrafo
*   @brief Tipo que armazena as informações das tarefas.
*   @see tgElementoGrafo
*/
/** @struct tgElementoGrafo
*   @brief Estrutura que armazena as informações das tarefas.
*   @var unsigned int id
*   @brief ID da tarefa
*   @var char szNome[100]
*   @brief Nome da tarefa
*   @var bool executado
*   @brief Estado da tarefa (já executado ou ainda não executado)
*   @var int tempoDuracao
*   @brief Tempo de duração da execução da tarefa
*   @var int tempoInicMin
*   @brief Tempo mínimo até a função estar passível de execução
*   @var int qtdPreReq
*   @brief Número de pré-requisitos que a tarefa tem
*   @var tpElementoReq * lstPreReq
*   @see tpElementoReq
*   @brief Lista de pré-requisitos da tarefa
*   @var struct tgElementoGrafo * prox
*   @brief Ponteiro para a próxima tarefa
*/
   typedef struct tgElementoGrafo{
	   unsigned int id; 
	   char szNome[100] ;
	   bool executado;
	   int tempoDuracao;
	   int tempoInicMin;
	   int qtdPreReq;
	   tpElementoReq *lstPreReq;
	   struct tgElementoGrafo *prox;
   }tpElementoGrafo;

/** @typedef struct grafo * pGrafo
*   @brief Tipo ponteiro para cabeça do grafo.
*/
   typedef struct grafo{
       tpElementoGrafo *org;
       int tempo;
   }* pGrafo;

/* ponteiro para lista de tarefas apenas por ID */
   typedef tpElementoReq * pListaId;
 
/** Funções **/

/** @fn pGrafo ED_CriarGrafo()
*   @brief Aloca o espaço na memória para cabeça da estrutura.
*/
   pGrafo    ED_CriarGrafo();

/** @fn void ED_GravarGrafo(pGrafo, FILE *)
*   @brief Escreve o grafo em um .txt.
*   @param pGrafo: ponteiro para cabeça do grafo
*   @param ponteiro para arquivo
*/
   void      ED_GravarGrafo(pGrafo, FILE *);

/** @fn void ED_DesalocarGrafo(pGrafo, FILE *)
*   @brief Desaloca a memória do grafo após escrever o grafo em um txt.
*   @param pGrafo: ponteiro para cabeça do grafo
*   @param ponteiro para arquivo
*/
   void      ED_DesalocarGrafo(pGrafo, FILE *);

/** @fn void ED_DestruirGrafo(pGrafo)
*   @brief Desaloca o grafo sem salvar as informações em um .txt.
*   @param pGrafo: ponteiro para cabeça do grafo
*/
   void      ED_DestruirGrafo(pGrafo);

/** @fn void ED_DesalocarTarefa(*tpElementoGrafo)
*   @brief Desaloca o espaço da memória alocado para a tarefa.
*   @param *toElementoGrafo: ponteiro para a tarefa
*/
   void      ED_DesalocarTarefa(*tpElementoGrafo);

/** @fn void ED_DesalocarReq(*tpElementoReq);
*   @brief Desaloca o espaço da memória alocado para o requisito.
*   @param *tpElementoReq: ponteiro para o requisito
*/
   void      ED_DesalocarReq(*tpElementoReq);

/** @fn void ED_CriarRequisito(pGrafo, unsigned int, unsigned int)
*   @brief Aloca e preenche com as informações do requisito, já adicionando ao grafo.
*   @param pGrafo: ponteiro para cabeça do grafo
*   @param unsigned int: id da tarefa
*   @param unsigned int: id do requisito
*/
   void      ED_CriarRequisito(pGrafo, unsigned int, unsigned int);

/** @fn void ED_ExcluirRequisito(pGrafo, unsigned int, unsigned int)
*   @brief Desaloca o requisito, o retirando do grafo.
*   @param pGrafo: ponteiro para cabeça do grafo
*   @param unsigned int: id da tarefa
*   @param unsigned int: id do requisito
*/
   void      ED_ExcluirRequisito(pGrafo, unsigned int, unsigned int);
   
/** @fn void ED_CriarTarefa(pGrafo, tpElementoGrafo)
*   @brief Adiciona a estrutura com as informações da tarefa no grafo.
*   @param pGrafo: ponteiro para cabeça do grafo
*   @param tpElementoGrafo: struct com as informações da tarefa
*/
   void      ED_CriarTarefa(pGrafo, tpElementoGrafo); 
   
/** @fn bool ED_EhTarefaSemReq(pGrafo, unsigned int)
*   @brief Verifica se a tarefa não tem pre-requisitos.
*   @param pGrafo: ponteiro para cabeça do grafo
*   @param unsigned int: id da tarefa
*/
   bool      ED_EhTarefaSemReq(pGrafo, unsigned int);
   
/** @fn void ED_ExcluirTarefa(pGrafo, unsigned int)
*   @brief Remove as tarefas do grafo.
*   @param pGrafo: ponteiro para cabeça do grafo
*   @param unsigned int: id da tarefa
*/
   void      ED_ExcluirTarefa(pGrafo, unsigned int);
   
/** @fn void ED_EditarId(pGrafo, unsigned int, unsigned int)
*   @brief Edita o Id da tarefa.
*   @param pGrafo: ponteiro para cabeça do grafo
*   @param unsigned int: antigo id da tarefa
*   @param unsigned int: novo id da tarefa
*/
   void      ED_EditarId(pGrafo, unsigned int, unsigned int);

/** @fn void ED_EditarNome(pGrafo, unsigned int, char *)
*   @brief Edita o nome da tarefa.
*   @param pGrafo: ponteiro para cabeça do grafo
*   @param unsigned int: id da tarefa
*   @param string: novo nome da tarefa
*/
   void      ED_EditarNome(pGrafo, unsigned int, char *);

/** @fn void ED_EditarEstadoExec(pGrafo, unsigned int, bool)
*   @brief Edita o tempo de duração da execução da tarefa.
*   @param pGrafo: ponteiro para cabeça do grafo
*   @param unsigned int: id da tarefa
*   @param int: novo tempo de execução da tarefa
*/
   void      ED_EditarEstadoExec(pGrafo, unsigned int, bool);

/** @fn void ED_EditarDuracao(pGrafo, unsigned int, int)
*   @brief Edita o tempo de duração da execução da tarefa.
*   @param pGrafo: ponteiro para cabeça do grafo
*   @param unsigned int: id da tarefa
*   @param int: novo tempo de execução da tarefa
*/
   void      ED_EditarDuracao(pGrafo, unsigned int, int);

/** @fn void ED_EditarInicMin(pGrafo, unsigned int, int)
*   @brief Edita o tempo mínio para a tarefa estar passível de ser executada.
*   @param pGrafo: ponteiro para cabeça do grafo
*   @param unsigned int: id da tarefa
*   @param int: novo tempo mínimo de espera
*/
   void      ED_EditarInicMin(pGrafo, unsigned int, int);
   
#endif
