#include "arbori.h"
#include <string.h>

void createTree(Nod **root){
    *root=NULL;
}

Nod * newNode (char *team_name,float summary) {
Nod * node = ( Nod *) malloc ( sizeof ( Nod ));

node->team_name=(char *)malloc(50*sizeof(char));
strcpy(node->team_name,team_name);

node->summary=summary;

node ->left = node ->right = NULL ;
node->height=0;
return node ;
}

Nod* insert(Nod* node, char *team_name,float key) {
    // Dacă arborele (subarborele) este gol, creează un nod nou
    if (node == NULL) 
        return newNode(team_name,key);

    // Altminteri, coboară la stânga sau la dreapta
    if (key < node->summary)
        node->left = insert(node->left, team_name,key);
    else if (key > node->summary)
        node->right = insert(node->right,team_name,key);
    else if(key==node->summary){
        if (strcmp(node->team_name,team_name)<0)
        node->left = insert(node->left, team_name,key);
    else if (strcmp(node->team_name,team_name)>0)
        node->right = insert(node->right,team_name,key);
    }
        
    // Pointerul node se întoarce nemodificat pe acest return
    return node;
}

int height ( Nod* root ){
int hs , hd;
if ( root == NULL ) return -1;
// inaltimea subarborelui stang
hs = height (root -> left );
// inaltimea subarborelui drept
hd = height (root -> right );
// returneaza inaltimea nodului
return 1+(( hs >hd) ? hs:hd );
}

void printLevel ( Nod * root , int level ){
if ( root == NULL ) return ;
if ( level == 1) printf ("  %-30s     %.2f", root ->team_name,root->summary);
else if ( level > 1) {
printLevel (root ->left , level -1);
printLevel (root ->right , level -1);
}
}

void levelOrderTraversal ( Nod * root ){
int h = height ( root );
int i;
// consider nivelul 1 cel al radacinii
for (i=1; i <=h; i ++){
printLevel (root , i);
printf ("\n");
}
}

void freeTree(Nod *root){
    int h = height ( root );
int i;

for (i=1; i <=h; i ++){
    free(root->team_name);
    free(root);
}
}

int isEmptyTree(Nod *root){
    return(root==NULL);
}

int nodeHeight ( Nod * root ){
if ( root == NULL ) return -1;
else return root -> height ;
}


Nod * RightRotation ( Nod *z) { // z nod cu —K— ¿1
Nod *y = z-> left ;
Nod *T3 = y-> right ;

y-> right = z;
z-> left = T3;
// Modifica inaltimile pentru z si y
z-> height = max( nodeHeight (z-> left ) ,
nodeHeight (z-> right ))+1;
y-> height = max( nodeHeight (y-> left ) ,
nodeHeight (y-> right ))+1;
return y; // noua radacina
}


Nod * LeftRotation ( Nod *z) {
Nod *y = z-> right ;
Nod *T2 = y-> left ;
y-> left = z;
z-> right = T2;
z-> height = max( nodeHeight (z-> left ) ,
nodeHeight (z-> right ))+1;
y-> height = max( nodeHeight (y-> left ) ,
nodeHeight (y-> right ))+1;
return y;
}

Nod * LRRotation ( Nod *Z) {
Z-> left = LeftRotation (Z-> left );
return RightRotation (Z);
}

Nod * RLRotation ( Nod *Z) {
Z-> right = RightRotation (Z-> right );
return LeftRotation (Z);
}

Nod * insertAVL ( Nod * node , char *team_name,float key) {
// 1. inserare nod
if ( node == NULL ){
node = newNode(team_name,key);
}

if ( key < node ->summary)
node -> left = insertAVL (node ->left ,team_name, key );
else if (key > node -> summary)
node -> right = insertAVL (node ->right ,team_name, key );
else if(key==node->summary){
   if (strcmp (team_name,node ->team_name)<0)
node -> left = insertAVL (node ->left ,team_name, key );
else if (strcmp(team_name,node->team_name)>0)
node -> right = insertAVL (node ->right ,team_name, key );
}
else return node ; // nu exista chei duplicat

node -> height = 1 + max( nodeHeight (node -> left ) ,
nodeHeight (node -> right ));


int k = ( nodeHeight (node -> left ) -
nodeHeight (node -> right ));


if (k > 1 && key < node ->left -> summary)
return RightRotation ( node );

if (k < -1 && key > node ->right -> summary)
return LeftRotation ( node );

if (k > 1 && key > node ->left -> summary)
return LRRotation ( node );

if (k < -1 && key < node ->right -> summary)
return RLRotation ( node );
return node ; // returneaza nodul nemodificat
}

int max (int a,int b) {
return ((a>b)?a:b);
}
