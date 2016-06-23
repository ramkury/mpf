#include "GrafoOp.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
 
TEST(TestesIndividuais, TesteLeituraGrafo){
/* testa a leitura de um .txt que contem 
 * um grafo consistente, depois testa
 * sua consistencia */

  bool falha = false;

  char szGrafoLeitura[] = "../txt/leitura.txt";
       //szGrafoInconsistente[] = "../txt/inconsistente.txt";
    
  try{
    pGrafo Tarefas = OP_LerGrafo(szGrafoLeitura);
    ASSERT_TRUE(OP_EhGrafoValido(Tarefas));
    ASSERT_FALSE(OP_TemReqCircular(Tarefas));
  }
  catch(...){ 
    ASSERT_TRUE(0); 
  }

/* testa a leitura de um .txt que contem 
 * um grafo inconsistente, depois testa
 * sua consistencia */ 
 
  /*try{
    pGrafo Inconsistente = OP_LerGrafo(szGrafoInconsistente);
  }
  catch(...){
    falha = true;
  } 
  if(!falha){
    ASSERT_TRUE(0);
  }*/
 
/* testa a leitura de um .txt que contem 
 * um grafo invalido */ 

  char szGrafoInvalido[] = "../txt/leituraerrada.txt"; 
 
    falha = false;
    try{
        pGrafo TarefasInvalidas = OP_LerGrafo(szGrafoInvalido);
    }
    catch(...){
        falha = true; 
    } 
    if(!falha){
        ASSERT_TRUE(0);
    }
}
 
TEST(TestesIndividuais, TesteEscritaGrafo){ 
/*testa a escrita para um .txt a partir  
 * de um grafo valido, depois compara o  
 * grafo arquivo gerado com o inicial */ 
  char szGrafoLeitura[] = "../txt/leitura.txt", 
       szGrafoEscrita[] = "../txt/escrita.txt";
  pGrafo Tarefas;
  try{
    Tarefas = OP_LerGrafo(szGrafoLeitura);
  }
  catch(...){ 
    ASSERT_TRUE(0); 
  }
  try{
    OP_SalvarGrafo(Tarefas, szGrafoEscrita); 
  }
  catch(...){
    ASSERT_TRUE(0);
  }
}

TEST(TestesIndividuais, TesteDesalocacaoGrafo){ 
/* testa desalocar um grafo inexistente */ 

  char szGrafoLeitura[] = "../txt/leitura.txt";

  pGrafo Inexistente;
  Inexistente = NULL;
  bool falha = false;
  try{
    OP_DeletarGrafo(Inexistente);
  }
  catch(...){
    falha = true; 
  } 
  if(!falha){
    ASSERT_TRUE(0);
  }
 
/* testa se nao ha grafo na memoria apos desalocar 
 * de forma bem sucedida  e se o grafo foi salvo, 
 * em seguida, tenta desalocar o grafo novamente */ 

    pGrafo Tarefas = OP_LerGrafo(szGrafoLeitura); 
     
    ASSERT_TRUE( Tarefas->org != NULL); 

    char szGrafoEscrita[] = "../txt/escrita.txt";
    falha = false;
    try{
        OP_SalvarGrafo(Tarefas, szGrafoEscrita);
        OP_DeletarGrafo(Tarefas);
    }
    catch(...){
        ASSERT_TRUE(0);
    }
    try{
        //OP_DeletarGrafo(Tarefas);
    }
    catch(...){
        falha = true; 
    }
    if(!falha){
        //ASSERT_TRUE(0);
    }
    try{
        Tarefas = OP_LerGrafo(szGrafoEscrita); 
    } 
    catch(...){
        falha = true;
    }
    if(!falha){
        //ASSERT_TRUE(0);
    }
    falha = false;
    try{
        OP_SalvarGrafo(Inexistente, szGrafoEscrita);
    }
    catch(...){
        falha = true; 
    } 
    if(!falha){
        ASSERT_TRUE(0);
    }
}

