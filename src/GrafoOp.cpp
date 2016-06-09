#include "GrafoOp.h"

/** Funções **/

/*****************************************************
*                                                    *
*  Fazer função para assertivas com throws internos  *
*  para ver se pCabeca é valido e se tem elementos   *
*          Assert também para idExistente            *
*                                                    *
******************************************************/


  void    OP_LerGrafo(pGrafo pCabeca, FILE *arq){
    if(arq == NULL){ //assertiva
      throw //EXCEPTION ARQ_INVALIDO
    }
    if(pCabeca == NULL){ //assertiva
      throw //EXCEPTION GRAFO_INVALIDO
    }
  }

  void    OP_SalvarGrafo(pGrafo pCabeca, FILE *arq){
    if(arq == NULL){ //assertiva
      throw //EXCEPTION ARQ_INVALIDO
    }
    if(pCabeca == NULL){ //assertiva
      throw //EXCEPTION GRAFO_INVALIDO
    }
    if(pCabeca->org == NULL){ //assertiva
      throw //EXCEPTION GRAFO_SEM_TAREFAS
    }
  }

  void    OP_DeletarGrafo(pGrafo pCabeca){

  }

  int     OP_CalcularTempMinExec(pGrafo pCabeca, unsigned int idTarefa){
    if(pCabeca == NULL){ //assertiva
      throw //EXCEPTION GRAFO_INVALIDO
    }
    if(pCabeca->org == NULL){ //assertiva
      throw //EXCEPTION GRAFO_SEM_TAREFAS
    }
  }

  void    OP_EditarId(pGrafo pCabeca, unsigned int idTarefa, unsigned int novoIdTarefa){
    if(pCabeca == NULL){ //assertiva
      throw //EXCEPTION GRAFO_INVALIDO
    }
    if(pCabeca->org == NULL){ //assertiva
      throw //EXCEPTION GRAFO_SEM_TAREFAS
    }

  } // verificar se novo id já não existe

  void    OP_EditarNome(pGrafo pCabeca, unsigned int idTarefa, char * novoNome){
    if(pCabeca == NULL){ //assertiva
      throw //EXCEPTION GRAFO_INVALIDO
    }
    if(pCabeca->org == NULL){ //assertiva
      throw //EXCEPTION GRAFO_SEM_TAREFAS
    }
  }

  void    OP_EditarEstadoExec(pGrafo pCabeca, unsigned int idTarefa, bool estadoExec){
    if(pCabeca == NULL){ //assertiva
      throw //EXCEPTION GRAFO_INVALIDO
    }
    if(pCabeca->org == NULL){ //assertiva
      throw //EXCEPTION GRAFO_SEM_TAREFAS
    }
  }

  void    OP_EditarDuracao(pGrafo pCabeca, unsigned int idTarefa, int novoTempoDuracao){
    if(pCabeca == NULL){ //assertiva
      throw //EXCEPTION GRAFO_INVALIDO
    }
    if(pCabeca->org == NULL){ //assertiva
      throw //EXCEPTION GRAFO_SEM_TAREFAS
    }
  }

  void    OP_EditarInicMin(pGrafo pCabeca, unsigned int idTarefa, int novoTempoInicMin){
    if(pCabeca == NULL){ //assertiva
      throw //EXCEPTION GRAFO_INVALIDO
    }
    if(pCabeca->org == NULL){ //assertiva
      throw //EXCEPTION GRAFO_SEM_TAREFAS
    }
  }

  void    OP_ExcluirTarefa(pGrafo pCabeca, unsigned int idTarefa){
    if(pCabeca == NULL){ //assertiva
      throw //EXCEPTION GRAFO_INVALIDO
    }
    if(pCabeca->org == NULL){ //assertiva
      throw //EXCEPTION GRAFO_SEM_TAREFAS
    }
  }

  void    OP_CriarTarefa(pGrafo pCabeca, tpElementoGrafo tarefa){

  } // controlar para não permitir ids repetidos

  void    OP_CriarRequisito(pGrafo pCabeca, unsigned int idTarefa, unsigned int idReq){
    if(pCabeca == NULL){ //assertiva
      throw //EXCEPTION GRAFO_INVALIDO
    }
    if(pCabeca->org == NULL){ //assertiva
      throw //EXCEPTION GRAFO_SEM_TAREFAS
    }

  }
   
  void    OP_ExcluirRequisito(pGrafo pCabeca, unsigned int idTarefa, unsigned int idReq){
    if(pCabeca == NULL){ //assertiva
      throw //EXCEPTION GRAFO_INVALIDO
    }
    if(pCabeca->org == NULL){ //assertiva
      throw //EXCEPTION GRAFO_SEM_TAREFAS
    }
  }

  bool   OP_EhIdExistente(pGrafo pCabeca, unsigned int id){

    if(pCabeca == NULL){
      return false; // id não existe
    }

    if(pCabeca->org == NULL){
      return false; // id não existe
    }

    tpElementoGrafo *temp = pCabeca->org->prox;

    while(temp != NULL){
      if(temp->id == id){
        return true; // id encontrado
      }
      temp = temp->prox;
    }

    if(pCabeca->org->prox == NULL){
      if(pCabeca->org->id == id){
        return true; // id encontrado
      }else{
        return false; // id não existe
      }
    }

    return false; // id não encontrado
  }