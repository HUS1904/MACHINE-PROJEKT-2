#include <stdio.h>
#include <ctype.h>
#include <strings.h>

char lastCommand[];
char message[];
char input[];

void run();
void printBoard();
void mainMenu();

int main(){
    run();
}

void printBoard(){
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\t\n");

    //More to be implemented.
}

void mainMenu(){
    printf("\nLAST Command: %c", *lastCommand);
    printf("\nMessage: %c", *message);
    printf("\nINPUT > ");
    scanf("%2s", &input);

    if (strcmp(input, "LD") == 0) {
        printf("LD command\n");
    } else if (strcmp(input, "SW") == 0) {
        printf("SW command\n");
    } else if (strcmp(input, "SL") == 0) {
        printf("SL command\n");
    } else if (strcmp(input, "SR") == 0) {
        printf("SR command\n");
    } else if (strcmp(input, "SD") == 0) {
        printf("SD command\n");
    } else if (strcmp(input, "QQ") == 0) {
        printf("QQ command - Quitting\n");
    } else {
        printf("Unknown command\n");
    }
    strcpy(lastCommand, input);
}

void run(){
    printBoard();
    mainMenu();
}