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
