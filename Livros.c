#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Livros.h"
#include "Requesitantes.h"

#define Sucesso 0
#define Insucesso 1

Livro *CriarLivro(int ISBN, char *titulo, char *autor, char *area, int day, int month, int year, int n_rcoes) {
    Livro *L = (Livro *)malloc(sizeof(Livro));
    if (L == NULL) {
        return NULL; // Verificação de alocação de memória
    }
    L->ISBN = ISBN;
    strcpy(L->titulo, titulo);
    strcpy(L->autor, autor);
    strcpy(L->area, area);
    L->data_publi.day = day;
    L->data_publi.month = month;
    L->data_publi.year = year;
    L->n_requesicoes = n_rcoes;

    return L;
}

int destruirLivro(Livro *l) {
    if (!l) return Insucesso;

    free(l);

    return Sucesso;
}

void MostrarLivro(Livro *L) {
    if (!L) return;

    printf("\n/////Livro/////\n");
    printf("ISBN: %d\n", L->ISBN);
    printf("Titulo: %s\n", L->titulo);
    printf("Autor: %s\n", L->autor);
    printf("Area: %s\n", L->area);
    printf("Data de publicacao: %d/%d/%d\n", L->data_publi.day, L->data_publi.month, L->data_publi.year);
    printf("Numero de requesicoes: %d\n", L->n_requesicoes);
    printf("\n///////////////\n");
}
