
#include "Player.h"
  //E --> error: 3

// Constructor: Initializes player with zero points
Player::Player() : points(0) {}

// Places word on board and calculates score
void Player::play_word(ScrabbleBoard& board, const std::string& word, 
                       int row, int col, bool horizontal) {
    // Place each letter on the board
    for (size_t i = 0; i < word.length(); ++i) { //error1: Implicit conversion loses integer precision: 'size_t' (aka 'unsigned long') to 'int'
        int r = horizontal ? row : row + i;
        int c = horizontal ? col + i : col;
        board.board[r][c] = word[i];// E2: 'board' is a private member of 'ScrabbleBoard' + no viable overloaded '='
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
void Player::set_name(const std::string& name) {// E3: Out-of-line definition of 'set_name' does not match any declaration in 'Player'
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

