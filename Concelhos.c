#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Concelhos.h"
#define Sucesso 0
#define Insucesso 1

int LFConc(CL *C)
{
  //Codigo


  //FILE *f = fopen("concelhos.txt", "r");
  FILE *f = fopen("concelhos", "r");

  if(f == NULL){
    printf("Erro ao abrir o arquivo Concelhos.txt\n");
    return Insucesso;
  }

  while (!feof(f)) {
      Conc novoConcelho;
      if (fscanf(f, "%s\t%[^\n]", novoConcelho.id_Conc, novoConcelho.nome_conc) == 2) {
          C->NEL++;
          C->Concelhos = realloc(C->Concelhos, C->NEL * sizeof(Conc));
          C->Concelhos[C->NEL - 1] = novoConcelho;
      }
  }

  fclose(f);

  return Sucesso;
  //Fim Codigo
}

int MostrarConcelhos(CL *C)
{
  printf("Entrei na funcao %s\n", __FUNCTION__);
  //Codigo
  if(!C) return Insucesso;
  if(!C->Concelhos) return Insucesso;

  for(int i = 0; i < C->NEL; i++){
    printf("%s - %s\n", C->Concelhos[i].id_Conc,C->Concelhos[i].nome_conc);
  }
  printf("Numero de concelhos: [%d]\n", C->NEL);
  printf("Sai da funcao %s\n", __FUNCTION__);
  return Sucesso;
  //Fim Codigo
}

int VerConcelhos(CL *C, char *id){
  if(!C) return Insucesso;

  for(int i = 0; i < C->NEL; i++){
    if(strcmp(C->Concelhos[i].id_Conc, id) == 1){
      return Insucesso;
    }else{
      return Sucesso;
    }
  }
  return Sucesso;
}

int VerConcelhosPorNome(CL *C, char *nomeConcelho){
  if(!C) return Insucesso;

  for(int i = 0; i < C->NEL; i++){
    if(strcmp(C->Concelhos[i].nome_conc, nomeConcelho) == 1){
      return Insucesso;
    }else{
      return Sucesso;
    }
  }
  return Sucesso;
}

