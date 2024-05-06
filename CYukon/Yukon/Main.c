#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "Load.h"
#include "Card.h"
#include "Board.h"
#include "Split.h"
#include "SaveDeck.h"
#include "Shuffle.h"
#include <winsock2.h>
#include <winsock.h>

#define PORT 8080
#define BUFFER_SIZE 1024


WSADATA wsa;
SOCKET sockfd;
struct sockaddr_in server_addr, client_addr;
int recv_len, client_len,send_len;

char lastCommand[100];
char message[100];
char input[BUFFER_SIZE + 1];
char response[BUFFER_SIZE + 1];
char filename[100];
char command[100];
char card[10];
char sourceCol[10];
char destCol[10];
bool loaded;
bool winCondition;

Card* columns[7];
Card* foundations[4];
Card* deck;


void printBoard();
const char* mainMenu();
const char* playMenu();
void rewrite();
void move(Card** colFrom, Card** colTo,const char cardName[3]);
void run();
void decideWin();

int main(){
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) {
        printf("Failed to create socket\n");
        return 1;
    }

    // Initialize server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the specified port
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Bind failed\n");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    printf("Server listening on port %d\n", PORT);


        client_len = sizeof(client_addr);







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
    int splitIndex;
    while (continueMainMenu && strcmp(command, "QQ") != 0) {
        printBoard();
        printf("\nLAST Command: %s", lastCommand);
        printf("\nMessage: %s", message);
        printf("\nINPUT >");

        if(!winCondition) {
            recv_len = recvfrom(sockfd, input, BUFFER_SIZE, 0, (struct sockaddr *) &client_addr, &client_len);
            if (recv_len == SOCKET_ERROR) {
                printf("Receive failed\n");
            }

            sscanf(input, "%s", command);
            // Null-terminate the received data
            input[recv_len] = '\0';
            sscanf(input, "%s %s", command, filename);
            printf("\n");
        } else{
            sscanf(input, "%s", "QQ");
        }




        if (strcmp(command, "LD") == 0) {
            resetColumns(columns);
            resetFoundations(foundations);
            strcmp(filename, "") == 0
            ? strcpy(message, load("default.txt", &deck))
            : strcpy(message, load(filename, &deck));
            if(strcmp(message, "OK") == 0){
                sprintf(response, "%s", message);
                arrangeEvenly(columns, deck);
            } else {
                sprintf(response, "%s", message);
            }



        } else if (strcmp(command, "SW") == 0) {
            if (!loaded) {
                strcpy(message, "Error: no deck is loaded");
                sprintf(response, "%s", message);

            } else {
                resetColumns(columns);
                resetFoundations(foundations);
                arrangeVisible(columns, deck);
                rewrite();
                strcpy(message, "OK");
                sprintf(response, "%s", message);

            }
        }

        else if (strcmp(command, "SI") == 0) {
            resetColumns(columns);
            resetFoundations(foundations);
            if (deck) { // Ensure deck is loaded before attempting to split

                splitIndex = atoi(filename);
                printf("%d",splitIndex);
                if(splitIndex >= 52 || splitIndex < 1) {
                    splitIndex = rand() % 50 + 1;
                }
                // Now call splitDeck with either the provided or default index
                strcpy(message, splitDeck(&deck, splitIndex));
                arrangeEvenly(columns, deck);
                strcpy(filename,"");
                sprintf(response, "%s", "OK\n");
            } else {
                printf("Load a deck first.\n");
                sprintf(response, "%s", "load a deck first.\n");
            }
        }

        else if (strcmp(command, "SR") == 0) {
            resetColumns(columns);
            resetFoundations(foundations);
            shuffle(&deck);
            arrangeEvenly(columns, deck);
            sprintf(response, "%s", "OK\n");
        }

        else if (strcmp(command, "SD") == 0) {
            strcmp(filename, "") == 0
            ? strcpy(message, connectToFile("cards.txt"))
            : strcpy(message, connectToFile(filename));
            if(strcmp(message,"OK") == 0){
                saveE(deck);
                sprintf(response, "%s", message);
            }
        }

        else if (strcmp(command, "P") == 0) {
            resetColumns(columns);
            resetFoundations(foundations);
            arrangeP(columns, deck);
            strcpy(message, "OK");
            sprintf(response, "%s", message);
            send_len = sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&client_addr, client_len);
            playMenu();
            continueMainMenu = false;


        } else {
            strcpy(message, "ERROR: Unknown command");
            sprintf(response, "%s", message);

        }
        send_len = sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&client_addr, client_len);
        strcpy(lastCommand, input);
    }
    return input;
}

