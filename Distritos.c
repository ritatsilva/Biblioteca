#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Distritos.h"
#define Sucesso 0
#define Insucesso 1

int LFDist(DL *D)
{
  //Codigo

  FILE *f = fopen("distritos.txt", "r");

  if(f == NULL){
    printf("Erro ao abrir o arquivo distritos.txt\n");
    return Insucesso;
  }

  while (!feof(f)) {
      Dist novoDist;
      if (fscanf(f, "%s\t%[^\n]", novoDist.id_dist, novoDist.nome_dist) == 2) {
          D->NEL++;
          D->Distritos = realloc(D->Distritos, D->NEL * sizeof(Dist));
          D->Distritos[D->NEL - 1] = novoDist;
      }
  }

  fclose(f);

  return Sucesso;
  //Fim Codigo
}

int MostrarDistritos(DL *D)
{
   //Codigo
  printf("Entrei na funcao %s\n", __FUNCTION__);

  if(!D) return Insucesso;
  if(!D->Distritos) return Insucesso;

  for(int i = 0; i < D->NEL; i++){
    printf("%s - %s\n", D->Distritos[i].id_dist,D->Distritos[i].nome_dist);
  }
  printf("Numero de distritos: [%d]\n", D->NEL);
  printf("Sai da funcao %s\n", __FUNCTION__);

  return Sucesso;
  //Fim Codigo
}

int VerificarIdd(DL *D, char *idd){
  if(!D) return Insucesso;

  for(int i = 0; i < D->NEL; i++){
    if(strcmp(D->Distritos[i].id_dist, idd) == 1){
      return Insucesso;
    }else{
      return Sucesso;
    }
  }
  return Sucesso;
}
