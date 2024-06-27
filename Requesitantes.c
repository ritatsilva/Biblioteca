#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Requesitantes.h"
#include "Freguesias.h"
#include "Distritos.h"
#include "Concelhos.h"

#define Sucesso 0
#define Insucesso 1
#define EXISTE 2

void EscreverListaRqsNoFile(RL *R){
  if(!R) return;
  if(!R->Inicio) return;

  FILE *f = fopen("requesitantes.txt", "w");

  NO_Req *no = R->Inicio;

  while(no){
    fprintf(f, "%s\t%s\t%d-%d-%d\t%s\n",no->Info->id_requesitante, no->Info->nome_req, no->Info->data_nasc.day, no->Info->data_nasc.month, no->Info->data_nasc.year,no->Info->id_freguesia);
    no = no->Prox;
  }

  fclose(f);
}

Req *CriarReq(char *id,char *txt, int day, int month, int year, char *ifd){

  Req *R = (Req *)malloc(sizeof(Req));

  strcpy(R->id_requesitante, id);
  strcpy(R->nome_req, txt);
  R->data_nasc.day = day;
  R->data_nasc.month = month;
  R->data_nasc.year = year;
  strcpy(R->id_freguesia, ifd);
  R->nRecoes = 0;
  return R;
}

RL *CriarRL(){

  RL *R = (RL *)malloc(sizeof(RL));
  R->NEL = 0;
  R->Inicio = NULL;
  return R;
}

void DestruirListaReqs(RL *R){
  if(!R) return;

  NO_Req *no = R->Inicio;
  while(no){
    free(no->Info);
    no = no->Prox;
  }
  free(R);
}

date CriarData(int day, int month, int year){
  date d;

  d.day = day;
  d.month = month;
  d.year = year;

  return d;
}

int LFReq(CL *C,DL *D,FL *F,RL *R)
{

  FILE *File = fopen("requesitantes.txt", "r");

  if(F == NULL){
    return Insucesso;
  }

  char NOME[101];
  char ID[11];
  char DATA[11];
  char IDF[7];
  date data;


  while(!feof(File)){

    fscanf(File, "%s\t%[^\t]\t%s\t%s\n", ID, NOME, DATA, IDF);

    int VerCod = CheckID(ID);

    if(VerCod == Insucesso){
      EscreverReqLogs(ID, NOME, DATA, IDF);
    }else{
      data = SepararData(DATA);
      if(data.day == 0){
        EscreverReqLogs(ID, NOME, DATA, IDF);
      }else{
        int dt = CheckData(data);
        if(dt == Insucesso){
          EscreverReqLogs(ID, NOME, DATA, IDF);
        }else{
          int VerIdf = CheckIdf(F, IDF);//Funcao para ver se a fregueisa existe no ficheiro das freguesias
          if(VerIdf == Insucesso){
            EscreverReqLogs(ID, NOME, DATA, IDF);


          }else{
            char distrito[3];
            char concelho[3];
            char freguesia[3];

            sscanf(IDF, "%2s%2s%2s", distrito, concelho, freguesia);


            int VerDistrito = VerificarIdd(D, distrito);//Funcao para ver se o distritos existe no ficheiro dos distritos
            if(VerDistrito == Insucesso){
              EscreverReqLogs(ID, NOME, DATA, IDF);
            }else{
              char concelho2[5];
              sscanf(IDF, "%4s%2s",concelho2, freguesia);
              int VerConcelho = VerConcelhos(C, concelho2);//Funcao para ver se o concelho existe no ficheiro dos concelhod
              if(VerConcelho == Insucesso){
                EscreverReqLogs(ID, NOME, DATA, IDF);
              }
              else{
                Req *r = CriarReq(ID, NOME, data.day, data.month, data.year, IDF);
                AdicionarReq(R, r);
              }
            }
          }
        }
      }
    }
  }

  fclose(File);


  return Sucesso;
}

int AdicionarReq(RL *lista_req,Req *req){
  //Codigo
  if(!req) {
    printf("Nao existe req");
    return Insucesso;
  }
  NO_Req *novo = (NO_Req *)malloc(sizeof(NO_Req));
  novo->Info = req;
  novo->Prox = lista_req->Inicio;
  lista_req->Inicio = novo;
  lista_req->NEL++;

  return Sucesso;
}