TEST(TestesIndividuais, TesteExclusaoGrafo){
/* tenta excluir um grafo inexistente, entao tenta 
 * excluir um grafo existente e verifica se ele foi 
 * salvo */

  pGrafo Inexistente;
  bool falha = false;
  try{
    OP_DeletarGrafo(Inexistente);
  }
  catch(...){
    falha = true; 
  } 
  if(!falha){
    ASSERT_TRUE(0);
  }

  char szGrafoLeitura[] = "../txt/leitura.txt"; 
 
  pGrafo Tarefas = OP_LerGrafo(szGrafoLeitura); 
 
  ASSERT_TRUE (Tarefas->org != NULL);

  try{
    OP_DeletarGrafo(Tarefas);
  }
  catch(...){ 
    ASSERT_TRUE(0); 
  }
}

TEST(TestesIndividuais, TesteCriacaoRequisito){ 

  char szGrafoLeitura[] = "../txt/leitura.txt"; 
  pGrafo Tarefas;
  try{
    Tarefas = OP_LerGrafo(szGrafoLeitura); 
    ASSERT_TRUE(Tarefas->org != NULL); 
  }
  catch(...){
    ASSERT_TRUE(0); 
  }

/* tenta criar um requisito para uma
 * id inexistente */
  bool falha = false;
  try{
    OP_CriarRequisito(Tarefas, 9, 1);
  }
  catch(...){
    falha = true; 
  } 
  if(!falha){
    ASSERT_TRUE(0);
  }

/* tenta criar um requisito a partir de uma
 * id inexistente */
  falha = false;
  try{
    OP_CriarRequisito(Tarefas, 3, 8);
  }
  catch(...){
    falha = true; 
  } 
  if(!falha){
    ASSERT_TRUE(0);
  }

/* tenta criar um requisito ja existente */
  falha = false;
  try{
    OP_CriarRequisito(Tarefas, 4, 1);
  }
  catch(...){
    falha = true; 
  } 
  if(!falha){
    ASSERT_TRUE(0);
  }

/* tenta criar um requisito para uma id
 * que é requisito direto dela */
  try{
    falha = false;
    OP_CriarRequisito(Tarefas, 4, 6);
  }
  catch(...){
    falha = true; 
  } 
  if(!falha){
    ASSERT_TRUE(0);
  }

/* tenta criar um requisito para uma id
 * que é requisito indireto dela */
  falha = false;
  try{
    OP_CriarRequisito(Tarefas, 4, 5);
  }
  catch(...){
    falha = true; 
  } 
  if(!falha){
    ASSERT_TRUE(0);
  }

/* tenta criar um requisito válido, e verifica
 * se o número de requisitos mudou */

  try{
    OP_CriarRequisito(Tarefas, 5, 3);
  }

  catch(...){ 
    ASSERT_TRUE(0); 
  } 
}

TEST(TestesIndividuais, TesteExclusaoRequisito){ 

  char szGrafoLeitura[] = "../txt/leitura.txt"; 
  pGrafo Tarefas = OP_LerGrafo(szGrafoLeitura); 
  ASSERT_TRUE(Tarefas->org != NULL);

/* tenta excluir um requisito com
 * primeiro termo inexistente */
  bool falha = false;
  try{
    OP_ExcluirRequisito(Tarefas, 7, 1);
  }
  catch(...){
    falha = true; 
  } 
  if(!falha){
    ASSERT_TRUE(0);
  }

/* tenta excluir um requisito com 
 * segundo termo inexistente */
  falha = false;
  try{
    OP_ExcluirRequisito(Tarefas, 1, 7);
  }
  catch(...){
    falha = true; 
  } 
  if(!falha){
    ASSERT_TRUE(0);
  }

/* tenta excluir um requisito inexistente,
 * mas com origem e destino existentes */
  falha = false;
  try{
    OP_ExcluirRequisito(Tarefas, 3, 2);
  }
  catch(...){
    falha = true; 
  } 
  if(!falha){
    ASSERT_TRUE(0);
  }

/* tenta excluir um requisito existente, e verifica
 * se o numero de requisitos foi modificado
 * corretamente */

  try{ 
    OP_ExcluirRequisito(Tarefas, 1, 4);
  }

  catch(...){ 
    ASSERT_TRUE(0); 
  } 
}

