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
	   int tempDuracao;
	   int tempInicMin;
	   int qtdPreReq;
	   tpElementoReq *lstPreReq;
	   struct tgElementoGrafo *prox;
   }tpElementoGrafo;

/* cabeça da estrutura */
   typedef struct grafo{
       tpElementoGrafo *org;
   }* pGrafo;

/* ponteiro para lista de tarefas apenas por ID */
   typedef tpElementoReq * pListaId;
 
/** Funções **/

/* aloca a cabeça do grafo */
   pGrafo    AlocarGrafo();
   
/* lê o grafo do txt */
   void      LerGrafo(pGrafo, FILE *);

/* escreve o grafo em um txt */
   void      GravarGrafo(pGrafo, FILE *);

/* desaloca a memória do grafo após escrever o grafo em um txt */
   void      DesalocarGrafo(pGrafo, FILE *);

/* desaloca o grafo sem salvar as informações em um txt */
   void      DestruirGrafo(pGrafo);
   
/* aloca e preenche com as informações do requisito, já adicionando ao grafo */
   void      CriarRequisito(pGrafo, unsigned int, unsigned int);
   
/* desaloca o requisito, retirando do grafo */
   void      ExcluirRequisito(pGrafo, unsigned int, unsigned int);
   
/* adiciona a estrutura com as informações da tarefa no grafo */
   void      CriarTarefa(pGrafo, tpElementoGrafo); // controlar para não permitir ids repetidos
   
/* verifica se a tarefa não tem pre-requisitos */
   bool      EhTarefaSemReq(pGrafo, unsigned int);
   
//campo executado: será atualizado para o tempo fornecido pelo usuario ou fica fixo com o valor lido do txt?
   
/* remore as tarefas - apenas se elas não forem pre-requisito de outras tarefas */
   void      ExcluirTarefa(pGrafo, unsigned int);
   
/* funções de edição de tarefa */
   void      EditarId(pGrafo, unsigned int, unsigned int);	// verificar se novo id já não existe
   void      EditarNome(pGrafo, unsigned int, char *);
   void      EditarEstadoExec(pGrafo, unsigned int, bool);
   void      EditarDuracao(pGrafo, unsigned int, int);
   void      EditarInicMin(pGrafo, unsigned int, int);
   
/* calcula o menor tempo para execução da tarefa */
   void      CalcularTempMinExec(pGrafo, unsigned int);

/* retona ponteiro para o primeiro elemento de uma lista com os IDs das tarefas já completadas */
   pListaId  TarefasCompletadas(pGrafo, int);