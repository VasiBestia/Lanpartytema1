#include "cozistive.h"
#include <string.h>

Queue* createQueue() {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

int isEmpty(Queue *q) {
    return (q->front == NULL);
}

void enQueue(Queue *q, char *nume_echipe,float points) {
    Nodul *newNode = (Nodul *)malloc(sizeof(Nodul));
    newNode->team_name=(char *)malloc(50*sizeof(char));

    strcpy(newNode->team_name,nume_echipe);
    newNode->summary=points;
    newNode->next = NULL;
    newNode->prev = q->rear;
    
    if (q->rear == NULL) { // Queue was empty
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

void printQueue(Queue *q){
     Nodul *current=q->front;
	 printf("coada este:");
	 while(current!=NULL){
		printf("%s\n",current->team_name);
		current=current->next;
	 }
	 printf("\n");
}

void runde(Queue *q){
    
    Nodul *current=q->front;
	 while(current!=NULL){
		printf("%-30s - %30s\n",current->team_name,current->next->team_name);
		current=current->next;
        if(current!=NULL){
            current=current->next;
        }
        else{
            break;
        }
	 }
}

void freeQueue(Queue* q) {
    Nodul * current = q->front;
    Nodul * next_node;

    // Iterăm prin coadă și eliberăm fiecare nod
    while (current != NULL) {
        next_node = current->next; // Salvăm pointerul către următorul nod
        free(current); // Eliberăm memoria pentru nodul curent
        current = next_node; // Avansăm la următorul nod
    }

    // Setăm front-ul și rear-ul la NULL
    q->front = NULL;
    q->rear = NULL;
}

void StackCreate(Nodul **top) {
    *top = NULL;
}

int isEmptyStack(Nodul *top){
     return (top == NULL);
}

/*Nodul *pop( Nodul ** top) {
if ( isEmptyStack (* top )) return;
Nodul * temp =(* top );

Nodul *aux=temp;
// sterge elementul din varf
*top =(* top)-> next ;
free ( temp );
return aux ;
}*/

void push(Nodul **top, char *team_name, float points) {
    Nodul *newNode = (Nodul *)malloc(sizeof(Nodul));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->team_name = (char *)malloc(50 * sizeof(char));
    if (newNode->team_name == NULL) {
        printf("Memory allocation for team_name failed\n");
        free(newNode); // eliberăm memoria pentru newNode înainte de a ieși
        return;
    }
    strcpy(newNode->team_name, team_name);
    newNode->summary = points;
    newNode->next = *top;
    *top = newNode;
}

void freeStack(Nodul ** top) {
    Nodul* current = *top;
    Nodul* next_node;

    // Iterați prin listă și eliberați fiecare nod
    while (current != NULL) {
        next_node = current->next; // Salvăm pointerul către următorul nod
        free(current); // Eliberăm memoria pentru nodul curent
        current = next_node; // Avansăm la următorul nod
    }

    // Setăm capul listei la NULL
    *top = NULL;
}


void printStack(Nodul **top){
     Nodul *current=*top;
	 while(current!=NULL){
		printf("%-30s -%.2f\n",current->team_name,current->summary);
		current=current->next;
	 }
	 printf("\n");
}

void etape(Queue *q, Nodul *winnerstop, Nodul *loserstop) {

    Nodul *temp = q->front;
    while (temp != NULL && temp->next != NULL) {
        if (temp->summary < temp->next->summary) {
            push(&loserstop, temp->team_name, temp->summary);
            temp->next->summary += 1.00;
            push(&winnerstop, temp->next->team_name, temp->next->summary);
        } else if (temp->summary > temp->next->summary) {
            push(&loserstop, temp->next->team_name, temp->next->summary);
            temp->summary += 1.00;
            push(&winnerstop, temp->team_name, temp->summary);
        } else {
            push(&loserstop, temp->next->team_name, temp->next->summary);
            temp->summary += 1.00;
            push(&winnerstop, temp->team_name, temp->summary);
        }

        temp = temp->next;
        if (temp != NULL && temp->next != NULL) {
            temp = temp->next;
        } else {
            break;
        }
    }

    printf("castig:\n");
    printStack(&winnerstop);
    printf("pierz:\n");
    printStack(&loserstop);

    freeQueue(q);
    q=createQueue();

     temp=winnerstop;
    while(temp!=NULL){
         enQueue(q, temp->team_name, temp->summary);
        temp = temp->next;
    }

    
    runde(q);

    freeStack(&loserstop);
    freeStack(&winnerstop);

    StackCreate(&winnerstop);
    StackCreate(&loserstop);

}