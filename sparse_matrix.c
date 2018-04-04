#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long int ulli;

typedef struct node{
    double value; //8
    ulli i, j; //8
    struct node *r_node, *b_node; //16
}Node;

typedef struct head{
    ulli pos;
    struct head *next;
    Node *node; //8
}Head;

typedef struct sparse_m{
    ulli numc, numr; //16
    Head *row, *col; //16
}Sparse_Matrix;

Head* InsertHead(Head *first, ulli pos)
{
    Head *curr, *tmp;
    curr = first;
    tmp = malloc(sizeof(Head));
    
    if(curr->pos > pos){
        tmp->pos = curr->pos;
        tmp->next = curr->next;
        tmp->node = curr->node;
        
        first->next = tmp;
        first->pos = pos;
        first->node = NULL;
        return first;
    }
    
    while(curr->next !=NULL && curr->next->pos <= pos) curr = curr->next;
    
    if(curr->pos = pos) return curr;
    
    tmp->node  = NULL;
    tmp->pos   = pos;
    tmp->next  = NULL;
    
    if(curr->next == NULL){
        curr->next = tmp;
        return tmp;
    }
    
    tmp->next  = curr->next;
    curr->next = tmp;
    return tmp;

}

void InsertFirstNode(Sparse_Matrix *first,  ulli row, ulli col, double val)
{
    Node *tmp =  malloc(sizeof(Node));
    tmp->i      = row;
    tmp->j      = col;
    tmp->value  = val;
    tmp->b_node = NULL;
    tmp->r_node = NULL;
    
    Head *c, *r;
    
    first->col = malloc(sizeof(Node));
    first->row = malloc(sizeof(Node));
    
    c = first->col;
    r = first->row;
    
    c->pos = col;
    c->node = tmp;
    c->next = NULL;
        
    r->pos = row;
    r->node = tmp;
    r->next = NULL;

}

Node *SearchNode(Node *node, ulli pos, int horizontal){
    Node *curr;
    curr = node;
    
    if(horizontal){
        while(curr->r_node != NULL && curr->r_node->j <= pos) curr = curr->r_node;
    }else{
        while(curr->b_node != NULL && curr->b_node->i <= pos) curr = curr->b_node;
    }
    
    return curr;
}

void InsertNode(Sparse_Matrix *first, ulli row, ulli col, double val)
{
    if(first == NULL) 
    {
        InsertFirstNode(first, row, col, val);
        return;
    }
    
    Node *tmp = malloc(sizeof(Node));

    tmp->i=row;
    tmp->j=col;
    tmp->value=val;
    tmp->b_node = NULL;
    tmp->r_node = NULL;
    
    Head *c, *r;
    c = InsertHead(first->col, col);
    r = InsertHead(first->row, row);
    
    Node *curr;
    
    if(c->node == NULL) c->node = tmp;
    else
    {
        curr = SearchNode(c->node, row, 0);
        if(curr->i > row){
            tmp->b_node = curr->b_node;
            curr->b_node = tmp;
            tmp->r_node = curr->r_node;
            tmp->value = curr->value;
            curr->value = val;
            tmp->i = curr->i;
            curr->i = row;
            tmp->j = curr->j;
            curr->j = col;
        }else if(curr->b_node == NULL){
            curr->b_node = tmp;
        }else{
            tmp->b_node = curr->b_node;
            curr->b_node = tmp;
        }
        
    }
        
    if(r->node == NULL) r->node = tmp;
    else
    {
        curr = SearchNode(r->node, col, 1);
        if(curr->j > col){
            tmp->r_node = curr->r_node;
            curr->r_node = tmp;
            tmp->b_node = curr->b_node;
            tmp->value = curr->value;
            curr->value = val;
            tmp->j = curr->j;
            curr->j = col;
            tmp->i = curr->i;
            curr->i = row;
        }else if(curr->r_node == NULL){
            curr->r_node = tmp;
        }else{
            tmp->r_node = curr->r_node;
            curr->r_node = tmp;
        }
    }
     

}

void PrintMatrix(Sparse_Matrix *first)
{
    
}

void ReadMatrix(ulli nums, Sparse_Matrix *first)
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

    Sparse_Matrix *A = malloc(sizeof(Sparse_Matrix));
    Sparse_Matrix *B = malloc(sizeof(Sparse_Matrix));
    ulli NA, NB;
    
    
    A->row = NULL;
    A->col = NULL;
    
    B->row = NULL;
    B->col = NULL;
    
    //scanf("%llu %llu %llu %llu %llu %llu", &(firstA->numr), &(firstA->numc), &NA, &(firstB->numr), &(firstB->numc), &NB);
    /*
    firstA->numr = LA;
    firstA->numc = CA;
    firstB->numr = LB;
    firstB->numc = CB;
    */
    //printf("%llu %llu %llu %llu %llu %llu\n", firstA->numr, firstA->numc, NA, firstB->numr, firstB->numc, NB);
    


}
