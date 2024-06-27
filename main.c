#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Incluindo headers necess�rios
#include "Distritos.h"
#include "Concelhos.h"
#include "Freguesias.h"
#include "Requesitantes.h"
#include "Livros.h"
#include "Requesicoes.h"
#include "Biblioteca.h"

// Declara��o da fun��o de menu
int menu();

// Fun��o principal
int main(void) {
    if (menu() != 0) {
        fprintf(stderr, "Ocorreu um erro no menu.\n");
    }
    return 0;
}

// Fun��o de menu
int menu() {
    int opcao1, opcao2, opcao3, opcao4;

    // Alocando mem�ria para as listas de distritos, concelhos e freguesias
    DL *D = (DL *)malloc(sizeof(DL));
    if (D == NULL) {
        fprintf(stderr, "Erro ao alocar mem�ria para DL.\n");
        return 1;
    }

    CL *C = (CL *)malloc(sizeof(CL));
    if (C == NULL) {
        fprintf(stderr, "Erro ao alocar mem�ria para CL.\n");
        free(D);
        return 1;
    }

    FL *F = (FL *)malloc(sizeof(FL));
    if (F == NULL) {
        fprintf(stderr, "Erro ao alocar mem�ria para FL.\n");
        free(D);
        free(C);
        return 1;
    }

    // Inicializando as listas (n�o alocando, apenas zerando os ponteiros)
    D->head = NULL;
    C->head = NULL;
    F->head = NULL;

    // Criando lista de requisitantes e adicionando um requisitante exemplo
    RL *R = CriarRL();
    if (R == NULL) {
        fprintf(stderr, "Erro ao criar lista de requisitantes.\n");
        free(D);
        free(C);
        free(F);
        return 1;
    }

    Req *rr = CriarReq("123123123", "Jaime", 12, 12, 2012, "123123");
    if (rr == NULL) {
        fprintf(stderr, "Erro ao criar requisitante.\n");
        DestruirListaReqs(R);
        free(D);
        free(C);
        free(F);
        return 1;
    }
    AdicionarReq(R, rr);

    // Carregando dados de arquivos
    LFDist(D);
    LFConc(C);
    LFFreg(F);
    LFReq(C, D, F, R);

    // Criando biblioteca e carregando arquivos relacionados
    BIBLIOTECA *B = CriarBiblioteca("ESTGV", "Logs.txt");
    if (B == NULL) {
        fprintf(stderr, "Erro ao criar biblioteca.\n");
        DestruirListaReqs(R);
        free(D);
        free(C);
        free(F);
        return 1;
    }
    LoadFicheiroBiblioteca(B);

    // Criando lista de requisi��es e carregando dados de arquivo
    RcoesL *r = CriarLRcoes();
    if (r == NULL) {
        fprintf(stderr, "Erro ao criar lista de requisi��es.\n");
        DestruirBiblioteca(B);
        DestruirListaReqs(R);
        free(D);
        free(C);
        free(F);
        return 1;
    }
    LerFicheiroRceos(r, R);

    // Loop principal do menu
    while (1) {
        // Exibindo menu principal
        printf("\n*******************************************\n");
        printf("*                  MENU                   *\n");
        printf("*******************************************\n");
        printf("1 - Biblioteca\n");
        printf("2 - Requisitantes\n");
        printf("3 - Requisi��es\n");
        printf("4 - Determinar mem�ria ocupada\n");
        printf("5 - Guardar dados\n");
        printf("6 - Gravar XML\n");
        printf("7 - Sair\n");
        printf("*******************************************\n");
        printf("Escolha uma op��o: ");
        if (scanf("%d", &opcao1) != 1) {
            fprintf(stderr, "Erro na leitura da op��o.\n");
            break;
        }

        // Processando op��o escolhida
        switch (opcao1) {
            case 1:
                // Submenu de biblioteca
                printf("\n---------------- Biblioteca ----------------\n");
                printf("1 - Adicionar livros � biblioteca\n");
                printf("2 - Listar livros da biblioteca\n");
                printf("3 - �rea com mais livros\n");
                printf("4 - Verificar se livro existe (ISBN)\n");
                printf("5 - Listar os livros mais recentes\n");
                printf("6 - Livro mais requisitado\n");
                printf("7 - �rea mais requisitada\n");
                printf("Escolha uma op��o: ");
                if (scanf("%d", &opcao2) != 1) {
                    fprintf(stderr, "Erro na leitura da op��o.\n");
                    break;
                }

                // Vari�veis usadas no submenu de biblioteca
                int isbn;
                char autor[101];
                char area[101];
                char titulo[101];
                int day, month, year;

                // Processando op��o do submenu de biblioteca
                switch (opcao2) {
                    case 1:
                        // Adicionando livro
                        printf("\nDigite os seguintes dados do livro:\n");
                        printf("ISBN: ");
                        if (scanf("%d", &isbn) != 1) {
                            fprintf(stderr, "Erro na leitura do ISBN.\n");
                            break;
                        }
                        printf("T�tulo: ");
                        if (scanf("%100s", titulo) != 1) {
                            fprintf(stderr, "Erro na leitura do t�tulo.\n");
                            break;
                        }
                        printf("Autor: ");
                        if (scanf("%100s", autor) != 1) {
                            fprintf(stderr, "Erro na leitura do autor.\n");
                            break;
                        }
                        printf("�rea: ");
                        if (scanf("%100s", area) != 1) {
                            fprintf(stderr, "Erro na leitura da �rea.\n");
                            break;
                        }
                        printf("Data de publica��o (dd mm aaaa): ");
                        if (scanf("%d %d %d", &day, &month, &year) != 3) {
                            fprintf(stderr, "Erro na leitura da data.\n");
                            break;
                        }
                        Livro *L = CriarLivro(isbn, titulo, autor, area, day, month, year, 0);
                        if (L == NULL) {
                            fprintf(stderr, "Erro ao criar livro.\n");
                            break;
                        }
                        AddHashing(B->HLivros, L);
                        escreverLivroFile("Livros.txt", L);
                        break;
                    case 2:
                        // Listando livros da biblioteca
                        ShowBiblioteca(B);
                        break;
                    case 3:
                        // Implementar l�gica para exibir a �rea com mais livros
                        // AreaComMaisLivros(l_livros);
                        break;
                    case 4:
                        // Verificando se livro existe pelo ISBN
                        printf("Digite o ISBN do livro: ");
                        if (scanf("%d", &isbn) != 1) {
                            fprintf(stderr, "Erro na leitura do ISBN.\n");
                            break;
                        }
                        Livro *lll = PesquisaPorISBN(B, isbn);
                        MostrarLivro(lll);
                        break;
                    case 5:
                        // Implementar l�gica para listar livros mais recentes
                        // livros_mais_recentes(l_livros);
                        break;
                    case 6:
                        // Implementar l�gica para exibir o livro mais requisitado
                        // LivroMaisRequesitado(l_livros);
                        break;
                    case 7:
                        // Implementar l�gica para exibir a �rea mais requisitada
                        // AreaMaisRequisitada();
                        break;
                    default:
                        printf("Op��o inv�lida!\n");
                }
                break;
            case 2:
                // Submenu de requisitantes
                printf("\n-------------- Requisitantes ---------------\n");
                printf("1 - Incluir novos requisitantes\n");
                printf("2 - Verificar se requisitante existe\n");
                printf("3 - Listar requisitantes (com ordena��o � escolha)\n");
                printf("4 - Idade m�xima dos requisitantes\n");
                printf("5 - M�dia das idades dos requisitantes\n");
                printf("6 - Contar pessoas com idade superior a um valor\n");
                printf("7 - Idade com mais requisitantes\n");
                printf("8 - Mostrar requisi��es de um requisitante\n");
                printf("9 - Pessoas que nunca requisitaram\n");
                printf("10 - Requisitantes com livros requisitados\n");
                printf("11 - Sobrenome mais usado\n");
                printf("12 - Pessoas de um dado Distrito/Concelho com um nome/apelido\n");
                printf("Escolha uma op��o: ");
                if (scanf("%d", &opcao3) != 1) {
                    fprintf(stderr, "Erro na leitura da op��o.\n");
                    break;
                }

                // Vari�veis usadas no submenu de requisitantes
                char nome[101];
                int idade;

                // Processando op��o do submenu de requisitantes
                switch (opcao3) {
                    case 1:
                        // Incluindo novos requisitantes
                        AdicionarRequesitanteUI(R);
                        break;
                    case 2:
                        // Verificando se requisitante existe
                        printf("Digite o nome do requisitante: ");
                        if (scanf("%100s", nome) != 1) {
                            fprintf(stderr, "Erro na leitura do nome.\n");
                            break;
                        }
                        Req *rAux = PesquisaPorNomeReq(nome, R);
                        MostrarReq(rAux);
                        break;
                    case 3:
                        // Listando requisitantes
                        // listar_requisitantes(r_livros);
                        break;
                    case 4:
                        // Idade m�xima dos requisitantes
                        int idade_max = idade_maxima_requisitantes(R);
                        printf("Idade m�xima: %d\n", idade_max);
                        break;
                    case 5:
                        // M�dia das idades dos requisitantes
                        float media_idades = media_idades_requisitantes(R);
                        printf("M�dia das idades: %.2f\n", media_idades);
                        break;
                    case 6:
                        // Contando pessoas com idade superior a um valor
                        printf("Digite a idade m�nima: ");
                        if (scanf("%d", &idade) != 1) {
                            fprintf(stderr, "Erro na leitura da idade m�nima.\n");
                            break;
                        }
                        int count = contar_pessoas_com_idade_superior(R, idade);
                        printf("N�mero de pessoas com idade superior a %d: %d\n", idade, count);
                        break;
                    case 7:
                        // Idade com mais requisitantes
                        int idade_mais_req = idade_com_mais_requisitantes(R);
                        printf("Idade com mais requisitantes: %d\n", idade_mais_req);
                        break;
                    case 8:
                        // Mostrando requisi��es de um requisitante
                        printf("Digite o nome do requisitante: ");
                        if (scanf("%100s", nome) != 1) {
                            fprintf(stderr, "Erro na leitura do nome.\n");
                            break;
                        }
                        listar_requisicoes_de_requisitante(R, nome);
                        break;
                    case 9:
                        // Listando pessoas que nunca requisitaram
                        listar_pessoas_que_nunca_requisitaram(R);
                        break;
                    case 10:
                        // Listando requisitantes com livros requisitados
                        listar_requisitantes_com_livros_requisitados(R);
                        break;
                    case 11:
                        // Mostrando sobrenome mais usado
                        char sobrenome[101];
                        sobrenome_mais_usado(R, sobrenome);
                        printf("Sobrenome mais usado: %s\n", sobrenome);
                        break;
                    case 12:
                        // Listando pessoas de um dado Distrito/Concelho com um nome/apelido
                        char distrito[101];
                        char concelho[101];
                        printf("Digite o Distrito: ");
                        if (scanf("%100s", distrito) != 1) {
                            fprintf(stderr, "Erro na leitura do distrito.\n");
                            break;
                        }
                        printf("Digite o Concelho: ");
                        if (scanf("%100s", concelho) != 1) {
                            fprintf(stderr, "Erro na leitura do concelho.\n");
                            break;
                        }
                        printf("Digite o nome/apelido: ");
                        if (scanf("%100s", nome) != 1) {
                            fprintf(stderr, "Erro na leitura do nome/apelido.\n");
                            break;
                        }
                        listar_pessoas_de_distrito_concelho_com_nome(R, distrito, concelho, nome);
                        break;
                    default:
                        printf("Op��o inv�lida!\n");
                }
                break;
            case 3:
                // Submenu de requisi��es
                printf("\n--------------- Requisi��es ----------------\n");
                printf("1 - Requisitar livro\n");
                printf("2 - Entregar livro\n");
                printf("3 - Listar requisi��es\n");
                printf("4 - Top 10 livros mais requisitados\n");
                printf("Escolha uma op��o: ");
                if (scanf("%d", &opcao4) != 1) {
                    fprintf(stderr, "Erro na leitura da op��o.\n");
                    break;
                }

                // Processando op��o do submenu de requisi��es
                switch (opcao4) {
                    case 1:
                        // Requisitando livro
                        requisitar_livro(B, r, R);
                        break;
                    case 2:
                        // Entregando livro
                        entregar_livro(B, r, R);
                        break;
                    case 3:
                        // Listando requisi��es
                        listar_requisicoes(r);
                        break;
                    case 4:
                        // Listando top 10 livros mais requisitados
                        top10_livros_mais_requisitados(B);
                        break;
                    default:
                        printf("Op��o inv�lida!\n");
                }
                break;
            case 4:
                // Determinando mem�ria ocupada
                // Implementar l�gica para determinar a mem�ria ocupada
                break;
            case 5:
                // Guardando dados
                escreverLivroFile("Livros.txt", B->HLivros);
                escreverRequesicaoUnica("Requisicoes.txt", r);
                atualizarFileRecoes(R);
                break;
            case 6:
                // Gravando XML
                EscreverXML(B);
                break;
            case 7:
                // Saindo do programa
                DestruirLRcoes(r);
                DestruirBiblioteca(B);
                DestruirListaReqs(R);
                free(D);
                free(C);
                free(F);
                printf("Saindo do programa...\n");
                return 0;
            default:
                printf("Op��o inv�lida!\n");
        }
    }
}
