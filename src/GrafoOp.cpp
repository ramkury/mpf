#include "GrafoOp.h"

/* Funções */

   pGrafo OP_LerGrafo(char * szNomeArq){

      FILE * arq;
      arq = fopen(szNomeArq, "r");

      if(arq == NULL){ //assertiva
         throw TS_ExcecaoFlhFopen; //EXCEPTION FALHA_FOPEN_ARQ
      }

      int tempQtdPreReq;
      int i;
      unsigned int id;
      char szLinha[1000];
      char * szCampoAtual;
      char szSeparadores[] = "' \n";
      pGrafo pCabeca;
      tpElementoGrafo * pTarefa;
      pCabeca = ED_CriarGrafo();

      fgets(szLinha, 1000, arq);
      while(!feof(arq)){ // tenta ler id e já colocar na tarefa

         pTarefa = (tpElementoGrafo *)calloc(sizeof(tpElementoGrafo), 1);

         szCampoAtual = strtok(szLinha, szSeparadores);
         pTarefa->id  = atoi(szCampoAtual);
         szCampoAtual = strtok(NULL, "'");
         strcpy(pTarefa->szNome, szCampoAtual);
         szCampoAtual          = strtok(NULL, szSeparadores);
         pTarefa->executado    = (bool) atoi(szCampoAtual);
         szCampoAtual          = strtok(NULL, szSeparadores);
         pTarefa->tempoDuracao = atoi(szCampoAtual);
         szCampoAtual          = strtok(NULL, szSeparadores);
         pTarefa->tempoInicMin = atoi(szCampoAtual);
         szCampoAtual          = strtok(NULL, szSeparadores);
         tempQtdPreReq         = atoi(szCampoAtual);
         pTarefa->qtdPreReq    = 0;
         pTarefa->lstPreReq    = NULL;
         pTarefa->prox         = NULL;

         if(!OP_EhTarefaValida(pCabeca, pTarefa)){ // assertiva estrutural
            throw TS_ExcecaoTrfInval; //EXCEPTION TAREFA_INVALIDA
         }

         ED_CriarTarefa(pCabeca, pTarefa);

         for(i = 0; i < tempQtdPreReq; i++){

            szCampoAtual = strtok(NULL, szSeparadores);
            id           = atoi(szCampoAtual);
            ED_CriarRequisito(pTarefa, id);

         }

         fgets(szLinha, 1000, arq);

      }

      OP_VerificarReq(pCabeca);
      if(OP_TemReqCircular(pCabeca)){
         throw TS_ExcecaoReqCirc; //EXCEPTION REQUISITOS_CIRCULARES_GRAFO_INCONSISTENTE
      }

      return pCabeca;
  
   }

  void    OP_SalvarGrafo(pGrafo pCabeca, char * szNomeArq){

      FILE * arq = fopen(szNomeArq, "w");

      if(arq == NULL){ //assertiva
       throw TS_ExcecaoFlhFopen; //EXCEPTION FALHA_FOPEN_ARQ
      }

      if(!OP_EhGrafoValido(pCabeca)){ // assertiva
         throw TS_ExcecaoGrafoInval; //EXCEPTION GRAFO_INVALIDO
      }

      ED_GravarGrafo(pCabeca, arq);

  }

   void   OP_DeletarGrafo(pGrafo pCabeca){

      if(pCabeca == NULL){ //assertiva
         throw TS_ExcecaoGrafoInval; //EXCEPTION GRAFO_INEXISTENTE
      }

      ED_DestruirGrafo(pCabeca);

   }

   int    OP_CalcularTempoMinExec(pGrafo pCabeca, unsigned int idTarefa){

      if(!OP_EhGrafoValido(pCabeca)){ // assertiva de entrada
         throw TS_ExcecaoGrafoInval; //EXCEPTION GRAFO_INVALIDO
      }

      if(ED_EhIdExistente(pCabeca, idTarefa) == NULL){ // assertiva de entrada
         throw TS_ExcecaoTrfInval; //EXCEPTION TAREFA_INVALIDA
      }

         return ED_CalcularTempoMinExec(pCabeca, idTarefa);

   }

   void   OP_EditarId(pGrafo pCabeca, unsigned int idTarefa, unsigned int novoIdTarefa){

      if(!OP_EhGrafoValido(pCabeca)){ // assertiva
         throw TS_ExcecaoGrafoInval; //EXCEPTION GRAFO_INVALIDO
      }

      if(ED_EhIdExistente(pCabeca, novoIdTarefa) != NULL){
         throw TS_ExcecaoIdJahExiste; //EXCEPTION ID_JAH_EXISTE
      }

      tpElementoGrafo *pTarefa = ED_EhIdExistente(pCabeca, idTarefa);

      if(pTarefa == NULL){ // assertiva
         throw TS_ExcecaoIdTrfInval; //EXCEPTION ID_TAREFA_INVALIDO
      }

      ED_EditarId(pTarefa, novoIdTarefa);

   } // verificar se novo id já não existe

   void   OP_EditarNome(pGrafo pCabeca, unsigned int idTarefa, char * novoNome){

      if(!OP_EhGrafoValido(pCabeca)){ // assertiva
         throw TS_ExcecaoGrafoInval; //EXCEPTION GRAFO_INVALIDO
      }

      tpElementoGrafo *pTarefa;
      pTarefa = ED_EhIdExistente(pCabeca, idTarefa);

      if(pTarefa == NULL){ // assertiva
         throw TS_ExcecaoIdTrfInval; //EXCEPTION ID_TAREFA_INVALIDO
      }

      ED_EditarNome(pTarefa, novoNome);

   }

   void   OP_EditarEstadoExec(pGrafo pCabeca, unsigned int idTarefa, bool estadoExec){

      if(!OP_EhGrafoValido(pCabeca)){ // assertiva
         throw TS_ExcecaoGrafoInval; //EXCEPTION GRAFO_INVALIDO
      }

      tpElementoGrafo *pTarefa = ED_EhIdExistente(pCabeca, idTarefa);

      if(pTarefa == NULL){ // assertiva
         throw TS_ExcecaoIdTrfInval; //EXCEPTION ID_TAREFA_INVALIDO
      }

      ED_EditarEstadoExec(pTarefa, estadoExec);

   }

   void   OP_EditarDuracao(pGrafo pCabeca, unsigned int idTarefa, int novoTempoDuracao){

      if(!OP_EhGrafoValido(pCabeca)){ // assertiva
         throw TS_ExcecaoGrafoInval; //EXCEPTION GRAFO_INVALIDO
      }

      if(novoTempoDuracao < 0){ // assertiva
         throw TS_ExcecaoDurNgtv; //EXCEPTION DURACAO_NEGATIVA
      }

      tpElementoGrafo *pTarefa = ED_EhIdExistente(pCabeca, idTarefa);

      if(pTarefa == NULL){ // assertiva
         throw TS_ExcecaoIdTrfInval; //EXCEPTION ID_TAREFA_INVALIDO
      }

      ED_EditarDuracao(pTarefa, novoTempoDuracao);

   }

   void   OP_EditarInicMin(pGrafo pCabeca, unsigned int idTarefa, int novoTempoInicMin){

      if(!OP_EhGrafoValido(pCabeca)){ // assertiva
         throw TS_ExcecaoGrafoInval; //EXCEPTION GRAFO_INVALIDO
      }

      if(novoTempoInicMin < 0){ // assertiva
         throw TS_ExcecaoTmpNgtv; //EXCEPTION TEMPO_NEGATIVO
      }

      tpElementoGrafo *pTarefa = ED_EhIdExistente(pCabeca, idTarefa);

      if(pTarefa == NULL){ // assertiva
        throw TS_ExcecaoIdTrfInval; //EXCEPTION ID_TAREFA_INVALIDO
      }

      ED_EditarInicMin(pTarefa, novoTempoInicMin);

   }

   void   OP_ExcluirTarefa(pGrafo pCabeca, unsigned int idTarefa){

      if(!OP_EhGrafoValido(pCabeca)){ // assertiva
         throw TS_ExcecaoGrafoInval; //EXCEPTION GRAFO_INVALIDO
      }

      tpElementoGrafo *pTarefa = ED_EhIdExistente(pCabeca, idTarefa);

      if(pTarefa == NULL){ // assertiva
         throw TS_ExcecaoIdTrfInval; //EXCEPTION ID_TAREFA_INVALIDO
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
         throw TS_ExcecaoGrafoInval; //EXCEPTION GRAFO_INEXISTENTE
      }

      tpElementoGrafo * pTarefa;
      pTarefa   = (tpElementoGrafo *)calloc(1, sizeof(tpElementoGrafo));
      * pTarefa = tarefa;
      pTarefa->qtdPreReq = 0;
      pTarefa->lstPreReq = NULL;
      pTarefa->prox      = NULL;

      if(!OP_EhTarefaValida(pCabeca, pTarefa)){ //assertiva
         throw TS_ExcecaoTrfInval; //EXEPTION TAREFA_INVALIDA
      }

      ED_CriarTarefa(pCabeca, pTarefa);

   } 

   void   OP_CriarRequisito(pGrafo pCabeca, unsigned int idTarefa, unsigned int idReq){

      if(!OP_EhGrafoValido(pCabeca)){ // assertiva
         throw TS_ExcecaoGrafoInval; //EXCEPTION GRAFO_INVALIDO
      }

      if(ED_EhIdExistente(pCabeca, idReq) == NULL){ // assertiva
         throw TS_ExcecaoIdReqInval; //EXCEPTION ID_REQ_INVALIDO
      }

      tpElementoGrafo *pTarefa;
      int numTarefas;

      pTarefa    = pCabeca->org;
      numTarefas = 0;

      while(pTarefa != NULL){ // descobre número de tarefas
         pTarefa = pTarefa->prox;
         numTarefas++;
      }

      pTarefa    = ED_EhIdExistente(pCabeca, idTarefa);

      if(pTarefa == NULL){ // assertiva
         throw TS_ExcecaoIdTrfInval; //EXCEPTION ID_TAREFA_INVALIDO
      }

      ED_CriarRequisito(pTarefa, idReq);
   
      if(ED_TemCamCircular(pCabeca, pTarefa, numTarefas, 0)){ // assertiva
         OP_ExcluirRequisito(pCabeca, idTarefa, idReq);
         throw TS_ExcecaoReqCirc; //EXCEPTION CRIA_CAMINHO_CIRCULAR
      }

   }
   
   void   OP_ExcluirRequisito(pGrafo pCabeca, unsigned int idTarefa, unsigned int idReq){

      if(!OP_EhGrafoValido(pCabeca)){ // assertiva
         throw TS_ExcecaoGrafoInval; //EXCEPTION GRAFO_INVALIDO
      }

      tpElementoGrafo *pTarefa = ED_EhIdExistente(pCabeca, idTarefa);

      if(pTarefa == NULL){ // assertiva
         throw TS_ExcecaoIdTrfInval; //EXCEPTION ID_TAREFA_INVALIDO
      }

      if(!ED_EhReqExistente(pTarefa, idReq)){ // assertiva
         throw TS_ExcecaoIdReqInval; //EXCEPTION ID_REQ_INVALIDO
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

      if(!OP_EhGrafoValido(pCabeca)){ // assertiva
         throw TS_ExcecaoGrafoInval; //EXCEPTION GRAFO_INVALIDO
      }

      tpElementoGrafo *pTarefaTemp = pCabeca->org;
      tpElementoReq *pReqTemp;

      while(pTarefaTemp != NULL){  // varre todas as tarefas
         pReqTemp = pTarefaTemp->lstPreReq;

         while(pReqTemp != NULL){ // varre todos os requisitos

            if(!ED_EhIdExistente(pCabeca, pReqTemp->id)){ // se requisito não tiver id válido
               OP_ExcluirRequisito(pCabeca, pTarefaTemp->id, pReqTemp->id); // exclui requisito com id inválido
            }
            
            pReqTemp = pReqTemp->prox;
         }

         pTarefaTemp = pTarefaTemp->prox;
      }

   }

   bool   OP_EhTarefaValida(pGrafo pCabeca, tpElementoGrafo * pTarefa){

      if(ED_EhIdExistente(pCabeca, pTarefa->id) != NULL){
         return false;
      }

      if(pTarefa->tempoDuracao < 0){
         return false;
      }

      if(pTarefa->tempoInicMin < 0){
         return false;
      }

      return true;

   } // função de apoio para as assertivas estruturais

   bool   OP_TemOrigem(pGrafo pCabeca){

      if(!OP_EhGrafoValido(pCabeca)){ // assertiva
         throw TS_ExcecaoGrafoInval; //EXCEPTION GRAFO_INVALIDO
      }

      return ED_TemOrigem(pCabeca);
   
   }

   bool   OP_TemReqCircular(pGrafo pCabeca){

      if(!OP_EhGrafoValido(pCabeca)){ // assertiva
         throw TS_ExcecaoGrafoInval; //EXCEPTION GRAFO_INVALIDO
      }

      tpElementoGrafo * pTarefaTemp;
      int numTarefas;

      pTarefaTemp = pCabeca->org;
      numTarefas  = 0;

      while(pTarefaTemp != NULL){ // descobre número de tarefas
         pTarefaTemp = pTarefaTemp->prox;
         numTarefas++;
      }

      pTarefaTemp = pCabeca->org; // reinicia o ponteiro

      while(pTarefaTemp != NULL){   // varre todas tarefas

         if(ED_TemCamCircular(pCabeca, pTarefaTemp, numTarefas, 0)){
            return true; // se tiver um caminho circular já mostra a existencia de requisitos circulares
         }

         pTarefaTemp = pTarefaTemp->prox;

      }

      return false; // nada foi encontrado

   }
