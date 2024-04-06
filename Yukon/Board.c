#include <stddef.h>
#include "Card.h"
#include "Board.h"

const char* maybe(Card* x) {
    return x == NULL ? "  " : x->name;
}
