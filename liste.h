#ifndef LISTE_H
#define LISTE_H

#include<stdio.h>
#include<stdlib.h>

typedef struct Player {
    char *firstName;
    char *secondName;
    float points;
} Player;

typedef struct Team {
    int numar_coechipieri;
    char *nume_echipa;
    Player *player;  
    float total;
} Team;

typedef struct Node {
    Team *team;
    struct Node *next;
} Node;

// Function prototypes
void ListCreate(Node **head);
void AddAtTheEnd(Node **head, int numar_coechipieri, char *nume_echipa,FILE *intrare);
void printList(Node **head);
void FreeStack(Node *head);
void calculpunctaje(float p[],Node *head,int numar_echipe);
void swap(float *a, float *b) ;
int partition(float arr[], int low, int high);
void quicksort(float arr[], int low, int high);
int powerof2max(int numar_echipe);
void deleteNode(Node **head, float points);
void freeTeam(Team *team);

#endif // LISTE_H
