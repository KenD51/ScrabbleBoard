Player.cpp
#include "Player.h"

// Constructor: Initializes player with zero points
Player::Player() : points(0) {}

// Places word on board and calculates score
void Player::play_word(ScrabbleBoard& board, const std::string& word, 
                       int row, int col, bool horizontal) {
    // Place each letter on the board
    for (size_t i = 0; i < word.length(); ++i) {
        int r = horizontal ? row : row + i;
        int c = horizontal ? col + i : col;
        board.board[r][c] = word[i];
    }
    
    // Add word score to player's total
    points += calculate_score(word);
    
    // Check for bingo (using all tiles)
    if (word.length() == 7) {
        points += 50;
        std::cout << "Bingo! 50 bonus points added!" << std::endl;
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
            // ... (other cases)
            default:
                score += 0; break; // For blank tiles
        }
    }
    return score;
}

// Setter for player name
void Player::set_name(const std::string& name) {
    this->name = name;
}

// Getter for player name
std::string Player::get_name() const {
    return name;
}

// Getter for player points
int Player::get_points() const {
    return points;
}

