#include "GrafoED.h"
 
/* Funções */

   pGrafo    ED_CriarGrafo(){

      pGrafo pCabeca;
      pCabeca        = (pGrafo)calloc(1,sizeof(grafo));
      pCabeca->tempo = 0;

      return pCabeca;

   }

   void      ED_GravarGrafo(pGrafo pCabeca, FILE * arq){

      tpElementoGrafo * pTarefaTemp;
      tpElementoGrafo   tarefaTemp;
      tpElementoReq   * pReqTemp;

      pTarefaTemp = pCabeca->org;

      while(pTarefaTemp != NULL){ // varre as tarefas uma a uma escrevendo no arquivo

         tarefaTemp = * pTarefaTemp;
         pReqTemp   = pTarefaTemp->lstPreReq;

         fprintf(arq, "%u '%s' ", tarefaTemp.id, tarefaTemp.szNome); // escreve o id e nome

         if(tarefaTemp.executado){ // escreve se foi ou não executado
            fprintf(arq, "1 ");
         }else{
            fprintf(arq, "0 ");
         }
         
         fprintf(arq, "%d %d %d", tarefaTemp.tempoDuracao, tarefaTemp.tempoInicMin, tarefaTemp.qtdPreReq); // escreve duração, inic mín e qtd de pré-req

         if(!ED_EhTarefaSemReq(pTarefaTemp)){ // se tiver pré-requisito

            while(pReqTemp != NULL){ // varre as listas de pré-requisitos

               fprintf(arq, " %d", pReqTemp->id); // escreve os ids dos requisitos

               pReqTemp = pReqTemp->prox;
            }
         }

         fprintf(arq, "\n"); // quebra de linha ao final da tarefa

         pTarefaTemp = pTarefaTemp->prox;
      }

   }

   void      ED_DesalocarGrafo(pGrafo pCabeca, FILE * arq){

      ED_GravarGrafo(pCabeca, arq);
      ED_DestruirGrafo(pCabeca);

   }

   void      ED_DestruirReq(tpElementoReq * pReq){

      if(pReq->prox != NULL){
         ED_DestruirReq(pReq->prox);
      }

      free(pReq);

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

   void      ED_DestruirGrafo(pGrafo pCabeca){

      if(pCabeca->org != NULL){
         ED_DestruirTarefas(pCabeca->org);
      }

      free(pCabeca);

   }

   void      ED_CriarRequisito(tpElementoGrafo * pTarefa, unsigned int idReq){

      tpElementoReq *pReq;
      pReq     = (tpElementoReq *)malloc(sizeof(tpElementoReq));
      pReq->id = idReq;

      if(pTarefa->lstPreReq != NULL){
         pReq->prox = pTarefa->lstPreReq;
      }

      pTarefa->lstPreReq = pReq;
      pTarefa->qtdPreReq = (pTarefa->qtdPreReq + 1);

   }

   void      ED_ExcluirRequisito(tpElementoGrafo * pTarefa, unsigned int idReq){

      tpElementoReq * pTemp;
      tpElementoReq * pTempAnt;

      pTemp    = pTarefa->lstPreReq;
      pTempAnt = pTarefa->lstPreReq;

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

      pTarefa->qtdPreReq = (pTarefa->qtdPreReq -1);

   }
   
   void      ED_CriarTarefa(pGrafo pCabeca, tpElementoGrafo * pTarefa){

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

      tpElementoGrafo * pTemp;
      tpElementoGrafo * pTempAnt;
      pTemp    = pCabeca->org;
      pTempAnt = pCabeca->org;

      if(pTemp->id == idTarefa){
         if(pTemp->lstPreReq != NULL){
            ED_DestruirReq(pTemp->lstPreReq);
         }
         pCabeca->org = pTemp->prox;
         free(pTemp);
         return;
      }

      while(pTemp != NULL){

         if(pTemp->id == idTarefa){

            if(pTemp->lstPreReq != NULL){
               ED_DestruirReq(pTemp->lstPreReq);
            } 

            pTempAnt->prox = pTemp->prox;
            free(pTemp);
            break;
         }

         pTempAnt = pTemp;
         pTemp    = pTemp->prox;
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

      pTarefa->tempoInicMin = novoTempoInicMin;

   }
   
   tpElementoGrafo * ED_EhIdExistente(pGrafo pCabeca, unsigned int id){

      if(pCabeca == NULL){
         return NULL; // id não existe
      }

      if(pCabeca->org == NULL){
         return NULL; // id não existe
      }

      tpElementoGrafo * pTemp;
      pTemp = pCabeca->org;

      while(pTemp != NULL){

         if(pTemp->id == id){
           return pTemp; // id encontrado
         }

         pTemp = pTemp->prox;
      } 

      return NULL; // id não encontrado

   }

   bool ED_EhReqExistente(tpElementoGrafo * pTarefa, unsigned int idReq){

      tpElementoReq * pTemp;
      pTemp = pTarefa->lstPreReq;

      while(pTemp != NULL){

         if(pTemp->id == idReq){
           return true; // id encontrado
         }

         pTemp = pTemp->prox;
      }

      return false; // id não encontrado

   }

   bool   ED_TemOrigem(pGrafo pCabeca){

      tpElementoGrafo * pTarefa;
      pTarefa = pCabeca->org;

      while(pTarefa != NULL){

         if(ED_EhTarefaSemReq(pTarefa)){
            return true;
         }

         pTarefa = pTarefa->prox;

      }

      return false;

   }

   int ED_CalcularTempoMinExec(pGrafo pCabeca, unsigned int idTarefa){

      tpElementoGrafo * pTarefa;
      pTarefa = ED_EhIdExistente(pCabeca, idTarefa);

      if(pTarefa->executado){
         return 0;
      }

      if(pTarefa->qtdPreReq == 0){
         return (pTarefa->tempoInicMin + pTarefa->tempoDuracao);
      }

      tpElementoReq * pReqTemp;
      int tempo;
      pReqTemp = pTarefa->lstPreReq;
      tempo    = 0;

      while(pReqTemp != NULL){

         tempo = tempo + ED_CalcularTempoMinExec(pCabeca, pReqTemp->id);
         pReqTemp = pReqTemp->prox;

      }

      return tempo;

   }

   bool ED_TemCamCircular(pGrafo pCabeca, tpElementoGrafo * pTarefa, int numTarefas, int numChamada){

      if(numTarefas < numChamada){ // se chamar a função mais vezes que o número de tarefas existe caminho circular
         return true;
      }

      tpElementoReq * pReqTemp;

      if(!ED_EhTarefaSemReq(pTarefa)){ // se a tarefa não é origem

         pReqTemp = pTarefa->lstPreReq;
         
         while(pReqTemp != NULL){   // enquanto tiver requisitos
         
            if(ED_TemCamCircular(pCabeca, ED_EhIdExistente(pCabeca, pTarefa->lstPreReq->id), numTarefas, numChamada+1)){  // procura caminho circular
               return true; // se tiver caminho circular, propaga
            }

            pReqTemp = pReqTemp->prox; // tenta pro próximo requisito
         }
      }

      return false; // passou por tudo e retornou sem caminhos, então, eles não existem
   }
