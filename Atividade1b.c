#include <stdio.h>
#include <stdlib.h> // Para usarmos malloc, free, etc

typedef struct LinkedNode LinkedNode;
struct LinkedNode {
  int RA;
  int CodTopico;
  LinkedNode *next;
};

LinkedNode *InsertAfter(LinkedNode* list, int RA, int CodTopico) {
  
  LinkedNode *tmp = malloc(sizeof(LinkedNode));
  if(tmp == NULL) return NULL;
  
  tmp->RA = RA;
  tmp->CodTopico = CodTopico;
  tmp->next = list->next;
  list->next=tmp;
  return tmp;
}

LinkedNode *BuscaRA(LinkedNode* first, int RA){
  LinkedNode *curr, *prev;
  curr=first;
/*
  while(curr!=NULL){
    if(curr->next==NULL) return curr;
    if(curr->RA==RA){
      do{
        prev = curr;
        curr=curr->next;
      }while(curr->RA==RA && curr!=NULL);
      return prev;
    }else{
      prev = curr;
      curr=curr->next;
    }
  }
  return prev;*/
  while(curr != NULL && curr->RA != RA){
    prev = curr;
    curr = curr->next;
  }
  
  if(curr == NULL){ //adiciono ao final
    return prev;
  }else{
    while(curr != NULL && curr->RA == RA){
      prev = curr;
      curr = curr->next;
    }
    return prev;
  }
  
}

LinkedNode *lerSeq () {

  LinkedNode* first = NULL;
  LinkedNode* last = NULL;
  
  
  int RA=0, CodTopico=0;
  
  do{
    scanf("%d %d", &RA, &CodTopico);
    if(RA!=-1 || CodTopico!=-1){
      if (first==NULL){
        first=malloc(sizeof(LinkedNode));
        first->RA=RA;
        first->CodTopico=CodTopico;
        first->next=NULL;
      }else{
        last=BuscaRA(first, RA);
        InsertAfter(last, RA, CodTopico);
      }
    }
  }while(RA!=-1 || CodTopico!=-1);
  
  return first;
}

void printSeq(LinkedNode *seq){ // Imprimindo bonitinho
  LinkedNode *curr = seq;
  while (curr != NULL) {
    printf("%d %d\n", curr->RA, curr->CodTopico);
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
