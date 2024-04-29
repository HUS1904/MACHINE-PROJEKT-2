#ifndef MACHINE_PROJEKT_2_LOAD_H
#define MACHINE_PROJEKT_2_LOAD_H
#include "Card.h"

// Create a single list deck out of a file
const char* load(const char* filename, Card** list);

// Arrange a deck evenly into the provided column array
void arrangeEvenly(Card* columns[7], Card* deck);

// Arrange a deck evenly into the provided column array and unhide every card
void arrangeVisible(Card* columns[7], Card* deck);

void arrangeP(Card* columns[7], Card* deck);

#endif //MACHINE_PROJEKT_2_LOAD_H
