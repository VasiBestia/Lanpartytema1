#include "liste.h"
#include <string.h>

// Initializes the linked list
void ListCreate(Node **head) {
    *head = NULL;
}

// Adds a new team and its players at the beginning of the list
void AddAtBeginning(Node **head, int numar_coechipieri, char *nume_echipa, FILE *intrare) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->team = (Team *)malloc(sizeof(Team));
    newNode->team->numar_coechipieri = numar_coechipieri;
    newNode->team->nume_echipa = (char *)malloc(50 * sizeof(char));
    strcpy(newNode->team->nume_echipa, nume_echipa);
    
    newNode->team->player = (Player *)malloc(numar_coechipieri * sizeof(Player));

    for (int i = 0; i < numar_coechipieri; i++) {
        char firstname[50], secondname[50];
        int points;

        fscanf(intrare, "%s %s %d", firstname, secondname, &points);
        newNode->team->player[i].firstName = strdup(firstname);
        newNode->team->player[i].secondName = strdup(secondname);
        newNode->team->player[i].points = points;
    }

    newNode->next = *head;
    *head = newNode;
}

// Prints all players in the list
void StackPrint(Node **head,FILE *iesire) {
    Node *current = *head;
    while (current != NULL) {
        fprintf(iesire,"%d %s\n",current->team->numar_coechipieri, current->team->nume_echipa);
        for (int i = 0; i < current->team->numar_coechipieri; i++) {
            fprintf(iesire,"%s %s %d\n",
                current->team->player[i].firstName,
                current->team->player[i].secondName,
                current->team->player[i].points);
        }
        fprintf(iesire,"\n");
        current = current->next;
    }
    fprintf(iesire,"\n");
}

// Frees all allocated memory in the list
void FreeStack(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;

        for (int i = 0; i < temp->team->numar_coechipieri; i++) {
            free(temp->team->player[i].firstName);
            free(temp->team->player[i].secondName);
        }
        free(temp->team->player);
        free(temp->team->nume_echipa);
        free(temp->team);
        free(temp);
    }
}
void printListReverse(Node **head,FILE *iesire) {
    Node *stack[100]; 
    int top = -1;

   
    Node *temp = *head;
    while (temp != NULL) {
        stack[++top] = temp;
        temp = temp->next;
    }

    while (top >= 0) {
        Node *node = stack[top--];
        fprintf(iesire,"%d %s\n", node->team->numar_coechipieri, node->team->nume_echipa);
        for (int i = 0; i < node->team->numar_coechipieri; i++) {
            fprintf(iesire,"%s %s %d\n",
                   node->team->player[i].firstName,
                   node->team->player[i].secondName,
                   node->team->player[i].points);
        }
        fprintf(iesire,"\n");
    }
}
