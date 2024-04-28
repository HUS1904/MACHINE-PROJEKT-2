#ifndef MACHINE_PROJEKT_2_CARD_H
#define MACHINE_PROJEKT_2_CARD_H
#include <stdbool.h>

typedef struct cardType Card;

struct cardType {
    char name[3];
    char suit; // Clubs, Hearts, Diamonds, Spades (C, H, D, S)
    int precedence; // Ace through King (A,1,...9,T,J,Q,K)
    bool hidden; // Whether the card is visible or not
    Card *next; // The card on top of this one
    Card *previous; // The card below this one
};

// Factory function for Card struct
Card buildCard(const char name[2]);

// Links two cards together
void linkCards(Card *previous, Card *next);

// Links one card with two others on either side of it
void insert(Card *previous, Card *next, Card *inserted);

// Gets a pointer to the first card of a list
Card* first(Card *check);

// Gets a pointer to the last card of a list
Card* last(Card *check);

// Get the nth card following the one given
Card* get(Card *from, int n);

// Remove a card, link its neighbours and free its memory
void removeCard(Card *removed);

// Get the length of a list of cards
int length(Card *first);

// Returns pointer to card with name if found within col
Card* matchFound(Card* col, const char cardName[3]);

// Checks if the two cards are of a different suit
bool isDifferentSuit(Card* a, Card* b);

// Checks if card a is one rank below card b
bool isOneRankLower(Card* a, Card* b);

// Checks if card a is one rank above card b
bool isOneRankHigher(Card* a, Card* b);

// For each function
void forEach(void (*fun)(Card*), Card* card);

#endif