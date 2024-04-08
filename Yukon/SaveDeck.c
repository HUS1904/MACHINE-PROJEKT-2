#include <stdio.h>
#include <string.h>
#include "Card.h"

void save(const char* filename, Card* Columns[7], Card* deck) {
    FILE* file = fopen(filename, "w"); // Open the file for writing (creates if it doesn't exist)

    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    for (int i = 0, j = 0; i < 52; i++, j++) {
        j = j >= 7 ? 0 : j;

        // Declare name1 array to hold the card name
        char name1[3];

        // Copy the card name from the Card structure to name1
        strcpy(name1, get(Columns[j], i)->name);

        // Write the card name to the file
        fprintf(file, "%s\n", name1);
    }

    fclose(file); // Close the file
}