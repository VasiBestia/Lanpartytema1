#include "liste.h"
#include "liste.c"
#include "cozistive.h"
#include "cozistive.c"

int main(int argc, char *argv[]) {
    Node *head;
    FILE *intrare;
    FILE* iesire;
    int numar_echipe;
    int numar_coechipieri;
    char nume_echipa[50]; // Use a fixed-size array
    float p[120];

    ListCreate(&head);

    intrare = fopen("C:\\github\\Lanpartytem1\\date\\t4\\d.in", "r");
    if (intrare == NULL) {
        perror("Error opening file");
        return 1;
    }

    iesire = fopen("rezultateleteste.txt", "w");
    if (iesire == NULL) {
        perror("Error opening file");
        return 1;
    }


    fscanf(intrare, "%d", &numar_echipe);
    fprintf(iesire,"%d\n", numar_echipe);

    for (int i = 0; i < numar_echipe; i++) {
        fscanf(intrare, "%d %[^\n]", &numar_coechipieri, nume_echipa);
        AddAtBeginning(&head, numar_coechipieri, nume_echipa, intrare);
    }

    
    
    printListReverse(&head,iesire);
    calculpunctaje(p,head,numar_echipe);

    

    printf("\n");

    Node *current;
    current=head;
    for(int i=0;i<numar_echipe;i++){
        current->team->total=p[i];
        current=current->next;
    }   

    quicksort(p,0,numar_echipe-1);
    
    int kickoff=powerof2max(numar_echipe);

    for(int i=0;i<numar_echipe-kickoff;i++){
        current=head;
        while(current!=NULL){
            if(current->team->total==p[i]){
                deleteNode(&head,current->team->total);
                break;
            }
          current=current->next;
        }
    }


    Queue *q = createQueue();
    Nodul *winnerstop, *loserstop;
    StackCreate(&winnerstop);
    StackCreate(&loserstop);

    
    current = head;  
    while (current != NULL) {
        enQueue(q, current->team->nume_echipa, current->team->total);
        current = current->next;
    }

    int index=1;
    printf(" ---Round No:%d\n",index);
    runde(q);

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
     
    index++; 
    printf(" ---Round No:%d\n",index);
    runde(q);

    freeStack(&loserstop);
    freeStack(&winnerstop);

    while(kickoff>8){
        index++;
        printf(" ---Round No:%d\n",index);
        etape(q,winnerstop,loserstop);
        kickoff/=2;
    }

    FreeStack(head);
    fclose(intrare);
    fclose(iesire);

    return 0;
}
