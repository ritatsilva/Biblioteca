#include "Biblioteca.h"

#define Sucesso 0
#define Insucesso 1

/** \brief Aloca Memoria para uma Biblioteca
 *
 * \param _nome char* : Nome da Biblioteca
 * \param _logs char* : Ficheiro dos Logs
 * \return BIBLIOTECA* : Retorna o ponteiro para a biblioteca
 * \author Docentes & Alunos
 * \date   11/04/2024
 *
 */
BIBLIOTECA *CriarBiblioteca(char *_nome, char *_logs)
{
    BIBLIOTECA *Bib = (BIBLIOTECA *)malloc(sizeof(BIBLIOTECA));
    Bib->NOME = (char *)malloc((strlen(_nome) + 1) * sizeof(char));
    strcpy(Bib->NOME, _nome);
    strcpy(Bib->FICHEIRO_LOGS, _logs);
    Bib->HLivros = CriarHashing();
    //Bib->LRequisicoes = CriarListaRequisicoes();
    //Bib->LRequisitantes = CriarListaPessoas();
    return Bib;
}

/** \brief Funcao para Mostrar toda a Biblioteca
 *
 * \param B BIBLIOTECA* : Ponteiro para a Biblioteca
 * \return void
 * \author : Docentes e Alunos
 * \date   : 11/04/2024
 */
void ShowBiblioteca(BIBLIOTECA *B)
{
    FILE *F_Logs = fopen(B->FICHEIRO_LOGS, "a");
    time_t now = time(NULL);

    fprintf(F_Logs, "Entrei em %s na data %s\n", __FUNCTION__, ctime(&now));

    printf("NOME BIBLIOTECA = [%s]\n", B->NOME);
    ShowHashing(B->HLivros);

    fclose(F_Logs);
}

void DestruirBiblioteca(BIBLIOTECA *B)
{
    FILE *F_Logs = fopen(B->FICHEIRO_LOGS, "a");
    time_t now = time(NULL) ;
    fprintf(F_Logs, "Entrei em %s na data %s\n", __FUNCTION__, ctime(&now));

    free(B->NOME);

    NO_CHAVE *atual = B->HLivros->LChaves->Inicio;

    NO_CHAVE *proximo;

    while (atual != NULL) {
        proximo = atual->Prox;
        free(atual->KEY);
        free(atual);
        atual = proximo;
    }

    free(B->HLivros->LChaves);
    free(B->HLivros);

    return;
}

