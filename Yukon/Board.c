#include <stddef.h>
#include <stdlib.h>
#include "Card.h"
#include "Board.h"

const char* maybe(Card* x) {
    return x == NULL
        ? "  "
        : x->hidden
            ? x->name
            : x->name;
}

const char* maybeF(Card* x) {
    return x == NULL ? "[]" : last(x)->name;
}

void resetColumns(Card* columns[7]) {
    for (int i = 0; i < 7; ++i) {
        for (int j = 12; j >= 0; --j) {
            free(get(columns[i],j));
        }
        columns[i] = NULL;
    }
}
