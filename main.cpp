
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

