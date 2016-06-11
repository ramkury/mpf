#include "GrafoOp.h"

/* Funções */

   pGrafo OP_LerGrafo(char * szNomeArq){

      FILE * arq;
      arq = fopen(szNomeArq, "w");

      if(arq == NULL){ //assertiva
         throw //EXCEPTION FALHA_FOPEN_ARQ
      }

      if(pCabeca == NULL){ //assertiva
         throw //EXCEPTION GRAFO_INEXISTENTE
      }

      int tempQtdPreReq;
      int i;
      unsigned int id;
      pGrafo pCabeca;
      tpElementoGrafo * pTarefa;
      pCabeca = ED_CriarGrafo();

      while(fscanf(arq, "%d", id) != EOF){ // tenta ler id e já colocar na tarefa

         pTarefa = (tpElementoGrafo *)malloc(sizeof(tpElementoGrafo));

         pTarefa->id = id;
         fgetc(arq);
         fscanf(arq, "[^ ]", pTarefa->szNome); // pega o nome da tarefa
         fgetc(arq);
         fscanf(arq, "%d", pTarefa->executado); // pega o estado da execução
         fgetc(arq);
         fscanf(arq, "%d", pTarefa->tempoDuracao); // pega o tempo de duração
         fgetc(arq);
         fscanf(arq, "%d", pTarefa->tempoInicMin); // pega o tempo de início mínimo
         fgetc(arq);
         fscanf(arq, "%d", tempQtdPreReq); // pega a quantidade de requisitos

         pTarefa->qtdPreReq = tempQtdPreReq; // passa a quatidade para a tarefa
         pTarefa->lstPreReq = NULL;
         pTarefa->prox      = NULL;

         if(!OP_EhTarefaValida(pCabeca, pTarefa)){ // assertiva estrutural
            throw //EXCEPTION TAREFA_INVALIDA
         }

         ED_CriarTarefa(pCabeca, pTarefa);

         for(i = 0; i < tempQtdPreReq; i++){

            fscanf(arq, "%d", id);
            fgetc(arq);
            ED_CriarRequisito(pTarefa, id);

         }

      }

      OP_VerificarReq(pCabeca);
      if(OP_TemReqCircular(pCabeca)){
         throw //EXCEPTION REQUISITOS_CIRCULARES_GRAFO_INCONSISTENTE
      }

      return pCabeca;
  
   }

  void    OP_SalvarGrafo(pGrafo pCabeca, char * szNomeArq){

      FILE * arq = fopen(szNomeArq, "w");

      if(arq == NULL){ //assertiva
       throw //EXCEPTION FALHA_FOPEN_ARQ
      }

      if(!OP_EhGrafoValido){ // assertiva
         throw //EXCEPTION GRAFO_INVALIDO
      }

      ED_GravarGrafo(pCabeca, arq);

  }

   void   OP_DeletarGrafo(pGrafo pCabeca){

      if(pCabeca == NULL){ //assertiva
         throw //EXCEPTION GRAFO_INEXISTENTE
      }

      ED_DestruirGrafo(pCabeca);

   }

   int    OP_CalcularTempoMinExec(pGrafo pCabeca, unsigned int idTarefa){

      if(!OP_EhGrafoValido){ // assertiva de entrada
         throw //EXCEPTION GRAFO_INVALIDO
      }

      if(ED_EhIdExistente(pCabeca, idTarefa) == NULL){ // assertiva de entrada
         throw //EXCEPTION TAREFA_INVALIDA
      }

         return ED_CalcularTempoMinExec(pCabeca, idTarefa);

   }

   void   OP_EditarId(pGrafo pCabeca, unsigned int idTarefa, unsigned int novoIdTarefa){

      if(!OP_EhGrafoValido){ // assertiva
         throw //EXCEPTION GRAFO_INVALIDO
      }

      if(ED_EhIdExistente(pCabeca, novoIdTarefa) != NULL){
         throw //EXCEPTION ID_JAH_EXISTE
      }

      tpElementoGrafo *pTarefa = ED_EhIdExistente(idTarefa);

      if(pTarefa == NULL){ // assertiva
         throw //EXCEPTION ID_TAREFA_INVALIDO
      }

      ED_EditarId(pTarefa, novoIdTarefa);

   } // verificar se novo id já não existe

   void   OP_EditarNome(pGrafo pCabeca, unsigned int idTarefa, char * novoNome){

      if(!OP_EhGrafoValido){ // assertiva
         throw //EXCEPTION GRAFO_INVALIDO
      }

      tpElementoGrafo *pTarefa = ED_EhIdExistente(idTarefa);

      if(pTarefa == NULL){ // assertiva
         throw //EXCEPTION ID_TAREFA_INVALIDO
      }

      ED_EditarNome(pTarefa, novoNome);

   }

   void   OP_EditarEstadoExec(pGrafo pCabeca, unsigned int idTarefa, bool estadoExec){

      if(!OP_EhGrafoValido){ // assertiva
         throw //EXCEPTION GRAFO_INVALIDO
      }

      tpElementoGrafo *pTarefa = ED_EhIdExistente(idTarefa);

      if(pTarefa == NULL){ // assertiva
         throw //EXCEPTION ID_TAREFA_INVALIDO
      }

      ED_EditarEstadoExec(pTarefa, estadoExec);

   }

   void   OP_EditarDuracao(pGrafo pCabeca, unsigned int idTarefa, int novoTempoDuracao){

      if(!OP_EhGrafoValido){ // assertiva
         throw //EXCEPTION GRAFO_INVALIDO
      }

      if(novoTempoDuracao < 0){ // assertiva
         throw //EXCEPTION DURACAO_NEGATIVA
      }

      tpElementoGrafo *pTarefa = ED_EhIdExistente(idTarefa);

      if(pTarefa == NULL){ // assertiva
         throw //EXCEPTION ID_TAREFA_INVALIDO
      }

      ED_EditarDuracao(pTarefa, novoTempoDuracao);

   }

   void   OP_EditarInicMin(pGrafo pCabeca, unsigned int idTarefa, int novoTempoInicMin){

      if(!OP_EhGrafoValido){ // assertiva
         throw //EXCEPTION GRAFO_INVALIDO
      }

      if(novoTempoInicMin < 0){ // assertiva
         throw //EXCEPTION TEMPO_NEGATIVO
      }

      tpElementoGrafo *pTarefa = ED_EhIdExistente(idTarefa);

      if(pTarefa == NULL){ // assertiva
        throw //EXCEPTION ID_TAREFA_INVALIDO
      }

      ED_EditarInicMin(pTarefa, novoTempoInicMin);

   }

   void   OP_ExcluirTarefa(pGrafo pCabeca, unsigned int idTarefa){

      if(!OP_EhGrafoValido){ // assertiva
         throw //EXCEPTION GRAFO_INVALIDO
      }

      tpElementoGrafo *pTarefa = ED_EhIdExistente(idTarefa);

      if(pTarefa == NULL){ // assertiva
         throw //EXCEPTION ID_TAREFA_INVALIDO
      }

      tpElementoGrafo * pTarefaTemp = pCabeca->org;
      tpElementoReq * pReqTemp;

      while(pTarefaTemp != NULL){ // varre as tarefas em busca de pré-requisitos para tarefa a ser excluida
         pReqTemp = pTarefaTemp->lstPreReq;

         while(pReqTemp != NULL){ // varre os requisitos das tarefas em busca de pré-requisitos com id da tarefa a ser excluida

            if(pReqTemp->id == idTarefa){ // verifica se existe um pré-requisito com o id da tarefa que está sendo excluida
               ED_ExcluirRequisito(pTarefa, idTarefa); // retira essa tarefa dos pré-requisitos de outras tarefas
            }

            pReqTemp = pReqTemp->prox;
         }

         pTarefaTemp = pTarefaTemp->prox;
      }

      ED_ExcluirTarefa(pCabeca, idTarefa);

   }

   void   OP_CriarTarefa(pGrafo pCabeca, tpElementoGrafo tarefa){

      if(pCabeca == NULL){ //assertiva
         throw //EXCEPTION GRAFO_INEXISTENTE
      }

      tpElementoGrafo * pTarefa;
      pTarefa   = (tpElementoGrafo *)malloc(sizeof(tpElementoGrafo));
      * pTarefa = tarefa;
      pTarefa->qtdPreReq = 0;
      pTarefa->lstPreReq = NULL;
      pTarefa->prox      = NULL;

      if(!OP_EhTarefaValida(pCabeca, pTarefa)){ //assertiva
         throw //EXEPTION TAREFA_INVALIDA
      }

      ED_CriarTarefa(pCabeca, pTarefa);

   } 

   void   OP_CriarRequisito(pGrafo pCabeca, unsigned int idTarefa, unsigned int idReq){

      if(!OP_EhGrafoValido){ // assertiva
         throw //EXCEPTION GRAFO_INVALIDO
      }

      if(ED_EhIdExistente(idReq) == NULL){ // assertiva
         throw //EXCEPTION ID_REQ_INVALIDO
      }

      tpElementoGrafo *pTarefa;
      int numTarefas;

      pTarefa    = pCabeca->org;
      numTarefas = 0;

      while(pTarefa != NULL){ // descobre número de tarefas
         numTarefas++;
      }

      pTarefa    = ED_EhIdExistente(idTarefa);

      if(pTarefa == NULL){ // assertiva
         throw //EXCEPTION ID_TAREFA_INVALIDO
      }

      ED_CriarRequisito(pTarefa, idReq);
   
      if(ED_TemCamCircular(pCabeca, pTarefa, numTarefas, 0)){ // assertiva
         OP_ExcluirRequisito(pCabeca, idTarefa, idReq);
         throw //EXCEPTION CRIA_CAMINHO_CIRCULAR
      }

   }
   
   void   OP_ExcluirRequisito(pGrafo pCabeca, unsigned int idTarefa, unsigned int idReq){

      if(!OP_EhGrafoValido){ // assertiva
         throw //EXCEPTION GRAFO_INVALIDO
      }

      tpElementoGrafo *pTarefa = ED_EhIdExistente(idTarefa);

      if(pTarefa == NULL){ // assertiva
         throw //EXCEPTION ID_TAREFA_INVALIDO
      }

      if(!ED_EhReqExistente(pTarefa, idReq)){ // assertiva
         throw //EXCEPTION ID_REQ_INVALIDO
      }

      ED_ExcluirRequisito(pTarefa, idReq);

   }

   bool   OP_EhGrafoValido(pGrafo pCabeca){

      if(pCabeca == NULL){ // grafo inexistente
         return false;  
      }

      if(pCabeca->org == NULL){ // grafo sem tarefas
         return false;
      }

      return true;

   }

   void   OP_VerificarReq(pGrafo pCabeca){

      if(!OP_EhGrafoValido){ // assertiva
         throw //EXCEPTION GRAFO_INVALIDO
      }

      tpElementoGrafo *pTarefaTemp = pCabeca->org;
      tpElementoReq *pReqTemp;

      while(pTarefaTemp != NULL){  // varre todas as tarefas
         pReqTemp = pTarefaTemp->lstPreReq;

         while(pReqTemp != NULL){ // varre todos os requisitos

            if(ED_EhIdExistente(pCabeca, pReqTemp->id)){ // se requisito não tiver id válido
               OP_ExcluirRequisito(pCabeca, pTarefaTemp->id, pReqTemp->id) // exclui requisito com id inválido
            }
            
            pReqTemp = pReqTemp->prox;
         }

         pTarefaTemp = pTarefaTemp->prox;
      }

   }

   bool   OP_EhTarefaValida(pGrafo pCabeca, tpElementoGrafo * pTarefa){

      if(ED_EhIdExistente(pGrafo pCabeca, pTarefa->id) != NULL){
         return false;
      }

      if(pTarefa->tempoDuracao < 0){
         return false;
      }

      if(pTarefa->tempoInicMin < 0){
         return false;
      }

   } // função de apoio para as assertivas estruturais

   bool   OP_TemOrigem(pGrafo pCabeca){

      if(!OP_EhGrafoValido){ // assertiva
         throw //EXCEPTION GRAFO_INVALIDO
      }

      return ED_TemOrigem(pCabeca);
   
   }

   bool   OP_TemReqCircular(pGrafo pCabeca){

      if(!OP_EhGrafoValido){ // assertiva
         throw //EXCEPTION GRAFO_INVALIDO
      }

      tpElementoGrafo * pTarefaTemp;
      int numTarefas;

      pTarefaTemp = pCabeca->org;
      numTarefas  = 0;

      while(pTarefaTemp != NULL){ // descobre número de tarefas
         numTarefas++;
      }

      pTarefaTemp = pCabeca->org; // reinicia o ponteiro

      while(pTarefaTemp != NULL){   // varre todas tarefas

         if(ED_TemCamCircular(pCabeca, pTarefa, numTarefas, 0)){
            return true; // se tiver um caminho circular já mostra a existencia de requisitos circulares
         }

      }

      return false; // nada foi encontrado

   }