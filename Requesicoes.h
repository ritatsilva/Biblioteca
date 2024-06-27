#ifndef REQUESICOES_H_INCLUDED
#define REQUESICOES_H_INCLUDED

#include <time.h>
#include <stdio.h>
#include "Freguesias.h"
#include "Distritos.h"
#include "Concelhos.h"
#include "Requesitantes.h"
#include "Livros.h"

typedef struct Requesicoes{
  char nomeLivro[101];
  Req *r;
  date dataRcoes;
  int estado;
}Rcoes;

typedef struct _no_rcoes{
  Rcoes *Info;
  struct _no_rcoes *Prox;
}NO_Rcoes;

typedef struct RequesicoesLigadas{
  int NEL;
  NO_Rcoes *Inicio;
}RcoesL;

RcoesL *CriarLRcoes();

Rcoes *CriarRcoes(char *nomeLiro, Req *r, int day, int month, int year, int estado);

int adicionarRcoesLista(RcoesL *R, Rcoes *Rcoes, Req *r);

void MostrarRcoes(Rcoes *R);

void MostrarListaRcoes(RcoesL *R);

int destruirRcoes(Rcoes *R);

int escreverRecoes(RcoesL *R);

int escreverRequesicaoUnica(Rcoes *r);

int MostrarRequesicoesDoReq(char *idReq, RL *R,RcoesL *r);

int ReqVazias(RL *R);

int RequesicoesExistentes(RcoesL *rcoesl);

Rcoes *pesquisarRcoes(RcoesL *R, char *nomeLivro, char *nomeRequesitante);

void atualizarFileRecoes(RcoesL *R);

int LerFicheiroRceos(RcoesL *R, RL *rr);

#endif // REQUESICOES_H_INCLUDED
