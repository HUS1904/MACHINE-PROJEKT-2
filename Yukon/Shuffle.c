#include <stdlib.h>
#include "Shuffle.h"

const char* shuffle(Card** deck) {
    int deckLength;
    Card* previous = NULL;

    do {
        deckLength = length(first(*deck));

        int r = (rand() % (deckLength - 1)) + 1;
        Card* extracted = get(*deck, r);
        Card* current = malloc(sizeof(Card));
        *current = buildCard(extracted->name);

        if (!current->precedence) {
            break;
        }

        linkCards(previous, current);
        previous = current;
        removeCard(extracted);
    } while (deckLength > 2);

    linkCards(previous, *deck);
    *deck = first(previous);

    return "OK";
}
