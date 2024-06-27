#ifndef REQUESITANTES_H_INCLUDED
#define REQUESITANTES_H_INCLUDED


#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Freguesias.h"
#include "Distritos.h"
#include "Concelhos.h"



typedef struct date {
    int day;
    int month;
    int year;
}date;

typedef struct Requesitante{
  char id_requesitante[10];
  char nome_req[101];
  date data_nasc;
  char id_freguesia[7];
  int nRecoes;
}Req;

typedef struct _no_r
{
  Req *Info;
  struct _no_r *Prox;
}NO_Req;

typedef struct RL{
  int NEL;
  NO_Req *Inicio;
}RL;

Req *CriarReq(char *id,char *txt, int day, int month, int year, char *ifd);

RL *CriarRL();

void DestruirListaReqs(RL *R);

date CriarData(int day, int month, int year);

int AdicionarReq(RL *R,Req *req);

int LFReq(CL *C,DL *D,FL *F,RL *R);

void MostrarListaReq(RL *R);

void MostrarRequesitantes(Req *R);

int CheckID(char *id);

int EscreverReqLogs(char *id, char *txt, char *data, char *idf);

int EscreverReq(Req *R);

date SepararData(char *data);

int CheckData(date data);

int CheckIdf(FL *F, char *idf);

void EscreverListaRqsNoFile(RL *R);

///////////////Funcoes novas//////////////////

Req *pesquisarReq(char *nome, RL *R);//Feita

void ListarPorIdf(RL *R);//Feita

void OrdenarListaInteiros(int lista[], int tamanho);//Funcao util

int compararInteiros(const void *a, const void *b);//funcao util

void VerIdadeMaxima(RL *R);//Feita

void VerMediaIdades(RL *R);//Feita

void IdadesMaiorQue(int idade, RL *R);//Feita

void VerNumReqIdade(RL *R);//Feita

void SobrenomeMaisUsado(RL *R);//Feita

int MaiorIdiceListaReq(int lista[], int length);//Funcao util

void NumSobrenomePorConcelho(char *nomeConcelho,char *apelido, RL *R, CL *C);//Por Fazer

int NumSobrenomePorDistrito(RL *R, DL *D);//Por fazer

//////EXTRAS//////

void ListarReqDataNascDomingo(RL *R);//Por fazer

void ListarDataNascQuaresma(RL *R);//Por fazer

//////EXTRAS//////

///////////////Funcoes novas//////////////////


#endif // REQUESITANTES_H_INCLUDED