int CheckData(date data){

  int calendario[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  int calendarioBisexto[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if(data.year > 2024 || data.month > 12){
    return Insucesso;
  }else{
    int ano = data.year % 100;
    if(ano % 4 != 0){
      if(data.day > calendario[data.month - 1]){
        return Insucesso;
      }
    }else if(ano % 4 == 0){
      if(data.day > calendarioBisexto[data.month - 1]){
        return Insucesso;
      }
    }
  }

  return Sucesso;
}

date SepararData(char *data){
  date d;
  date d2 = {0};

  if(sscanf(data, "%d-%d-%d", &d.day, &d.month, &d.year) == 3){
    return d;
  }else{
    return d2;
  }
}

void MostrarListaReq(RL *R)
{
  if(!R) return;
  NO_Req *Req = R->Inicio;

  while(Req)
  {
    MostrarRequesitantes(Req->Info);
    Req = Req->Prox;
  }
}

void MostrarRequesitantes(Req *requesitante){
  if(!requesitante) return;
  printf("\n///////////////////////////\n");
  printf( "ID: %s\n", requesitante->id_requesitante);
  printf( "Nome: %s\n", requesitante->nome_req);
  printf( "Data de nascimento: %d/%d/%d\n", requesitante->data_nasc.day, requesitante->data_nasc.month, requesitante->data_nasc.year);
  printf( "ID da freguesia: %s\n", requesitante->id_freguesia);
  printf("Numero requesicoes: %d\n", requesitante->nRecoes);
  printf("\n///////////////////////////\n");
}

int CheckID(char *cod){
  //Codigo
  int tamanho = strlen(cod);
  int soma = 0;
  int cod2 = atoi(cod);

  if(tamanho != 9){
    return Insucesso;
  }else if(tamanho == 9){
    for(int i = 0; i < tamanho; i++){
       soma += cod2 % 10;
       cod2 = cod2 / 10;
    }
    if(soma % 10 == 0){
      return Sucesso;
    }else{
      return Insucesso;
    }
  }
  //Fim Codigo
  return Sucesso;

}

int EscreverReqLogs(char *id,char *txt, char *data, char *idf){
  //Codigo

  FILE *F = fopen("Logs.txt","a");

  fprintf(F, "%s\t%s\t%s\t%s\n",id, txt, data, idf);

  fclose(F);

  return Sucesso;
}

int CheckIdf(FL *F, char *idf){
  if(!F) return Insucesso;

  for(int i = 0; i < F->NEL; i++){
    if(strcmp(F->Freguesia[i].id_freg, idf) == 1){
      return Insucesso;
    }else{
      return Sucesso;
    }
  }
  return Sucesso;
}

Req *pesquisarReq(char *nome, RL *R){
  if(!R) return NULL;
  if(!R->Inicio) return NULL;

  NO_Req *Req = R->Inicio;
  while(Req){
    if(strcmp(Req->Info->nome_req, nome) == 0){
      return Req->Info;
    }
    Req = Req->Prox;
  }

  return NULL;
}

void VerIdadeMaxima(RL *R){
  if(!R) return;
  if(!R->Inicio) return;

  NO_Req *Req = R->Inicio;

  int max = 2024 - Req->Info->data_nasc.year;

  while(Req){
    if((2024 - Req->Info->data_nasc.year) >max){
      max = 2024 - Req->Info->data_nasc.year;
    }
    Req = Req->Prox;
  }
  printf("A pessoa mais velha tem %d anos", max);
}

void VerMediaIdades(RL *R){
  if(!R) return;
  if(!R->Inicio) return;

  NO_Req *Req = R->Inicio;

  float soma = 0.0;
  while(Req){
    soma += 2024 - Req->Info->data_nasc.year;
    Req = Req->Prox;
  }
  float media = soma / R->NEL;

  printf("A media das idades e: %.2f", media);
}

void IdadesMaiorQue(int idade,RL *R){
  if(!R) return;
  if(!R->Inicio) return;

  NO_Req *Req = R->Inicio;

  int count = 0;

  while(Req){
    if((2024 - Req->Info->data_nasc.year) > idade){
      count++;
    }
    Req = Req->Prox;
  }
  printf("Existem %d pessoas com mais de %d anos", count, idade);
}

void VerNumReqIdade(RL *R){
  if(!R) return;
  if(!R->Inicio) return;

  int idadesDif[R->NEL];
  int numeroIdades[R->NEL];

  for(int i = 0; i < R->NEL; i++){
    idadesDif[i] = 0;
    numeroIdades[i] = 0;
  }

  NO_Req *req = R->Inicio;
  int totalIdadesDif = 0;

  while(req){
    int found = 0;
    for(int i = 0; i < totalIdadesDif; i++){
      if(idadesDif[i] == (2024 - req->Info->data_nasc.year)){
        numeroIdades[i]++;
        found = 1;
        break;
      }
    }
    if(!found && totalIdadesDif < R->NEL){
      idadesDif[totalIdadesDif] = (2024 - req->Info->data_nasc.year);
      numeroIdades[totalIdadesDif]++;
      totalIdadesDif++;
    }
    req = req->Prox;
  }

  int tamanhoLista = sizeof(numeroIdades) / sizeof(numeroIdades[0]);
  int j = MaiorIdiceListaReq(numeroIdades, tamanhoLista);

  if(totalIdadesDif > 0){
    printf("A idade mais comum e: %d", idadesDif[j]);

  }
}

void SobrenomeMaisUsado(RL *R) {
    if (!R || !R->Inicio) return;

    char listaSN[R->NEL][30];
    int sobrenome_count[R->NEL];

    for (int i = 0; i < R->NEL; i++) {
        listaSN[i][0] = '\0';
        sobrenome_count[i] = 0;
    }

    NO_Req *req = R->Inicio;
    int totalSobrenomes = 0;

    while (req) {
        char *sobreNome = strrchr(req->Info->nome_req, ' ');
        if (sobreNome) {
            sobreNome++;
            int found = 0;
            for (int i = 0; i < totalSobrenomes; i++) {
                if (strcmp(sobreNome, listaSN[i]) == 0) {
                    sobrenome_count[i]++;
                    found = 1;
                    break;
                }
            }

            if (!found && totalSobrenomes < R->NEL) {
                strncpy(listaSN[totalSobrenomes], sobreNome, 30);
                listaSN[totalSobrenomes][29] = '\0';
                sobrenome_count[totalSobrenomes]++;
                totalSobrenomes++;
            }
        }
        req = req->Prox;
    }

    int maxIndex = 0;
    for (int i = 1; i < totalSobrenomes; i++) {
        if (sobrenome_count[i] > sobrenome_count[maxIndex]) {
            maxIndex = i;
        }
    }

    if (totalSobrenomes > 0) {
        printf("Sobrenome mais usado: %s, com %d ocorrências\n", listaSN[maxIndex], sobrenome_count[maxIndex]);
    } else {
        printf("Nenhum sobrenome encontrado.\n");
    }
}

int MaiorIdiceListaReq(int lista[], int j){
  int maior = 0;
  for(int i = 0; i < j; i++){
    if(lista[i] == 0){
      return maior;
    }else if(lista[i] > lista[maior]){
      maior = i;
    }
  }
  return maior;
}

void OrdenarListaInteiros(int lista[], int tamanho){
  qsort(lista, tamanho, sizeof(int), compararInteiros);

  for(int i = 0; i < tamanho; i++){
    printf("%d\n", lista[i]);
  }
}

int compararInteiros(const void *a, const void *b){
  return (*(int*)a - *(int*)b);
}

void ListarPorIdf(RL *R) {
    if (!R) return;
    if (!R->Inicio) return;

    NO_Req *req = R->Inicio;

    int idf[R->NEL];
    int idx = 0;

    while (req) {
        int j = atoi(req->Info->id_freguesia);

        int found = 0;
        for (int i = 0; i < idx; i++) {
            if (idf[i] == j) {
                found = 1;
                break;
            }
        }

        if (!found) {
            idf[idx++] = j;
        }
        req = req->Prox;
    }

    qsort(idf, idx, sizeof(int), compararInteiros);

    for (int i = 0; i < idx; i++) {
        printf("%d\n", idf[i]);
    }
}
