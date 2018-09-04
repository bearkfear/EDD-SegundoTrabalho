#define TAM 20
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main(void)
{
    setlocale(LC_ALL, "");

    Cidade cid[TAM], *v;
    v = cid;

    inicializa(v);

    short int opcao = 0;
    while (1)
    {
        system("cls");

        printf(
            "MENU PRINCIPAL DO MAPA RODOVIÁRIO\n\n"
            "1. Cadastrar cidade\n"
            "2. Cadastrar caminho entre cidades\n"
            "3. Obter vizinhos de uma cidade\n"
            "4. Obter rotas entre cidades\n"
            "5. Remover Cidade\n"
            "6. Remover Caminho\n"
            "7. Alterar informações de distância entre cidades\n"
            "8. Alterar informações de cidade\n"
            "9. Sair do programa\n"
            "Digite a sua opcão: ");
        scanf("%hi", &opcao);

        switch (opcao)
        {
        case 1:
        {
            system("cls");
            v = obterCadastrarCidade(v);
            getchar();
            break;
        }
        case 2:
        {
            system("cls");
            obterCadastrarCaminho(v);
            break;
        }
        case 3:
        {
            system("cls");
            limpaBuffer();

            printf("Digite o nome da cidade: ");
            char valor[50];
            getString(valor);
            mostrarCidade(v, valor);
            getchar();
            break;
        }
        case 4:
        {
            // obter rotas entre duas cidades
            break;
        }
        case 5:
        {
            obterRemoverCidade(v);
            // remover cidade
            break;
        }
        case 6:
        {
            obterRemoverCaminho(v);
            break;
        }
        case 7:
        {
            //  Alterar informações de distância entre cidades
        }
        case 8:
        {
            obterAlterarCidade(v);
            break;
        }
        case 9:
        {
            return 0;
            break;
        }
        default:
        {
            printf("\n\tOPÇÃO INCORRETA!\n\n");
        }
        }
    }
    return 0;
}
