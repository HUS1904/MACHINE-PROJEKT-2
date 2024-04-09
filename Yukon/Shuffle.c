#include <stdlib.h>
#include "Shuffle.h"

const char* shuffle(Card** deck) {
    int deckLength;
    Card* previous = NULL;

    while (true) {
        deckLength = length(*deck);
        if(deckLength < 3)
            break;

        int r = rand() % deckLength;
        Card* current = malloc(sizeof(Card));
        *current = buildCard(get(*deck, r)->name);

        if (!current->precedence)
            continue;

        linkCards(previous, current);
        previous = current;
        removeCard(get(*deck, r));
    }
    linkCards(previous, *deck);
    *deck = first(previous);

    return "OK";
}
