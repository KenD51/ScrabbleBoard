//I changed The get_letter() method to correctly return char instead of int, as the letter itself is a char.
//I fixed constructor for Player to accept a std::string for the player's name and an int for their points.
//Compilors think letter rack is missing: remove_letter, fill_rack, print_rack, and is_empty, so i added them
//Removed duplicate #include <string> to avoid redundancy.



#ifndef SCRABBLE_H
#define SCRABBLE_H

#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>
#include <string>
#include <cstdlib>

class LetterTile {
private:
    char letter;
    int point_value;
public:
    LetterTile(char the_letter, int the_value) : letter(the_letter), point_value(the_value) {}
    char get_letter() const { return letter; }
    int get_point_value() const { return point_value; }
};

class LetterBag {
public:
    std::vector<LetterTile> Bag;

    LetterBag() {
        // Initialize the letter bag with the standard Scrabble distribution
        addTiles('A', 9, 1);
        addTiles('B', 2, 3);
        addTiles('C', 2, 3);
        addTiles('D', 4, 2);
        addTiles('E', 12, 1);
        addTiles('F', 2, 4);
        addTiles('G', 3, 2);
        addTiles('H', 2, 4);
        addTiles('I', 9, 1);
        addTiles('J', 1, 8);
        addTiles('K', 1, 5);
        addTiles('L', 4, 1);
        addTiles('M', 2, 3);
        addTiles('N', 6, 1);
        addTiles('O', 8, 1);
        addTiles('P', 2, 3);
        addTiles('Q', 1, 10);
        addTiles('R', 6, 1);
        addTiles('S', 4, 1);
        addTiles('T', 6, 1);
        addTiles('U', 4, 1);
        addTiles('V', 2, 4);
        addTiles('W', 2, 4);
        addTiles('X', 1, 8);
        addTiles('Y', 2, 4);
        addTiles('Z', 1, 10);
        addTiles('*', 2, 0); // Blank tiles
    }

    void addTiles(char letter, int count, int value);
    bool is_empty() const;
    LetterTile draw_tile();
};

class LetterRack {
private:
    static const int SIZE = 7;
    LetterTile rack[SIZE];
public:
    LetterTile remove_letter(const char letter);
    void fill_rack();
    void print_rack() const;
    bool is_empty();
};

// This is a tile structure that will be used in the Scrabble board.
struct Square {
    char letter = ' ';
};

class ScrabbleBoard {
private:
    std::vector<std::vector<Square>> board; // 2D Vector for board representation
    static const int BOARD_SIZE = 15; // Scrabble board size (15x15)
public:
    ScrabbleBoard() : board(BOARD_SIZE, std::vector<Square>(BOARD_SIZE)) {}

    // Function to check if the given word placement is valid
    bool isValidPlacement(const std::string& word, int row, int col, char direction) const;

    // Function to print the board
    void printBoard() const;

    // Function to place a word on the board (if placement is valid)
    bool placeWord(const std::string& word, int row, int col, char direction);
};

class Player {
private:
    std::string name;
    LetterRack rack;
    int order_number;
public:
    int points = 0;
    
    // Constructor: Initializes player with a name and points
    Player(const std::string& the_name, int the_points) : name(the_name), points(the_points) {}

    int get_order_number() { return order_number; }

    // Places word on board and calculates score
    void play_word(ScrabbleBoard& board, const std::string& word, int row, int col, bool horizontal);

    // Calculates score for a given word
    int calculate_score(const std::string& word);

    // Getter for the player's rack
    LetterRack get_rack();
};

class EndGame : public Player {
private:
    std::vector<std::string> winner;
public:
    // Computes final score considering the player's rack
    void compute_final_score(LetterRack& rack);

    // Determines the winner of the game
    void determine_winner(Game& scrabble);
};

class Game {
private:
    int pass_count = 0;
public:
    int playerNum;
    std::vector<Player> players;
    ScrabbleBoard board;
    LetterBag bag;

    // Getter for pass count
    int get_pass_count() const { return pass_count; }

    Game(); // Constructor

    // Starts the game
    void play_game();

    // Function to check if the word can be placed on the board
    bool isValidPlacement(const std::vector<std::vector<Square>>& board, const std::string& word, int row, int col, char direction);

    // Determines the turn order of the players
    void determine_turn_order();
};

#endif // SCRABBLE_H


