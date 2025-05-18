// GameBoard.cpp
// This cpp file contains the implementations of the Scrabble board class.
// It prints the board and allows words to be placed on the board, while also validating them.

#include "scrabble.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>

using namespace std;

const int BOARD_SIZE = 15; // Make sure this matches your board size everywhere

// Add a flag to track if the first word has been placed
bool firstWordPlaced = false;

// GameBoard constructor: initializes the board with empty squares and the center marker
GameBoard::GameBoard() : board(initializeBoard()) {}

// initializeBoard function. Returns a 2D vector of Square objects
// This function initializes the board with empty squares and places the center marker.
std::vector<std::vector<Square>> GameBoard::initializeBoard() {
    // Create a 15x15 board of empty squares
    std::vector<std::vector<Square>> newBoard(BOARD_SIZE, std::vector<Square>(BOARD_SIZE));
    // Place the center star at (7,7) for 0-based row/col 7,7
    int center = (BOARD_SIZE - 1) / 2; // 0-based index for row 7, col 7
    newBoard[center][center].letter = '*'; // Set the center square to a star
    return newBoard; // Board is initialized with empty squares
}

// This function prints the Scrabble board to the console in a formatted way.
// It includes row and column numbers for reference and displays the letters on the board.
void GameBoard::printBoard() const {
    // Print column headers (1 to BOARD_SIZE)
    cout << "    ";
    for (int j = 0; j < BOARD_SIZE; ++j) {
        cout << setw(3) << j + 1 << " "; // Print column numbers with spacing
    }
    cout << endl;
    cout << "   " << string(4 * BOARD_SIZE + 1, '_') << endl;

    // Print each row of the board
    for (int i = 0; i < BOARD_SIZE; ++i) {
        cout << setw(2) << i + 1 << " |"; // Print row number with a vertical separator
        for (int j = 0; j < BOARD_SIZE; ++j) {
            // Print the letter on each square
            cout << setw(3) << board[i][j].letter << "|";
        }
        cout << endl;
        cout << "   " << string(4 * BOARD_SIZE + 1, '_') << endl;
    }
}

// isValidPlacement function checks if a word can be placed at the specified position on the board.
// It checks if the word fits within the board boundaries and if the placement is valid
// according to the rules (first word covers center, subsequent words connect).
bool GameBoard::isValidPlacement(const std::string& word, int row, int col, char direction) const {
    // Convert to 0-based indexing
    int wordLength = word.length();
    row--;
    col--;
    direction = toupper(direction);

    // Debug output for placement
    cout << "Debug (isValidPlacement): Checking placement for word '" << word << "' at row " << row + 1 << ", column " << col + 1 << " in direction '" << direction << "'." << endl;
    cout << "Debug (isValidPlacement): Word length: " << wordLength << endl;

    // Check board boundaries
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        cout << "Debug (isValidPlacement): Placement out of board boundaries." << endl;
        return false;
    }

    // Check if the word fits horizontally or vertically
    if ((direction == 'H' && col + wordLength > BOARD_SIZE) ||
        (direction == 'V' && row + wordLength > BOARD_SIZE)) {
        cout << "Debug (isValidPlacement): Placement exceeds board boundaries." << endl;
        return false;
    }

    // First word must cover the center square
    if (!firstWordPlaced) {
        cout << "Debug (isValidPlacement): Validating first word placement." << endl;
        int center = BOARD_SIZE / 2; // Center is at index 7 (0-based)
        bool coversCenter = false;
        // Check if any letter of the word covers the center square
        for (int i = 0; i < wordLength; ++i) {
            int r = row + (direction == 'V' ? i : 0);
            int c = col + (direction == 'H' ? i : 0);
            if (r == center && c == center) {
                coversCenter = true;
                break;
            }
        }
        if (!coversCenter) {
            cout << "Debug (isValidPlacement): First word does not cover the center." << endl;
            return false;
        }
        cout << "Debug (isValidPlacement): First word covers the center." << endl;
        return true;
    } else {
        // For subsequent words, must connect to existing words
        bool connects = false;
        for (int i = 0; i < wordLength; ++i) {
            int r = row + (direction == 'V' ? i : 0);
            int c = col + (direction == 'H' ? i : 0);
            char boardLetter = board[r][c].letter;
            // If overlapping a letter, it must match
            if (boardLetter != ' ' && boardLetter != '*') {
                if (boardLetter == std::toupper(word[i])) {
                    // Overlap is valid
                } else {
                    std::cout << "Debug: Overlapping, different letter at position (" << r + 1 << ", " << c + 1 << ")." << std::endl;
                    return false;
                }
            }
            // Check if the current letter's position has an adjacent existing letter
            int dr[] = {-1, 1, 0, 0}; // Row offsets: up, down, same row
            int dc[] = {0, 0, -1, 1}; // Column offsets: same column, left, right
            for (int j = 0; j < 4; ++j) {
                int nr = r + dr[j];
                int nc = c + dc[j];
                // If adjacent square is within bounds and not empty, the word connects
                if (nr >= 0 && nr < BOARD_SIZE && nc >= 0 && nc < BOARD_SIZE && board[nr][nc].letter != ' ') {
                    connects = true;
                    break;
                }
            }
            if (connects) break;
        }
        if (!connects) {
            cout << "Debug (isValidPlacement): Subsequent word does not connect to existing letters." << endl;
            return false;
        }
        cout << "Debug (isValidPlacement): Placement is valid." << endl;
        return true;
    }
}

