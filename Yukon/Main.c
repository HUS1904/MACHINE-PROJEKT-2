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
void move(Card* colFrom, Card* colTo,const char cardName[3]);
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
        } else if (strcmp(input, "SL") == 0) {
            printf("SL command\n");
        } else if (strcmp(input, "SR") == 0) {
            printf("SR command\n");
        } else if (strcmp(input, "SD") == 0) {
            printf("SD command\n");
        } else if (strcmp(command, "P") == 0) {
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
            printf("Starting move\n");
            move(columns[sourceCol[1] - '1'], columns[destCol[1] - '1'], card);
            strcpy(message, "OK");
        }
        strcpy(lastCommand, input);
    }
    return input;
}

void move(Card* colFrom, Card* colTo, const char cardName[3]){
    printf("Moving card: %s, from column with first card: %s, to column with first card %s\n", cardName, colFrom->name, colTo->name);
    Card* a = matchFound(colFrom, cardName);
    Card* b = last(colTo);

    a->previous->next = NULL;
    a->previous = b;
    b->next = a;
    a->hidden = false;
}

void run(){
    loaded = false;
    while (strcmp(command, "QQ") != 0) {
        //printBoard();
        strcpy(command, mainMenu());
    }
}