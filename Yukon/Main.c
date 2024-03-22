#include <stdio.h>

char lastCommand[];
char message[];
char input[];

void run();
void printBoard();

int main(){
    run();
}

void printBoard(){
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\t\n");

    //More to be implemented.

    printf("\nLAST Command: %c", lastCommand);
    printf("\nMessage: %c", message);
    printf("\nINPUT > ");
}

void run(){
    printBoard();
}