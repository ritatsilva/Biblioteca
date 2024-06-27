#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Freguesias.h"

#define Sucesso 0
#define Insucesso 1

int LFFreg(FL *F)
{
  //Codigo

  FILE *f = fopen("freguesias.txt", "r");


  if(f == NULL){
    printf("Erro ao abrir o arquivo freguesias.txt\n");
    return Insucesso;
  }

  while (!feof(f)) {
      Freg novoFreg;
      if (fscanf(f, "%s\t%[^\n]", novoFreg.id_freg, novoFreg.nome_freg) == 2) {
          F->NEL++;
          F->Freguesia = realloc(F->Freguesia, F->NEL * sizeof(Freg));
          F->Freguesia[F->NEL - 1] = novoFreg;
      }
  }

  fclose(f);

  return Sucesso;
  //Fim Codigo
}

int MostrarFreguesia(FL *F)
{
  //Codigo
  printf("Entrei na funcao %s\n", __FUNCTION__);

  if(!F) return Insucesso;
  if(!F->Freguesia) return Insucesso;

  for(int i = 0; i < F->NEL; i++){
    printf("%s - %s\n", F->Freguesia[i].id_freg,F->Freguesia[i].nome_freg);
  }
  printf("Numero de freguesias: [%d]\n", F->NEL);
  printf("Sai da funcao %s\n", __FUNCTION__);

  return Sucesso;
  //Fim Codigo
}

int VerificarIdf(char *idf){
  int tamanho = strlen(idf);
  if( tamanho == 0) return Insucesso;

  char distrito[3];
  char concelho[3];
  char freguesia[3];

  sscanf(idf, "%2s%2s%2s", distrito, concelho, freguesia);

  printf( "Distrito: %s\n", distrito);
  printf( "Concelho: %s\n", concelho);
  printf( "Freguesia: %s\n", freguesia);



  return Sucesso;
}
