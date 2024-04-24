#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "Load.h"
#include "Card.h"
#include "Board.h"
#include "Split.h"
#include "SaveDeck.h"
#include "Shuffle.h"

char lastCommand[100];
char message[100];
char input[100];
char filename[100];
char command[100];
char card[10];
char sourceCol[10];
char destCol[10];
bool loaded;

Card* columns[7];
Card* foundations[4];
Card* deck;


void printBoard();
const char* mainMenu();
const char* playMenu();
void move(Card** colFrom, Card** colTo,const char cardName[3]);
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
    for (int i=7;i < 26;i++) {
        if (get(columns[0], i) == NULL && get(columns[1], i) == NULL && get(columns[2], i) == NULL
            && get(columns[3], i) == NULL && get(columns[4], i) == NULL && get(columns[5], i) == NULL
            && get(columns[6], i) == NULL) {
            return;
        } else {
            printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
                   maybe(get(columns[0], i)),
                   maybe(get(columns[1], i)),
                   maybe(get(columns[2], i)),
                   maybe(get(columns[3], i)),
                   maybe(get(columns[4], i)),
                   maybe(get(columns[5], i)),
                   maybe(get(columns[6], i))
            );
        }
    }
}

const char* mainMenu() {
    bool continueMainMenu = true;
    while (continueMainMenu && strcmp(command, "QQ") != 0) {
        printBoard();
        printf("\nLAST Command: %s", lastCommand);
        printf("\nMessage: %s", message);
        printf("\nINPUT >");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
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
        }

        else if (strcmp(input, "SI") == 0) {
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
        }

        else if (strcmp(input, "SR") == 0) {
            resetColumns(columns);
            shuffle(&deck);
            arrangeEvenly(columns, deck);
        }

        else if (strcmp(input, "SD") == 0) {
            strcmp(filename, "") == 0
            ? strcpy(message, connectToFile("cards.txt"))
            : strcpy(message, connectToFile(filename));
            if(strcmp(message,"OK") == 0){
                saveE(deck);
            }
        }

        else if (strcmp(command, "P") == 0) {
            resetColumns(columns);
            arrangeP(columns, deck);
            playMenu();
            continueMainMenu = false;
            strcpy(message, "OK");
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
        printf("\nINPUT >");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;  // Remove newline character
        if(strlen(input) == 9) {
            strcpy(sourceCol, strtok(input, ":"));
            strcpy(card, strtok(&input[3], "->"));
            strcpy(destCol, &input[7]);
        } else if(strlen(input) == 6) {
            strcpy(sourceCol, strtok(input, ":"));
            strcpy(destCol, &input[4]);
            strcpy(card, last(columns[sourceCol[1] - '1'])->name);
        }

        if (strcmp(input, "Q") == 0) {
            strcpy(message, "OK");
            inPlayMenu = false;
        } else {
            // Move a card to an empty foundation
            if(destCol[0] == 'F'){
                if(foundations[destCol[1] - '1'] == NULL && matchFound(columns[sourceCol[1] - '1'], card)->precedence >= 1){
                    move(&columns[sourceCol[1] - '1'], &foundations[destCol[1] - '1'], card);
                    strcpy(message, "OK");
                    // Move a card to a non-empty foundation
                } else if( matchFound(columns[sourceCol[1] - '1'], card)->precedence - foundations[destCol[1] - '1']->precedence == 1 && !isDifferentSuit(matchFound(columns[sourceCol[1] - '1'], card), foundations[destCol[1] - '1'])){
                    move(&columns[sourceCol[1] - '1'], &foundations[destCol[1] - '1'], card);
                    strcpy(message, "OK");
                }
                // Standard move
            } else if(isDifferentSuit(matchFound(columns[sourceCol[1] - '1'], card), last(columns[destCol[1] - '1'])) && isOneRankLower(matchFound(columns[sourceCol[1] - '1'], card), last(columns[destCol[1] - '1']))){
                move(&columns[sourceCol[1] - '1'], &columns[destCol[1] - '1'], card);
                strcpy(message, "OK");
                // Move K to an empty column
            } else if(card[0] == 'K' && destCol[0] == 'C' && columns[destCol[1] - '1'] == NULL){
                move(&columns[sourceCol[1] - '1'], &columns[destCol[1] - '1'], card);
                strcpy(message, "OK");
            } else{
                strcpy(message, "Error: not a valid move!");
            }

            //Unhide the last card of a column if hidden.
            if((last(columns[sourceCol[1] - '1']) != NULL)) {
                if (last(columns[sourceCol[1] - '1'])->hidden) {
                    last(columns[sourceCol[1] - '1'])->hidden = false;
                }
            }
        }
        strcpy(lastCommand, input);
    }
    return input;
}

void move(Card** colFrom, Card** colTo, const char cardName[3]){
    Card* a = matchFound(*colFrom, cardName);
    Card* b = last(*colTo);

    if(a->previous != NULL) {
        a->previous->next = NULL;
    }
    else {
        *colFrom = NULL;
    }

    if(b != NULL) {
        a->previous = b;
        b->next = a;
    } else {
        *colTo = a;
        a->previous = NULL;
    }

    a->hidden = false;
}

void run(){
    loaded = false;
    while (strcmp(command, "QQ") != 0) {
        //printBoard();
        strcpy(command, mainMenu());
    }
}