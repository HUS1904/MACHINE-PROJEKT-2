#include <string.h>
#include <stdbool.h>

typedef struct cardType Card;

struct cardType {
    char name[2];
    char suit; // Clubs, Hearts, Diamonds, Spades (C, H, D, S)
    int precedence; // Ace through King (A,1,...9,T,J,Q,K)
    bool hidden; // Whether the card is visible or not
    Card *next; // The card on top of this one
    Card *previous; // The card below this one
};

Card buildCard(char name[2]) {
    Card newCard;
    strcpy(newCard.name, name);
    newCard.suit = name[1];
    int precedence;
    switch (name[0]) {
        case 'A':
            precedence = 1;
            break;
        case '2':
            precedence = 2;
            break;
        case '3':
            precedence = 3;
            break;
        case '4':
            precedence = 4;
            break;
        case '5':
            precedence = 5;
            break;
        case '6':
            precedence = 6;
            break;
        case '7':
            precedence = 7;
            break;
        case '8':
            precedence = 8;
            break;
        case '9':
            precedence = 9;
            break;
        case 'T':
            precedence = 10;
            break;
        case 'J':
            precedence = 11;
            break;
        case 'Q':
            precedence = 12;
            break;
        case 'K':
            precedence = 13;
            break;
        default:
            precedence = 0;
    } // Map the first character of the card name to an integer
    newCard.precedence = precedence;
    newCard.hidden = true;
    newCard.next = NULL;
    newCard.previous = NULL;
    return newCard;
}

void linkCards(Card *previous, Card *next) {
    next->previous = previous;
    previous->next = next;
}

void insert(Card *previous, Card *next, Card *inserted) {
    previous->next = inserted;
    inserted->previous = previous;
    inserted->next = next;
    next->previous = inserted;
}

Card* first(Card *check) {
    return check->previous == NULL ? check : first(check->previous);
}

Card* last(Card *check) {
    return check->next == NULL ? check : last(check->next);
}
