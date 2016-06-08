#ifndef GRAFO-OP
#define GRAFO-OP

#include "GrafoED.h"

/*! \fn void OP_LerGrafo(pGrafo, File *)
    \brief A partir de um arquivo .txt gera o grafo do gerenciador.
    \param pGrafo: ponteiro para cabeça do grafo
    \param ponteiro para arquivo
*/
   void    OP_LerGrafo(pGrafo, FILE *);

/*! \fn void OP_SalvarGrafo(pGrafo, FILE *)
    \brief Escreve o grafo em um .txt.
    \param pGrafo: ponteiro para cabeça do grafo
    \param ponteiro para arquivo
*/
   void    OP_SalvarGrafo(pGrafo, FILE *);

/*! \fn void OP_DeletarGrafo(pGrafo, FILE *)
    \brief Deleta o grafo.
    \param pGrafo: ponteiro para cabeça do grafo
*/
   void    OP_DeletarGrafo(pGrafo);

/*! \fn int  OP_CalcularTempMinExec(pGrafo, unsigned int)
    \brief Calcula o menor tempo necessário para a tarefa ser executada.
    \param pGrafo: ponteiro para cabeça do grafo
    \param unsigned int: id da tarefa
*/
   int         OP_CalcularTempMinExec(pGrafo, unsigned int);

/*! \fn void  OP_EditarId(pGrafo, unsigned int, unsigned int)
    \brief Edita o Id da tarefa.
    \param pGrafo: ponteiro para cabeça do grafo
    \param unsigned int: antigo id da tarefa
    \param unsigned int: novo id da tarefa
*/
   void      OP_EditarId(pGrafo, unsigned int, unsigned int);	// verificar se novo id já não existe

/*! \fn void  OP_EditarNome(pGrafo, unsigned int, unsigned int)
    \brief Edita o nome da tarefa.
    \param pGrafo: ponteiro para cabeça do grafo
    \param unsigned int: id da tarefa
    \param string: novo nome da tarefa
*/
   void      OP_EditarNome(pGrafo, unsigned int, char *);

/*! \fn void  OP_EditarEstadoExec(pGrafo, unsigned int, unsigned int)
    \brief Edita o estado de execução da tarefa.
    \param pGrafo: ponteiro para cabeça do grafo
    \param unsigned int: id da tarefa
    \param bool: verdadeiro se executado, falso se não executado
*/
   void      OP_EditarEstadoExec(pGrafo, unsigned int, bool);

/*! \fn void  OP_EditarDuracao(pGrafo, unsigned int, unsigned int)
    \brief Edita o tempo de duração da execução da tarefa.
    \param pGrafo: ponteiro para cabeça do grafo
    \param unsigned int: id da tarefa
    \param int: novo tempo de execução da tarefa
*/
   void      OP_EditarDuracao(pGrafo, unsigned int, int);

/*! \fn void  OP_EditarInicMin(pGrafo, unsigned int, unsigned int)
    \brief Edita o tempo mínio para a tarefa estar passível de ser executada.
    \param pGrafo: ponteiro para cabeça do grafo
    \param unsigned int: id da tarefa
    \param int: novo tempo mínimo de espera
*/
   void      OP_EditarInicMin(pGrafo, unsigned int, int);

/*! \fn void  OP_ExcluirTarefa(pGrafo, unsigned int)
    \brief Exclui a tarefa.
    \param pGrafo: ponteiro para cabeça do grafo
    \param unsigned int: id da tarefa
*/
   void      OP_ExcluirTarefa(pGrafo, unsigned int);

/*! \fn void  OP_CriarTarefa(pGrafo, tpElementoGrafo)
    \brief Cria a tarefa.
    \param pGrafo: ponteiro para cabeça do grafo
    \param tpElementoGrafo: struct com as informações da tarefa
*/
   void      OP_CriarTarefa(pGrafo, tpElementoGrafo); // controlar para não permitir ids repetidos

/*! \fn void  OP_CriarRequisito(pGrafo, unsigned int, unsigned int)
    \brief Cria novos requisitos para tarefas.
    \param pGrafo: ponteiro para cabeça do grafo
    \param unsigned int: id da tarefa
    \param unsigned int: id do requisito a ser adicionado
*/
   void      OP_CriarRequisito(pGrafo, unsigned int, unsigned int);
   
/*! \fn void  OP_ExcluirRequisito(pGrafo, unsigned int, unsigned int)
    \brief Exclui requisito da tarefa.
    \param pGrafo: ponteiro para cabeça do grafo
    \param unsigned int: id da tarefa
    \param unsigned int: id do requisito a ser retirado
*/
   void      OP_ExcluirRequisito(pGrafo, unsigned int, unsigned int);

#endif
