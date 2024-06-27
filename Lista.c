#include "Lista.h"

//--------------------------------------------------
/** \brief Permite alocar mem�ria para uma lista
 *
 * \return LISTA* : Retorna a lista alocada
 * \date 10/04/2024
 * \author Docentes de ED
 */
LISTA *CriarLista()
{
    LISTA *L = (LISTA *)malloc(sizeof(LISTA));
    L->NEL = 0;
    L->Inicio = NULL;
    return L;
}

//--------------------------------------------------
void AddInicio(LISTA *L, Livro *X)
{
    if (!L) return;
    NO *aux = (NO *)malloc(sizeof(NO));
    aux->Info = X;
    aux->Prox = L->Inicio;
    L->Inicio = aux;
    L->NEL++;
}

//--------------------------------------------------
void ShowLista(LISTA *L)
{
    if (!L) return;
    //printf("NEL = %d\n", L->NEL);
    NO *P = L->Inicio;
    while (P != NULL)
    {
        MostrarLivro(P->Info);
        P = P->Prox;
    }
}

//--------------------------------------------------
void DestruirLista(LISTA *L)
{
    //printf("Implementar <%s>\n", __FUNCTION__);
    if (!L) return;
    NO *Martim;
    NO *Helder = L->Inicio;
    while (Helder)
    {
        Martim = Helder->Prox;
        destruirLivro(Helder->Info);
        free (Helder);
        Helder = Martim;
    }
    free(L);
}

//--------------------------------------------------
Livro *PesquisarLista(LISTA *L, char *_nome)
{
    printf("Implementar <%s>\n", __FUNCTION__);
    if (L == NULL) return NULL;
    NO *P = L->Inicio;
    while (P)
    {
        if (strcmp(P->Info->area, _nome) == 0)
            return P->Info;
        P = P->Prox;
    }
    return NULL;
}

//--------------------------------------------------
int SizeLista(LISTA *L)
{
    if (!L) return -1;
    return L->NEL;
}
//--------------------------------------------------
//--------------------------------------------------
//--------------------------------------------------
