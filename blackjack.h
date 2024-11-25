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
    Deck *hand;
    int score;
    int number_of_cards;
} Player;

void initialize_deck(Deck **deck);
void deal_card(Deck **deck, Player *player);
void display_player_hand(Player *player);

#endif blackjack_h