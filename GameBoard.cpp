// gameboard.cpp
// This cpp file contains the implementations of the Scrabble board class. It prints the board and allows words to be placed on the board, while also validating them.

#include "scrabble.h"
#include <iostream>
#include <iomanip>
#include <cctype> // For toupper
#include <string>

using namespace std;

// this is a 2D vector that creates the scrabble board that is 15 x 15
vector<vector<Square>> initializeBoard() {
    return vector<vector<Square>>(15, vector<Square>(15));
}

// Function to print the Scrabble board
void printBoard(const vector<vector<Square>>& board) {
    //Creates the header and the column numbers
    cout << "   ";
    for (int j = 0; j < 15; ++j) {
        cout << setw(4) << j + 1 << " ";
    }
    //Creates the ___ line for the column
    cout << endl;
    cout << "   ";
    for (int j = 0; j < 15; ++j) {
        cout << "______";
    }
    cout << endl;

    //Creates the rows.
    for (int i = 0; i < 15; ++i) {
        cout << setw(2) << i + 1 << " |";
        for (int j = 0; j < 15; ++j) {
            if (i == 6 && j == 6) { //Places a star in the middle
                cout << setw(4) << "*" << "|";
            } else {
                //When printing the board again, the entire word is capitalized
                cout << setw(4) << (board[i][j].letter == ' ' ? " " : string(1, toupper(board[i][j].letter))) << "|";
            }
        }
        //Formatting lines for the rows
        cout << endl << "   ";
        for (int j = 0; j < 15; ++j) {
            cout << "_____";
        }
        cout << endl;
    }
}

// Function to check if the given word is valid. Checks if the word placed goes off the board or if is not given a valid direction.
bool isValidPlacement(const vector<vector<Square>>& board, const string& word, int row, int col, char direction) {
    int wordLength = word.length();
    int boardSize = 15;

    row--; // Adjusting to 0-based indexing
    col--; // Adjusting to 0-based indexing
    direction = toupper(direction);

    // Case 1: Given coordinates are off the board
    if (row < 0 || row >= boardSize || col < 0 || col >= boardSize) {
        cout << "Starting position is off the board." << endl;
        return false;
    }

    // Case 2: Horizontal coordinates go off board
    if (direction == 'H') {
        if (col + wordLength > boardSize) {
            cout << "Word goes off the board (horizontally)." << endl;
            return false;
        }

        // Check if the horizontal placement overlaps with existing letters
        for (int i = 0; i < wordLength; ++i) {
            if (board[row][col + i].letter != ' ' && board[row][col + i].letter != toupper(word[i])) {
                cout << "There is already a letter in the way (horizontal)." << endl;
                return false;
            }
        }
    } else if (direction == 'V') {
        if (row + wordLength > boardSize) {
            cout << "Word goes off the board (vertically)." << endl;
            return false;
        }

        // Check if the vertical placement overlaps with existing letters
        for (int i = 0; i < wordLength; ++i) {
            if (board[row + i][col].letter != ' ' && board[row + i][col].letter != toupper(word[i])) {
                cout << "There is already a letter in the way (vertical)." << endl;
                return false;
            }
        }
    } else {
        cout << "Invalid direction. Use 'H' for horizontal or 'V' for vertical." << endl;
        return false;
    }

    return true;
}

// Function to place a word on the board (if placement is valid)
bool placeWord(vector<vector<Square>>& board, const string& word, int row, int col, char direction) {
    if (isValidPlacement(board, word, row, col, direction)) {
        int wordLength = word.length();
        row--; // Adjusting to 0-based indexing
        col--; // Adjusting to 0-based indexing
        direction = toupper(direction);

        // Writes the word horizontally, left to right
        if (direction == 'H') {
            for (int i = 0; i < wordLength; ++i) {
                board[row][col + i].letter = toupper(word[i]);
            }
        } else if (direction == 'V') {
            for (int i = 0; i < wordLength; ++i) {
                board[row + i][col].letter = toupper(word[i]);
            }
        }
        return true;
    }
    return false;
}
