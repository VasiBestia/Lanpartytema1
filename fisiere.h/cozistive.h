#ifndef COZISTIVE_H
#define COZISTIVE_H

#include<stdio.h>
#include<stdlib.h>

typedef struct Nodul {
    char *team_name;
    float summary;
    struct Nodul *next;
    struct Nodul *prev;
} Nodul;

typedef struct Q{
    Nodul *front;
    Nodul *rear;
}Queue;


Queue* createQueue();
int isEmpty(Queue *q);
void enQueue(Queue *q, char *nume_echipe,float points);
void printQueue(Queue *q);
void freeQueue(Queue *q);
void runde(Queue *q);
void deleteNodeQueue(Queue *q, char *team_name);

void StackCreate(Nodul **top);
void push ( Nodul ** top ,char *team_name,float points);
void freeStack(Nodul **top);
void printStack(Nodul **top);
int isEmptyStack(Nodul *q);
Queue *copyQueue(Queue *q);
void sortQueue(Queue *q);

void etape2(Queue *q,int index);

#endif