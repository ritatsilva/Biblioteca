#ifndef FREGUESIAS_H_INCLUDED
#define FREGUESIAS_H_INCLUDED

typedef struct Freguesia{
  char id_freg[7];
  char nome_freg[100];
}Freg;

typedef struct FreguesiaLigados{
  int NEL;
  Freg *Freguesia;
}FL;

int LFFreg(FL *F);

int MostrarFreguesia(FL *F);

int VerificarIdf(char *idf);


#endif // FREGUESIAS_H_INCLUDED
