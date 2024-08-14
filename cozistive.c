#include "cozistive.h"
#include <string.h>

Queue *createQueue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

int isEmpty(Queue *q)
{
    return (q->front == NULL);
}

void enQueue(Queue *q, char *nume_echipe, float points)
{
    Nodul *newNode = (Nodul *)malloc(sizeof(Nodul));
    newNode->team_name = (char *)malloc(50 * sizeof(char));

    strcpy(newNode->team_name, nume_echipe);
    newNode->summary = points;
    newNode->next = NULL;
    newNode->prev = q->rear;

    if (q->rear == NULL)
    { // Queue was empty
        q->front = q->rear = newNode;
    }
    else
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

void printQueue(Queue *q)
{
    Nodul *current = q->front;
    while (current != NULL)
    {
        printf("%s\n", current->team_name);
        current = current->next;
    }
    printf("\n");
}

void runde(Queue *q)
{

    Nodul *current = q->front;
    while (current != NULL && current->next != NULL)
    {
        printf("%-30s - %30s\n", current->team_name, current->next->team_name);
        current = current->next->next;
    }
}

void freeQueue(Queue *q)
{
    Nodul *current = q->front;
    Nodul *next_node;

    // Iterăm prin coadă și eliberăm fiecare nod
    while (current != NULL)
    {
        next_node = current->next; // Salvăm pointerul către următorul nod
        free(current);             // Eliberăm memoria pentru nodul curent
        current = next_node;       // Avansăm la următorul nod
    }

    // Setăm front-ul și rear-ul la NULL
    q->front = NULL;
    q->rear = NULL;
}

void StackCreate(Nodul **top)
{
    *top = NULL;
}

int isEmptyStack(Nodul *top)
{
    return (top == NULL);
}

void push(Nodul **top, char *team_name, float points)
{
    Nodul *newNode = (Nodul *)malloc(sizeof(Nodul));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->team_name = (char *)malloc(50 * sizeof(char));
    if (newNode->team_name == NULL)
    {
        printf("Memory allocation for team_name failed\n");
        free(newNode); // eliberăm memoria pentru newNode înainte de a ieși
        return;
    }
    strcpy(newNode->team_name, team_name);
    newNode->summary = points;
    newNode->next = *top;
    *top = newNode;
}

void freeStack(Nodul **top)
{
    Nodul *current = *top;
    Nodul *next_node;

    // Iterați prin listă și eliberați fiecare nod
    while (current != NULL)
    {
        next_node = current->next; // Salvăm pointerul către următorul nod
        free(current);             // Eliberăm memoria pentru nodul curent
        current = next_node;       // Avansăm la următorul nod
    }

    // Setăm capul listei la NULL
    *top = NULL;
}

void printStack(Nodul **top)
{
    Nodul *current = *top;
    while (current != NULL)
    {
        printf("%-30s -%.2f\n", current->team_name, current->summary);
        current = current->next;
    }
    printf("\n");
}

void deleteNodeQueue(Queue *q, char *team_name)
{
    if (q->front == NULL)
    {
        printf("Coada este goală.\n");
        return;
    }

    Nodul *temp = q->front, *prev = NULL;

    // Dacă nodul de șters este primul nod
    if (temp != NULL && strcmp(temp->team_name, team_name) == 0)
    {
        q->front = temp->next;
        if (q->front == NULL)
        { // Dacă coada devine goală
            q->rear = NULL;
        }
        free(temp);
        return;
    }

    // Caută nodul de șters
    while (temp != NULL && strcmp(temp->team_name, team_name) != 0)
    {
        prev = temp;
        temp = temp->next;
    }

    // Dacă nodul nu a fost găsit
    if (temp == NULL)
    {
        printf("Nodul cu valoarea nu a fost găsit.\n");
        return;
    }

    // Deconectează nodul din listă
    prev->next = temp->next;

    // Dacă nodul șters era ultimul nod
    if (temp == q->rear)
    {
        q->rear = prev;
    }

    free(temp->team_name);
    free(temp);
}

void etape2(Queue *q, int index)
{
    Nodul *winnerstop;
    Nodul *loserstop;

    StackCreate(&loserstop);
    StackCreate(&winnerstop);

    Nodul *temp = q->front;
    while (temp != NULL && temp->next != NULL)
    {
        if (temp->summary < temp->next->summary)
        {
            push(&loserstop, temp->team_name, temp->summary);
            temp->next->summary += 1.00;
            push(&winnerstop, temp->next->team_name, temp->next->summary);
        }
        else if (temp->summary > temp->next->summary)
        {
            push(&loserstop, temp->next->team_name, temp->next->summary);
            temp->summary += 1.00;
            push(&winnerstop, temp->team_name, temp->summary);
        }
        else
        {
            push(&loserstop, temp->next->team_name, temp->next->summary);
            temp->summary += 1.00;
            push(&winnerstop, temp->team_name, temp->summary);
        }

        temp = temp->next->next;
    }

    printf("WINNERS OF ROUND NO:%d\n", index);
    printStack(&winnerstop);

    temp = loserstop;
    while (temp != NULL)
    {
        deleteNodeQueue(q, temp->team_name);
        temp = temp->next;
    }

    freeStack(&loserstop);
    freeStack(&winnerstop);
}

Queue *copyQueue(Queue *q)
{
    Queue *newQueue = createQueue(); // Create a new queue

    Nodul *current = q->front;
    while (current != NULL)
    {
        enQueue(newQueue, current->team_name, current->summary); // Enqueue each element from the original queue to the new queue
        current = current->next;
    }

    return newQueue;
}
void sortQueue(Queue *q)
{
    Nodul *current = q->front;
    Nodul *index = NULL;
    char *temp_team_name;
    float temp_summary;

    if (isEmpty(q))
    {
        printf("Coada este goală.\n");
        return;
    }
    else
    {
        while (current != NULL)
        {
            index = current->next;

            while (index != NULL)
            {
                if (current->summary < index->summary)
                {
                    // Swap team names
                    temp_team_name = current->team_name;
                    current->team_name = index->team_name;
                    index->team_name = temp_team_name;

                    // Swap summaries
                    temp_summary = current->summary;
                    current->summary = index->summary;
                    index->summary = temp_summary;
                }

                index = index->next;
            }

            current = current->next;
        }
    }
}
        