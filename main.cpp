
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cctype> // For toupper

using namespace std;

// Structure to represent a square on the board
struct Square {
    char letter = ' ';
};

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
// Function to check if the given word is valid. Checks if the word placed goes off the board or if is not fiven a valid direction.
bool isValidPlacement(const vector<vector<Square>>& board, const string& word, int row, int col, char direction) {
    int wordLength = word.length();
    int boardSize = 15;

    row--; // Adjusting to 0-based indexing
    col--; // Adjusting to 0-based indexing
    direction = toupper(direction);

    //Case 1: Given coordinates are off the board
    if (row < 0 || row >= boardSize || col < 0 || col >= boardSize) {
        cout << "Starting position is off the board." << endl;
        return false;
    }

    //Case 2: Horizontal coordinates go off board
    if (direction == 'H') {
        if (col + wordLength > boardSize) {
            cout << "Word goes off the board (horizontally)." << endl;
            return false;
        }
	  //Case passes
        return true;
    //Case 3: Vertical coordinates go off board
    } else if (direction == 'V') {
        if (row + wordLength > boardSize) {
            cout << "Word goes off the board (vertically)." << endl;
            return false;
        }
        //Case passes
        return true;

    } 
	//Case 3: Wrong letter
else {
        cout << "Invalid direction. Use 'H' for horizontal or 'V' for vertical." << endl;
        return false;
    }
}







// Function to place a word on the board (if placement is valid)
bool placeWord(vector<vector<Square>>& board, const string& word, int row, int col, char direction) {
    if (isValidPlacement(board, word, row, col, direction)) {
        int wordLength = word.length();
        row--; // Adjusting to 0-based indexing
        col--; // Adjusting to 0-based indexing
        direction = toupper(direction);

	  //Writes the word horizontally, left to right.
        if (direction == 'H') {
            for (int i = 0; i < wordLength; ++i) {
                board[row][col + i].letter = toupper(word[i]);
            }
	//Writes the word horizontally, up to down.
        } else if (direction == 'V') {
            for (int i = 0; i < wordLength; ++i) {
                board[row + i][col].letter = toupper(word[i]);
            }
        }
        return true;
    }
    return false;
}

int main() {
    //Create board
    vector<vector<Square>> scrabbleBoard = initializeBoard();
    printBoard(scrabbleBoard);

    //Word and its coordinates
    string wordToPlay;
    int startRow, startCol;
    char direction;


    //Asks the player to place a word down
    //To place a word down, you must provide the word, the row number, the column number, and whether if it is horizontal or vertical.
    cout << "\nPlace a word (word row column direction - e.g., hello 8 4 H): ";
    cin >> wordToPlay >> startRow >> startCol >> direction;

	

	//IsValidPlacement will check to see if it works.
    if (isValidPlacement(scrabbleBoard, wordToPlay, startRow, startCol, direction)) {
        cout << "Placement is valid (basic check)." << endl;
        if (placeWord(scrabbleBoard, wordToPlay, startRow, startCol, direction)) {
            cout << "\nBoard after placement:" << endl;
            printBoard(scrabbleBoard);
        }
    } else {
        cout << "Placement is invalid." << endl;
    }

    return 0;
}

