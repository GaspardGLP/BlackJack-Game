#include "blackjack.h"

// Creates a linked list of 52 cards
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

            new_deck->card = malloc(sizeof(Card));
            if (!new_deck->card) {
                printf("Memory allocation failed for card\n");
                free(new_deck);
                exit(1);
            }

            new_deck->card->value = values[j];
            new_deck->card->color = colors[i];
            new_deck->card->points = points[j];
            new_deck->next = *deck;

            *deck = new_deck;
        }
    }
}

// Removes the first card from the deck and adds it to a player's hand
void deal_card(Deck **deck, Player *player) {
    if (*deck == NULL) {
        printf("No cards left in the deck\n");
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

// Prints all the cards in a player's hand
void display_player_hand(const char *name, Player *player) {
    Deck *current = player->hand;

    printf("%s's hand:\n", name);

    while (current) {
        printf("- %s of %s (Points: %d)\n", current->card->value, current->card->color, current->card->points);
        current = current->next;
    }
    printf("Total score: %d\n", player->score);
}

void shuffle_deck(Deck **deck) {
    // Count the total number of nodes in the linked list
    int count = 0;
    Deck *current = *deck;
    while (current) {
        count++;
        current = current->next;
    }

    if (count <= 1) return;

    // Create an array of pointers to the nodes
    Deck **array = malloc(count * sizeof(Deck *));
    if (!array) {
        printf("Memory allocation failed for shuffle!\n");
        exit(1);
    }

    // Populate the array with pointers to the nodes
    current = *deck;
    for (int i = 0; i < count; i++) {
        array[i] = current;
        current = current->next;
    }

    // Fisher-Yates shuffle
    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Deck *temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    // Rebuild the linked list using the shuffled array
    *deck = array[0];
    current = *deck;
    for (int i = 1; i < count; i++) {
        current->next = array[i];
        current = current->next;
    }
    current->next = NULL;

    free(array);
}

void play_game(Deck **deck, Player *player, Player *dealer) {
    // Distribuer deux cartes à chaque joueur
    deal_card(deck, player);
    deal_card(deck, player);
    deal_card(deck, dealer);
    deal_card(deck, dealer);

    printf("\n");
    display_player_hand("Player", player);
    printf("\n");
    display_player_hand("Dealer", dealer);

    // Tour du joueur
    char choice;
    while (1) {
        printf("\nPlayer, do you want to (h)it or (s)tand? ");
        scanf(" %c", &choice);

        if (choice == 'h') {
            deal_card(deck, player);
            printf("\n");
            display_player_hand("Player", player);

            if (player->score > 21) {
                printf("\nPlayer busts! You lose.\n");
                return; // Fin de la partie
            }
        } else if (choice == 's') {
            break; // Le joueur s'arrête
        } else {
            printf("Invalid choice. Please enter 'h' or 's'.\n");
        }
    }

    // Tour du dealer
    printf("\nDealer's turn:\n");
    while (dealer->score < 17) {
        deal_card(deck, dealer);
        display_player_hand("Dealer", dealer);

        if (dealer->score > 21) {
            printf("\nDealer busts! You win!\n");
            return; // Fin de la partie
        }
    }

    // Comparer les scores
    printf("\nFinal scores:\n");
    printf("Player: %d\n", player->score);
    printf("Dealer: %d\n", dealer->score);

    if (player->score > dealer->score) {
        printf("\nYou win!\n");
    } else if (player->score < dealer->score) {
        printf("\nDealer wins!\n");
    } else {
        printf("\nIt's a tie!\n");
    }
}

// Releases all the memory used by the deck or hand
void free_deck(Deck **deck) {
    while (*deck) {
        Deck *temp = *deck;
        *deck = (*deck)->next;
        free(temp->card);
        free(temp);
    }
}
