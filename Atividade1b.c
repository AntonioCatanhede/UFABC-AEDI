#include <stdio.h>
#include <stdlib.h> // Para usarmos malloc, free, etc

typedef struct LinkedNode LinkedNode;
struct LinkedNode {
  unsigned int ra;
  unsigned int duvida;
  LinkedNode *next;
};

LinkedNode* appendNode(LinkedNode *last, int ra, int duvida) {

  if (last != NULL)
    if (last->next != NULL) return NULL;

  LinkedNode *tmp = malloc(sizeof(LinkedNode));
  if (tmp == NULL) {
    return NULL;
  }

  tmp->ra = ra;
  tmp->duvida=duvida;
  tmp->next = NULL;

  if (last != NULL)
    last->next = tmp;

  return tmp;
}

LinkedNode* InsertAfter(LinkedNode* list, int ra, int duvida) {
  
  LinkedNode *tmp = malloc(sizeof(LinkedNode));

  tmp->ra = ra;
  tmp->duvida = duvida;
  tmp->next = list->next;
  list->next=tmp;
  
  return tmp;
}

LinkedNode *BuscaRA(LinkedNode* first, int ra){
  LinkedNode *curr, *last;
  curr=first;

  while(curr!=NULL){
    if (curr->next==NULL) return curr;
    if(curr->ra==ra){
      while(curr->ra==ra && curr->next!=NULL){
        last = curr;
        curr=curr->next;
      }
      return last;
    }else{
      curr=curr->next;
    }
  }
  return curr;
}

LinkedNode *lerSeq () {

  LinkedNode* first = NULL;
  LinkedNode* last = NULL;
  
  
  int ra=0, duvida=0;
  
  do{
    scanf("%d %d", &ra, &duvida);
    if(ra>0 && duvida>0){
      if (first==NULL){
        first=appendNode(first, ra, duvida);
        last=first;
      }else{
        last=BuscaRA(first, ra);
        InsertAfter(last, ra, duvida);
      }
    }
  }while(ra!=-1 || duvida!=-1);
  
  return first;
}

void printSeq(LinkedNode *seq){ // Imprimindo bonitinho
  LinkedNode *curr = seq;
  while (curr != NULL) {
    printf("%d %d\n", curr->ra, curr->duvida);
    curr = curr->next;
  }
}


void liberaLista(LinkedNode* list){
  LinkedNode *tmp, *curr;
  curr=list;
  
  while(curr!=NULL){
    tmp=curr->next;
    free(curr);
    curr = tmp;
  }
}


int main (void) {
  
  LinkedNode *listDuvidas;

  listDuvidas = lerSeq();
  printSeq(listDuvidas);

  liberaLista(listDuvidas);

  return 0;
}
