#include "blackjack.h"

int main() {
    srand(time(NULL));

    Deck *deck = NULL;
    Player player = {NULL, 0, 0};
    Player dealer = {NULL, 0, 0};

    // Initialiser et mélanger le deck
    initialize_deck(&deck);
    shuffle_deck(&deck);

    // Jouer une partie
    play_game(&deck, &player, &dealer);

    // Libérer la mémoire
    free_deck(&deck);

    return 0;
}