// placeWord function updates the board with the placed word if the placement is valid.
// It calls isValidPlacement to check validity, then places the word horizontally or vertically.
bool GameBoard::placeWord(const std::string& word, int row, int col, char direction) {
    // Convert to 0-based indexing
    row--;
    col--;
    direction = toupper(direction);

    cout << "Debug (placeWord): Attempting to place '" << word << "' at row " << row + 1 << ", column " << col + 1 << " in direction '" << direction << "'." << endl;

    // Validate placement
    if (isValidPlacement(word, row + 1, col + 1, direction)) {
        int wordLength = word.length();

        // Place the word on the board horizontally
        if (direction == 'H') {
            cout << "Debug (placeWord): Placing horizontally." << endl;
            for (int i = 0; i < wordLength; ++i) {
                board[row][col + i].letter = toupper(word[i]);
            }
        }
        // Place the word on the board vertically
        else if (direction == 'V') {
            cout << "Debug (placeWord): Placing vertically." << endl;
            for (int i = 0; i < wordLength; ++i) {
                board[row + i][col].letter = toupper(word[i]);
            }
        }

        // Mark that the first word has been placed
        firstWordPlaced = true;
        return true;
    } else {
        cout << "Invalid placement as determined by isValidPlacement." << endl;
        return false;
    }
}

// Returns the letter at the specified board position (row, col).
// Returns ' ' if out of bounds.
char GameBoard::getTile(int row, int col) const {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) return ' ';
    return board[row][col].letter;
}

// Helper: Collect all words formed by a placement (main and perpendicular)
// Returns a vector of all words formed by placing 'word' at (row, col) in the given direction.
std::vector<std::string> GameBoard::getAllWordsFormed(const std::string& word, int row, int col, bool horizontal) const {
    std::vector<std::string> words;
    int wordLength = word.length();
    row--; col--; // Convert to 0-based indexing

    // Main word: find the full word in the main direction (including existing letters)
    std::string mainWord;
    int r = row, c = col;
    // Find start of main word by moving backwards until empty or star
    while (r > 0 && !horizontal && board[r-1][c].letter != ' ' && board[r-1][c].letter != '*') r--;
    while (c > 0 && horizontal && board[r][c-1].letter != ' ' && board[r][c-1].letter != '*') c--;
    mainWord.clear();
    for (int i = 0; i < (horizontal ? BOARD_SIZE-c : BOARD_SIZE-r); ++i) {
        char ch = board[r + (horizontal ? 0 : i)][c + (horizontal ? i : 0)].letter;
        if (ch == ' ' || ch == '*') break;
        mainWord += ch;
    }
    // If mainWord is empty, use the placed word
    if (mainWord.empty()) mainWord = word;
    words.push_back(mainWord);

    // For each letter placed, check for perpendicular words formed
    for (int i = 0; i < wordLength; ++i) {
        int pr = row + (horizontal ? 0 : i);
        int pc = col + (horizontal ? i : 0);
        // Only check if this square is empty or being replaced (i.e., a new tile is placed)
        if (board[pr][pc].letter == ' ' || board[pr][pc].letter == '*') {
            std::string perpWord;
            int start = (horizontal ? pr : pc);
            int fixed = (horizontal ? pc : pr);
            // Find start of perpendicular word
            while (start > 0 && board[horizontal ? start-1 : pr][horizontal ? pc : start-1].letter != ' ' && board[horizontal ? start-1 : pr][horizontal ? pc : start-1].letter != '*')
                start--;
            // Build perpendicular word
            for (int j = 0; j < BOARD_SIZE; ++j) {
                int rr = horizontal ? start+j : pr;
                int cc = horizontal ? pc : start+j;
                if (rr < 0 || rr >= BOARD_SIZE || cc < 0 || cc >= BOARD_SIZE) break;
                char ch = board[rr][cc].letter;
                // If this is the placed letter, use the new letter
                if (rr == pr && cc == pc) ch = toupper(word[i]);
                if (ch == ' ' || ch == '*') break;
                perpWord += ch;
            }
            // Only add if the perpendicular word is longer than 1 letter
            if (perpWord.length() > 1) words.push_back(perpWord);
        }
    }
    return words;
}

// Checks if all words formed by a placement are valid using Game::dictionaryCheck
// Returns true if all words are valid, false otherwise.
bool GameBoard::allAdjacentWordsValid(const std::string& word, int row, int col, bool horizontal, Game& game) const {
    auto words = getAllWordsFormed(word, row, col, horizontal);
    for (const auto& w : words) {
        if (!game.dictionaryCheck(w)) {
            std::cout << "Invalid adjacent word: " << w << std::endl;
            return false;
        }
    }
    return true;
}
