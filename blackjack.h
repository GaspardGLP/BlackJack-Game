#ifndef blackjack_h
#define blackjack_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Card {
    char *value;
    char *color;
    int points;
} Card;

typedef struct Deck {
    Card *card;
    struct Deck *next;
} Deck;

typedef struct Player {
    Card main[11];
    int number_of_cards;
    int score;
} Player;

void initialize_deck(Deck **deck);

#endif blackjack_h