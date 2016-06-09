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

   void      ED_GravarGrafo(pGrafo pCabeca, FILE *arq){

   }

   void      ED_DesalocarGrafo(pGrafo pCabeca, FILE *arq){

   }

   void      ED_DestruirGrafo(pGrafo pCabeca){

   }

   void      ED_DesalocarTarefa(*tpElementoGrafo){

   }

   void      ED_DesalocarReq(*tpElementoReq){

   }
  
           /////////////////////////////////////////////////////////////////////
          //                                                                 //
         //                                                                 //
        //       Pode passar como parâmetro um ponteiro para uma           //
       //        tarefa específica, ou como a ED tem cabeça o             //
      //        único parâmetro válido é a cabeça do grafo?              //
     //                                                                 //
    //       Passar o ponteiro da tarefa específico evita              //
   //     outra passagem por todos elementos na busca via id          //
  //                                                                 //
 //                                                                 //
/////////////////////////////////////////////////////////////////////

   void      ED_CriarRequisito(pGrafo pCabeca, *tpElementoGrafo pTarefa, unsigned int idReq){

      tpElementoReq *pReq = (*tpElementoReq)malloc(sizeof(tpElementoReq));
      pReq->id = idReq;
      if(pTarefa->lstPreReq != NULL){
         pReq->prox = pTarefa->lstPreReq;
      }
      pTarefa->lstPreReq = pReq;

   }

   void      ED_ExcluirRequisito(pGrafo pCabeca, unsigned int, unsigned int){

   }
   
   void      ED_CriarTarefa(pGrafo pCabeca, tpElementoGrafo tarefa){

      tpElementoGrafo *pTarefa = (*tpElementoGrafo)malloc(sizeof(tpElementoGrafo));
      pTarefa = tarefa;
      if(pCabeca->org != NULL){
         pTarefa->prox = pCabeca->org;
      }
      pCabeca->org = pTarefa;

   }
   
   bool      ED_EhTarefaSemReq(pGrafo pCabeca, unsigned int){

   }
   
   void      ED_ExcluirTarefa(pGrafo pCabeca, unsigned int){

   }

   void      ED_EditarId(pGrafo pCabeca, unsigned int, unsigned int){

   }

   void      ED_EditarNome(pGrafo pCabeca, unsigned int, char *){
 
   }

   void      ED_EditarEstadoExec(pGrafo pCabeca, unsigned int, bool){

   }

   void      ED_EditarDuracao(pGrafo pCabeca, unsigned int, int){

   }

   void      ED_EditarInicMin(pGrafo pCabeca, unsigned int, int){

   }
   