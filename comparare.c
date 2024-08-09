#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void print_difference(const char *file1, const char *file2);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    print_difference(argv[1], argv[2]);

    return 0;
}

void print_difference(const char *file1, const char *file2) {
    FILE *fp1 = fopen(file1, "r");
    FILE *fp2 = fopen(file2, "r");

    if (fp1 == NULL || fp2 == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line1[MAX_LINE_LENGTH];
    char line2[MAX_LINE_LENGTH];
    int line_number = 1;

    while (fgets(line1, sizeof(line1), fp1) != NULL &&
           fgets(line2, sizeof(line2), fp2) != NULL) {
        if (strcmp(line1, line2) != 0) {
            printf("Difference at line %d:\n", line_number);
            printf("File 1: %s", line1);
            printf("File 2: %s", line2);
        }
        line_number++;
    }

    // Check if there are remaining lines in file1
    while (fgets(line1, sizeof(line1), fp1) != NULL) {
        printf("Extra line in %s at line %d:\n", file1, line_number);
        printf("%s", line1);
        line_number++;
    }

    // Check if there are remaining lines in file2
    while (fgets(line2, sizeof(line2), fp2) != NULL) {
        printf("Extra line in %s at line %d:\n", file2, line_number);
        printf("%s", line2);
        line_number++;
    }

    fclose(fp1);
    fclose(fp2);
}
