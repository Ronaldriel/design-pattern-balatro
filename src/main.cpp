#include "ShuffleDeck.h"
#include "ScoringSystem.h"

int main() {
    std::vector<Card> deck = createDeck();
    shuffleDeck(deck);

    const int ROUNDS          = 4;
    const int targets[ROUNDS] = {1, 2, 4, 5};
    const int MAX_PLAYS        = 3;
    const int MAX_DISCARDS    = 3;
    const int MAX_DISCARD_CARDS = 3;

    std::cout << "==============================\n";
    std::cout << "   Blackjack Challenge!\n";
    std::cout << "   52 cards, 4 rounds.\n";
    std::cout << "==============================\n";

    int drawn = 0;
    std::vector<Card> hand;
    fillHand(hand, deck, drawn);

    for (int round = 0; round < ROUNDS; round++) {
        int target       = targets[round];
        int blackjacks   = 0;
        int playsUsed    = 0;
        int discardsUsed = 0;

        std::cout << "\n";
        std::cout << "==============================\n";
        std::cout << "  ROUND " << (round + 1) << "  |  Goal: " << target << " Blackjack(s)\n";
        std::cout << "==============================\n";

        bool quitGame = false;

        while (blackjacks < target && playsUsed < MAX_PLAYS) {
            int remaining = (int)deck.size() - drawn;

            printHand(hand);
            std::cout << "  Blackjacks : " << blackjacks << " / " << target << "\n";
            std::cout << "  Plays      : " << playsUsed << " / " << MAX_PLAYS << "\n";
            std::cout << "  Discards   : " << discardsUsed << " / " << MAX_DISCARDS << "\n";
            std::cout << "  Deck left  : " << remaining << "\n";
            std::cout << "------------------------------\n";
            std::cout << "  1. Play\n";
            std::cout << "  2. Discard\n";
            std::cout << "  0. Quit\n";
            std::cout << "  Choice: ";

            std::string choice;
            std::getline(std::cin, choice);

            if (choice == "0") {
                quitGame = true;
                break;
            }

            // ── PLAY ──────────────────────────────────────────────────────
            if (choice == "1") {
                if (playsUsed >= MAX_PLAYS) {
                    std::cout << "  No plays remaining this round!\n";
                    continue;
                }
                std::vector<int> playIndices;
                do {
                    playIndices = getPlayChoices(hand);
                    if (playIndices.empty())
                        std::cout << "  Select at least one card to play!\n";
                } while (playIndices.empty());

                std::cout << "\n  Playing: ";
                std::vector<Card> played;
                for (int idx : playIndices) {
                    played.push_back(hand[idx]);
                    std::cout << hand[idx].rank << hand[idx].suit << " ";
                }
                std::cout << "\n";

                int score = calculateScore(played);
                std::cout << "  Score   : " << score;
                if (score == 21) {
                    std::cout << "  *** BLACKJACK! ***\n";
                    blackjacks++;
                } else if (score > 21) {
                    std::cout << "  -- BUST!\n";
                } else {
                    std::cout << "\n";
                }
                std::cout << "==============================\n";

                playsUsed++;
                discardAndDraw(hand, deck, drawn, playIndices);
                fillHand(hand, deck, drawn);

            // ── DISCARD ───────────────────────────────────────────────────
            } else if (choice == "2") {
                if (discardsUsed >= MAX_DISCARDS) {
                    std::cout << "  No discards remaining this round!\n";
                    continue;
                }

                std::vector<int> discardIndices = getDiscardChoices(hand, MAX_DISCARD_CARDS);
                if (discardIndices.empty()) {
                    std::cout << "  No cards discarded.\n";
                    continue;
                }

                std::cout << "  Discarding: ";
                for (int idx : discardIndices)
                    std::cout << hand[idx].rank << hand[idx].suit << " ";
                std::cout << "\n";

                discardAndDraw(hand, deck, drawn, discardIndices);
                fillHand(hand, deck, drawn);
                discardsUsed++;
                std::cout << "  Discards used: " << discardsUsed << "/" << MAX_DISCARDS << "\n";
                std::cout << "==============================\n";

            } else {
                std::cout << "  Invalid choice. Enter 1, 2, or 0.\n";
            }

            // Deck & hand exhausted
            if (hand.empty()) {
                std::cout << "\n  No cards left! Game over!\n";
                std::cout << "==============================\n";
                quitGame = true;
                break;
            }
        }

        if (!quitGame && playsUsed >= MAX_PLAYS && blackjacks < target) {
            std::cout << "\n  Out of plays! Round " << (round + 1) << " failed.\n";
            std::cout << "==============================\n";
            return 0;
        }

        if (quitGame) {
            std::cout << "\n  Game ended. Final round: " << (round + 1) << "\n";
            std::cout << "==============================\n";
            return 0;
        }

        // Round complete
        if (round < ROUNDS - 1) {
            std::cout << "\n  Round " << (round + 1) << " Complete! On to round " << (round + 2) << "!\n";
            std::cout << "==============================\n";
        } else {
            std::cout << "\n";
            std::cout << "==============================\n";
            std::cout << "  YOU WIN! All 4 rounds cleared!\n";
            std::cout << "==============================\n";
        }
    }

    return 0;
}

