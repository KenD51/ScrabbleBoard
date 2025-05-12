// LetterBag.cpp
#include "scrabble.h"
#include <random>

// Constructor: Initializes the bag with standard Scrabble tile distribution
LetterBag::LetterBag() {
    // Add tiles according to standard Scrabble distribution
    // Format: addTiles(letter, count, point_value)
    addTiles('A', 9, 1);
    addTiles('B', 2, 3);
    // ... (rest of initialization)
}

// Adds specified number of tiles to the bag
void LetterBag::addTiles(char letter, int count, int value) {
    for (int i = 0; i < count; ++i) {
        letter_bag.emplace_back(letter, value);
    }
}

// Checks if the bag is empty
bool LetterBag::is_empty() const {
    return letter_bag.empty();
}

// Draws a random tile from the bag
LetterTile LetterBag::draw_tile() {
    if (letter_bag.empty()) {
        throw std::runtime_error("Bag is empty");
    }
    
    // Set up random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, letter_bag.size() - 1);
    
    // Select and remove a random tile
    int index = dist(gen);
    LetterTile tile = letter_bag[index];
    letter_bag.erase(letter_bag.begin() + index);
    return tile;
}


