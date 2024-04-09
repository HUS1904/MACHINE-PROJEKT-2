#include <stdio.h>
#include <stdbool.h>
#include "Unhide.h"
#include "Card.h"
#include "Main.h"

const char* unhide(Card** deck){
    if(loaded == false) return "Error: no deck is loaded";

    for (int i = 0; i < 52; ++i) {
        Card *current = get(deck, i);
        current->hidden = false;
    }

    return "OK\0";
}