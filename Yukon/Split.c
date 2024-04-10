#include "Card.h"
#include <stdio.h>
#include <stdbool.h>
#include "Split.h"

const char* splitDeck(Card** deck, int splitIndex) {
    if (splitIndex <= 0 || *deck == NULL) {
        return "Invalid split index or empty deck.";
    }

    // Get the card at the split index and the beginning of the second deck
    Card* splitAt = get(*deck, splitIndex - 1); // Adjust if your indexing is off by one
    if (splitAt == NULL || splitAt->next == NULL) {
        return "Split index out of bounds.";
    }

    Card* secondDeck = splitAt->next;
    splitAt->next->previous = NULL; // Disconnect the second deck from the first
    splitAt->next = NULL; // End the first deck

    // Now you have two decks: *deck and secondDeck, let's interleave them
    interleaveDecks(deck, &secondDeck);

    return "OK";
}
void interleaveDecks(Card** firstDeck, Card** secondDeck) {
    Card* currentFirst = *firstDeck;
    Card* currentSecond = *secondDeck;
    Card* nextFirst = NULL;
    Card* nextSecond = NULL;

    while (currentFirst != NULL && currentSecond != NULL) {
        // Store next cards
        nextFirst = currentFirst->next;
        nextSecond = currentSecond->next;

        // Interleave
        currentFirst->next = currentSecond;
        currentSecond->previous = currentFirst;

        if (nextFirst != NULL) { // Prepare for the next iteration
            nextFirst->previous = currentSecond;
        }

        currentSecond->next = nextFirst;

        // Move to next cards
        currentFirst = nextFirst;
        currentSecond = nextSecond;
    }
}