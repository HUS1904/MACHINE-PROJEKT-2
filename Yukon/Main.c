#include <stdio.h>

char lastCommand[] = input;
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
    printf("\nLAST Command: %c", lastCommand);
    printf("\nMessage: %c", message);
    printf("\nINPUT > ");
    scanf("%c", input);

}

void run(){
    printBoard();
}