#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "Load.h"
#include "Card.h"
#include "Board.h"

char lastCommand[100];
char message[100];
char input[100];
char filename[100];
char command[100];


Card* columns[7];
Card* foundations[4];
Card* deck;

void run();
void printBoard();
const char* mainMenu();
const char* splitDeck(Card** deck, int splitIndex);
void interleaveDecks(Card** firstDeck, Card** secondDeck);



int main(){
    run();
}

void printBoard(){
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t\t%s\tF1\n",
           maybe(get(columns[0], 0)),
           maybe(get(columns[1], 0)),
           maybe(get(columns[2], 0)),
           maybe(get(columns[3], 0)),
           maybe(get(columns[4], 0)),
           maybe(get(columns[5], 0)),
           maybe(get(columns[6], 0)),
           maybeF(get(foundations[0], 0))
           );
    printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
            maybe(get(columns[0], 1)),
            maybe(get(columns[1], 1)),
            maybe(get(columns[2], 1)),
            maybe(get(columns[3], 1)),
            maybe(get(columns[4], 1)),
            maybe(get(columns[5], 1)),
            maybe(get(columns[6], 1))
    );
    printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t\t%s\tF2\n",
           maybe(get(columns[0], 2)),
           maybe(get(columns[1], 2)),
           maybe(get(columns[2], 2)),
           maybe(get(columns[3], 2)),
           maybe(get(columns[4], 2)),
           maybe(get(columns[5], 2)),
           maybe(get(columns[6], 2)),
           maybeF(get(foundations[1], 0))
    );
    printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
           maybe(get(columns[0], 3)),
           maybe(get(columns[1], 3)),
           maybe(get(columns[2], 3)),
           maybe(get(columns[3], 3)),
           maybe(get(columns[4], 3)),
           maybe(get(columns[5], 3)),
           maybe(get(columns[6], 3))
    );
    printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t\t%s\tF3\n",
           maybe(get(columns[0], 4)),
           maybe(get(columns[1], 4)),
           maybe(get(columns[2], 4)),
           maybe(get(columns[3], 4)),
           maybe(get(columns[4], 4)),
           maybe(get(columns[5], 4)),
           maybe(get(columns[6], 4)),
           maybeF(get(foundations[2], 0))
    );
    printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
           maybe(get(columns[0], 5)),
           maybe(get(columns[1], 5)),
           maybe(get(columns[2], 5)),
           maybe(get(columns[3], 5)),
           maybe(get(columns[4], 5)),
           maybe(get(columns[5], 5)),
           maybe(get(columns[6], 5))
    );
    printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t\t%s\tF4\n",
           maybe(get(columns[0], 6)),
           maybe(get(columns[1], 6)),
           maybe(get(columns[2], 6)),
           maybe(get(columns[3], 6)),
           maybe(get(columns[4], 6)),
           maybe(get(columns[5], 6)),
           maybe(get(columns[6], 6)),
           maybeF(get(foundations[3], 0))
    );
    printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
           maybe(get(columns[0], 7)),
           maybe(get(columns[1], 7)),
           maybe(get(columns[2], 7)),
           maybe(get(columns[3], 7)),
           maybe(get(columns[4], 7)),
           maybe(get(columns[5], 7)),
           maybe(get(columns[6], 7))
    );
    //More to be implemented.
}

const char* mainMenu(){
    printf("\nLAST Command: %s", lastCommand);
    printf("\nMessage: %s", message);
    printf("\nINPUT > ");
    gets(input);
    sscanf(input, "%s %s", command, filename);

    if (strcmp(command, "LD") == 0) {
        resetColumns(columns);

        strcmp(filename, "") == 0
            ? strcpy(message, load("default.txt", &deck))
            : strcpy(message, load(filename, &deck));
        if(strcmp(message, "OK") == 0)
            arrangeEvenly(columns, deck);
    } else if (strcmp(input, "SW") == 0) {
        printf("SW command\n");
    } else if (strcmp(command, "SI") == 0) {
        resetColumns(columns);
        if (deck) { // Ensure deck is loaded before attempting to split
            int splitIndex = 26; // Default split index
            char splitIndexStr[100]; // Buffer to hold potential index from input

            if (sscanf(input, "%s %s", command, splitIndexStr) == 2) {
                // Try to convert the second part of the input to an integer
                int tempIndex = atoi(splitIndexStr); // Converts string to integer
                if (tempIndex > 0 && tempIndex < 52) { // Assuming deck size of 52, adjust if necessary
                    splitIndex = tempIndex; // Use the provided valid index
                } else {
                    printf("Invalid index provided. Using default index 26.\n");
                }
            }

            // Now call splitDeck with either the provided or default index
            strcpy(message, splitDeck(&deck, splitIndex));
            // Optionally, directly print the deck to visualize the changes
        } else {
            printf("Load a deck first.\n");
        }
    }else if (strcmp(input, "SR") == 0) {
        printf("SR command\n");
    } else if (strcmp(input, "SD") == 0) {
        printf("SD command\n");
    } else if (strcmp(input, "QQ") == 0) {
        printf("QQ command - Quitting\n");
    } else {
        printf("Unknown command\n");
    }
    strcpy(lastCommand, input);
    return input;
}

const char* splitDeck(Card** deck, int splitIndex) {
    if (splitIndex <= 0 || *deck == NULL) {
        return "Invalid split index or empty deck.";
    }

    // Get the card at the split index and the beginning of the second deck
    Card* splitAt = get(*deck, splitIndex - 1); // Adjust if your indexing is off by one
    if (splitAt == NULL || splitAt->next == NULL) {
        return "Split index out of bounds.";
    }

    Card* secondDeck = splitAt->next;
    splitAt->next->previous = NULL; // Disconnect the second deck from the first
    splitAt->next = NULL; // End the first deck

    // Now you have two decks: *deck and secondDeck, let's interleave them
    interleaveDecks(deck, &secondDeck);

    return "OK";
}
void interleaveDecks(Card** firstDeck, Card** secondDeck) {
    Card* currentFirst = *firstDeck;
    Card* currentSecond = *secondDeck;
    Card* nextFirst = NULL;
    Card* nextSecond = NULL;

    while (currentFirst != NULL && currentSecond != NULL) {
        // Store next cards
        nextFirst = currentFirst->next;
        nextSecond = currentSecond->next;

        // Interleave
        currentFirst->next = currentSecond;
        currentSecond->previous = currentFirst;

        if (nextFirst != NULL) { // Prepare for the next iteration
            nextFirst->previous = currentSecond;
        }

        currentSecond->next = nextFirst;

        // Move to next cards
        currentFirst = nextFirst;
        currentSecond = nextSecond;
    }
}


void run(){
    while (strcmp(command, "QQ") != 0) {
        printBoard();
        strcpy(command, mainMenu());
    }
}