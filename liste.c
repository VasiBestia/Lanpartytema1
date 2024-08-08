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
        float points;

        fscanf(intrare, "%s %s %f", firstname, secondname, &points);
        newNode->team->player[i].firstName = strdup(firstname);
        newNode->team->player[i].secondName = strdup(secondname);
        newNode->team->player[i].points = points;
    }

    newNode->next = *head;
    *head = newNode;
}

// Prints all players in the list
void printListReverseupdt(Node **head) {
    Node *stack[100]; 
    int top = -1;

   
    Node *temp = *head;
    while (temp != NULL) {
        stack[++top] = temp;
        temp = temp->next;
    }

    while (top >= 0) {
        Node *node = stack[top--];
        printf("%s\n",node->team->nume_echipa);
        
        printf("Punctaj echipa:%.2f\n",node->team->total);
        printf("\n");
    }
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
            fprintf(iesire,"%s %s %.2f\n",
                   node->team->player[i].firstName,
                   node->team->player[i].secondName,
                   node->team->player[i].points);
        }
        fprintf(iesire,"\n");
    }
}

void calculpunctaje(float p[],Node *head,int numar_echipe){
    int index=0;
         while(head!=NULL){
            float s=0.00;
            for(int i=0;i<head->team->numar_coechipieri;i++)
              s+=head->team->player[i].points;
            s=(float)s/head->team->numar_coechipieri;
            p[index++]=s;
            head=head->next;
         }
            
                
}


int powerof2max(int numar_echipe){
    int p=1;
    while(p<numar_echipe){
      p*=2;
    }

      if(p>numar_echipe){
      p/=2;
      }
    return p;
}


void swap(float *a, float *b) {
    float t = *a;
    *a = *b;
    *b = t;
}

int partition(float arr[], int low, int high) {
    float pivot = arr[high];  // Alegem ultimul element ca pivot
    int i = (low - 1);  // Indexul elementului mai mic

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;  // Incrementăm indexul elementului mai mic
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}


void quicksort(float arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

void freeTeam(Team *team) {
    if (team) {
        free(team->nume_echipa);
        for (int i = 0; i < team->numar_coechipieri; i++) {
            free(team->player[i].firstName);
            free(team->player[i].secondName);
        }
        free(team->player);
        free(team);
    }
}

void deleteNode(Node **head, float points) {
    if (*head == NULL) return;

    Node *headcopy = *head;
    
    // Dacă primul nod conține echipa de șters
    if (headcopy->team->total==points) {
        *head = (*head)->next;
        freeTeam(headcopy->team);
        free(headcopy);
        return;
    }

    Node *prev = *head;
    
    while (headcopy != NULL) {
        if ( headcopy->team->total != points) {
            prev = headcopy;
            headcopy = headcopy->next;
        } else {
            prev->next = headcopy->next;
            freeTeam(headcopy->team);
            free(headcopy);
            return;
        }
    }
}
