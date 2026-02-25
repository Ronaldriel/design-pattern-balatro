#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <sstream>

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
    std::cout << "  [" << index << "] " << card.rank << " " << card.suit << "\n";
}

void printHand(const std::vector<Card>& hand) {
    std::cout << "\n>> Your Hand:\n";
    std::cout << "------------------------------\n";
    for (int i = 0; i < (int)hand.size(); i++)
        printCard(hand[i], i + 1);
    std::cout << "------------------------------\n";
}

// Returns list of 0-based indices to discard
std::vector<int> getDiscardChoices(int handSize) {
    std::cout << "\n  Enter card numbers to discard (e.g: 1, 2) or 0 to keep all: ";
    std::string line;
    std::cin.ignore();
    std::getline(std::cin, line);

    std::vector<int> indices;
    if (line == "0" || line.empty()) return indices;

    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, ',')) {
        try {
            int num = std::stoi(token);
            if (num >= 1 && num <= handSize)
                indices.push_back(num - 1); // convert to 0-based
        } catch (...) {}
    }

    // Remove duplicates and sort descending for safe removal
    std::sort(indices.begin(), indices.end());
    indices.erase(std::unique(indices.begin(), indices.end()), indices.end());

    return indices;
}

// Discard selected cards from hand, draw replacements from deck
void discardAndDraw(std::vector<Card>& hand, std::vector<Card>& deck, int& drawn, const std::vector<int>& discardIndices) {
    int count = (int)discardIndices.size();
    int available = (int)deck.size() - drawn;
    int toDraw = std::min(count, available);

    // Remove discarded cards (descending order to keep indices valid)
    for (int i = count - 1; i >= 0; i--)
        hand.erase(hand.begin() + discardIndices[i]);

    // Draw replacements from deck
    for (int i = 0; i < toDraw; i++) {
        hand.push_back(deck[drawn]);
        drawn++;
    }

    std::cout << "  Discarded " << count << " card(s), drew " << toDraw << " new card(s).\n";
}