#include "ShuffleDeck.h"

int main() {
    std::vector<Card> deck = createDeck();
    shuffleDeck(deck);

    std::cout << "==============================\n";
    std::cout << "    52-Card Deck Shuffled!\n";
    std::cout << "==============================\n";

    int drawn = 0;
    char choice = 'y';

    // Draw initial 5 cards into hand
    std::vector<Card> hand;
    int toDraw = std::min(5, (int)deck.size());
    for (int i = 0; i < toDraw; i++)
        hand.push_back(deck[drawn++]);

    while (true) {
        int remaining = (int)deck.size() - drawn;

        printHand(hand);
        std::cout << "  Cards left in deck: " << remaining << "\n";
        std::cout << "==============================\n";

        // Ask to discard
        std::vector<int> discardIndices = getDiscardChoices((int)hand.size());

        if (!discardIndices.empty()) {
            discardAndDraw(hand, deck, drawn, discardIndices);
            remaining = (int)deck.size() - drawn;

            printHand(hand);
            std::cout << "  Cards left in deck: " << remaining << "\n";
            std::cout << "==============================\n";
        } else {
            std::cout << "  Keeping all cards.\n";
            std::cout << "==============================\n";
        }

        if (remaining <= 0) {
            std::cout << "\n  Deck is now empty!\n";
            std::cout << "==============================\n";
            break;
        }

        // Ask to draw another 5
        std::cout << "\n  Draw another 5? (y/n): ";
        std::cin >> choice;

        if (choice == 'n' || choice == 'N') {
            std::cout << "\n  Stopped drawing. " << remaining << " card(s) remain in the deck.\n";
            std::cout << "==============================\n";
            break;
        }

        // Draw 5 new cards into hand (replace hand)
        hand.clear();
        int nextDraw = std::min(5, (int)deck.size() - drawn);
        for (int i = 0; i < nextDraw; i++)
            hand.push_back(deck[drawn++]);
    }

    return 0;
}