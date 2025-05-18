// LetterBag.cpp
// Implementation of the LetterBag class for the Scrabble game
// Handles tile distribution and random drawing mechanics

#include "scrabble.h" // Ensure all necessary declarations are included
#include <random>      // For random number generation
#include <stdexcept>   // For exception handling

// Constructor: Initializes the bag with standard Scrabble tile distribution
LetterBag::LetterBag() {
    // Initialize all tiles according to official Scrabble distribution:
    // Format: addTiles(letter, count, point_value)
    
    // Vowels
    addTiles('A', 9, 1);  // 9 'A' tiles worth 1 point each
    addTiles('E', 12, 1); // Most common letter
    addTiles('I', 9, 1);
    addTiles('O', 8, 1);
    addTiles('U', 4, 1);
    
    // Consonants
    addTiles('B', 2, 3);
    addTiles('C', 2, 3);
    addTiles('D', 4, 2);
    addTiles('F', 2, 4);
    addTiles('G', 3, 2);
    addTiles('H', 2, 4);
    addTiles('J', 1, 8);  // Rare high-value
    addTiles('K', 1, 5);
    addTiles('L', 4, 1);
    addTiles('M', 2, 3);
    addTiles('N', 6, 1);
    addTiles('P', 2, 3);
    addTiles('Q', 1, 10); // Highest value letter
    addTiles('R', 6, 1);
    addTiles('S', 4, 1);
    addTiles('T', 6, 1);
    addTiles('V', 2, 4);
    addTiles('W', 2, 4);
    addTiles('X', 1, 8);
    addTiles('Y', 2, 4);
    addTiles('Z', 1, 10);
    
    // Special tiles
    addTiles('*', 2, 0);  // Blank/wildcard tiles (0 points)
}

// Adds specified number of tiles to the bag
// Parameters:
//   letter - The character to add (A-Z or * for blank)
//   count - How many of this tile to add
//   value - Point value for this tile
void LetterBag::addTiles(char letter, int count, int value) {
    // Create and add the specified number of tiles
    for (int i = 0; i < count; ++i) {
        Bag.emplace_back(letter, value);  // Constructs tile in-place
    }
}

// Checks if the bag is empty
// Returns:
//   true if no tiles remain, false otherwise
bool LetterBag::is_empty() const {
    return Bag.empty();  // Vector's empty() method
}

// Draws a random tile from the bag
// Returns:
//   A LetterTile object
// Throws:
//   std::runtime_error if bag is empty
LetterTile LetterBag::draw_tile() {
    // Check for empty bag first
    if (Bag.empty()) {
        throw std::runtime_error("Bag is empty");
    }
    
    // Set up random number generation:
    // random_device for seeding
    std::random_device rd;  
    // Mersenne Twister engine for good distribution
    std::mt19937 gen(rd());  
    // Uniform distribution across possible indices
    std::uniform_int_distribution<> dist(0, Bag.size() - 1);  
    
    // Select random tile
    int index = dist(gen);  // Generate random index
    LetterTile tile = Bag[index];  // Copy the tile
    
    // Remove tile from bag
    Bag.erase(Bag.begin() + index);
    
    return tile;  // Return the drawn tile
}