#ifndef TRIE_H
#define TRIE_H
#define false 0
#define true 1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct node
{
    char *conteudo;
    short int folha;
    struct node *filho[26];
};
typedef struct node Node;
typedef Node *Raiz;
Node *cria_trie();
Node *cria_no();
void insere_trie(char *, char *, Node **);
void remove_trie(char *, Node **);
void imprime_trie(Node **, char *);
void imprime_prefix_trie(Node **, char *, char *k);
void salva_trie(FILE *ar, Node **, char *);
void libera_trie(Node **);
int busca_trie(char *, Node **);
int verifica_filho(Node *);

#endif