int LoadFicheiroBiblioteca(BIBLIOTECA *B)
{

    FILE *F_Logs = fopen(B->FICHEIRO_LOGS, "a");
    time_t now = time(NULL);
    fprintf(F_Logs, "Entrei em %s na data %s\n", __FUNCTION__, ctime(&now));

    FILE *F_Livro = fopen("ficheiros/Livros.txt", "r");
    if(!F_Livro){
        printf("aaa");
        return Insucesso;
    }

    char ISBN[100];
    char titulo[100];
    char autor[100];
    char area[100];
    char dta[100];
    date data_publi;
    int day, month, year;
    char n_requesicoes[100];

    char *ISBN2;
    char *titulo2;
    char *autor2;
    char *area2;
    char *dta2;
    char *n_requesicoes2;

    while(!feof(F_Livro)){
        fscanf(F_Livro, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n\n", ISBN, area, titulo, autor, dta, n_requesicoes);

        ISBN2 = strrchr(ISBN, ':');
        ISBN2+=2;
        int isbn = atoi(ISBN2);
        //printf("%d\n", isbn);

        area2 = strrchr(area, ':');
        area2+=2;
        //printf("%s\n", area2);

        titulo2 = strrchr(titulo, ':');
        titulo2+=2;
        //printf("%s\n", titulo2);

        autor2 = strrchr(autor, ':');
        autor2+=2;
        //printf("%s\n", autor2);

        dta2 = strrchr(dta, ':');
        dta2+=2;
        sscanf(dta2, "%d/%d/%d", &day, &month, &year);
        //printf("%d/%d/%d\n", day, month, year);

        n_requesicoes2 = strrchr(n_requesicoes, ':');
        n_requesicoes2+=2;
        int nrcoes = atoi(n_requesicoes2);
        //printf("%d\n", nrcoes);

        Livro *ll = CriarLivro(isbn, titulo2, autor2, area2, day, month, year, nrcoes);
        AddHashing(B->HLivros, ll);

    }

    return EXIT_SUCCESS;
    fclose(F_Logs);
}

int AddLivroBiblioteca(BIBLIOTECA *B, Livro *L)
{
    FILE *F_Logs = fopen(B->FICHEIRO_LOGS, "a");
    FILE *Livro = fopen("ficheiros/Livros.txt", "a");

    time_t now = time(NULL);
    fprintf(F_Logs, "Entrei em %s na data %s\n", __FUNCTION__, ctime(&now));

    if(!B)
        return Insucesso;
    if(!L)
        return  Insucesso;

    AddHashing(B->HLivros, L);

    fclose(F_Logs);
    fclose(Livro);

    return EXIT_SUCCESS;
}
int RemoverLivroBiblioteca(BIBLIOTECA *B, int isbn)
{
    FILE *F_Logs = fopen(B->FICHEIRO_LOGS, "a");
    time_t now = time(NULL) ;
    fprintf(F_Logs, "Entrei em %s na data %s\n", __FUNCTION__, ctime(&now));
    if(!B)
        return Insucesso;
    if(!B->HLivros)
        return Insucesso;

    NO_CHAVE *no_chave = B->HLivros->LChaves->Inicio;
    while (no_chave) {
        NO *anterior = NULL;
        NO *atual = no_chave->DADOS->Inicio;
        while (atual) {
            if (atual->Info->ISBN == isbn) {
                if (anterior) {
                    anterior->Prox = atual->Prox;
                } else {
                    no_chave->DADOS->Inicio = atual->Prox;
                }
                free(atual->Info);
                free(atual);
                no_chave->DADOS->NEL--;
                fprintf(F_Logs, "Livro com ISBN %d removido com sucesso.\n", isbn);
                fclose(F_Logs);
                return EXIT_SUCCESS;
            }
            anterior = atual;
            atual = atual->Prox;
        }
        no_chave = no_chave->Prox;
    }
    fclose(F_Logs);
    return EXIT_SUCCESS;
}
Livro *LivroMaisRequisitadoBiblioteca(BIBLIOTECA *B)
{
    FILE *F_Logs = fopen(B->FICHEIRO_LOGS, "a");
    time_t now = time(NULL) ;
    fprintf(F_Logs, "Entrei em %s na data %s\n", __FUNCTION__, ctime(&now));



    NO_CHAVE *chave_atual = B->HLivros->LChaves->Inicio;
    while (chave_atual != NULL) {
        NO *livro_atual = chave_atual->DADOS->Inicio;
        while (livro_atual != NULL) {
            Livro *livro = (Livro *) livro_atual->Info;
            int max = livro->n_requesicoes;
            if (livro->n_requesicoes > max) {
                max = livro->n_requesicoes;
                return livro_atual->Info;
            }
            livro_atual = livro_atual->Prox;
        }
        chave_atual = chave_atual->Prox;

    }

    fclose(F_Logs);
    return NULL;
}

char *AreaMaisComum(BIBLIOTECA *B)
{
    FILE *F_Logs = fopen(B->FICHEIRO_LOGS, "a");
    time_t now = time(NULL) ;
    fprintf(F_Logs, "Entrei em %s na data %s\n", __FUNCTION__, ctime(&now));

    // Aqui o teu codigo

    fclose(F_Logs);
    return NULL;
}

int escreverLivroFile(char *F_Livro, Livro *L){
    if(!L) return Insucesso;

    FILE *Livro = fopen(F_Livro, "a");

    if(!Livro) return Insucesso;

    fprintf(Livro, "ISBN: %d\nArea: %s\nTitulo: %s\nAutor: %s\nDataPublica��o: %d/%d/%d\nNumeroRequesi��es: %d\n\n",L->ISBN, L->area, L->titulo, L->autor, L->data_publi.day, L->data_publi.month,L->data_publi.year, L->n_requesicoes);


    fclose(Livro);
    return Sucesso;
}


Livro *PesquisaPorISBN(BIBLIOTECA *B, int isbn){

    FILE *F_Logs = fopen(B->FICHEIRO_LOGS, "a");
    if (F_Logs == NULL) {
        perror("Erro ao abrir o ficheiro de logs");
        return NULL;
    }

    time_t now = time(NULL);
    fprintf(F_Logs, "Entrei em %s na data %s\n", __FUNCTION__, ctime(&now));

    NO_CHAVE *chave_atual = B->HLivros->LChaves->Inicio;
    while (chave_atual != NULL) {
        NO *livro_atual = chave_atual->DADOS->Inicio;
        while (livro_atual != NULL) {
            Livro *livro = (Livro *) livro_atual->Info;
            if (isbn == livro->ISBN) {
                return livro_atual->Info;
            }
            livro_atual = livro_atual->Prox;
        }
        chave_atual = chave_atual->Prox;
    }


    fclose(F_Logs);
    return NULL;
}

void atualizarNReqsLivro(BIBLIOTECA *B, Rcoes *r){
    if(!B){
        return;
    }

    NO_CHAVE *chave_atual = B->HLivros->LChaves->Inicio;
    while (chave_atual != NULL){
        NO *livro_atual = chave_atual->DADOS->Inicio;
        while (livro_atual != NULL){
            Livro *livro = PesquisaPorNome(B, livro_atual->Info->titulo);
            livro->n_requesicoes++;
        }
        livro_atual = livro_atual->Prox;
    }
    chave_atual = chave_atual->Prox;
}

Livro *PesquisaPorNome(BIBLIOTECA *B, char *nome){
    FILE *F_Logs = fopen(B->FICHEIRO_LOGS, "a");
    if (F_Logs == NULL) {
        perror("Erro ao abrir o ficheiro de logs");
        return NULL;
    }

    time_t now = time(NULL);
    fprintf(F_Logs, "Entrei em %s na data %s\n", __FUNCTION__, ctime(&now));

    NO_CHAVE *chave_atual = B->HLivros->LChaves->Inicio;
    while (chave_atual != NULL) {
        NO *livro_atual = chave_atual->DADOS->Inicio;
        while (livro_atual != NULL) {
            Livro *livro = (Livro *) livro_atual->Info;
            if (strcmp(nome, livro->titulo)==0) {
                return livro_atual->Info;
            }
            livro_atual = livro_atual->Prox;
        }
        chave_atual = chave_atual->Prox;
    }

    fclose(F_Logs);
    return NULL;
}

void escreverLivrosNoFile(BIBLIOTECA *B){
    FILE *F_Logs = fopen(B->FICHEIRO_LOGS, "a");
    FILE *F_Livro = fopen("ficheiros/Livros.txt", "w");
    if (F_Logs == NULL){
        perror("Erro ao abrir o ficheiro de logs");
        return;
    }
    time_t now = time(NULL);
    fprintf(F_Logs, "Entrei em %s na data %s\n", __FUNCTION__, ctime(&now));

    NO_CHAVE *chave_atual = B->HLivros->LChaves->Inicio;
    while (chave_atual != NULL){
        NO *livro_atual = chave_atual->DADOS->Inicio;
        while (livro_atual != NULL){
            Livro *livro = (Livro *) livro_atual->Info;
             fprintf(F_Livro, "ISBN: %d\nArea: %s\nTitulo: %s\nAutor: %s\nDataPublica��o: %d/%d/%d\nNumeroRequesi��es: %d\n\n",livro->ISBN, livro->area, livro->titulo, livro->autor, livro->data_publi.day, livro->data_publi.month,livro->data_publi.year, livro->n_requesicoes);
        }
        livro_atual = livro_atual->Prox;
    }
    chave_atual = chave_atual->Prox;

    fclose(F_Logs);
    fclose(F_Livro);
}


void EscreverXML(BIBLIOTECA *B, char *nomeFile){
    FILE *F_Logs = fopen(B->FICHEIRO_LOGS, "a");
    FILE *F_XML = fopen(nomeFile, "w");
    if (F_Logs == NULL){
        perror("Erro ao abrir o ficheiro de logs");
        return;
    }
    time_t now = time(NULL);
    fprintf(F_Logs, "Entrei em %s na data %s\n", __FUNCTION__, ctime(&now));

    if (F_XML == NULL){
        return;
    }
    fprintf(F_XML, "<BIBLIOTECA>\n");
    fprintf(F_XML, "<NOME>%s</NOME>\n", B->NOME);
    NO_CHAVE *no_chave = B->HLivros->LChaves->Inicio;
    while(no_chave){
        fprintf(F_XML, "\t<DADOS>\n");
        NO *no = no_chave->DADOS->Inicio;
        fprintf(F_XML,"\t\t<CHAVE>%s</CHAVE>\n", no_chave->KEY);
        while(no){
        fprintf(F_XML,"\t\t\t<TITULO>%s</TITULO>\n", no->Info->titulo);
            fprintf(F_XML, "\t\t\t<ISBN>%d</ISBN>\n", no->Info->ISBN);
            fprintf(F_XML, "\t\t\t<AUTOR>%s</AUTOR>\n", no->Info->autor);
            fprintf(F_XML, "\t\t<DATAPUBLI>%d/%d/%d</DATAPUBLI>\n", no->Info->data_publi.day, no->Info->data_publi.month, no->Info->data_publi.year);
            fprintf(F_XML, "\t\t<NUMRECOES>%d</NUMRECOES>\n", no->Info->n_requesicoes);
            fprintf(F_XML, "\t</DADOS>\n");
            no = no->Prox;
        }
        fprintf(F_XML, "\t</DADOS>\n");
        no_chave = no_chave->Prox;
    }
    fprintf(F_XML, "</BIBLIOTECA>\n");

    fclose(F_XML);
    fclose(F_Logs);

}