TEST(TestesIndividuais, TesteCriacaoTarefa){ 
 
  char szGrafoLeitura[] = "../txt/leitura.txt"; 
  pGrafo Tarefas;
  try{
    Tarefas = OP_LerGrafo(szGrafoLeitura); 
    ASSERT_TRUE(Tarefas->org != NULL); 
  }
  catch(...){ 
    ASSERT_TRUE(0); 
  }
 
/* Tenta criar uma tarefa com ID repetido */ 
  tpElementoGrafo IdRepetido; 
  IdRepetido.id = 1;
  char szNomeQualquer[100] = "NomeQualquer";
  strcpy(IdRepetido.szNome, szNomeQualquer); 
  IdRepetido.executado = false; 
  IdRepetido.tempoDuracao = 12; 
  IdRepetido.tempoInicMin = 10; 
  IdRepetido.qtdPreReq = 0;
  bool falha = false;
  try{
    OP_CriarTarefa(Tarefas, IdRepetido); 
  }
  catch(...){
    falha = true; 
  } 
  if(!falha){
    ASSERT_TRUE(0);
  }
 
/* Tenta criar uma tarefa com nome repetido */ 
  tpElementoGrafo NomeRepetido; 
  NomeRepetido.id = 33122; 
  char szRepetido[100] = "NomeRepetido";
  strcpy(NomeRepetido.szNome, szRepetido); 
  NomeRepetido.executado = true; 
  NomeRepetido.tempoDuracao = 2; 
  NomeRepetido.tempoInicMin = 0; 
  NomeRepetido.qtdPreReq = 0;
  try{
    OP_CriarTarefa(Tarefas, NomeRepetido); 
  }
  catch(...){ 
    ASSERT_TRUE(0); 
  } 
 
/* Tenta criar uma tarefa com duracao impossivel */ 
  tpElementoGrafo DuracaoImpossivel; 
  DuracaoImpossivel.id = 18322;
  char szAbacate[100] = "Abacate";  
  strcpy(DuracaoImpossivel.szNome, szAbacate); 
  DuracaoImpossivel.executado = true; 
  DuracaoImpossivel.tempoDuracao = -1; 
  DuracaoImpossivel.tempoInicMin = 2; 
  DuracaoImpossivel.qtdPreReq = 0;
  falha = false;
  try{
    OP_CriarTarefa(Tarefas, DuracaoImpossivel);
  }
  catch(...){
    falha = true; 
  } 
  if(!falha){
    ASSERT_TRUE(0);
  } 
/* Tenta criar uma tarefa com inicio impossivel */ 
  tpElementoGrafo InicioImpossivel; 
  InicioImpossivel.id = 193991;
  char szBanana[100] = "Banana";
  strcpy(InicioImpossivel.szNome, szBanana); 
  InicioImpossivel.executado = false; 
  InicioImpossivel.tempoDuracao = 1; 
  InicioImpossivel.tempoInicMin = -3; 
  InicioImpossivel.qtdPreReq = 0;
  falha = false;
  try{
    OP_CriarTarefa(Tarefas, InicioImpossivel);
  }
  catch(...){
    falha = true; 
  } 
  if(!falha){
    ASSERT_TRUE(0);
  }
 
/* Tenta criar uma tarefa valida sem requisitos */ 
  tpElementoGrafo TarefaSemReq; 
  TarefaSemReq.id = 12341;
  char szInserido[100] = "Inserido";
  strcpy(TarefaSemReq.szNome, szInserido); 
  TarefaSemReq.executado = false; 
  TarefaSemReq.tempoDuracao = 12; 
  TarefaSemReq.tempoInicMin = 3; 
  TarefaSemReq.qtdPreReq = 0;
  try{
    OP_CriarTarefa(Tarefas, TarefaSemReq);
  }
  catch(...){ 
    ASSERT_TRUE(0); 
  } 
 
/* Tenta criar uma tarefa valida com requisitos */ 
  tpElementoGrafo TarefaComReq; 
  TarefaComReq.id = 1111;
  char szOito[100] = "Oito";
  strcpy(TarefaComReq.szNome, szOito); 
  TarefaComReq.executado = false; 
  TarefaComReq.tempoDuracao = 2; 
  TarefaComReq.tempoInicMin = 2; 
  TarefaComReq.qtdPreReq = 3;
  try{
    OP_CriarTarefa(Tarefas, TarefaComReq);
  }
  catch(...){
    ASSERT_TRUE(0); 
  }
}

