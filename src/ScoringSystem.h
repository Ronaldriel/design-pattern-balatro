#pragma once

#include <vector>
#include <string>
#include "ShuffleDeck.h"

// Blackjack-style score: 2-10 = face, J/Q/K = 10, A = 11 or 1
int calculateScore(const std::vector<Card>& cards) {
    int score = 0;
    int aces = 0;
    for (auto& card : cards) {
        if (card.rank == "A") {
            aces++;
            score += 11;
        } else if (card.rank == "J" || card.rank == "Q" || card.rank == "K") {
            score += 10;
        } else {
            score += std::stoi(card.rank);
        }
    }
    // Reduce Ace from 11 to 1 if busting
    while (score > 21 && aces > 0) {
        score -= 10;
        aces--;
    }
    return score;
}
