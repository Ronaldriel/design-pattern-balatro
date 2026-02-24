#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

struct Card {
    std::string rank;
    std::string suit;
};

std::vector<Card> createDeck() {
    std::vector<std::string> ranks = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    std::vector<std::string> suits = {"♥", "♦", "♣", "♠"};

    std::vector<Card> deck;
    for (auto& suit : suits)
        for (auto& rank : ranks)
            deck.push_back({rank, suit});

    return deck;
}

void shuffleDeck(std::vector<Card>& deck) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(deck.begin(), deck.end(), rng);
}

void printCard(const Card& card, int index) {
    std::cout << "  Card " << index << ": [" << card.rank << " " << card.suit << "]\n";
}

int main() {
    std::vector<Card> deck = createDeck();
    shuffleDeck(deck);

    std::cout << "==============================\n";
    std::cout << "    52-Card Deck Shuffled!\n";
    std::cout << "==============================\n";

    int drawn = 0;
    char choice = 'y';

    while (choice == 'y' || choice == 'Y') {
        int remaining = (int)deck.size() - drawn;

        if (remaining <= 0) {
            std::cout << "\n  No more cards in the deck!\n";
            std::cout << "==============================\n";
            break;
        }

        int toDraw = std::min(5, remaining);

        std::cout << "\n>> Drawing " << toDraw << " card(s):\n";
        std::cout << "------------------------------\n";
        for (int i = 0; i < toDraw; i++)
            printCard(deck[drawn + i], drawn + i + 1);

        drawn += toDraw;
        remaining = (int)deck.size() - drawn;

        std::cout << "------------------------------\n";
        std::cout << "  Cards left in deck: " << remaining << "\n";
        std::cout << "==============================\n";

        if (remaining <= 0) {
            std::cout << "\n  Deck is now empty!\n";
            std::cout << "==============================\n";
            break;
        }

        std::cout << "\n  Draw another 5? (y/n): ";
        std::cin >> choice;
    }

    if (choice == 'n' || choice == 'N') {
        std::cout << "\n  Stopped drawing. " << (int)deck.size() - drawn << " card(s) remain in the deck.\n";
        std::cout << "==============================\n";
    }

    return 0;
}