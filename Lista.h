#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "Livros.h"

typedef struct no
{
    Livro    *Info;
    struct no *Prox;
}NO;

typedef struct
{
    int NEL;
    NO *Inicio;
}LISTA;


//--------------------------------------------------
LISTA *CriarLista();
//--------------------------------------------------
void AddInicio(LISTA *L, Livro *X);
//--------------------------------------------------
void ShowLista(LISTA *L);
//--------------------------------------------------
void DestruirLista(LISTA *L);
//--------------------------------------------------
Livro *PesquisarLista(LISTA *L, char *_nome);
//--------------------------------------------------
int SizeLista(LISTA *L);
//--------------------------------------------------
//--------------------------------------------------
//--------------------------------------------------
//--------------------------------------------------
//--------------------------------------------------

#endif // LISTA_H_INCLUDED
