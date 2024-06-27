#ifndef DISTRITOS_H_INCLUDED
#define DISTRITOS_H_INCLUDED

typedef struct Distrito{
  char id_dist[3];
  char nome_dist[100];
}Dist;

typedef struct DistritosLigados{
  int NEL;
  Dist *Distritos;
}DL;

int LFDist(DL *D);

int MostrarDistritos(DL *D);

int VerificarIdd(DL *D, char *idd);

#endif // DISTRITOS_H_INCLUDED
