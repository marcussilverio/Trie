#include "biblioteca.h"
//refiz a função e testei no ubuntu pra ter certeza que funcionava.
void le_entradas()
{
    int i;
    for (i = 0; i < 3; i++)
    {
        entrada[i] = (char *)calloc(1000, sizeof(char));
    }
    scanf("%s", entrada[0]);
    if (entrada[0][0] == '+')
    {
        scanf("%s %s", entrada[1], entrada[2]);
    }
    else if (entrada[0][0] != 'F' && entrada[0][0] != 'p')
    {
        scanf("%s", entrada[1]);
    }
    fflush(stdin);
    return;
}
void comando(Node **raiz)
{
    switch (*entrada[0])
    {
    case '+':
        inserir(raiz);
        break;
    case '-':
        remover(raiz);
        break;
    case '?':
        buscar(raiz);
        break;
    case 'p':
        imprimir(raiz);
        break;
    case 'w':
        salvar(entrada[1], raiz);
        break;
    case 'l':
        libera_trie(raiz);
        carregar(entrada[1], raiz);
        break;
    case 'F':
        sair(raiz);
        break;
    case 'P':
        prefixo(entrada[1], raiz);
        break;
    default:
        printf("Opcao invalida!\n");
        break;
    }
    return;
}
void inserir(Node **raiz)
{
    if (busca_trie(entrada[1], raiz))
    {
        //corrigido o erro em que não fazia de fato a sobrescrita.
        insere_trie(entrada[1], entrada[2], raiz);
        printf("[chave \"%s\" sobrescrita]\n", entrada[1]);
    }
    else
    {
        insere_trie(entrada[1], entrada[2], raiz);
        printf("[chave \"%s\" inserida]\n", entrada[1]);
    }
    return;
}
void remover(Node **raiz)
{
    if (busca_trie(entrada[1], raiz))
    {
        remove_trie(entrada[1], raiz);
        printf("[chave \"%s\" removida]\n", entrada[1]);
    }
    else
    {
        printf("[chave \"%s\" nao encontrada]\n", entrada[1]);
    }
    return;
}
void buscar(Node **raiz)
{
    if (busca_trie(entrada[1], raiz))
    {
        printf("\"%s\": \"%s\"\n", entrada[1], entrada[0]);
    }
    else
    {
        printf("[chave \"%s\" nao encontrada]\n", entrada[1]);
    }
    return;
}
void imprimir(Node **raiz)
{
    char *chave;
    chave = (char *)calloc(1000, sizeof(char));
    printf("{");
    if (*raiz == NULL) //corrigido o erro de imprimir apenas } quando a arvore esta vazia
        printf(" ");
    else
        imprime_trie(raiz, chave);
    printf("\b}\n");
    free(chave);
    return;
}
void salvar(char *arquivo, Node **raiz)
{
    FILE *arq = fopen(arquivo, "a");
    fclose(arq);
    arq = fopen(arquivo, "r+");
    char *chave;
    chave = (char *)calloc(1000, sizeof(char));
    fprintf(arq, "{");
    if (*raiz == NULL) //corrigido o erro de imprimir apenas } quando a arvore esta vazia
        fprintf(arq, " ");
    else
        salva_trie(arq, raiz, chave);
    fseek(arq, ftell(arq) - 1, SEEK_SET);
    fprintf(arq, "}");
    fclose(arq);
    printf("[arquivo %s salvo]\n", arquivo);
    return;
}
void carregar(char *arquivo, Node **raiz)
{
    FILE *arq = fopen(arquivo, "r");
    char c[2] = "";
    int i;
    char strAux[1000] = "", *chave, *conteudo;

    chave = (char *)malloc(sizeof(char) * 1000);
    conteudo = (char *)malloc(sizeof(char) * 1000);
    strcpy(chave, strAux);
    strcpy(conteudo, strAux);
    i = 1;
    while ((c[0] = fgetc(arq)) != EOF)
    {

        if ((c[0] != '{') && (c[0] != '}') && (c[0] != '\"') && (c[0] != ',') && (c[0] != ' '))
        {
            if ((c[0] == ':'))
                i = 0;
            else
            {
                if (i == 0)
                {
                    strncat(conteudo, c, 1000);
                }
                else
                {
                    strncat(chave, c, 1000);
                }
            }
        }
        if ((c[0] == ',') || (c[0] == '}'))
        {
            insere_trie(chave, conteudo, raiz);
            //corrigido o erro que o conteudo era adicionado com lixo de memoria.
            chave = (char *)malloc(sizeof(char) * 1000);
            conteudo = (char *)malloc(sizeof(char) * 1000);
            strcpy(chave, strAux);
            strcpy(conteudo, strAux);
            i = 1;
        }
    }
    fclose(arq);
    free(chave);
    free(conteudo);
    printf("[Arquivo %s carregado]\n", arquivo);
    return;
}
//adicionada a função que imprime todas as chaves com o prefixo requisitado
void prefixo(char *prefixo, Node **raiz)
{
    char *chave;
    chave = (char *)calloc(1000, sizeof(char));
    printf("{");
    if (*raiz == NULL)
        printf(" ");
    else
        imprime_prefix_trie(raiz, prefixo, chave);
    printf("\b}\n");
    free(chave);
    return;
}
void sair(Node **raiz)
{
    libera_trie(raiz);
    return;
}
