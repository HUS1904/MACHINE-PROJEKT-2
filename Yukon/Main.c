#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "Load.h"
#include "Card.h"
#include "Board.h"
#include "Split.h"
#include "SaveDeck.h"

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
const char* playMenu();
void run();




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
           maybeF(foundations[0])
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
           maybeF(foundations[1])
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
           maybeF(foundations[2])
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
           maybeF(foundations[3])
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
}

const char* mainMenu() {
    bool continueMainMenu = true;
    while (continueMainMenu && strcmp(command, "QQ") != 0) {
        printBoard();
        printf("\nLAST Command: %s", lastCommand);
        printf("\nMessage: %s", message);
        printf("\nINPUT > ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        sscanf(input, "%s %s", command, filename);
const char* mainMenu(){
    strcpy(command, "");
    strcpy(filename, "");
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
        } else if (strcmp(command, "SW") == 0) {
            if (!loaded) {
                strcpy(message, "Error: no deck is loaded");
            } else {
                resetColumns(columns);
                arrangeVisible(columns, deck);
                strcpy(message, "OK");
            }
        } else if (strcmp(input, "SL") == 0) {
            printf("SL command\n");
        } else if (strcmp(input, "SR") == 0) {
            printf("SR command\n");
        } else if (strcmp(input, "SD") == 0) {
            printf("SD command\n");
        } else if (strcmp(command, "P") == 0) {
            playMenu();
            continueMainMenu = false;
        } else {
            strcpy(message, "ERROR: Unknown command");
        }
        strcpy(lastCommand, input);
    }
    return input;
}

const char* playMenu() {
    bool inPlayMenu = true;
    while (inPlayMenu) {
        printBoard();
        printf("\nLAST Command: %s", lastCommand);
        printf("\nMessage: %s", message);
        printf("\nINPUT > ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;  // Remove newline character
        sscanf(input, "%s %s", command, filename);

        if (strcmp(command, "move") == 0) {
            strcpy(message, "OK");
        } else if (strcmp(command, "Q") == 0) {
            strcpy(message, "OK");
            inPlayMenu = false;
        } else {
            strcpy(message, "ERROR: Unknown command");
        }
        strcpy(lastCommand, input);
        if(strcmp(message, "OK") == 0)
            arrangeEvenly(columns, deck);
    } else if (strcmp(input, "SW") == 0) {
        printf("SW command\n");
    } else if (strcmp(command, "SI") == 0) {
        resetColumns(columns);
        if (deck) { // Ensure deck is loaded before attempting to split
            int splitIndex = atoi(filename);
            if(splitIndex >= 52 || splitIndex < 1) {
                splitIndex = rand() % 50 + 1;
            }
            // Now call splitDeck with either the provided or default index
            strcpy(message, splitDeck(&deck, splitIndex));
            arrangeEvenly(columns, deck);
            // Optionally, directly print the deck to visualize the changes
        } else {
            printf("Load a deck first.\n");
        }
    }else if (strcmp(input, "SR") == 0) {
        printf("SR command\n");
    } else if (strcmp(command, "SD") == 0) {
        strcmp(filename, "") == 0
        ? strcpy(message, connectToFile("cards.txt"))
        : strcpy(message, connectToFile(filename));
        if(strcmp(message,"OK") == 0){
            saveE(deck);
        }
    } else if (strcmp(command, "QQ") == 0) {
        printf("QQ command - Quitting\n");
    } else {
        printf("Unknown command\n");
    }
    return input;
}




void run(){
    while (strcmp(command, "QQ") != 0) {
        printBoard();
        strcpy(command, mainMenu());
    }
}