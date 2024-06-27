#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Livros.h"
#include "Lista.h"
#include "Hashing.h"
#include "Requesicoes.h"
typedef struct
{
    char *NOME;
    char FICHEIRO_LOGS[50];

    HASHING *HLivros;
    //LISTA   *LRequisitantes;
    //LISTA_Requisicoes *LRequisicoes;
}BIBLIOTECA;

BIBLIOTECA *CriarBiblioteca(char *_nome, char *_logs);

void ShowBiblioteca(BIBLIOTECA *B);

void DestruirBiblioteca(BIBLIOTECA *B);

int LoadFicheiroBiblioteca(BIBLIOTECA *B);

int AddLivroBiblioteca(BIBLIOTECA *B, Livro *L);

int RemoverLivroBiblioteca(BIBLIOTECA *B, int isbn);

Livro *LivroMaisRequisitadoBiblioteca(BIBLIOTECA *B);

int escreverLivroFile(char *F_Livro, Livro *L);

Livro *PesquisaPorISBN(BIBLIOTECA *B, int isbn);

Livro *PesquisaPorNome(BIBLIOTECA *B, char *nome);

void atualizarNReqsLivro(BIBLIOTECA *B, Rcoes *r);

void escreverLivrosNoFile(BIBLIOTECA *B);

void EscreverXML(BIBLIOTECA *B, char *nomeFile);


#endif // BIBLIOTECA_H_INCLUDED
