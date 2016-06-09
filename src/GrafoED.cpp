#include "GrafoED.h"

/* typedef struct tgElementoReq{
	   unsigned int id;
	   struct tgElementoReq *prox;
   }tpElementoReq;
*/
/* typedef struct tgElementoGrafo{
	   unsigned int id; 
	   char szNome[100] ;
	   bool executado;
	   int tempoDuracao;
	   int tempoInicMin;
	   int qtdPreReq;
	   tpElementoReq *lstPreReq;
	   struct tgElementoGrafo *prox;
   }tpElementoGrafo;

  typedef struct grafo{
       tpElementoGrafo *org;
       int tempo;
   }* pGrafo;
*/
//   typedef tpElementoReq * pListaId;
 
/** Funções **/

   pGrafo    ED_CriarGrafo(){

      pGrafo pCabeca = (pGrafo)calloc(1,sizeof(grafo));
      pCabeca->tempo = 0;
      return pCabeca;

   }

   void      ED_GravarGrafo(pGrafo pCabeca, FILE * arq){

   }

   void      ED_DesalocarGrafo(pGrafo pCabeca, FILE * arq){

      ED_GravarGrafo(pCabeca, arq);
      ED_DestruirGrafo(pCabeca);

   }

   void      ED_DestruirGrafo(pGrafo pCabeca){

      if(pCabeca->org != NULL){
         ED_DestruirTarefas(pCabeca->org);
      }

      free(pCabeca);

   }

   void      ED_DestruirTarefas(tpElementoGrafo * pTarefa){

      if(pTarefa->lstPreReq != NULL){
         ED_DestruirReq(pTarefa->lstPreReq);
      }

      if(pTarefa->prox != NULL){
         ED_DestruirTarefas(pTarefa->prox);
      }

      free(pTarefa);

   }

   void      ED_DestruirReq(tpElementoReq * pReq){

      if(pReq->prox != NULL){
         ED_DestruirReq(pReq->prox);
      }

      free(pReq);

   }

   void      ED_CriarRequisito(tpElementoGrafo * pTarefa, unsigned int idReq){

      tpElementoReq *pReq = (tpElementoReq *)malloc(sizeof(tpElementoReq));
      pReq->id            = idReq;

      if(pTarefa->lstPreReq != NULL){
         pReq->prox = pTarefa->lstPreReq;
      }

      pTarefa->lstPreReq = pReq;

   }

   void      ED_ExcluirRequisito(tpElementoGrafo * pTarefa, unsigned int idReq){

      tpElementoReq * pTemp    = pTarefa->lstPreReq;
      tpElementoReq * pTempAnt = pTarefa->lstPreReq;

      if(pTemp->id == idReq){
         pTarefa->lstPreReq = pTemp->prox;
         free(pTemp);
      }

      while(pTemp != NULL){

         if(pTemp->id == idReq){
            pTempAnt->prox = pTemp->prox;
            free(pTemp);
         }

         pTempAnt = pTemp;
         pTemp = pTemp->prox;
      }

   }
   
   void      ED_CriarTarefa(pGrafo pCabeca, tpElementoGrafo tarefa){

      tpElementoGrafo * pTarefa = (tpElementoGrafo *)malloc(sizeof(tpElementoGrafo));
      pTarefa                   = tarefa;

      if(pCabeca->org != NULL){
         pTarefa->prox = pCabeca->org;
      }

      pCabeca->org = pTarefa;

   }
   
   bool      ED_EhTarefaSemReq(tpElementoGrafo * pTarefa){

      if(pTarefa->qtdPreReq == 0){
         return true;
      }else{
         return false;
      }

   }
   
   void      ED_ExcluirTarefa(pGrafo pCabeca, unsigned int idTarefa){

      tpElementoGrafo * pTemp    = pCabeca->org;
      tpElementoGrafo * pTempAnt = pCabeca->org;

      if(pTemp->id == idTarefa){
         pCabeca->org = pTemp->prox;
         free(pTemp);
      }

      while(pTemp != NULL){

         if(pTemp->id == idTarefa){
            pTempAnt->prox = pTemp->prox;
            free(pTemp);
         }

         pTempAnt = pTemp;
         pTemp = pTemp->prox;
      }

   }

   void      ED_EditarId(tpElementoGrafo * pTarefa, unsigned int novoId){

      pTarefa->id = novoId;

   }

   void      ED_EditarNome(tpElementoGrafo * pTarefa, char *novoNome){
 
      strcpy(novoNome, pTarefa->szNome);

   }

   void      ED_EditarEstadoExec(tpElementoGrafo * pTarefa, bool novoEstado){

      pTarefa->executado = novoEstado;

   }

   void      ED_EditarDuracao(tpElementoGrafo * pTarefa, int novaDuracao){

      pTarefa->tempoDuracao = novaDuracao;

   }

   void      ED_EditarInicMin(tpElementoGrafo * pTarefa, int novoTempoInicMin){

      pTarefa->tempoInicMin = novoTempoInicMin

   }
   
   tpElementoGrafo * ED_EhIdExistente(pGrafo pCabeca, unsigned int id){

      if(pCabeca == NULL){
         return NULL; // id não existe
      }

      if(pCabeca->org == NULL){
         return NULL; // id não existe
      }

      tpElementoGrafo * pTemp = pCabeca->org;

      while(pTemp != NULL){

         if(pTemp->id == id){
           return pTemp; // id encontrado
         }

         pTemp = pTemp->prox;
      } 

      return NULL; // id não encontrado

   }

   bool ED_EhReqExistente(tpElementoGrafo * pTarefa, unsigned int idReq){

      tpElementoReq * pTemp = pTarefa->lstPreReq;

      while(pTemp != NULL){

         if(pTemp->id == idReq){
           return true; // id encontrado
         }

         pTemp = pTemp->prox;
      }

      return false; // id não encontrado

   }