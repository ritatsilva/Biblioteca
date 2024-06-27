#ifndef CONCELHOS_H_INCLUDED
#define CONCELHOS_H_INCLUDED

typedef struct Concelho{
  char id_Conc[5];
  char nome_conc[100];
}Conc;

typedef struct ConcelhosLigados{
  int NEL;
  Conc *Concelhos;
}CL;


int LFConc(CL *C);

int MostrarConcelhos(CL *C);

int VerConcelhos(CL *C, char *id);

int VerConcelhosPorNome(CL *C, char *nomeConcelho);

#endif // CONCELHOS_H_INCLUDED
