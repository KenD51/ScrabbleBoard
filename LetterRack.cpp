// LetterRack.cpp
// Implementation of LetterRack class for Scrabble game
#include "scrabble.h"  // Include the header file with class declarations
#include <iostream>    // For input/output operations
#include <stdexcept>   // For standard exception handling

// Default Constructor
// Initializes an empty rack with placeholder tiles
LetterRack::LetterRack() {
    for (int i = 0; i < SIZE; ++i) {
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

// Fills empty slots in the rack with tiles from the bag
// Parameters:
//   bag - Reference to the LetterBag to draw tiles from
void LetterRack::fill_rack(LetterBag& bag) {
    for (int i = 0; i < SIZE; i++) {
        // Check for placeholder tiles (empty slots)
        if (rack[i].get_letter() == '?' && !bag.is_empty()) {
            // Draw new tile from bag and place in rack
            rack[i] = bag.draw_tile();
            tile_count++;  // Increment tile count
        }
    }
}

// Displays the current letters in the rack
void LetterRack::print_rack() const {
    std::cout << "Your rack contains: ";
    // Print each tile's letter
    for (int i = 0; i < SIZE; i++) {
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
