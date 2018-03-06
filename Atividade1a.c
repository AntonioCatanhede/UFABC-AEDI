#include <stdio.h>
#include <stdlib.h> // Para usarmos malloc, free, etc

typedef struct LinkedNode LinkedNode;
struct LinkedNode {
  int ra;
  int duvida;
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

LinkedNode *lerSeq () {

  LinkedNode* first = NULL;
  LinkedNode* last = NULL;
  
  
  int ra=0, duvida=0;
  
  do{
    scanf("%d %d", &ra, &duvida);
    if(ra!=-1 && duvida!=-1){
      if (first==NULL){
        first=appendNode(first, ra, duvida);
        last=first;
      }else{
        last->next=appendNode(last, ra, duvida);
        last=last->next;
      }
    }
  }while(ra!=-1 && duvida!=-1);
  
  return first;
}

void printSeq(LinkedNode *seq){ // Imprimindo bonitinho
  LinkedNode *curr = seq;
  while (curr != NULL) {
    printf("%d %d", curr->ra, curr->duvida);
    curr = curr->next;
    printf("\n");
  }
}



int main (void) {
  
  LinkedNode *listDuvidas;

  listDuvidas = lerSeq();
  printSeq(listDuvidas);


  return 0;
}
