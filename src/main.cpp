#include "GrafoOp.h"

int main(){

	pGrafo pCabeca;
	tpElementoGrafo * pTarefa;
	tpElementoReq * pReq;
	char leTeste[] = "../txt/RGrafo.txt";
	char wrTeste[] = "../txt/WGrafo.txt";

	pCabeca = OP_LerGrafo(leTeste);
	pTarefa = pCabeca->org;

	printf("ID   Nome   Estado de Execução   Duração   Inicio   Quantidade de requisitos   Lista de requisitos\n");

	while(pTarefa != NULL){

		pReq = pTarefa->lstPreReq;

		printf("%u '%s' %d %d %d %d", pTarefa->id, pTarefa->szNome, pTarefa->executado, pTarefa->tempoDuracao, pTarefa->tempoInicMin, pTarefa->qtdPreReq);
		
		while(pReq != NULL){

			printf(" %u", pReq->id);

			pReq = pReq->prox;

		}

		printf("\n");

		pTarefa = pTarefa->prox;
	}

	OP_SalvarGrafo(pCabeca, wrTeste);

	return 0;

}
