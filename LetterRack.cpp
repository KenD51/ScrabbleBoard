// LetterRack.cpp
// Implementation of LetterRack class for Scrabble game
#include "scrabble.h" // Ensure all necessary declarations are included
#include <iostream>    // For input/output operations
#include <stdexcept>   // For standard exception handling

// Default Constructor
// Initializes an empty rack with placeholder tiles
LetterRack::LetterRack() {
    for (int i = 0; i < SIZE; i++) { // Fixed syntax error by adding the missing operand 'i'
        // Create empty tiles (space character with 0 points)
        rack[i] = LetterTile(' ', 0);
    }
    tile_count = 0;  // Initialize with no tiles
}

// Removes a specific letter from the rack
// Parameters:
//   letter - The character to remove from the rack
// Returns:
//   The LetterTile that was removed
// Throws:
//   std::domain_error if the letter isn't found in the rack
LetterTile LetterRack::remove_letter(char letter) {
    // Search through all rack positions
    for (int i = 0; i < SIZE; i++) {
        if (rack[i].get_letter() == letter) {
            // Save the found tile
            LetterTile tmp = rack[i];
            // Replace with placeholder (' ' tile with 0 points)
            rack[i] = LetterTile(' ', 0);
            tile_count--;  // Decrement tile count
            return tmp;    // Return the removed tile
        }
    }
    // Throw exception if letter not found
    throw std::domain_error("The rack does not contain that letter.");
}

// Fixed fill_rack function to match declaration
void LetterRack::fill_rack(LetterBag& bag) {
    for (int i = 0; i < SIZE; i++) {
        if (rack[i].get_letter() == ' ' && !bag.is_empty()) {
            LetterTile tile = bag.draw_tile();
            rack[i] = tile;
            tile_count++;  // Increment tile count
        } else if (bag.is_empty()) {
            throw std::runtime_error("Bag is empty. Cannot fill rack further.");
        }
    }
}

// Replaces a tile
void LetterRack::replace_tile(int index, LetterTile& newTile) {
    rack[index] = newTile;
}

// Exchange tile
void LetterRack::exchange_tile(const char letter, LetterBag& bag) {
    LetterTile removed_tile = remove_letter(letter);
    bag.addTiles(removed_tile.get_letter(), 1, removed_tile.get_point_value());
    fill_rack(bag);
}

// Displays the current letters in the rack
void LetterRack::print_rack() const {
    std::cout << "Your rack contains: ";
    // Print each tile's letter
    for (int i = 0; i < SIZE; i++) { // Fixed syntax error by adding the missing operand 'i'
        std::cout << rack[i].get_letter() << " ";
    }
    std::cout << std::endl;
}

// Returns the number of tiles currently in the rack
// Returns:
//   Integer count of non-empty tiles
int LetterRack::get_tile_count() const { 
    return tile_count; 
}

// Added operator[] to access tiles in the rack
const LetterTile& LetterRack::operator[](int index) const {
    if (index < 0 || index >= SIZE) {
        throw std::out_of_range("Index out of bounds");
    }
    return rack[index];
}

// Check if the rack contains a specific letter
// Parameters:
//   letter - The character to check for in the rack
// Returns:
//   True if the letter is found, false otherwise
bool LetterRack::has_letter(char letter) const {
    for (int i = 0; i < SIZE; ++i) {
        if (rack[i].get_letter() == letter) {
            return true;
        }
    }
    return false;
}
