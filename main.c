#include "liste.h"
#include "liste.c"
#include "cozistive.h"
#include "cozistive.c"
#include "arbori.h"
#include "arbori.c"

int main(int argc, char *argv[])
{
    Node *head;
    FILE  *intrare2;
    FILE *iesire;
    int numar_echipe;
    int numar_coechipieri;
    char nume_echipa[50]; // Use a fixed-size array
    float p[120];

    ListCreate(&head);

    

    intrare2 = fopen("d.in", "r");
    if (intrare2 == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    iesire = fopen("rezultateteste.txt", "w");
    if (iesire == NULL)
    {
        perror("Error opening file");
        return 1;
    }


    fscanf(intrare2, "%d", &numar_echipe);

    for (int i = 0; i < numar_echipe; i++)
    {
        fscanf(intrare2, "%d %[^\n]", &numar_coechipieri, nume_echipa);
        AddAtTheEnd(&head, numar_coechipieri, nume_echipa, intrare2);
    }
    
      calculpunctaje(p,head,numar_echipe);

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
      
      current = head;
      while (current != NULL) {
          enQueue(q, current->team->nume_echipa, current->team->total);
          current = current->next;
      }
      int index=1;
      
      Queue *qcopy;
      while(kickoff>1){
        printf("---Round No:%d\n", index);
          runde(q);
        kickoff=kickoff/2;
        etape2(q,index);
        if(kickoff==8){
          qcopy=copyQueue(q);
        }
        index++;
      }
      sortQueue(qcopy);

      printf("TOP 8 TEAMS:\n");
        Nodul *aux = qcopy->front;
    while (aux != NULL)
    {
        printf("%-30s   -%.2f\n", aux->team_name, aux->summary);
        aux = aux->next;
    }
    printf("\n");

      Nod *root=NULL;

      
      root=insertNode(root,qcopy->front->team_name,qcopy->front->summary);
      root=insertNode(root,qcopy->front->next->team_name,qcopy->front->next->summary);
      printf("%s %.2f\n",root->team,root->summary);
    // Apel în main:
printf("Traversare in-order a arborelui:\n");
inOrderTraversal(root);


      FreeStack(head);
      FreeTree(root);
      fclose(intrare2);
      fclose(iesire);
      

      return 0;
  
}
