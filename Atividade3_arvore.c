#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node {
	int data;
	struct tree_node *left_p, *right_p;
}tree_node;

typedef struct LinkedNode {
  int RA;
  struct LinkedNode *next;
}LinkedNode;

tree_node * t_search(tree_node *root, int V, int *comp)
{
  *comp=1;
	while (root) {
		if (root->data == V)
			return root;
		if (root->data < V)
			root = root->right_p;
		else
			root = root->left_p;
		*comp+=1;
	}
  if(root == NULL){
      *comp-=1;
  }
	return NULL;
}

int t_insert(tree_node **root, int V)
{
	while(*root) {
		if ((*root)->data == V)
			return 1;
		if ((*root)->data > V)
			root = &((*root)->left_p);
		else
			root = &((*root)->right_p);
	}
	if (!(*root = (tree_node*)malloc(sizeof(tree_node))))
		return 2;
	(*root)->data = V;
	(*root)->left_p = NULL;
	(*root)->right_p = NULL;
	return 0;
}

LinkedNode *InsertAfter(LinkedNode* list, int RA) {
  
  LinkedNode *tmp = malloc(sizeof(LinkedNode));
  if(tmp == NULL) return NULL;
  
  tmp->RA = RA;
  tmp->next = list->next;
  list->next=tmp;
    
  return tmp;
}

LinkedNode *InsertFirst(LinkedNode* list, int RA) {
  
  LinkedNode *tmp = malloc(sizeof(LinkedNode));
  if(tmp == NULL) return NULL;
  
  tmp->RA = RA;
  tmp->next = list;
  return tmp;
}

LinkedNode *BuscaRA(LinkedNode* first, int RA, int *comp){
  LinkedNode *curr, *prev;
  curr=first;
  *comp=1;
  while(curr != NULL && curr->RA < RA){
    prev = curr;
    curr = curr->next;
    *comp+=1;
  }
  if(curr==NULL){
      *comp-=1;
  }
  return prev;

}

void printSeq(LinkedNode *seq){ // Imprimindo bonitinho
  LinkedNode *curr = seq;
  while (curr != NULL) {
    printf("%d\n", curr->RA);
    curr = curr->next;
  }
}

int main(int argc, char** argv)
{
	
  char op;
  int ra;
  int comp_l, comp_t;
  tree_node *tp, *root_p = 0;
  LinkedNode *first = NULL;
  LinkedNode *last=NULL;
  
 do{
    
    scanf("%c %d", &op, &ra);
    
    if(op=='I'){
      t_insert(&root_p, ra);
      if (first==NULL){
        first=malloc(sizeof(LinkedNode));
        first->RA=ra;
        first->next=NULL;
      }else{
        if(first->RA > ra ){
            first = InsertFirst(first, ra);
        }else{
            last=BuscaRA(first, ra, &comp_l);
            InsertAfter(last, ra);
        }
      }
    }else if(op=='B'){
      BuscaRA(first, ra, &comp_l);
      t_search(root_p, ra, &comp_t);
      printf("L=%d A=%d\n", comp_l, comp_t);
      //printSeq(first);
    }
    
  } while(!(op=='P' && ra==0));
  
	return 0;
}