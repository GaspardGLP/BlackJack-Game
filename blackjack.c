#include "blackjack.h"

void initialize_deck(Deck **deck) {
    char *values[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
    char *colors[] = {"Spades", "Hearts", "Diamonds", "Clubs"};
    int points[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

    *deck = NULL;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            Deck *new_deck = malloc(sizeof(Deck));
            if (!new_deck) {
                printf("Memory allocation failed\n");
                exit(1);
            }

            new_deck->card->value = values[i];
            new_deck->card->color = colors[i];
            new_deck->card->points = points[i];
            new_deck->next = *deck;

            *deck = new_deck;
        }
    }
}

void deal_card(Deck **deck, Player *player) {
    if (*deck == NULL) {
        printf("No card left in the deck\n");
        exit(1);
    }

    //Deal the top card from the deck
    Deck *card_to_deal = *deck;
    *deck = (*deck)->next;

    //Add card to the player's hand
    card_to_deal->next = player->hand;
    player->hand = card_to_deal;

    //Player details
    player->score += card_to_deal->card->points;
    player->number_of_cards++;
}

void display_player_hand(Player *player) {
    Deck *current = player->hand;

    printf("Player hand:\n");

    while (current) {
        printf("- %s of %s (Points: %d)\n", current->card->value, current->card->color, current->card->points);
        current = current->next;
    }
    printf("Total score: %d\n", player->score);
}
