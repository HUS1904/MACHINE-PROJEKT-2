#ifndef MACHINE_PROJEKT_2_BOARD_H
#define MACHINE_PROJEKT_2_BOARD_H

// Returns a card's name if it's not hidden and two spaces if NULL
const char* maybe(Card* x);

// Returns either the name of the last card in a list or []
const char* maybeF(Card* x);

// Resets columns
void resetColumns(Card* columns[7]);

#endif //MACHINE_PROJEKT_2_BOARD_H
