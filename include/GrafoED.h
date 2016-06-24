#ifndef GRAFO_ED
#define GRAFO_ED

#include <cstdlib>
#include <cstdio>
#include <cstring>

/** @file GrafoED.h
*   @brief Arquivo de cabeçalho com as funções que interagem diretamente com o grafo, executando inserções, exclusões e edições na estrutura de dados
*   @sa GrafoOp.h
*/

/** @typedef struct tpElementoReq tgElementoReq
*   @brief Tipo que armazena as informações dos requisitos.
*   @see tgElementoGrafo
*/
/** @struct tgElementoReq
*   @brief Estrutura que armazena as informações dos requisitos.
*   @var unsigned int id: ID do requisito
*   @var struct tgElementoReq * prox: Ponteiro para o próximo pré-requisito
*/
   typedef struct tgElementoReq{
	   unsigned int id;
	   struct tgElementoReq * prox;
   }tpElementoReq;

/** @typedef struct tgElementoGrafo tpElementoGrafo
*   @brief Tipo que armazena as informações das tarefas.
*   @see tgElementoGrafo
*/
/** @struct tgElementoGrafo
*   @brief Estrutura que armazena as informações das tarefas.
*   @var unsigned int id: ID da tarefa
*   @var char szNome[100]: Nome da tarefa
*   @var bool executado: Estado da tarefa (já executado ou ainda não executado)
*   @var int tempoDuracao: Tempo de duração da execução da tarefa
*   @var int tempoInicMin: Tempo mínimo até a função estar passível de execução
*   @var int qtdPreReq: Número de pré-requisitos que a tarefa tem
*   @var tpElementoReq * lstPreReq: Lista dos pré-requisitos
*   @see tpElementoReq
*   @var struct tgElementoGrafo * prox: Ponteiro para a próxima tarefa
*/
   typedef struct tgElementoGrafo{
	   unsigned int id; 
	   char szNome[100] ;
	   bool executado;
	   int tempoDuracao;
	   int tempoInicMin;
	   int qtdPreReq;
	   tpElementoReq * lstPreReq;
	   struct tgElementoGrafo * prox;
   }tpElementoGrafo;

/** @typedef struct grafo * pGrafo
*   @brief Tipo ponteiro para cabeça do grafo.
*/
   typedef struct grafo{
       tpElementoGrafo * org;
       int tempo;
   }* pGrafo;

/* ponteiro para lista de tarefas apenas por ID */
   typedef tpElementoReq * pListaId;



/** @fn pGrafo ED_CriarGrafo()
*   @brief Aloca o espaço na memória para cabeça da estrutura.
*   @return ponteiro para cabeça do grafo
*/
   pGrafo    ED_CriarGrafo();

/** @fn void ED_GravarGrafo(pGrafo, FILE *)
*   @brief Escreve o grafo em um .txt.
*   @param ponteiro para cabeça do grafo
*   @param ponteiro para arquivo
*   @return void
*/
   void      ED_GravarGrafo(pGrafo, FILE *);

/** @fn void ED_DesalocarGrafo(pGrafo, FILE *)
*   @brief Desaloca a memória do grafo após escrever o grafo em um txt.
*   @param ponteiro para cabeça do grafo
*   @param ponteiro para arquivo
*   @return void
*/
   void      ED_DesalocarGrafo(pGrafo, FILE *);

/** @fn void ED_DestruirGrafo(pGrafo)
*   @brief Desaloca o grafo sem salvar as informações em um .txt.
*   @param ponteiro para cabeça do grafo
*   @return void
*/
   void      ED_DestruirGrafo(pGrafo);

/** @fn void ED_DestruirTarefas(tpElementoGrafo *)
*   @brief Desaloca o espaço da memória alocado para a tarefa.
*   @param ponteiro para a tarefa
*   @return void
*/
   void      ED_DestruirTarefas(tpElementoGrafo *);

/** @fn void ED_DestruirReq(tpElementoReq *);
*   @brief Desaloca o espaço da memória alocado para o requisito.
*   @param ponteiro para o requisito
*   @return void
*/
   void      ED_DestruirReq(tpElementoReq *);

/** @fn void ED_CriarRequisito(tpElementoGrafo *, unsigned int)
*   @brief Aloca e preenche com as informações do requisito, já adicionando ao grafo.
*   @param ponteiro para tarefa
*   @param id do requisito a ser criado
*   @return void
*/
   void      ED_CriarRequisito(tpElementoGrafo *, unsigned int);

/** @fn void ED_ExcluirRequisito(tpElementoGrafo *, unsigned int)
*   @brief Desaloca o requisito, o retirando do grafo.
*   @param ponteiro para tarefa
*   @param id do requisito a ser excluido
*   @return void
*/
   void      ED_ExcluirRequisito(tpElementoGrafo *, unsigned int);
   
