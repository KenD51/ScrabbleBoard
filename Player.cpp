#include "scrabble.h" // Ensure LetterBag is included
#include <iostream>
#include <string>

// Returns the order number of the player (e.g., 1st, 2nd player)
int Player::get_order_number() const {
    return order_number;
}

// Returns the current score (total points) of the player
int Player::get_points() const {
    return points;
}

// Adds points to the player's score
void Player::add_points(int additional_points) {
    points += additional_points;
}

// Implemented missing Player::get_rack function
LetterRack Player::get_rack() const {
    return rack;
}

// Implemented missing Player::set_name function
void Player::set_name(const std::string& name) {
    this->name = name;
}

// Implemented missing Player::get_name function
std::string Player::get_name() const {
    return name;
}

// Main function to allow a player to play a word on the board
bool Player::play_word(GameBoard& board, const std::string& word, int row, int col, bool horizontal) {
    if (board.placeWord(word, row, col, horizontal ? 'H' : 'V')) {
        points += calculate_score(word);

        // Check for bingo (using all tiles - assuming rack size is 7)
        if (word.length() == rack.get_tile_count()) {
            points += 50;
            std::cout << "Bingo! 50 bonus points added!" << std::endl;
        }
        return true; // Word successfully placed
    } else {
        std::cout << "Invalid word placement." << std::endl;
        return false; // Word placement failed
    }
}

// Helper function to calculate Scrabble score of a word based on individual letters
int Player::calculate_score(const std::string& word) {
    int score = 0;
    // Loop through each character in the word
    for (char c : word) {
        // Convert to uppercase to handle lowercase input
        char uc = std::toupper(static_cast<unsigned char>(c));
        // Add points based on standard Scrabble letter values
        switch (uc) {
            case 'A': case 'E': case 'I': case 'L': case 'N': 
            case 'O': case 'R': case 'S': case 'T': case 'U':
                score += 1; // Common letters worth 1 point
                break;
            case 'D': case 'G':
                score += 2; // Slightly less common letters worth 2 points
                break;
            case 'B': case 'C': case 'M': case 'P':
                score += 3;
                break;
            case 'F': case 'H': case 'V': case 'W': case 'Y':
                score += 4;
                break;
            case 'K':
                score += 5;
                break;
            case 'J': case 'X':
                score += 8;
                break;
            case 'Q': case 'Z':
                score += 10;
                break;
            default:
                break; // Ignore invalid characters
        }
    }
    return score;
}
