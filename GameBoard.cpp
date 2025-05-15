// GameBoard.cpp
// This cpp file contains the implementations of the Scrabble board class. It prints the board and allows words to be placed on the board, while also validating them.

#include "scrabble.h" // Ensure LetterBag is included
#include <iostream>
#include <iomanip>
#include <cctype> // For toupper
#include <string>

using namespace std;

// Add a flag to track if the first word has been placed
bool firstWordPlaced = false;

// Modify the GameBoard constructor to initialize the board with empty squares
GameBoard::GameBoard() : board(initializeBoard()) {}

//initializeBoard function. Returns a 2D vector of Square objects
// This function initializes the board with empty squares
std::vector<std::vector<Square>> GameBoard::initializeBoard() {
    std::vector<std::vector<Square>> newBoard(BOARD_SIZE, std::vector<Square>(BOARD_SIZE));
    // Place the center star at (6,6) for 1-based row/col 7,7
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
            // Print the center star only at (6,6) for 1-based (7,7)
            if (i == 6 && j == 6 && board[i][j].letter == '*') {
                cout << setw(3) << '*' << "|";
            } else {
                cout << setw(3) << board[i][j].letter << "|";
            }
        }
        cout << endl;
        cout << "   " << string(4 * BOARD_SIZE + 1, '_') << endl;
    }
}

//IsvalidPlacement function checks if a word can be placed at the specified position on the board.
// It checks if the word fits within the board boundaries and if the placement is valid.
//It has yet to check if the word overlaps with existing letters on the board.
bool GameBoard::isValidPlacement(const std::string& word, int row, int col, char direction) const {
    int wordLength = word.length();
    row--; // Adjusting to 0-based indexing
    col--; // Adjusting to 0-based indexing
    direction = toupper(direction);

    cout << "Debug: Checking placement for word '" << word << "' at row " << row + 1 << ", column " << col + 1 << " in direction '" << direction << "'." << endl;
    cout << "Debug: Word length: " << wordLength << endl;
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        cout << "Debug: Placement out of board boundaries." << endl;
        return false;
    }

    if (direction == 'H' && col + wordLength > BOARD_SIZE) {
        cout << "Debug: Horizontal placement exceeds board boundaries." << endl;
        return false;
    }

    if (direction == 'V' && row + wordLength > BOARD_SIZE) {
        cout << "Debug: Vertical placement exceeds board boundaries." << endl;
        return false;
    }

    if (!firstWordPlaced) {
        cout << "Debug: Validating first word placement." << endl;
        bool coversCenter = false;
        for (int i = 0; i < wordLength; ++i) {
            int r = row + (direction == 'V' ? i : 0);
            int c = col + (direction == 'H' ? i : 0);
            if (r == BOARD_SIZE / 2 && c == BOARD_SIZE / 2) {
                coversCenter = true;
                break;
            }
        }
        if (!coversCenter) {
            cout << "Debug: First word does not cover the center star." << endl;
            return false;
        }
    }

    // Check for overlapping letters (only relevant after the first word)
    if (firstWordPlaced) {
        for (int i = 0; i < wordLength; ++i) {
            char boardLetter;
            if (direction == 'H') {
                boardLetter = board[row][col + i].letter;
            } else { // direction == 'V'
                boardLetter = board[row + i][col].letter;
            }

            if (boardLetter != ' ' && boardLetter != '*' && boardLetter != toupper(word[i])) {
                cout << "Debug: Overlap with a different letter at position (" << row + 1 << ", " << col + 1 << ")." << endl;
                return false; // Overlap with a different letter
            }
        }
    }

    cout << "Debug: Placement is valid." << endl;
    return true;
}

// Update the placeWord function to ensure proper validation for vertical placements
bool GameBoard::placeWord(const std::string& word, int row, int col, char direction) {
    int center = BOARD_SIZE / 2; // Corrected center index

    row--; // Adjust to 0-based indexing
    col--; // Adjust to 0-based indexing
    direction = toupper(direction);

    if (!firstWordPlaced) {
        bool coversCenter = false;
        for (int i = 0; i < word.length(); ++i) {
            int r = row + (direction == 'V' ? i : 0);
            int c = col + (direction == 'H' ? i : 0);
            if (r == center && c == center) {
                coversCenter = true;
                break;
            }
        }
        if (!coversCenter) {
            cout << "The first word must cover the center square (" << center + 1 << "," << center + 1 << ")." << endl;
            return false;
        }
    } else {
        // For subsequent words, need to check if they connect to existing letters.
        bool connects = false;
        for (int i = 0; i < word.length(); ++i) {
            int r = row + (direction == 'V' ? i : 0);
            int c = col + (direction == 'H' ? i : 0);
            if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c].letter != ' ') {
                connects = true;
                break;
            }
            // Also check adjacent empty squares for existing letters
            int dr[] = {-1, 1, 0, 0};
            int dc[] = {0, 0, -1, 1};
            for (int j = 0; j < 4; ++j) {
                int nr = r + dr[j];
                int nc = c + dc[j];
                if (nr >= 0 && nr < BOARD_SIZE && nc >= 0 && nc < BOARD_SIZE && board[nr][nc].letter != ' ') {
                    connects = true;
                    break;
                }
            }
            if (connects) break;
        }
        if (!connects) {
            cout << "Subsequent words must connect to an existing letter on the board." << endl;
            return false;
        }
    }

    if (isValidPlacement(word, row + 1, col + 1, direction)) {
        int wordLength = word.length();

        if (direction == 'H') { // Horizontal placement
            for (int i = 0; i < wordLength; ++i) {
                board[row][col + i].letter = toupper(word[i]);
            }
        } else if (direction == 'V') { // Vertical placement
            for (int i = 0; i < wordLength; ++i) {
                board[row + i][col].letter = toupper(word[i]);
            }
        }

        firstWordPlaced = true; // Mark the first word as placed
        return true;
    } else {
        cout << "Invalid placement. Please try again." << endl;
        return false; // Do not switch turns
    }
}
