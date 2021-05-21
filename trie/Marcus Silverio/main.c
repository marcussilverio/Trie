#include "biblioteca.h"
int main()
{
  Raiz *raiz;
  raiz = (Node **)malloc(sizeof(Node));
  *raiz = cria_trie();
  do
  {
    le_entradas();
    comando(raiz);
  } while (entrada[0][0] != 'F');
  free(raiz);

  return 0;
}
