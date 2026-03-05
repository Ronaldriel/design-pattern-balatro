#pragma once

#include <iostream>
#include <string>

void enterShop(int currentRound) {
    std::cout << "\n";
    std::cout << "==============================\n";
    std::cout << "       🛒 SHOP 🛒\n";
    std::cout << "  (After Round " << currentRound << ")\n";
    std::cout << "==============================\n";
    std::cout << "\n";
    std::cout << "  Welcome to the shop!\n";
    std::cout << "  (Currently empty - under construction)\n";
    std::cout << "\n";
    std::cout << "  Press Enter to continue...\n";
    std::cout << "==============================\n";
    
    std::string dummy;
    std::getline(std::cin, dummy);
}
