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
            // Replace with placeholder ('?' tile with 0 points)
            rack[i] = LetterTile('?', 0);
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
            std::cout << "Added tile '" << tile.get_letter() << "' to rack at position " << i << "." << std::endl;
        } else if (rack[i].get_letter() != ' ') {
            std::cout << "Rack position " << i << " already filled with tile '" << rack[i].get_letter() << "'." << std::endl;
        } else {
            std::cout << "Bag is empty. Cannot fill rack further." << std::endl;
        }
    }
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
LetterTile& LetterRack::operator[](int index) {
    if (index < 0 || index >= SIZE) {
        throw std::out_of_range("Index out of bounds");
    }
    return rack[index];
}

const LetterTile& LetterRack::operator[](int index) const {
    if (index < 0 || index >= SIZE) {
        throw std::out_of_range("Index out of bounds");
    }
    return rack[index];
}
