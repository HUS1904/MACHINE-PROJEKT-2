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


    while (line++ < 52) {

        if (fscanf(file, "%s", name) != -1) {

            Card *next = (Card *) malloc(sizeof(Card));
            *next = buildCard(name);

            if (matchFound(first, next->name) != NULL) {
                static char error[100];
                sprintf(error, "card %s from file %s is a duplicate", next->name, filename);
                return error;
            }

            if (next->precedence == 0) {
                static char error[100];
                sprintf(error, "Error: broken card %s at line %d.", next->name, line);
                fclose(file);
                return error;
            }


            linkCards(first, next); // Link each pair of cards together
            first = next; // Redefine first ahead of next iteration

        } else{
            static char error[100];
            sprintf(error, "%s","error file does not have 52 cards");
            fclose(file);
            return error;
        }
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

void arrangeVisible(Card* columns[7], Card* deck) {
    for (int i = 0, j = 0; i < 52; i++, j++) {
        j = j >= 7 ? 0 : j; // Resets j if it gets too large

        Card* current = malloc(sizeof(Card));
        *current = buildCard(get(deck,i)->name);
        current->hidden = false;

        // If the first element of a column is null set it to the current card
        // otherwise get the last element of that column and set its next to be the current card
        if (columns[j] == NULL) {
            columns[j] = current;
        } else {
            linkCards(last(columns[j]), current);
        }
    }
}

void arrangeP(Card* columns[7], Card* deck) {
    int maxRows = 11; // Maximum rows determined by the largest value in distribution
    int distribution[7] = {1, 6, 7, 8, 9, 10, 11}; // Custom distribution for each column
    int cardIndex = 0;  // Index to track the current card in the deck
    int cardCount[7] = {0}; // Track the number of cards in each column

    for (int row = 0; row < maxRows && cardIndex < 52; row++) {
        for (int col = 0; col < 7 && cardIndex < 52; col++) {
            if (row < distribution[col]) { // Only add a card if the current row is within the distribution limit for that column
                Card* current = malloc(sizeof(Card));
                *current = buildCard(get(deck, cardIndex)->name);
                current->next = NULL;  // Ensure the new card points to NULL

                // Check if the card is among the last 5 in this column
                if (distribution[col] - cardCount[col] <= 5) {
                    current->hidden = false; // Set hidden to false for the last 5 cards
                } else {
                    current->hidden = true; // Otherwise, the card is hidden
                }

                // If the first element of a column is null, set it to the current card
                if (columns[col] == NULL) {
                    columns[col] = current;
                } else {
                    // Otherwise, get the last element of that column and set its next to be the current card
                    linkCards(last(columns[col]), current);
                }
                cardIndex++;  // Move to the next card in the deck
                cardCount[col]++; // Increment the count of cards in this column
            }
        }
    }
}


