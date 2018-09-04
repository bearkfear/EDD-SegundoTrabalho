#include <string.h>
#include "stringPlus.h"

typedef struct grafo
{
    int chave;
    char nomCidade[50];
    struct aresta *caminho;
} Cidade;
typedef struct aresta
{
    struct grafo *cidade;
    int peso;
    struct aresta *prox;
} Caminho;

void limpaBuffer()
{
    while (getchar() != '\n')
    {
    }
}

int buscarCidade(Cidade *cid, char nomeCidade[])
{

    if (cid == NULL || nomeCidade == NULL)
    {
        return -1;
    }

    char nome[50];
    strcpy(nome, nomeCidade);
    strcpy(nome, strlwr(nome));

    for (int i = 0; i < TAM; i++)
    {

        char nomDaCidade[50];
        strcpy(nomDaCidade, (cid + i)->nomCidade);

        if (strcmp(strlwr(nomDaCidade), nome) == 0)
        {
            return i;
        }
    }
    return -1;
}

void mostrarCidade(Cidade *cid, char nomCidade[])
{

    // verifica parâmetros

    if (!cid || !nomCidade)
    {
        return;
    }

    // buscar cidade para ser exibida;

    Cidade *origem = cid;
    int resultado = buscarCidade(origem, nomCidade);

    if (resultado == -1)
    {
        printf("Cidade não existe!\n");
        return;
    }
    origem = (origem + resultado);
    Caminho *caminho = origem->caminho;

    if (caminho == NULL)
    {
        printf("Cidade não tem rotas cadastradas, cadastre uma!\n");
        return;
    }

    while (caminho->prox != NULL)
    {

        printf("\tDe: \t\t%s\n", origem->nomCidade);
        printf("\tPara: \t\t%s\n", caminho->cidade->nomCidade);
        printf("\tDistância: \t%d km\n\n", caminho->peso);

        caminho = caminho->prox;
    }

    if (caminho != NULL)
    {
        printf("\tDe: \t\t%s\n", origem->nomCidade);
        printf("\tPara: \t\t%s\n", caminho->cidade->nomCidade);
        printf("\tDistância: \t%d Km\n\n", caminho->peso);
    }
}

void obterAlterarCidade(Cidade *v)
{

    limpaBuffer();
    printf("\tDigite o nome da cidade: ");
    char nomCidade[50];
    getString(nomCidade);

    if (strlen(nomCidade) < 2)
    {

        printf("Valor invalido!\nPressione qualquer tecla para continuar...");
        getchar();
        return;
    }
    int chave = buscarCidade(v, nomCidade);
    if (chave == -1)
    {

        printf("Cidade não existe!\n");
        printf("Pressione qualquer tecla para continuar...");
        getchar();
    }
    else
    {
        Cidade *cidade = (v + chave);
        printf("\tDigite um novo nome para a cidade: ");
        getString(nomCidade);
        capitalize(nomCidade);
        strcpy(cidade->nomCidade, nomCidade);
        printf("Nome da cidade alterado com sucesso!\naperte qualquer tecla para continuar: ");
        getchar();
    }
}

Caminho *removerListaCaminho(Cidade *l, Caminho *c, int peso)
{

    Caminho *ant = NULL;
    Caminho *p = c;

    while (p != NULL && p->peso != peso && p->cidade != l)
    {
        ant = p;
        p = p->prox;
    }

    if (p == NULL)
    {
        return c;
    }

    if (ant == NULL)
    {
        c = p->prox;
    }
    else
    {
        ant->prox = p->prox;
    }
    free(p);
    return c;
}

void removerCaminho(Cidade *v, char origem[], char destino[], unsigned int peso)
{

    // Verifica parâmetros
    if (!v || !origem || !destino || peso < 0)
    {
        printf("Valores invalidos!\n");
        getchar();
        return;
    }

    int chaveOrigem = buscarCidade(v, origem);
    int chaveDestino = buscarCidade(v, destino);

    if (chaveDestino < 0)
    {
        printf("Não foi possível remover caminho. %s não está cadastrado!\n", destino);
        getchar();
        return;
    }

    Cidade *ori = (v + chaveOrigem);
    Cidade *dest = (v + chaveDestino);

    Caminho *listaOri = ori->caminho;
    Caminho *listaDest = dest->caminho;

    ori->caminho = removerListaCaminho(dest, listaOri, peso);
    dest->caminho = removerListaCaminho(ori, listaDest, peso);
}

void obterRemoverCaminho(Cidade *v)
{

    printf("Digite o nome da cidade: ");
    limpaBuffer();
    char origem[100];
    getString(origem);
    mostrarCidade(v, origem);

    printf("Digite o nome da cidade destino: ");
    char destino[100];
    getString(destino);

    printf("Digite a distancia em Km: ");
    int peso = 0;
    scanf("%i", &peso);
    limpaBuffer();

    removerCaminho(v, origem, destino, (unsigned int)peso);
}

void removerCidade(Cidade *cid, char nomCidade[])
{

    int chave = buscarCidade(cid, nomCidade);

    Cidade *cidade = (cid + chave);

    Caminho *listaCidade = cidade->caminho;
    Caminho *proximo = NULL;
    while (listaCidade != NULL)
    {
        proximo = listaCidade->prox;
        removerCaminho(cid, nomCidade, listaCidade->cidade->nomCidade, listaCidade->peso);
        listaCidade = proximo;
    }
    cidade->chave = -1;
    strcpy(cidade->nomCidade, "");
    cidade->caminho = NULL;
}

