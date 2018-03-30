#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedNode LinkedNode;
struct LinkedNode{
    double valores;
    LinkedNode *next;
};

typedef struct Pilha Pilha;
struct Pilha {
    LinkedNode * topo;
};

void empilhar(Pilha * pilha, double valor){
    LinkedNode *tmp = malloc(sizeof(LinkedNode));
    tmp->valores = valor;
    tmp->next = NULL;
    
    if(pilha->topo==NULL){
        pilha->topo = tmp;
    }else{
        tmp->next=pilha->topo;
        pilha->topo=tmp;
    }

}

int desempilhar(Pilha * pilha){
    LinkedNode *tmp = pilha->topo;
    pilha->topo=pilha->topo->next;
    free(tmp);
    
    
}

int valido(LinkedNode *node){
    if(node==NULL) return 0;
    else return 1;
}

int main(int argc, char** argv) {
    
    char expr[101];
    char tmp[2];
    tmp[1]='\0';
    
    Pilha *p = malloc(sizeof(Pilha));
    
    scanf("%100s", expr);    
    
    int i=0;
    LinkedNode *n1=NULL, *n2=NULL, *n3=NULL;
    
    while(expr[i]!='\0'){
      tmp[0]=expr[i];
        switch (expr[i]){
            case 'h'://n1 x 3 
              if(!valido(n1)){
                printf("ERRO");
                return (-1);
              }
                n1->valores *= 3.0;
            break;
            
            case 'g': //(n1 x n2) + n3 
              if(!valido(n1) || !valido(n2) || !valido(n3)){
                printf("ERRO");
                return (-1);
              }
                n3->valores = (n3->valores*n2->valores)+n1->valores;
                desempilhar(p);
                desempilhar(p);
            break;
            
            case 'f'://(n1 x n1) - ((n2) / 2) + n3
              if(!valido(n1) || !valido(n2) || !valido(n3)){
                printf("ERRO");
                return (-1);
              }
              n3->valores = (n3->valores*n3->valores)-(n2->valores/2.0)+n1->valores;
              desempilhar(p);
              desempilhar(p);
            break;
            
            case '+'://n1 + n2 
                if(!valido(n1) || !valido(n2)){
                  printf("ERRO");
                  return (-1);
                }
                n2->valores = n1->valores + n2->valores;
                desempilhar(p);
            break;
            
            case '-'://n1 - n2 
                if(!valido(n1) || !valido(n2)){
                  printf("ERRO");
                  return (-1);
                }
                n2->valores = n2->valores - n1->valores;
                desempilhar(p);
            break;
            
            default:
                empilhar(p, atof(tmp));
        }
        n1=NULL;
        n2=NULL;
        n3=NULL;
        if(p != NULL){
          n1=p->topo;
          if(p->topo->next != NULL){
              n2=p->topo->next;
              if(p->topo->next->next != NULL){
                  n3=p->topo->next->next;
              }
          }
        }
        i++;
    }
    
    if(p->topo->next==NULL && p!=NULL){
      printf("%f", p->topo->valores);  
    }else{
      printf("ERRO");  
    }
    
    return (0);
}
