// LetterRack.cpp
#include "scrabble.h"
#include <iostream>

// Removes a specific letter from the rack
LetterTile LetterRack::remove_letter(char letter) {
    for (int i = 0; i < SIZE; i++) {
        if (rack[i].get_letter() == letter) {
            LetterTile tmp = rack[i];
            rack[i] = LetterTile('?', 0); // Replace with placeholder
            return tmp;
        }
    }
    throw std::domain_error("The rack does not contain that letter.");
}

// Fills empty slots in the rack with tiles from the bag
void LetterRack::fill_rack(LetterBag& bag) {
    for (int i = 0; i < SIZE; i++) {
        // Replace placeholder tiles if bag isn't empty
        if (rack[i].get_letter() == '?' && !bag.is_empty()) {
            rack[i] = bag.draw_tile();
        }
    }
}

// Displays the current letters in the rack
void LetterRack::print_rack() const {
    std::cout << "Your rack contains: ";
    for (int i = 0; i < SIZE; i++) {
        std::cout << rack[i].get_letter() << " ";
    }
    std::cout << std::endl;
}

