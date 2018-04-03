#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node {
    int ra, nota;
    struct tree_node *left_p, *right_p;
}tree_node;

int t_height(tree_node *root) 
{
   if (root==NULL) 
       return 0;
   else
   {
       int lheight = t_height(root->left_p);
       int rheight = t_height(root->right_p);
 
       if (lheight > rheight) 
           return(lheight+1);
       else return(rheight+1);
   }
}

tree_node * t_search(tree_node *root, int ra, int *comp)
{
  *comp=1;
    while (root) {
        if (root->ra == ra)
            return root;
        if (root->ra < ra)
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

tree_node *newNode(int ra, int nota)
{
    tree_node *temp =  malloc(sizeof(tree_node));
    temp->ra = ra;
    temp->nota = nota;
    temp->left_p = temp->right_p = NULL;
    return temp;
}

tree_node *t_insert(tree_node *root, int ra, int nota)
{

    if (root == NULL) return newNode(ra, nota);

    if (ra < root->ra)
        root->left_p  = t_insert(root->left_p, ra, nota);
    else if(ra > root->ra)
        root->right_p = t_insert(root->right_p, ra, nota);
    else 
        root->nota = nota;

    return root;
}

tree_node *t_min(tree_node *root_p){
    
    while(root_p->left_p  != NULL) root_p = root_p->left_p;
    return root_p;
}

tree_node *t_delete(tree_node *root, int ra) {
	if(root == NULL) return root; 
	else if(ra < root->ra) root->left_p = t_delete(root->left_p,ra);
	else if (ra > root->ra) root->right_p = t_delete(root->right_p,ra);
	else {
            tree_node *temp;
            if (root->left_p == NULL)
            {
                temp = root->right_p;
                free(root);
                return temp;
            }
            else if (root->right_p == NULL)
            {
                temp = root->left_p;
                free(root);
                return temp;
            }
            temp = t_min(root->right_p);
            root->ra = temp->ra;
            root->nota = temp->nota;
            root->right_p = t_delete(root->right_p, temp->ra);
	}
	return root;
}

void t_free(tree_node *root_p)
{
    if (root_p==NULL) return;
    t_free(root_p->left_p);
    t_free(root_p->right_p);
    free(root_p);
}

int main(int argc, char** argv)
{
    
  char op;
  int ra, nota;
  int comp_t;
  tree_node *tp = NULL, *root_p = NULL;
  
 do{
    
    scanf("\n%c", &op);
    
    if(op!='A' && op!='P'){
        scanf("%d", &ra);
        if(op=='I'){
          scanf("%d", &nota);
          root_p = t_insert(root_p, ra, nota);
        }
        else if(op=='B'){
            tp = t_search(root_p, ra, &comp_t);
            if(!tp) printf("C=%d Nota=%d\n", comp_t, -1);
            else printf("C=%d Nota=%d\n", comp_t, tp->nota);
        }
        else if(op=='R') root_p = t_delete(root_p, ra);
        
    }
    else if(op=='A') printf("A=%d\n", t_height(root_p)-1);      
    
  } while(op!='P');
  
  t_free(root_p);
  root_p = NULL;
  
  return 0;
}