void obterRemoverCidade(Cidade *cid)
{

    printf("Digite o nome da cidade: ");
    limpaBuffer();

    char nomCid[50];
    getString(nomCid);

    if (buscarCidade(cid, nomCid) == -1)
    {
        printf("Cidade não existe!");
        getchar();
    }
    else
    {
        removerCidade(cid, nomCid);
    }
}

Cidade *cadastrarCidade(Cidade *cid, char nomeCidade[])
{

    if (cid == NULL || nomeCidade == NULL)
    {
        return cid;
    }

    if (buscarCidade(cid, nomeCidade) == -1)
    {
        int chave = 0;
        for (int i = 0; i < TAM; ++i)
        {
            if ((cid + i)->chave == -1)
            {
                chave = i;
                break;
            }
        }

        (cid + chave)->chave = chave;
        strcpy((cid + chave)->nomCidade, nomeCidade);
    }
    else
    {
        printf("\nCidade já está cadastrada!\n");
    }

    return cid;
}

Cidade *obterCadastrarCidade(Cidade *v)
{
    printf("Digite o nome da cidade: ");
    char aux[50];
    limpaBuffer();
    getString(aux);
    capitalize(aux);
    return cadastrarCidade(v, aux);
}

void conectaAresta(Cidade *vertice, Caminho *aresta)
{

    if (vertice->caminho == NULL)
    {
        vertice->caminho = aresta;
    }
    else
    {

        Caminho *aux = vertice->caminho;

        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }

        if (aux != NULL && aux->prox == NULL)
        {
            aux->prox = aresta;
        }
    }
}

Caminho *criaAresta(Cidade *destino, int peso)
{

    Caminho *aresta = (Caminho *)malloc(sizeof(Caminho));
    aresta->peso = peso;
    aresta->cidade = destino;
    aresta->prox = NULL;
}

void adicionarAresta(Cidade *cid, char origem[], char destino[], int peso)
{

    // VERIFICA PARÂMETROS
    if (!cid || !origem || !destino || peso < 0)
    {
        printf("Valores incorretos!\n");
        return;
    }

    // BUSCA PELAS CIDADES
    Cidade *ori, *dest;

    int result = buscarCidade(cid, origem);
    if (result == -1)
    {
        printf("Cidade de origem não existe!\n");
        return;
    }
    else
    {
        ori = (cid + result);
    }

    result = buscarCidade(cid, destino);
    if (result == -1)
    {
        printf("Cidade de destino não existe!\n");
        return;
    }
    else
    {
        dest = (cid + result);
    }

    // ALOCA DINAMICAMENTE AS ARESTAS

    Caminho *aresta = criaAresta(dest, peso);
    Caminho *aresta2 = criaAresta(ori, peso);
    // CONECTA AS ARESTAS NAS LISTAS ENCADEADAS
    conectaAresta(ori, aresta);
    conectaAresta(dest, aresta2);
}

void obterCadastrarCaminho(Cidade *v)
{

    int peso;
    char origem[30];
    char destino[30];

    limpaBuffer();
    printf("Digite o nome da cidade de origem: ");
    getString(origem);

    printf("Digite o nome da cidade de destino: ");
    getString(destino);

    capitalize(origem);
    capitalize(destino);

    printf("Digite a distância em KM de %s até %s: ", origem, destino);
    scanf("%i", &peso);

    adicionarAresta(v, origem, destino, peso);
}

void inicializa(Cidade *v)
{

    for (int i = 0; i < TAM; i++)
    {
        (v + i)->chave = -1;
        (v + i)->caminho = NULL;
        strcpy((v + i)->nomCidade, "");
    }

    cadastrarCidade(v, "Passo Fundo");
    cadastrarCidade(v, "POA");
    cadastrarCidade(v, "Pelotas");
    cadastrarCidade(v, "Bagé");
    cadastrarCidade(v, "São Gabriel");
    cadastrarCidade(v, "Alegrete");
    cadastrarCidade(v, "São Borja");
    cadastrarCidade(v, "Santiago");
    cadastrarCidade(v, "Cruz Alta");
    cadastrarCidade(v, "SM");
    cadastrarCidade(v, "Uruguaiana");

    adicionarAresta(v, "Passo Fundo", "POA", 289);
    adicionarAresta(v, "POA", "Pelotas", 261);
    adicionarAresta(v, "Pelotas", "Bagé", 189);
    adicionarAresta(v, "Bagé", "São Gabriel", 268);
    adicionarAresta(v, "São Gabriel", "Alegrete", 204);
    adicionarAresta(v, "Alegrete", "São Borja", 315);
    adicionarAresta(v, "São Borja", "Santiago", 141);
    adicionarAresta(v, "Santiago", "Cruz Alta", 242);
    adicionarAresta(v, "Uruguaiana", "SM", 381);
    adicionarAresta(v, "Cruz Alta", "Passo Fundo", 149);
    adicionarAresta(v, "Cruz Alta", "SM", 134);
    adicionarAresta(v, "SM", "Santiago", 152);
    adicionarAresta(v, "SM", "Alegrete", 258);
    adicionarAresta(v, "SM", "São Gabriel", 182);
    adicionarAresta(v, "SM", "Bagé", 239);
    adicionarAresta(v, "SM", "POA", 291);
    adicionarAresta(v, "POA", "Bagé", 337);
}
