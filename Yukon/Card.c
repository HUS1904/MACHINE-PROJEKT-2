#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "Card.h"

Card buildCard(const char name[3]) {
    Card newCard;
    newCard.name[0] = name[0];
    newCard.name[1] = name[1];
    newCard.name[2] = '\0';
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
    // If the precedence is equal to 0, the card is broken
    newCard.precedence = precedence;
    if(newCard.suit != 'C' && newCard.suit != 'D' && newCard.suit != 'H' && newCard.suit != 'S')
        newCard.precedence = 0;
    newCard.hidden = true;
    newCard.next = NULL;
    newCard.previous = NULL;
    return newCard;
}

void linkCards(Card *previous, Card *next) {
    if(previous == next) {
        return;
    } else if(previous == NULL) {
        next->previous = NULL;
    } else if(next == NULL) {
        previous->next = NULL;
    } else {
        next->previous = previous;
        previous->next = next;
    }
}

void insert(Card *previous, Card *next, Card *inserted) {
    if(previous != NULL)
        previous->next = inserted;

    if(inserted->next != NULL) {
        inserted->next->previous = NULL;
    }

    inserted->previous = previous;
    inserted->next = next;

    if(next != NULL)
        next->previous = inserted;
}

void removeCard(Card *removed) {
    if (removed->previous != NULL)
        removed->previous->next = removed->next;
    if (removed->next != NULL)
        removed->next->previous = removed->previous;
    free(removed);
    removed = NULL;
}

int lengthAcc(Card* first, int n) {
    return first->next == NULL ? n : lengthAcc(first->next, n + 1);
}

int length(Card *first) {
    return first == NULL ? 0 : lengthAcc(first, 1);
}

Card* first(Card *check) {
    return check == NULL ? NULL : check->previous == NULL ? check : first(check->previous);
}

Card* last(Card *check) {
    return check == NULL ? NULL : check->next == NULL ? check : last(check->next);
}

Card* get(Card *from, int n) {
    if(from == NULL) {
        return NULL;
    }
    Card* card = from;
    while (card != NULL && n-- > 0) {
        card = card->next;
    }
    return card;
}

Card* matchFound(Card* col, const char cardName[3]){
    Card* current = col; // Start with the top card
    while (current != NULL) {  // Traverse until the end of the list
        if (strcmp(current->name, cardName) == 0) {
            return current;
        } else {
            current = current->next;  // Move to the next card
        }
    }
}

bool isDifferentSuit(Card* a, Card* b){
    return !(a->suit == b->suit);
}

bool isOneRankLower(Card* a, Card* b){
    return b->precedence - a->precedence == 1;
}

bool isOneRankHigher(Card* a, Card* b){
    return a->precedence - b->precedence == 1;
}

