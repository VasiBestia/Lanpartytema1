#ifndef LISTE_H
#define LISTE_H

#include<stdio.h>
#include<stdlib.h>

typedef struct Player {
    char *firstName;
    char *secondName;
    int points;
} Player;

typedef struct Team {
    int numar_coechipieri;
    char *nume_echipa;
    Player *player;  
} Team;

typedef struct Node {
    Team *team;
    struct Node *next;
} Node;

// Function prototypes
void ListCreate(Node **head);
void AddAtBeginning(Node **head, int numar_coechipieri, char *nume_echipa,FILE *intrare);
void printListReverse(Node **head,FILE *iesire);
void StackPrint(Node **head,FILE *iesire);
void FreeStack(Node *head);

#endif // LISTE_H
