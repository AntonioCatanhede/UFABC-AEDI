/*
Victor de Oliveira  11095612
Marcos Seiti Suzuki 11121816
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedNode LinkedNode;
struct  LinkedNode{
    int ra, nota;
    char nome[50];
    LinkedNode *next, *prev; 
};

LinkedNode *appendNode(LinkedNode *last, int ra, char nome[50], int nota) 
{
    LinkedNode *tmp = malloc(sizeof(LinkedNode));
    if (tmp == NULL)    return NULL; 

    tmp->ra = ra;
    strcpy(tmp->nome,nome);
    tmp->nota = nota;	
    tmp->next = NULL;
    tmp->prev = NULL; 

    if (last != NULL){   
        last->next = tmp;
        tmp->prev = last;
    }
    return tmp;
}

int buscaLinkedNode(LinkedNode *first, int key)
{
    	
    //if (key <= 0) return NULL;
    int pos = 0;	
    if (first->ra == key) return pos; 
    LinkedNode *aux = first->next;
    if (aux==NULL) return -1;
    while(aux->ra!=key){
        pos += 1;
        aux = aux->next;
        if (aux==NULL) return -1;
    }
    return pos+1;
}

void printaLista(LinkedNode *first)
{
    if (first!=NULL){
        printf("[%d %s %d]",first->ra, first->nome, first->nota);
        printf("\n");
        printaLista(first->next);
    }
}

int compareNodeValue(LinkedNode* node1, LinkedNode* node2, int modo){
    if(modo==1) return (node1->ra > node2->ra);
    else if(modo==2) return (strcmp(node1->nome, node2->nome)>0);
}

int selectionSort(LinkedNode *v, int modo) {
    LinkedNode *i, *j, *min;
    LinkedNode aux;
    long int comp=0;
    
    for (i=v; i->next!=NULL; i = i->next) {
        min = i;
        for (j=i->next; j!=NULL; j=j->next) {
            if (compareNodeValue(min, j, modo))
                min = j;
            comp++;
        }
        
        if (min!=i) {
            aux = *min;
            min->ra = i->ra;
            min->nota = i->nota;
            strcpy(min->nome, i->nome);
            i->ra = aux.ra;
            i->nota = aux.nota;
            strcpy(i->nome, aux.nome);
        }
    }
    
    return comp;
}

int insertionSort(LinkedNode* v, int modo) {
    LinkedNode *i, *j;
    LinkedNode *key = malloc(sizeof(LinkedNode));
    long int comp=0;
     
    for (i=v->next; i!=NULL; i=i->next) {
        *key = *i;
        
        j = i->prev;
        
        while(j!=NULL  && ++comp && compareNodeValue(j, key, modo)) {
            j->next->ra = j->ra;
            j->next->nota = j->nota;
            strcpy(j->next->nome, j->nome);
            j=j->prev;
        }
        if(j){
            j->next->ra = key->ra;
            j->next->nota = key->nota;
            strcpy(j->next->nome, key->nome);
        }else{
            v->next->ra = v->ra;
            v->next->nota = v->nota;
            strcpy(v->next->nome, v->nome);
            v->ra = key->ra;
            v->nota = key->nota;
            strcpy(v->nome, key->nome);
        }
    }
    
    return comp;
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

int main(void){
	
    LinkedNode *first = NULL;
    LinkedNode *last = NULL;
    char opcao;
    char nome[50];
    int ra, nota;
    int alg, modo, comp;

    do{
        scanf("\n%c", &opcao);
        if (opcao=='I'){
            scanf("%d %50s %d", &ra, nome, &nota);
            if (first == NULL){
                first = malloc(sizeof(LinkedNode));
                first->ra = ra;
                strcpy(first->nome,nome);
                first->nota = nota;
                first->next = NULL;
                first->prev = NULL;
                last = first;
            }else{
                last = appendNode(last, ra, nome, nota);}
        }else if(opcao=='O'){
            comp = 0;
            scanf("%d %d", &alg, &modo);
            if (alg==1){
                printf("Comparacoes=%d\n", selectionSort(first, modo));
            }else{
                printf("Comparacoes=%d\n", insertionSort(first, modo));
            }
        }else if(opcao=='M'){
            printaLista(first);
        }else if(opcao=='B'){
            scanf("%d", &ra);
            int posicao = buscaLinkedNode(first, ra);
            printf("Pos=%d\n", posicao);
        }

    }while(opcao!='P');
  
    liberaLista(first);
  
}
