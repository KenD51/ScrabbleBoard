#include "scrabble.h" // Includes the header file where class declarations and dependencies are defined

// Default Constructor: Initializes a Player object with 0 points
Player::Player() : points(0) {}

// Parameterized Constructor: Initializes a Player with a given name and points
// NOTE: This should be defined in the header file and implemented here, not declared inline.
Player::Player(std::string the_name, int the_points) : name(the_name), points(the_points) {}

// Returns the order number of the player (e.g., 1st, 2nd player)
int Player::get_order_number() const {
    return order_number;
}

// Returns the player's rack
LetterRack Player::get_rack() const {
    return rack;
}

// Returns the current score (total points) of the player
int Player::get_points() const {
    return points;
}

// Main function to allow a player to play a word on the board
void Player::play_word(GameBoard& board, const std::string& word, 
                       int row, int col, bool horizontal) {
    // Attempt to place the word on the board
    // placeWord returns true if the word placement is valid and successful
    if (board.placeWord(word, row, col, horizontal)) {
        // If placement is valid, calculate the word's score and add it to player's points
        points += calculate_score(word);
        // If placement is valid, remove the letters from the rack and replace them
        for (int i = 0; i < word.length(); i++) {
            char letter = word[i];
            rack.remove_letter(letter);
        }
        
        // Check if player used all 7 letters in the word (a "Bingo" in Scrabble)
        if (word.length() == 7) {
            points += 50; // Bonus points for bingo
            std::cout << "Bingo! 50 bonus points added!" << std::endl;
        }
    } else {
        // If the word could not be placed on the board (invalid position or overlap)
        std::cout << "Invalid word placement!" << std::endl;
    }
}

// Helper function to calculate Scrabble score of a word based on individual letters
int Player::calculate_score(const std::string& word) {
    int score = 0;
    // Loop through each character in the word
    for (char c : word) {
        // Add points based on standard Scrabble letter values
        switch (c) {
            case 'A': case 'E': case 'I': case 'L': case 'N': 
            case 'O': case 'R': case 'S': case 'T': case 'U':
                score += 1; // Common letters worth 1 point
                break;
            case 'D': case 'G':
                score += 2; // Slightly
        }
    }
}
