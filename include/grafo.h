#include <cstdlib>
#include <cstdio>
#include <cstring>

/** Enumerations de retorno **/
typedef enum Retornos {
    Ok,
    Erro}  Retornos;

/** Typedefs elementos **/

typedef struct elementoReq{
	int id;
	struct elementoReq *prox;
}origens;

typedef struct elementoGrafo{
	int id;
	char nome[100] ;
	bool executado;
	int duracao;
	int inic_min;
	int num_pre_req;
	elementoReq *lista_pre_req;
	struct elementoGrafo *prox;
}elementoGrafo;

typedef struct head{
	elementoGrafo *inicio;
}head;

/** Funções **/

