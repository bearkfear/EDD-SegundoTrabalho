/**
 * 
 * FUNÇÕES DE CONVERSÃO DE CASE (LOWER OR UPPER) NÃO IRÃO FUNCIONAR SEM A STRING ESTAR PRÉVIAMENTE DECLARADA NA MEMÓRIA
 * 
 * */

#include <string.h>
#include <stdio.h>
void capitalize(char *str);

char *strlwr(char *str);

char *strupr(char *str);

void *getString(char *saida);

char *strlwr(char *str)
{
    char *string = str;
    for (int i = 0; i < strlen(string); i++)
    {
        if (*(string + i) >= 65 && *(string + i) <= 90)
        {
            *(string + i) = *(string + i) + 32;
        }
    }
    return str;
}

char *strupr(char *str)
{
    char *string = str;
    for (int i = 0; i < strlen(string); i++)
    {
        if (*(string + i) >= 97 && *(string + i) <= 122)
        {
            *(string + i) = *(string + i) - 32;
        }
    }
    return str;
}

void *getString(char *saida)
{

    fgets(saida, 50, stdin);
    int tamanho = strlen(saida);
    *(saida + (tamanho - 1)) = '\0';
}

void capitalize(char *str)
{

    char *entrada;
    entrada = str;

    if (entrada != NULL)
    {

        int tamanho = strlen(entrada);

        int i = 0;
        while (i < tamanho)
        {

            if (*(entrada + i) >= 97 && *(entrada + i) <= 122)
            {
                *(entrada + i) -= 32;
            }

            while (*(entrada + i) != ' ' && i < tamanho)
            {
                i++;
            }
            i++;
        }
    }
}
