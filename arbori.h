#ifndef ARBORI_H
#define ARBORI_H

#include<stdio.h>
#include<stdlib.h>

typedef struct Nod {
    char *team_name;
    float summary;
    int height;
    struct Nod *left;
    struct Nod *right;
} Nod;

void createTree(Nod **root);
Nod * newNode (char *team_name,float summary);
Nod* insert(Nod* node, char *team_name,float key);
int height ( Nod* root );
void printLevel ( Nod * root , int level );
void levelOrderTraversal ( Nod * root );
void freeTree(Nod *root);
int isEmptyTree(Nod *root);
int nodeHeight ( Nod * root );
int max (int a,int b);
Nod * LeftRotation ( Nod *z);
Nod * RightRotation ( Nod *z);
Nod * RLRotation ( Nod *Z);
Nod * LRRotation ( Nod *Z);
Nod * insertAVL ( Nod * node , char *team_name,float key);

#endif