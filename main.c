#include "blackjack.h"

int main() {
    srand(time(NULL));

    Deck *deck = NULL;
    Player player = {NULL, 0, 0};
    Player dealer = {NULL, 0, 0};

    initialize_deck(&deck);

    printf("Initializing deck\n");

    deal_card(&deck, &player);
    deal_card(&deck, &player);
    deal_card(&deck, &dealer);
    deal_card(&deck, &dealer);

    printf("\nPlayer's hand:\n");
    display_player_hand(&player);

    printf("\nDealer's hand:\n");
    display_player_hand(&dealer);

    free_deck(deck);

    return 0;
}