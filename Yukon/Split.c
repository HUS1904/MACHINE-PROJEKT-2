#include "Card.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Split.h"

const char* splitDeck(Card** deck, int splitIndex) {
    printf("split index %i\n", splitIndex);
    if (splitIndex <= 0 || *deck == NULL) {
        return "Invalid split index or empty deck.";
    }

    // Get the card at the split index and the beginning of the second deck
    Card* splitAt = get(*deck, splitIndex); // Adjust if your indexing is off by one
    if (splitAt == NULL || splitAt->next == NULL) {
        return "Split index out of bounds.";
    }

    Card* secondDeck = splitAt->next;
    splitAt->next->previous = NULL; // Disconnect the second deck from the first
    splitAt->next = NULL; // End the first deck

    // Now you have two decks: *deck and secondDeck, let's interleave them
    if(splitIndex >= 25)
        interleaveDecks(deck, &secondDeck);
    else { // Flips which one is the first stack if the index is too small
        interleaveDecks(&secondDeck, deck);
        *deck = secondDeck;
    }

    return "OK";
}
void interleaveDecks(Card** deck, Card** secondDeck) {

    Card* firstLast = last(*deck);
    Card* secondLast = last(*secondDeck);

    Card* firstFirst = first(firstLast);
    Card* secondFirst = first(secondLast);
    printf("First: %s\tSecond: %s\n", firstFirst->name, secondFirst->name);

    while (firstLast != firstFirst && secondLast != secondFirst) {
        insert(firstFirst, firstFirst->next, secondFirst);

        firstFirst = firstFirst->next->next;
        secondFirst = first(secondLast);
        printf("Iteration finished:\nFirst: %s\tSecond: %s\n", firstFirst->name, secondFirst->name);
    }

    linkCards(firstLast, secondLast);
}