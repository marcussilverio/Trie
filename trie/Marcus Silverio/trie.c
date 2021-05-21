#include "trie.h"
#include "biblioteca.h"
typedef struct node Node;
Node *cria_trie()
{
    return NULL;
}
Node *cria_no()
{
    Node *no;
    int i;
    no = (Node *)malloc(sizeof(Node));

    for (i = 0; i < 26; i++)
    {
        no->filho[i] = NULL;
    }
    no->conteudo = NULL;
    no->folha = false;
    return no;
}
void insere_trie(char *chave, char *conteudo, Node **raiz)
{
    Node *no, *aux;
    char primeiroCaracter = chave[0];
    int posAlfabeto = (int)primeiroCaracter - 97;

    if (primeiroCaracter == '\n' || primeiroCaracter == '\0')
    {
        return;
    }

    if (*raiz == NULL)
    {
        no = cria_no();
        *raiz = no;
    }

    aux = *raiz;

    if (aux->filho[posAlfabeto] == NULL)
    {
        no = cria_no();
        aux->filho[posAlfabeto] = no;
    }
    if (chave[1] == '\0' || chave[1] == '\n')
    {
        aux->filho[posAlfabeto]->folha = true;
        aux->filho[posAlfabeto]->conteudo = conteudo;
    }
    insere_trie(&chave[1], conteudo, &aux->filho[posAlfabeto]);
    return;
}
int busca_trie(char *chave, Node **raiz)
{
    Node *aux = *raiz;
    char primeiroCaracter = chave[0];
    int posAlfabeto = (int)primeiroCaracter - 97;
    if (aux == NULL)
        return 0;

    if (primeiroCaracter == '\n' || primeiroCaracter == '\0')
    {
        if (aux->folha)
        {
            strcpy(entrada[0], aux->conteudo);
            return 1;
        }
        return 0;
    }
    if (aux->filho[posAlfabeto] != NULL)
    {
        busca_trie(&chave[1], &aux->filho[posAlfabeto]);
    }
    else
    {
        return 0;
    }
}
int verifica_filho(Node *no)
{
    int i;
    if (no != NULL)
    {
        for (i = 0; i < 26; i++)
        {
            if (no->filho[i] != NULL)
                return true;
        }
    }
    return false;
}
void remove_trie(char *chave, Node **raiz)
{
    Node *aux = *raiz;
    char primeiroCaracter = chave[0];
    int posAlfabeto = (int)primeiroCaracter - 97;

    if (raiz == NULL)
        return;

    if (primeiroCaracter == '\0' || primeiroCaracter == '\n')
    {
        aux->folha = false;
        aux->conteudo = NULL;
        return;
    }
    remove_trie(&chave[1], &aux->filho[posAlfabeto]);
    if (verifica_filho(aux->filho[posAlfabeto]) || aux->filho[posAlfabeto]->folha)
    {
        return;
    }
    else
    {
        aux->filho[posAlfabeto] = NULL;
        free(aux->filho[posAlfabeto]); //corrigido erro de liberação dos nodos
        return;
    }
    return;
}
void imprime_trie(Node **raiz, char *k)
{
    Node *aux = *raiz;
    int i = 0;
    char letra[2] = "";
    char *chave;
    chave = (char *)calloc(10000, sizeof(char));

    if (!verifica_filho(aux))
    {
        if (aux != NULL)
        {
            if (aux->folha)
            {
                printf("\"%s\":\"%s\",", k, aux->conteudo);
            }
            else
            {
                printf(" ");
            }
        }
        return;
    }
    else
    {
        if (aux->folha)
        {
            printf("\"%s\":\"%s\",", k, aux->conteudo);
        }
        do
        {
            strcpy(chave, k);
            letra[0] = (char)i + 97;
            if (aux->filho[i])
            {
                strcat(chave, letra);
                if (aux->filho[i]->folha)
                {
                    imprime_trie(&aux->filho[i], chave);
                }
                else
                {
                    imprime_trie(&aux->filho[i], chave);
                }
            }
            i++;

        } while (i < 26);
    }
    return;
}
void imprime_prefix_trie(Node **raiz, char *prefixo, char *k)
{
    Node *aux = *raiz;
    int i = 0;
    char letra[2] = "";
    char *chave;
    chave = (char *)calloc(10000, sizeof(char));

    if (!verifica_filho(aux))
    {
        if (aux != NULL)
        {
            if (aux->folha && strncmp(prefixo, k, strlen(prefixo)) == 0)
            {
                printf("\"%s\":\"%s\",", k, aux->conteudo);
            }
            else
            {
                printf(" ");
            }
        }
        return;
    }
    else
    {
        if (aux->folha && strncmp(prefixo, k, strlen(prefixo)) == 0)
        {
            printf("\"%s\":\"%s\",", k, aux->conteudo);
        }
        do
        {
            strcpy(chave, k);
            letra[0] = (char)i + 97;
            if (aux->filho[i])
            {
                strcat(chave, letra);
                if (aux->filho[i]->folha)
                {
                    imprime_prefix_trie(&aux->filho[i], prefixo, chave);
                }
                else
                {
                    imprime_prefix_trie(&aux->filho[i], prefixo, chave);
                }
            }
            i++;

        } while (i < 26);
    }
    return;
}
void salva_trie(FILE *arq, Node **raiz, char *k)
{
    Node *aux = *raiz;
    int i = 0;
    char letra[2] = "";
    char *chave;
    chave = (char *)calloc(10000, sizeof(char));

    if (!verifica_filho(aux))
    {
        if (aux != NULL)
        {
            if (aux->folha)
            {
                fprintf(arq, "\"%s\":\"%s\",", k, aux->conteudo);
            }
        }
        return;
    }
    else
    {
        if (aux->folha)
        {
            fprintf(arq, "\"%s\":\"%s\",", k, aux->conteudo);
        }
        do
        {
            strcpy(chave, k);
            letra[0] = (char)i + 97;
            if (aux->filho[i])
            {
                strcat(chave, letra);
                if (aux->filho[i]->folha)
                {
                    salva_trie(arq, &aux->filho[i], chave);
                }
                else
                {
                    salva_trie(arq, &aux->filho[i], chave);
                }
            }
            i++;

        } while (i < 26);
    }
    return;
}
void libera_trie(Node **raiz)
{

    Node *aux = *raiz;
    int i = 0;

    if (verifica_filho(aux))
    {
        for (i = 0; i < 26; i++)
        {
            if (aux->filho[i])
            {
                libera_trie(&aux->filho[i]);
            }
        }
    }
    if (aux == NULL)
        return;
    (*raiz) = NULL;
    free(*raiz); //corrigido erro de liberação duplicada
    return;
}