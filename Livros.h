#ifndef LIVROS_H_INCLUDED
#define LIVROS_H_INCLUDED

#include <time.h>
#include <stdio.h>

#include "Requesitantes.h"

typedef struct Livro{
  int ISBN;
  char titulo[100];
  char autor[50];
  char area[20];
  date data_publi;
  int n_requesicoes;
}Livro;


//LL *CriarLL();

Livro *CriarLivro(int ISBN, char *titulo, char *autor, char *area, int day, int month, int year, int n_rcoes);

//int adicionarLivroLista(LL *L, Livro *Livro);

int destruirLivro(Livro *l);

//int destruirListaLivros(LL *L);

void MostrarLivro(Livro *L);

void EscreverLivro(FILE *livro,Livro *L);


#endif // LIVROS_H_INCLUDED
