// gameboard.cpp
#include "scrabble.h"
#include <iostream>
#include <iomanip>
#include <cctype> // For toupper
#include <string> // Make sure to include string here as well

// Constructor to initialize the board
ScrabbleBoard::ScrabbleBoard() : board(BOARD_SIZE, std::vector<Square>(BOARD_SIZE)) {}

// Function to print the Scrabble board
void ScrabbleBoard::printBoard() const {
    std::cout << "    ";
    for (int j = 0; j < BOARD_SIZE; ++j) {
        std::cout << std::setw(4) << j + 1 << " ";
    }
    std::cout << std::endl;
    std::cout << "    ";
    for (int j = 0; j < BOARD_SIZE; ++j) {
        std::cout << "______";
    }
    std::cout << std::endl;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::cout << std::setw(2) << i + 1 << " |";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (i == 6 && j == 6) { // Row 7, Column 7 (0-indexed)
                std::cout << std::setw(4) << "*" << "|";
            } else {
                std::cout << std::setw(4) << (board[i][j].letter == ' ' ? " " : std::string(1, toupper(board[i][j].letter))) << "|";
            }
        }
        std::cout << std::endl << "    ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << "_____";
        }
        std::cout << std::endl;
    }
}

// Function to check if the given word placement is valid
bool ScrabbleBoard::isValidPlacement(const std::string& word, int row, int col, char direction) const {
    int wordLength = word.length();

    row--; // Adjusting to 0-based indexing
    col--; // Adjusting to 0-based indexing
    direction = toupper(direction);

    //Case 1: Given coordinates are off the board
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        std::cout << "Starting position is off the board." << std::endl;
        return false;
    }

    //Case 2: Horizontal coordinates go off board
    if (direction == 'H') {
        if (col + wordLength > BOARD_SIZE) {
            std::cout << "Word goes off the board (horizontally)." << std::endl;
            return false;
        }
        return true;
    } else if (direction == 'V') {
        //Case 3: Vertical coordinates go off board
        if (row + wordLength > BOARD_SIZE) {
            std::cout << "Word goes off the board (vertically)." << std::endl;
            return false;
        }
        return true;
    } else {
        //Case 4: Invalid direction
        std::cout << "Invalid direction. Use 'H' for horizontal or 'V' for vertical." << std::endl;
        return false;
    }
}

// Function to place a word on the board (if placement is valid)
bool ScrabbleBoard::placeWord(const std::string& word, int row, int col, char direction) {
    if (isValidPlacement(word, row, col, direction)) {
        int wordLength = word.length();
        row--; // Adjusting to 0-based indexing
        col--; // Adjusting to 0-based indexing
        direction = toupper(direction);

        //Writes the word horizontally
        if (direction == 'H') {
            for (int i = 0; i < wordLength; ++i) {
                board[row][col + i].letter = toupper(word[i]);
            }
        //Writes the word verically
        } else if (direction == 'V') {
            for (int i = 0; i < wordLength; ++i) {
                board[row + i][col].letter = toupper(word[i]);
            }
        }
        return true;
    }
    return false;
}


