#include "liste.h"
#include "liste.c"

int main(int argc, char *argv[]) {
    Node *head;
    FILE *intrare;
    FILE* iesire;
    int numar_echipe;
    int numar_coechipieri;
    char nume_echipa[50]; // Use a fixed-size array

    ListCreate(&head);

    intrare = fopen("C:\\github\\Lanpartytem1\\date\\t1\\d.in", "r");
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
    FreeStack(head);
    fclose(intrare);
    fclose(iesire);

    return 0;
}