/** @fn void ED_CriarTarefa(pGrafo, tpElementoGrafo *)
*   @brief Adiciona a estrutura com as informações da tarefa no grafo.
*   @param ponteiro para cabeça do grafo
*   @param ponteiro para struct com as informações da tarefa
*   @return void
*/
   void      ED_CriarTarefa(pGrafo, tpElementoGrafo *); 
   
/** @fn bool ED_EhTarefaSemReq(tpElementoGrafo *)
*   @brief Verifica se a tarefa não tem pre-requisitos.
*   @param ponteiro para a tarefa
*   @return void
*/
   bool      ED_EhTarefaSemReq(tpElementoGrafo *);
   
/** @fn void ED_ExcluirTarefa(pGrafo, unsigned int)
*   @brief Remove uma tarefa do grafo.
*   @param ponteiro para cabeça do grafo
*   @param id da tarefa a ser excluida
*   @return void
*/
   void      ED_ExcluirTarefa(pGrafo, unsigned int);
   
/** @fn void ED_EditarId(tpElementoGrafo *, unsigned int)
*   @brief Edita o Id da tarefa.
*   @param ponteiro para tarefa
*   @param unsigned novo id da tarefa
*   @return void
*/
   void      ED_EditarId(tpElementoGrafo *, unsigned int);

/** @fn void ED_EditarNome(tpElementoGrafo *, char *)
*   @brief Edita o nome da tarefa.
*   @param ponteiro para tarefa
*   @param novo nome da tarefa
*   @return void
*/
   void      ED_EditarNome(tpElementoGrafo *, char *);

/** @fn void ED_EditarEstadoExec(tpElementoGrafo *, bool)
*   @brief Edita o tempo de duração da execução da tarefa.
*   @param ponteiro para tarefa
*   @param novo tempo de execução da tarefa
*   @return void
*/
   void      ED_EditarEstadoExec(tpElementoGrafo *, bool);

/** @fn void ED_EditarDuracao(tpElementoGrafo *, int)
*   @brief Edita o tempo de duração da execução da tarefa.
*   @param ponteiro para tarefa
*   @param novo tempo de execução da tarefa
*   @return void
*/
   void      ED_EditarDuracao(tpElementoGrafo *, int);

/** @fn void ED_EditarInicMin(pGrafo, unsigned int, int)
*   @brief Edita o tempo mínio para a tarefa estar passível de ser executada.
*   @param ponteiro para tarefa
*   @param novo tempo mínimo de espera até a tarefa poder ser executada
*   @return void
*/
   void      ED_EditarInicMin(tpElementoGrafo *, int);

/** @fn tpElementoGrafo * ED_EhIdExistente(pGrafo, unsigned int)
*   @brief Verifica se o ID existe e retorna o ponteiro para a tarefa, caso não exista retorna NULL.
*   @param ponteiro para cabeça do grafo
*   @param id da tarefa
*   @return ponteiro para a tarefa do grafo
*/
   tpElementoGrafo *   ED_EhIdExistente(pGrafo, unsigned int);

/** @fn bool ED_EhReqExistente(tpElementoGrafo *, unsigned int)
*   @brief Verifica se o id pertence aos pré-requisitos de uma determinada tarefa.
*   @param ponteiro para a tarefa
*   @param id do requisito
*   @return true se o requisito existir, false se o requisito não existir
*/
   bool ED_EhReqExistente(tpElementoGrafo *, unsigned int);
   
/** @fn bool ED_TemOrigem(pGrafo)
*   @brief Verifica se o grafo tem origens (tarefas sem pré requisitos).
*   @param ponteiro para cabeça do grafo
*   @return true se o grafo tem origem, false se não tiver
*/
   bool ED_TemOrigem(pGrafo);

/** @fn bool ED_CalcularTempoMinExec(pGrafo, unsigned int)
*   @brief Calcula o tempo mínimo para a tarefa mudar para o estado de executado.
*   @param ponteiro para cabeça do grafo
*   @param id da tarefa
*   @return inteiro com o valor do tempo necessário
*/
   int ED_CalcularTempoMinExec(pGrafo, unsigned int);

/** @fn bool ED_TemCamCircular(pGrafo, tpElementoGrafo *, int, int)
*   @brief Verifica se existem caminhos circulares para uma tarefa específica.
*   @param ponteiro para cabeça do grafo
*   @param ponteiro para a tarefa
*   @param numero de tarefas existentes no grafo
*   @param numero da chamadas a função (controle de chamadas recursivas)
*   @return true se tiver caminho circular, false se não tiver
*/ 
   bool ED_TemCamCircular(pGrafo, tpElementoGrafo *, int, int);

#endif
