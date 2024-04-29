#include <stdio.h>
#include "Card.h"

const char* filename1;
const char* connectToFile(const char* filename) {
    filename1 = filename;
    FILE*  file = fopen(filename, "w"); // Open the file for writing
    if (file == NULL) {
        return "Error: Unable to open file";
    } else {
        fclose(file); // Close the file
        return "OK";
    }
}

void saveE(Card* deck) {
    FILE*  file1 = fopen(filename1, "w");

    if (file1 == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

        for(int i = 0; i<52;i++) {
            // Get the card pointer
            Card *current = get(deck,i);

            // Check if the card pointer is not NULL


            // Write the card name to the file
            fprintf(file1, "%s\n", current->name);
        }

    fclose(file1); // Close the file
}