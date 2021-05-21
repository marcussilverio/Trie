#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include "trie.h"

char *entrada[3];
void comando();
void le_entradas();
void inserir(Node **);
void remover(Node **);
void buscar(Node **);
void imprimir(Node **);
void salvar(char *, Node **);
void carregar(char *, Node **);
void prefixo(char *, Node **);
void sair(Node **);

#endif