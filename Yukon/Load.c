#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Load.h"
#include "Card.h"
#include "Main.h"

const char* load(const char* filename, Card** list) {
    if(!(access(filename, F_OK) == 0)) {
        return "Error: file does not exist";
    }
    printf("Loading file %s\n", filename);
    FILE* file = fopen(filename, "r"); // Open the file to be read
    printf("Opened file\n");
    char name[3]; // Char[] to be used for creating new cards
    int line = 1; // The current line of the file, to be used for error messages

    fscanf(file, "%s", name);
    Card* first = (Card*)malloc(sizeof(Card));
    *first = buildCard(name);

    if(first->precedence == 0) {
        static char error[100];
        // This can be changed if somebody wants the errors to look different, but we are required to provide the line
        sprintf(error, "Error: broken card %s at line %d.", first->name, line);
        fclose(file);
        return error;
    }

    *list = first;

    // Load all the other cards
    while (line++ < 52) {
        fscanf(file, "%s", name);
        Card* next = (Card*)malloc(sizeof(Card));
        *next = buildCard(name);

        if(next->precedence == 0) {
            static char error[100];
            sprintf(error, "Error: broken card %s at line %d.", next->name, line);
            fclose(file);
            return error;
        }

        linkCards(first, next); // Link each pair of cards together
        first = next; // Redefine first ahead of next iteration
    }

    fclose(file);
    loaded = true;
    return "OK\0";
}

void arrangeEvenly(Card* columns[7], Card* deck) {
    for (int i = 0, j = 0; i < 52; i++, j++) {
        j = j >= 7 ? 0 : j; // Resets j if it gets too large

        Card* current = malloc(sizeof(Card));
        *current = buildCard(get(deck,i)->name);

        // If the first element of a column is null set it to the current card
        // otherwise get the last element of that column and set its next to be the current card
        if (columns[j] == NULL) {
            columns[j] = current;
        } else {
            linkCards(last(columns[j]), current);
        }
    }
}
