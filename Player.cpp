#include "scrabble.h" // Includes the header file where class declarations and dependencies are defined
#include <iostream>

// Default Constructor: Initializes a Player object with 0 points
Player::Player() : points(0) {}

// Parameterized Constructor: Initializes a Player with a given name and points
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

// Returns the name of the player
std::string Player::get_name() const {
    return name;
}

// Main function to allow a player to play a word on the board
void Player::play_word(GameBoard& board, const std::string& word, int row, int col, char direction) {
    // Attempt to place the word and get all formed words and used letters
    WordPlacementResult result = board.placeWord(word, row, col, direction);

    if (result.valid && !result.words_formed.empty()) {
        int total_score = 0;

        std::cout << "Words formed: ";
        for (const std::string& w : result.words_formed) {
            std::cout << w << " ";
            total_score += calculate_score(w);
        }
        std::cout << std::endl;

        points += total_score;
        std::cout << "Score gained: " << total_score << std::endl;

        // Remove letters used from the rack
        for (char letter : result.letters_used_from_rack) {
            rack.remove_letter(letter);
        }

        // Check for Bingo (using all 7 letters from the rack)
        if (result.letters_used_from_rack.size() == 7) {
            points += 50;
            std::cout << "Bingo! 50 bonus points added!" << std::endl;
        }

    } else {
        std::cout << "Invalid word placement!" << std::endl;
    }
}

// Helper function to calculate Scrabble score of a word based on individual letters
int Player::calculate_score(const std::string& word) {
    int score = 0;
    for (char c : word) {
        switch (c) {
            case 'A': case 'E': case 'I': case 'L': case 'N': 
            case 'O': case 'R': case 'S': case 'T': case 'U':
                score += 1; break;
            case 'D': case 'G':
                score += 2; break;
            case 'B': case 'C': case 'M': case 'P':
                score += 3; break;
            case 'F': case 'H': case 'V': case 'W': case 'Y':
                score += 4; break;
            case 'K':
                score += 5; break;
            case 'J': case 'X':
                score += 8; break;
            case 'Q': case 'Z':
                score += 10; break;
            default:
                score += 0; break; // Blank tile or invalid
        }
    }
    return score;
}
