#include "GrafoOp.h"

/** Funções **/

  void    OP_LerGrafo(pGrafo pCabeca, FILE *arq){

    if(arq == NULL){ //assertiva
      throw //EXCEPTION ARQ_INVALIDO
    }

    if(pCabeca == NULL){ //assertiva
      throw //EXCEPTION GRAFO_INEXISTENTE
    }






    OP_VerificarReq(pCabeca);

  }

  void    OP_SalvarGrafo(pGrafo pCabeca, FILE *arq){

    if(arq == NULL){ //assertiva
      throw //EXCEPTION ARQ_INVALIDO
    }

    if(!OP_EhGrafoValido){ // assertiva
      throw //EXCEPTION GRAFO_INVALIDO
    }

  }

  void    OP_DeletarGrafo(pGrafo pCabeca){

    if(pCabeca == NULL){ //assertiva
      throw //EXCEPTION GRAFO_INEXISTENTE
    }

    ED_DestruirGrafo(pCabeca);

  }

  int     OP_CalcularTempMinExec(pGrafo pCabeca, unsigned int idTarefa){

    if(!OP_EhGrafoValido){ // assertiva
      throw //EXCEPTION GRAFO_INVALIDO
    }

  }

  void    OP_EditarId(pGrafo pCabeca, unsigned int idTarefa, unsigned int novoIdTarefa){

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

  void    OP_EditarNome(pGrafo pCabeca, unsigned int idTarefa, char * novoNome){

    if(!OP_EhGrafoValido){ // assertiva
      throw //EXCEPTION GRAFO_INVALIDO
    }

    tpElementoGrafo *pTarefa = ED_EhIdExistente(idTarefa);

    if(pTarefa == NULL){ // assertiva
        throw //EXCEPTION ID_TAREFA_INVALIDO
    }

    ED_EditarNome(pTarefa, novoNome);

  }

  void    OP_EditarEstadoExec(pGrafo pCabeca, unsigned int idTarefa, bool estadoExec){

    if(!OP_EhGrafoValido){ // assertiva
      throw //EXCEPTION GRAFO_INVALIDO
    }

    tpElementoGrafo *pTarefa = ED_EhIdExistente(idTarefa);

    if(pTarefa == NULL){ // assertiva
        throw //EXCEPTION ID_TAREFA_INVALIDO
    }

    ED_EditarEstadoExec(pTarefa, estadoExec);

  }

  void    OP_EditarDuracao(pGrafo pCabeca, unsigned int idTarefa, int novoTempoDuracao){

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

  void    OP_EditarInicMin(pGrafo pCabeca, unsigned int idTarefa, int novoTempoInicMin){

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

  void    OP_ExcluirTarefa(pGrafo pCabeca, unsigned int idTarefa){

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

  void    OP_CriarTarefa(pGrafo pCabeca, tpElementoGrafo tarefa){

    if(pCabeca == NULL){ //assertiva
      throw //EXCEPTION GRAFO_INEXISTENTE
    }

    if(ED_EhIdExistente(tarefa->id) != NULL){ // assertiva
      throw //EXCEPTION ID_JAH_EXISTE
    }

    ED_CriarTarefa(pCabeca, tarefa);

  } 

  void    OP_CriarRequisito(pGrafo pCabeca, unsigned int idTarefa, unsigned int idReq){

    if(!OP_EhGrafoValido){ // assertiva
      throw //EXCEPTION GRAFO_INVALIDO
    }

    if(ED_EhIdExistente(idReq) == NULL){ // assertiva
      throw //EXCEPTION ID_REQ_INVALIDO
    }

    tpElementoGrafo *pTarefa = ED_EhIdExistente(idTarefa);

    if(pTarefa == NULL){ // assertiva
      throw //EXCEPTION ID_TAREFA_INVALIDO
    }

    ED_CriarRequisito(pTarefa, idReq);

  }
   
  void    OP_ExcluirRequisito(pGrafo pCabeca, unsigned int idTarefa, unsigned int idReq){

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

  void     OP_VerificarReq(pGrafo pCabeca){

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