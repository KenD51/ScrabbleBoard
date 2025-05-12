// LetterBag.cpp
#include "scrabble.h"
#include <random>

// Constructor: Initializes the bag with standard Scrabble tile distribution
LetterBag::LetterBag() {
    // Add tiles according to standard Scrabble distribution
    // Format: addTiles(letter, count, point_value)
    addTiles('A', 9, 1);
    addTiles('B', 2, 3);
    addTiles('C', 2, 3);
    addTiles('D', 4, 2);
    addTiles('E', 12, 1);
    addTiles('F', 2, 4);
    addTiles('G', 3, 2);
    addTiles('H', 2, 4);
    addTiles('I', 9, 1);
    addTiles('J', 1, 8);
    addTiles('K', 1, 5);
    addTiles('L', 4, 1);
    addTiles('M', 2, 3);
    addTiles('N', 6, 1);
    addTiles('O', 8, 1);
    addTiles('P', 2, 3);
    addTiles('Q', 1, 10);
    addTiles('R', 6, 1);
    addTiles('S', 4, 1);
    addTiles('T', 6, 1);
    addTiles('U', 4, 1);
    addTiles('V', 2, 4);
    addTiles('W', 2, 4);
    addTiles('X', 1, 8);
    addTiles('Y', 2, 4);
    addTiles('Z', 1, 10);
    addTiles('*', 2, 0); // Blank tiles
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


