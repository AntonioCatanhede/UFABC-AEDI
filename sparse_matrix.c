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
    
    if(curr->pos == pos) return curr;
    
    tmp->node  = NULL;
    tmp->pos   = pos;
    tmp->next  = NULL;
    
    if(curr->pos < pos){
        tmp->next  = curr->next;
        curr->next = tmp;
        return tmp;
    }
    
    if(curr->next == NULL){
        curr->next = tmp;
        return tmp;
    }

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
    
    first->col = malloc(sizeof(Head));
    first->row = malloc(sizeof(Head));
    
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
        while(curr->r_node != NULL && curr->r_node->j < pos) curr = curr->r_node;
    }else{
        while(curr->b_node != NULL && curr->b_node->i < pos) curr = curr->b_node;
    }
    
    return curr;
}

void InsertNode(Sparse_Matrix *first, ulli row, ulli col, double val)
{
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
    else if(c->node->i > row){
       tmp->b_node = c->node;
       c->node = tmp;
    }
    else
    {
        curr = SearchNode(c->node, row, 0); //busca ao longo da coluna
        if(curr->i > row){
            tmp->b_node = curr->b_node;
            tmp->i      = curr->i;
            tmp->j      = curr->j;
            tmp->r_node = curr->r_node;
            tmp->value  = curr->value;
            
            curr->b_node= tmp;
            curr->i     = row;
            curr->j     = col;
            curr->r_node= NULL;
            curr->value = val;
        }else if(curr->b_node == NULL){
            curr->b_node = tmp;
        }else{
            tmp->b_node = curr->b_node;
            curr->b_node = tmp;
        } 
    }
        
    if(r->node == NULL) r->node = tmp;
    else if(r->node->j > col){
       tmp->r_node = r->node;
       r->node = tmp;
    }
    else
    {
        curr = SearchNode(r->node, col, 1); //busca ao longo da coluna
        if(curr->j > col){
            tmp->b_node = curr->b_node;
            tmp->i      = curr->i;
            tmp->j      = curr->j;
            tmp->r_node = curr->r_node;
            tmp->value  = curr->value;
            
            curr->b_node= NULL;
            curr->i     = row;
            curr->j     = col;
            curr->r_node= tmp;
            curr->value = val;
        }else if(curr->j == col){
            tmp->r_node = curr->r_node;
            curr->r_node = tmp;
        }else if(curr->r_node == NULL){
            curr->r_node = tmp;
        }
    }
     

}

void PrintMatrix(Sparse_Matrix *first)
{
    if(first == NULL){
        printf("ERRO\n\n");
        return;
    }
    
    ulli i, j, c, r;
    c = first->numc;
    r = first->numr;
    Head *row = first->row;
    Node *node;
    
    
    for(i=0; i<r; i++){
        if(row != NULL) node = row->node;
        printf("[");
        for(j=0; j<c; j++){
            if(node->i == i && node->j == j)
            {
                printf("%0.lf ", node->value);
                if(node->r_node != NULL) node = node->r_node;
            }
            else printf("0 ");
        }
        if(row != NULL && row->pos == i) row = row->next;
        printf("]\n");
    }
    
    printf("\n");
}

void ReadMatrix(ulli nums, Sparse_Matrix *first)
{
    ulli i, r, c;
    double val;
    Sparse_Matrix *tmp = first;
    
    for(i=0; i<nums; i++)
    {   
        scanf("%llu %llu %lf", &r, &c, &val);
        if(i==0) InsertFirstNode(tmp, r, c, val); 
        else InsertNode(tmp, r, c, val);
    }
}

double DotProd(Head *A, Head *B, ulli k){
    double sum = 0;
    ulli i;
    
    Node *nodeA, *nodeB;
    nodeA = A->node;
    nodeB = B->node;
    
    for(i = 0; i < k; i++){
        
        if(nodeA->j == nodeB->i && nodeB->i == i)
            sum += nodeA->value * nodeB->value;
        
        if(nodeA->r_node && nodeA->j <= i) nodeA = nodeA->r_node;
        if(nodeB->b_node && nodeB->i <= i) nodeB = nodeB->b_node;
    }
    
    return sum;
}

Sparse_Matrix * MultMatrix(Sparse_Matrix *A, Sparse_Matrix *B){
    
    if(A->numc != B->numr) {
        return NULL;
    }
    
    Sparse_Matrix *M = malloc(sizeof(Sparse_Matrix));
    
    ulli i, j, r, c, k;
    r = A->numr;
    c = B->numc;
    k = A->numc;
    double sum;
    
    M->numc = c;
    M->numr = r;
    M->col = NULL;
    M->row = NULL;
    
    Head *row = A->row;
    Head *col = B->col;
    
    for (i = 0; i < r; i++) {
        if(row->pos == i){
            for (j = 0; j < c; j++) {
                if(col->pos == j){
                    sum = DotProd(row, col, k);
                    if(M->col == NULL && M->row == NULL && sum != 0) InsertFirstNode(M, i, j, sum);
                    else if(sum != 0) InsertNode(M, i, j, sum);
                    sum = 0;
                    
                    if(col->next != NULL) col = col->next;
                }
            }
            col = B->col;
            if(row->next != NULL) row = row->next;
        }
    }
    
    return M;
}

void freeMatrix(Sparse_Matrix *A){
    if(!A) return;

    Head *c, *r, *tmpr, *tmpc;
    Node *tmp, *curr;
    c = A->col;
    r = A->row;
    tmp = r->node;
    curr = r->node;
    
    while(r){
        while(curr){
            tmp = curr->r_node;
            free(curr);
            curr = tmp;
        }
        tmpr = r->next;
        free(r);
        r = tmpr;
        if(r) curr = r->node;
    }
    
    while(c){
        tmpc = c->next;
        free(c);
        c = tmpc;
    }
    
}

int main()
{

    Sparse_Matrix *A, *B, *M;
    B = malloc(sizeof(Sparse_Matrix));
    A = malloc(sizeof(Sparse_Matrix));

    ulli NA, NB;
    char op;
    
    A->row = NULL;
    A->col = NULL;
    
    B->row = NULL;
    B->col = NULL;
    
    scanf("%llu %llu %llu %llu %llu %llu", &A->numr, &A->numc, &NA, &B->numr, &B->numc, &NB);
    //printf("%llu %llu %llu %llu %llu %llu\n", A->numr, A->numc, NA, B->numr, B->numc, NB);
    ReadMatrix(NA, A);
    ReadMatrix(NB, B);
    M = MultMatrix(A,B);
    scanf("\n%c", &op);
    
    while(op!='S'){
        if(op == 'A') PrintMatrix(A);
        else if(op == 'B') PrintMatrix(B);
        else if(op == 'M') PrintMatrix(M);
        scanf("\n%c", &op);
    }
    
    freeMatrix(A);
    freeMatrix(B);
    freeMatrix(M);
    free(A);
    free(B);
    free(M);
    
    return 0;

}
