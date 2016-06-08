#ifndef GRAFO-ED
#define GRAFO-ED

#include <cstdlib>
#include <cstdio>
#include <cstring>

/** Enumerations de retorno **/
   enum TS_fCondRet {
        TS_CondRetOk,
        TS_CondRetErro};

/** Typedefs elementos **/

/* requisitos */
   typedef struct tgElementoReq{
	   unsigned int id;
	   struct tgElementoReq *prox;
   }tpElementoReq;

/* tarefas */
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

/* cabeça da estrutura */
   typedef struct grafo{
       tpElementoGrafo *org;
       int tempo;
   }* pGrafo;

/* ponteiro para lista de tarefas apenas por ID */
   typedef tpElementoReq * pListaId;
 
/** Funções **/

/* aloca a cabeça do grafo */
   pGrafo    ED_AlocarGrafo();

/* escreve o grafo em um txt */
   void      ED_GravarGrafo(pGrafo, FILE *);

/* desaloca a memória do grafo após escrever o grafo em um txt */
   void      ED_DesalocarGrafo(pGrafo, FILE *);

/* desaloca o grafo sem salvar as informações em um txt */
   void      ED_DestruirGrafo(pGrafo);
   
/* aloca e preenche com as informações do requisito, já adicionando ao grafo */
   void      ED_CriarRequisito(pGrafo, unsigned int, unsigned int);
   
/* desaloca o requisito, retirando do grafo */
   void      ED_ExcluirRequisito(pGrafo, unsigned int, unsigned int);
   
/* adiciona a estrutura com as informações da tarefa no grafo */
   void      ED_CriarTarefa(pGrafo, tpElementoGrafo); 
   
/* verifica se a tarefa não tem pre-requisitos */
   bool      ED_EhTarefaSemReq(pGrafo, unsigned int);
   
   
/* remove as tarefas - apenas se elas não forem pre-requisito de outras tarefas */
   void      ED_ExcluirTarefa(pGrafo, unsigned int);
   
/* funções de edição de tarefa */
   void      ED_EditarId(pGrafo, unsigned int, unsigned int);	
   void      ED_EditarNome(pGrafo, unsigned int, char *);
   void      ED_EditarEstadoExec(pGrafo, unsigned int, bool);
   void      ED_EditarDuracao(pGrafo, unsigned int, int);
   void      ED_EditarInicMin(pGrafo, unsigned int, int);
   
#endif