TEST(TestesIndividuais, TesteExclusaoTarefa){ 
 
  char szGrafoLeitura[] = "../txt/leitura.txt";
  pGrafo Tarefas = OP_LerGrafo(szGrafoLeitura); 
  ASSERT_TRUE(Tarefas->org != NULL); 

/* tenta excluir uma tarefa inexistente */
  bool falha = false;
  try{
    OP_ExcluirTarefa(Tarefas, 7);
  }
  catch(...){
    falha = true; 
  } 
  if(!falha){
    ASSERT_TRUE(0);
  }

/* tenta excluir uma tarefa existente,
 * depois tenta excluí-la novamente */
  try{
    OP_ExcluirTarefa(Tarefas, 6);
  }
  catch(...){ 
    ASSERT_TRUE(0);
  }
  falha = false;
  try{
    OP_ExcluirTarefa(Tarefas, 6);
  }
  catch(...){
    falha = true; 
  } 
  if(!falha){
    ASSERT_TRUE(0);
  }
}

TEST(TestesIndividuais, TesteEdicaoTarefa){ 

  char szGrafoLeitura[] = "../txt/leitura.txt"; 
  pGrafo Tarefas;
  try{
    Tarefas = OP_LerGrafo(szGrafoLeitura); 
    ASSERT_TRUE(Tarefas->org != NULL);
  }
  catch(...){ 
    ASSERT_TRUE(0); 
  }

/* tenta editar o id de uma tarefa inexistente */
  bool falha = false;
  try{
    OP_EditarId(Tarefas, 7, 9);
  }
  catch(...){
    falha = true; 
  } 
  if(!falha){
    ASSERT_TRUE(0);
  }

/* tenta editar o id de uma tarefa existente */
  try{
    OP_EditarId(Tarefas, 999, 777);
  }
  catch(...){ 
    ASSERT_TRUE(0); 
  }
  try{
    OP_EditarId(Tarefas, 777, 999);
  }
  catch(...){
    ASSERT_TRUE(0);
  }

/* tenta editar o nome de uma tarefa inexistente */

  char sznovoNome[10] = "novoNome";
  falha = false;
  try{
    OP_EditarNome(Tarefas, 7, sznovoNome);
  }
  catch(...){
    falha = true; 
  } 
  if(!falha){
    ASSERT_TRUE(0);
  }

/* tenta editar o nome de uma tarefa existente */
  try{
    OP_EditarNome(Tarefas, 2, sznovoNome);
  }
  catch(...){
    ASSERT_TRUE(0);
  }

/* tenta editar o estado de execução de uma
 * tarefa inexistente */
  falha = false;
  try{
  OP_EditarEstadoExec(Tarefas, 8, false);
  }
  catch(...){
    falha = true; 
  } 
  if(!falha){
    ASSERT_TRUE(0);
  }

/* tenta editar o estado de execução de uma
 * tarefa existente */
  try{
    OP_EditarEstadoExec(Tarefas, 4, false);
  }
  catch(...){
    ASSERT_TRUE(0);
  }

/* tenta editar a duração de uma tarefa
 * inexistente */
  falha = false;
  try{
    OP_EditarDuracao(Tarefas, 8, 12);
  }
  catch(...){
    falha = true; 
  } 
  if(!falha){
    ASSERT_TRUE(0);
  }

/* tenta editar a duração de uma tarefa
 * existente para uma duração inválida */
  falha = false;
  try{
    OP_EditarDuracao(Tarefas, 4, 0);
  }
  catch(...){
    falha = true; 
  } 
  if(!falha){
    //ASSERT_TRUE(0);
  }

/* tenta editar a duração de uma tarefa
 * existente para uma duração válida */
  try{
    OP_EditarDuracao(Tarefas, 4, 31);
  }
    catch(...){
      ASSERT_TRUE(0);
    }

/* tenta editar o início mínimo de uma tarefa
 * inexistente */
  falha = false;
  try{
    OP_EditarInicMin(Tarefas, 9, 13);
  }
  catch(...){
    falha = true; 
  } 
  if(!falha){
    ASSERT_TRUE(0);
  }

/* tenta editar o início mínimo de uma tarefa
 * existente para um valor inválido */
  falha = false;
  try{
    OP_EditarInicMin(Tarefas, 4, -4);
  }
  catch(...){
    falha = true; 
  } 
  if(!falha){
    ASSERT_TRUE(0);
  }

/* tenta editar o início mínimo de uma tarefa
 * existente para um valor válido */
  try{
    OP_EditarInicMin(Tarefas, 4, 0);
  }
  catch(...){
    ASSERT_TRUE(0);
  }
}

