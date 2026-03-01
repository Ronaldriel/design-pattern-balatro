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
    bool discarded = false; // slot kosong setelah dibuang
};

std::vector<Card> createDeck() {
    std::vector<std::string> ranks = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    std::vector<std::string> suits = {"♥", "♦", "♣", "♠"};

    std::vector<Card> deck;
    for (auto& suit : suits)
        for (auto& rank : ranks)
            deck.push_back({rank, suit, false});

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

// Returns list of 0-based indices to discard, capped at maxCards
std::vector<int> getDiscardChoices(const std::vector<Card>& hand, int maxCards = 5) {
    if (hand.empty()) return {};

    std::cout << "\n  [ DISCARD ] Select up to " << maxCards
              << " card indices (e.g: 1,3) or 0 to cancel: ";
    std::string line;
    std::getline(std::cin, line);

    std::vector<int> indices;
    if (line == "0" || line.empty()) return indices;

    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, ',')) {
        try {
            int num = std::stoi(token);
            int idx = num - 1;
            if (idx >= 0 && idx < (int)hand.size())
                indices.push_back(idx);
        } catch (...) {}
    }

    std::sort(indices.begin(), indices.end());
    indices.erase(std::unique(indices.begin(), indices.end()), indices.end());
    if ((int)indices.size() > maxCards) indices.resize(maxCards);
    return indices;
}

// Remove cards at given indices and draw replacements appended to hand
void discardAndDraw(std::vector<Card>& hand, std::vector<Card>& deck, int& drawn, std::vector<int> indices) {
    // Sort descending so erasing doesn't shift later indices
    std::sort(indices.rbegin(), indices.rend());
    int count = (int)indices.size();

    for (int idx : indices)
        hand.erase(hand.begin() + idx);

    int drawCount = 0;
    for (int i = 0; i < count && drawn < (int)deck.size(); i++) {
        hand.push_back(deck[drawn++]);
        drawCount++;
    }

    if (drawCount > 0)
        std::cout << "  Drew " << drawCount << " new card(s).\n";
}

// Fill hand up to targetSize by drawing from deck
void fillHand(std::vector<Card>& hand, std::vector<Card>& deck, int& drawn, int targetSize = 5) {
    while ((int)hand.size() < targetSize && drawn < (int)deck.size())
        hand.push_back(deck[drawn++]);
}

// Get indices of cards the player wants to play for scoring
// Returns empty if input is invalid or empty
std::vector<int> getPlayChoices(const std::vector<Card>& hand) {
    std::cout << "\n  [ PLAY ] Select card indices to play (e.g: 1,3,5): ";
    std::string line;
    std::getline(std::cin, line);

    std::vector<int> indices;
    if (line.empty()) return indices;

    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, ',')) {
        try {
            int num = std::stoi(token);
            int idx = num - 1;
            if (idx >= 0 && idx < (int)hand.size())
                indices.push_back(idx);
        } catch (...) {}
    }

    std::sort(indices.begin(), indices.end());
    indices.erase(std::unique(indices.begin(), indices.end()), indices.end());
    return indices;
}