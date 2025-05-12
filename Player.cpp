#include "scrabble.h"

// Default Constructor: Initializes player with zero points
Player::Player() : points(0) {}

// Constructor
Player(std::string the_name = "Player", int the_points = 0) : name(the_name), points(the_points) {}

// Get the order number
int Player::get_order_number() const { return order_number; }

// Get the points for the player
int Player::get_points() const { return points; }

// Places word on board and calculates score
void Player::play_word(ScrabbleBoard& board, const std::string& word, 
                       int row, int col, bool horizontal) {
    // Place the word on the board (checking validity via board's placeWord)
    if (board.placeWord(word, row, col, horizontal)) {  // Calls placeWord from GameBoard
        // Add word score to player's total
        points += calculate_score(word);
        
        // Check for bingo (using all tiles)
        if (word.length() == 7) {
            points += 50;
            std::cout << "Bingo! 50 bonus points added!" << std::endl;
        }
    } else {
        std::cout << "Invalid word placement!" << std::endl;
    }
}

// Calculates score for a given word
int Player::calculate_score(const std::string& word) {
    int score = 0;
    for (char c : word) {
        // Score based on standard Scrabble letter values
        switch (c) {
            case 'A': case 'E': case 'I': case 'L': case 'N': 
            case 'O': case 'R': case 'S': case 'T': case 'U':
                score += 1; break;
            case 'D': case 'G':
                score += 2; break;
            // ... (other cases for other letters)
            default:
                score += 0; break; // For blank tiles
        }
    }
    return score;
}

// Getter for the rack
LetterRack Player::get_rack() const { return rack; }

// Setter for player name
void Player::set_name(const std::string& name) {  // E3: Out-of-line definition of 'set_name' does not match any declaration in 'Player'
    this->name = name;
}

// Getter for player name
std::string Player::get_name() const {
    return name;
}

// Set order number
void Player::set_order_number(int order) { order_number = order; }
