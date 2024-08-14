#ifndef ARBORI_H
#define ARBORI_H

#include<stdio.h>
#include<stdlib.h>

typedef struct Nod {
    char* team;
    float summary;
    struct Nod* left;
    struct Nod* right;
    int height;
} Nod;


Nod* newNode(char* team,float summary);
int getHeight(Nod* node);
int max(int a, int b);
int getBalance(Nod* node);
Nod* rightRotate(Nod* y);
Nod * leftRotate(Nod* x) ;
Nod* insertNode(Nod* node, char* team,float summary) ;
void printLevel2Teams(Nod* root);
void FreeTree(Nod* root);
void inOrderTraversal(Nod* root);

#endif