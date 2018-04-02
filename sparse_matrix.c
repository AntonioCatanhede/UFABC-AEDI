#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long int ulli;

typedef struct node{
    double value; //8
    ulli col, row; //8
    struct node *nextr, *nextc; //16
}Node;

typedef struct head{
    ulli pos;
    struct head *next;
    Node *node; //8
}Head;

typedef struct first{
    ulli numc, numr; //16
    Head *row, *col; //16
}First;

Head* InsertHead(Head **topo, ulli val)
{
    Head *curr, *tmp;
    curr = *topo;
    
    if(curr->pos > val){
        tmp = malloc(sizeof(Head));
        tmp->pos = val;
        tmp->next = *topo;
        **topo = *tmp;
        return tmp;
    }
    
    while(curr !=NULL || curr->pos < val) curr = curr->next;
    

}

void InsertFirstNode(First *first,  ulli row, ulli col, double val)
{
    Node *tmp =  malloc(sizeof(Node))
    tmp->col= col;
    tmp->row = row;
    tmp->value = val;
    
    Head *c, *r;
    c = first->col;
    r = first->row;
    
    first->col = malloc(sizeof(Node));
    first->row = malloc(sizeof(Node));
        
    c->pos = col;
    c->node = tmp;
    c->next = NULL;
        
    r->pos = row;
    r->node = tmp;
    r->next = NULL;

}


void InsertNode(First *first, ulli row, ulli col, double val)
{
    Node *tmp = malloc(sizeof(Node));

    tmp->col=col;
    tmp->row=row;
    tmp->value=val;
    tmp->nextc = NULL;
    tmp->nextr = NULL;
    
    Head *c, *r;
    c = first->col;
    r = first->row;
    
    
    while(c->next!=NULL && c->next->pos<=col) c = c->next;
    while(r->next!=NULL && r->next->pos<=row) r = r->next;
    
    Head *h_tmp;
    
    if(c->next == NULL){
        h_tmp = malloc(sizeof(Head));
        h_tmp->node = tmp;
        h_tmp->pos = col;
        c->next = h_tmp;
    }else if(c->next->pos <  col){
        h_tmp = malloc(sizeof(Head));
        h_tmp->node = tmp;
        h_tmp->pos = col;
        h_tmp->next = c->next;
        c->next = h_tmp;
        
    }

    if(r->next == NULL){
        h_tmp = malloc(sizeof(Head));
        h_tmp->node = tmp;
        h_tmp->pos = row;
        r->next = h_tmp;
    }else if(r->next->pos <  row){
        h_tmp = malloc(sizeof(Head));
        h_tmp->node = tmp;
        h_tmp->pos = row;
        h_tmp->next = r->next;
        r->next = h_tmp;
    }
    
    

}

void PrintMatrix(First *first)
{
    
}

void ReadMatrix(ulli nums, First *first)
{
    ulli i, r, c;
    double val;
    
    for(i=0; i<nums; i++)
    {
        scanf("%llu %llu %lf", &r, &c, &val);
        if(i==0) InsertFirstNode(first, r, c, val);
        else InsertNode(first, r, c, val);
    }
}

int main()
{

    First *firstA = malloc(sizeof(First));
    First *firstB = malloc(sizeof(First));
    ulli NA, NB;
    
    
    firstA->row = NULL;
    firstA->col = NULL;
    
    firstB->row = NULL;
    firstB->col = NULL;
    
    //scanf("%llu %llu %llu %llu %llu %llu", &(firstA->numr), &(firstA->numc), &NA, &(firstB->numr), &(firstB->numc), &NB);
    /*
    firstA->numr = LA;
    firstA->numc = CA;
    firstB->numr = LB;
    firstB->numc = CB;
    */
    //printf("%llu %llu %llu %llu %llu %llu\n", firstA->numr, firstA->numc, NA, firstB->numr, firstB->numc, NB);
    


}