const char* playMenu() {
    bool inPlayMenu = true;
    while (inPlayMenu) {
        rewrite();
        printBoard();
        printf("\nLAST Command: %s", lastCommand);
        printf("\nMessage: %s", message);
        printf("\nINPUT >");


            recv_len = recvfrom(sockfd, input, BUFFER_SIZE, 0, (struct sockaddr *) &client_addr, &client_len);
            if (recv_len == SOCKET_ERROR) {
                printf("Receive failed\n");
            }
            input[recv_len] = '\0';






        if(strlen(input) == 9) {
            strcpy(sourceCol, strtok(input, ":"));
            strcpy(card, strtok(&input[3], "->"));
            strcpy(destCol, &input[7]);
        } else if(strlen(input) == 6) {
            strcpy(sourceCol, strtok(input, ":"));
            strcpy(destCol, &input[4]);
            strcpy(card, last(columns[sourceCol[1] - '1'])->name);
        }
        printf("Accepted input\n");

        char sourcearr[3];
        sourcearr[0] = sourceCol[0];
        sourcearr[1] = sourceCol[1];
        sourcearr[2] = '\0';
        const char* source = sourcearr;


        if (strcmp(input, "Q") == 0) {
            strcpy(message, "OK");
            sprintf(response, "%s", message);
            inPlayMenu = false;
        } else {
            printf("Checking input\n");

        if(strcmp(destCol,source) != 0){

            // Move a card to an empty foundation
         if(destCol[0] == 'F'){
                if(foundations[destCol[1] - '1'] == NULL && matchFound(columns[sourceCol[1] - '1'], card)->precedence >= 1) {
                    move(&columns[sourceCol[1] - '1'], &foundations[destCol[1] - '1'], card);
                    rewrite();
                    strcpy(message, "OK");
                    sprintf(response, "%s", message);

                }else if( matchFound(columns[sourceCol[1] - '1'], card)->precedence - foundations[destCol[1] - '1']->precedence == 1 && !isDifferentSuit(matchFound(columns[sourceCol[1] - '1'], card), foundations[destCol[1] - '1'])) {
                    move(&columns[sourceCol[1] - '1'], &foundations[destCol[1] - '1'], card);
                    rewrite();
                    strcpy(message, "OK");
                    sprintf(response, "%s", message);
                }// Standard move
                }else if(isDifferentSuit(matchFound(columns[sourceCol[1] - '1'], card), last(columns[destCol[1] - '1'])) && isOneRankLower(matchFound(columns[sourceCol[1] - '1'], card), last(columns[destCol[1] - '1']))) {
             printf("Different suit\n");
             char from = sourceCol[1];
             char to = destCol[1];

             int fromcol = (int) from;
             int tocol = (int) to;

             if (fromcol <= 7 && tocol <= 7) {
                 move(&columns[sourceCol[1] - '1'], &columns[destCol[1] - '1'], card);
                 rewrite();
                 strcpy(message, "OK");
             } else {
                 strcpy(message, "Invalid column number");
             }
                sprintf(response, "%s", message);
                // Move K to an empty column
            } else if(card[0] == 'K' && destCol[0] == 'C' && columns[destCol[1] - '1'] == NULL){
                printf("Moving to empty column\n");
                move(&columns[sourceCol[1] - '1'], &columns[destCol[1] - '1'], card);
                rewrite();
                strcpy(message, "OK");
                sprintf(response, "%s", message);
            } else{
             strcpy(message, "Error: Invalid move");
             sprintf(response, "%s", message);

         }

            } else{
            strcpy(message, "Error: Same column move");
            sprintf(response, "%s", message);
        }
        }

                decideWin();


                if(winCondition){
                    strcpy(message, "You Won");
                    sprintf(response, "%s", message);
                    send_len = sendto(sockfd, response, strlen(response), 0, (struct sockaddr *) &client_addr, client_len);
                } else{
                    send_len = sendto(sockfd, response, strlen(response), 0, (struct sockaddr *) &client_addr, client_len);
                }


            //Unhide the last card of a column if hidden.
            if((last(columns[sourceCol[1] - '1']) != NULL)) {
                if (last(columns[sourceCol[1] - '1'])->hidden) {
                    last(columns[sourceCol[1] - '1'])->hidden = false;
                }
            }

        strcpy(lastCommand, input);

}

        return input;
    }

void move(Card** colFrom, Card** colTo, const char cardName[3]){
    printf("Started move\n");
    Card* a = matchFound(*colFrom, cardName);
    Card* b = last(*colTo);

        if (a->previous != NULL) {
            a->previous->next = NULL;
        } else {
            *colFrom = NULL;
        }

        if (b != NULL) {
            a->previous = b;
            b->next = a;
        } else {
            *colTo = a;
            a->previous = NULL;
        }

        a->hidden = false;

}

void rewrite(){

    FILE* state = fopen("state.txt","w");
    if (state == NULL) {
        perror("Error opening file");
        return;  // Exit function if file opening fails
    }

    forEach(&writeToFile,columns[0],state);

    forEach(&writeToFile,columns[1],state);

    forEach(&writeToFile,columns[2],state);

    forEach(&writeToFile,columns[3],state);

    forEach(&writeToFile,columns[4],state);
    forEach(&writeToFile,columns[5],state);
    forEach(&writeToFile,columns[6],state);
    forEach(&writeToFile,foundations[0],state);
    forEach(&writeToFile,foundations[1],state);
    forEach(&writeToFile,foundations[2],state);
    forEach(&writeToFile,foundations[3],state);
    fclose(state);

}

void decideWin(){
    for(int i = 0; i < 8;i++){
        if(columns[i] == NULL){
            if(i == 7){
                winCondition = true;
            }
        } else{
            winCondition = false;
            break;
        }
    }

}

void run(){
    loaded = false;
    while (strcmp(command, "QQ") != 0) {
        //printBoard();
        strcpy(command, mainMenu());
    }
    closesocket(sockfd);
    WSACleanup();
}