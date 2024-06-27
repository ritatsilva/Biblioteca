#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Freguesias.h"
#include "Distritos.h"
#include "Concelhos.h"
#include "Requesitantes.h"
#include "Livros.h"
#include "Requesicoes.h"

#define Sucesso 0
#define Insucesso 1

RcoesL *CriarLRcoes(){
  RcoesL *rl = (RcoesL *)malloc(sizeof(RcoesL));
  rl->NEL = 0;
  rl->Inicio = NULL;
  return rl;
}

Rcoes *CriarRcoes(char *nomeLivro, Req *r, int day, int month, int year, int estado){

  Rcoes *rcoes = (Rcoes *)malloc(sizeof(Rcoes));

  strcpy(rcoes->nomeLivro, nomeLivro);
  rcoes->r = r;
  rcoes->dataRcoes.day = day;
  rcoes->dataRcoes.month = month;
  rcoes->dataRcoes.year = year;
  rcoes->estado = estado;

  return rcoes;
}

int adicionarRcoesLista(RcoesL *R, Rcoes *Rcoes, Req *r){
  if(!R) return Insucesso;
  if(!Rcoes) return Insucesso;

  NO_Rcoes *novo = (NO_Rcoes *)malloc(sizeof(NO_Rcoes));

  novo->Info = Rcoes;
  novo->Prox = R->Inicio;
  R->Inicio = novo;
  R->NEL++;
  r->nRecoes++;


  return Sucesso;
}

void MostrarRcoes(Rcoes *R){
  if(!R) return;

  printf("/////Requesicoes/////\n");
  printf("Livro: %s\n", R->nomeLivro);
  printf("Requesitante: %s\n", R->r->nome_req);
  printf("Data de requisicao: %d/%d/%d\n", R->dataRcoes.day, R->dataRcoes.month, R->dataRcoes.year);
  printf("Estado da requesição: %d\n", R->estado);
  printf("\n///////////////\n");
}

Rcoes *pesquisarRcoes(RcoesL *R, char *nomeLivro, char *nomeRequesitante){

  NO_Rcoes *no_rcoes = R->Inicio;

  while(no_rcoes){
    if(strcmp(no_rcoes->Info->nomeLivro, nomeLivro) == 0){
      if(strcmp(no_rcoes->Info->r->nome_req, nomeRequesitante) == 0){
        return no_rcoes->Info;
      }
    }
    no_rcoes = no_rcoes->Prox;
  }
  return no_rcoes->Info;
}

void MostrarListaRcoes(RcoesL *R){
  if(!R) return;
  NO_Rcoes *rcoes = R->Inicio;
  while(rcoes){
    MostrarRcoes(rcoes->Info);
    rcoes = rcoes->Prox;
  }
}

int destruirRcoes(Rcoes *R){
  if(!R) return Insucesso;

  R->estado = 0;

  return Sucesso;
}

int escreverRequesicaoUnica(Rcoes *r){
  FILE *f = fopen("requesicoes.txt", "a");

  fprintf(f, "Livro: %s\nRequesitante: %s\nDataDeRequisicao: %d/%d/%d\nEstadoDaRequesição: %d\n\n", r->nomeLivro, r->r->nome_req, r->dataRcoes.day, r->dataRcoes.month, r->dataRcoes.year, r->estado);

  fclose(f);

  return Sucesso;
}

int escreverRecoes(RcoesL *R){
  if(!R) return Insucesso;
  if(!R->Inicio) return Insucesso;
  FILE *f = fopen("requesicoes.txt", "a");
  NO_Rcoes *r = R->Inicio;
  while(r){
    fprintf(f, "Livro: %s\nRequesitante: %s\nEstadoDaRequesição: %d\nDataDeRequisicao: %d/%d/%d\n\n", r->Info->nomeLivro,r->Info->r->nome_req,r->Info->estado,r->Info->dataRcoes.day, r->Info->dataRcoes.month, r->Info->dataRcoes.year);

    r = r->Prox;
  }

  fclose(f);
  return Sucesso;
}

int MostrarRequesicoesDoReq(char *idReq, RL *R,RcoesL *r){
  if(!R) return Insucesso;
  if(!R->Inicio) return Insucesso;

  NO_Rcoes *rcoes = r->Inicio;

  while(rcoes){
    if(strcmp(rcoes->Info->r->id_requesitante, idReq) == 0){
      MostrarRcoes(rcoes->Info);
    }
    rcoes = rcoes->Prox;
  }
  return Sucesso;
}

int ReqVazias(RL *R){
  if(!R) return Insucesso;
  if(!R->Inicio) return Insucesso;

  NO_Req *req = R->Inicio;

  while(req){
    if(req->Info->nRecoes == 0){
      MostrarRequesitantes(req->Info);
    }

    req = req->Prox;
  }

  return Sucesso;
}

int RequesicoesExistentes(RcoesL *rcoesl){
  if(!rcoesl) return Insucesso;
  if(!rcoesl->Inicio) return Insucesso;

  NO_Rcoes *rcoes = rcoesl->Inicio;

  while(rcoes){
    if(rcoes->Info->estado == 1){
      MostrarRcoes(rcoes->Info);
    }
    rcoes = rcoes->Prox;
  }
  return Sucesso;
}

void atualizarFileRecoes(RcoesL *R){
  if(!R) return;
  if(!R->Inicio) return;
  FILE *f = fopen("requesicoes.txt", "w");
  NO_Rcoes *r = R->Inicio;
  while(r){
    fprintf(f, "Livro: %s\nRequesitante: %s\nEstado da requesição: %d\nData de requisicao: %d/%d/%d\n\n", r->Info->nomeLivro,r->Info->r->nome_req,r->Info->estado,r->Info->dataRcoes.day, r->Info->dataRcoes.month,r->Info->dataRcoes.year);

    r = r->Prox;
  }

  fclose(f);
  return;
}

int LerFicheiroRceos(RcoesL *R, RL *rr){

  FILE *f = fopen("requesicoes.txt", "r");

  char nomeLivro[101];
  char nomeReq[101];
  char data[100];
  char estado[101];
  int day, month, year;

  char *nomeLivro2;
  char *nomeReq2;
  char *data2;
  char *estado2;

  while(!feof(f)){

    fscanf(f, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n\n", nomeLivro, nomeReq, estado, data);

    nomeLivro2 = strrchr(nomeLivro, ':');
    nomeLivro2+=2;

    nomeReq2 = strrchr(nomeReq, ':');
    nomeReq2+=2;
    Req *rrr = pesquisarReq(nomeReq2, rr);


    estado2 = strrchr(estado, ':');
    estado2+=2;
    int estado3 = atoi(estado2);

    data2 = strrchr(data, ':');
    data2+=2;
    sscanf(data2, "%d/%d/%d", &day, &month, &year);

    Rcoes *rcoes = CriarRcoes(nomeLivro2, rrr, day, month, year, estado3);
    adicionarRcoesLista(R, rcoes, rrr);

  }

  return Sucesso;
}