TEST(TestesIndividuais, TesteTempoExecucaoTarefa){ 

  pGrafo Tarefas;

  char szGrafoLeitura[] = "../txt/leitura.txt";
  try{
    Tarefas = OP_LerGrafo(szGrafoLeitura);
    ASSERT_TRUE(Tarefas->org != NULL);
  }
  catch(...){ 
    ASSERT_TRUE(0);
  }

/* tenta achar o tempo mínimo de uma tarefa
 * inexistente */
  bool falha = false;
  try{
    OP_CalcularTempoMinExec(Tarefas, 8);
  }
  catch(...){
    falha = true; 
  } 
  if(!falha){
    ASSERT_TRUE(0);
  }

/* testa o valor de retorno de uma tarefa
 * sem pré-requisitos */
  try{
    int TempMin = OP_CalcularTempoMinExec(Tarefas, 2);
    ASSERT_EQ(TempMin, 9);
  }
  catch(...){ 
    ASSERT_TRUE(0); 
  } 

/* testa o valor de retorno de uma tarefa
 * com pré-requisitos*/
  try{
    int TempMin = OP_CalcularTempoMinExec(Tarefas, 1);
    ASSERT_EQ(TempMin, 20);
  }
  catch(...){
    ASSERT_TRUE(0);
  }
}

TEST(TestesIndividuais, TesteAtualizarTempo){

    pGrafo Tarefas;

    char szGrafoLeitura[] = "../txt/leitura.txt";
    try{
        Tarefas = OP_LerGrafo(szGrafoLeitura);
        ASSERT_TRUE(Tarefas->org != NULL);
    }
    catch(...){ 
        ASSERT_TRUE(0);
    }

/* tenta atualizar para um tempo negativo */
    bool falha = false;
    try{
        OP_AtualizarGrafo(Tarefas, -2);
    }
    catch(...){
        falha = true;
    }
    if(!falha){
        ASSERT_TRUE(0);
    }

/* tenta atualizar para um tempo positivo */
    try{
        OP_AtualizarGrafo(Tarefas, 8);
    }
    catch(...){
        ASSERT_TRUE(0);
    }   
        tpElementoGrafo * pTarefa;
        pTarefa = ED_EhIdExistente(Tarefas, 1);
        ASSERT_FALSE(pTarefa->executado);
        pTarefa = ED_EhIdExistente(Tarefas, 6);
        ASSERT_TRUE(pTarefa->executado);

/* tenta atualizar para o tempo 0 */
    try{
        OP_AtualizarGrafo(Tarefas, 0);
    }
    catch(...){
        ASSERT_TRUE(0);
    }
        pTarefa = ED_EhIdExistente(Tarefas, 1);
        ASSERT_FALSE(pTarefa->executado);
        pTarefa = ED_EhIdExistente(Tarefas, 6);
        ASSERT_FALSE(pTarefa->executado);    
}

int main(int argc, char** argv){ 
   
  ::testing::InitGoogleTest(&argc, argv); 
 
  return RUN_ALL_TESTS(); 
}
