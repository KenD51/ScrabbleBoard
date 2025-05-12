//I changed The get_letter() method to correctly return char instead of int, as the letter itself is a char.
//I fixed constructor for Player to accept a std::string for the player's name and an int for their points.
//Compilors think letter rack is missing: remove_letter, fill_rack, print_rack, and is_empty, so i added them
//Removed duplicate #include <string> to avoid redundancy.
//Added game.h def

#ifndef SCRABBLE_H
#define SCRABBLE_H

#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>
#include <string>
#include <cstdlib>
#include <string>

class LetterTile {
private:
    char letter;
    int point_value;
public:
    LetterTile(char the_letter, int the_value) : letter(the_letter), point_value(the_value) {}
    int get_letter() const;
    int get_point_value() const;
};

class LetterBag {
public:
    std::vector<LetterTile> Bag;
    LetterBag() {
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

//This is a tile. Will merge later with scrabble board.
struct Square {
    char letter = ' ';
};

class ScrabbleBoard {
private:
    std::vector<std::vector<Square>> board; //2D Vector
    static const int BOARD_SIZE = 15; //Scrabble board has a length and width of 15 tiles. For error checking.
public:
    // Constructor to initialize the board
    ScrabbleBoard() : board(BOARD_SIZE, std::vector<Square>(BOARD_SIZE)) {}

    // Function to check if the given word placement is valid
    bool isValidPlacement(const std::string& word, int row, int col, char direction) const;

    //Function to print the board
    void printBoard() const;

    // Function to place a word on the board (if placement is valid)
    bool placeWord(const std::string& word, int row, int col, char direction);
};

// Player Class
class Player {
private:
    std::string name;
    LetterRack rack;
    int order_number;
public:
    int get_order_number() { return order_number; }
    int points = 0;
    Player(std::string the_name = "Player", int the_points = 0) : name(the_name), points(the_points) {}
    void play_word(ScrabbleBoard& board, const std::string& word, int row, int col, bool horizontal);
    int calculate_score(const std::string& word);
    LetterRack get_rack();
    void set_name(const std::string& name);
    std::string get_name() const;
    int get_points() const;
};

// Game Class
class Game {
private:
    int pass_count;              // To track the number of consecutive passes
    int playerNum;               // Number of players in the game
    std::vector<Player> players; // Vector to hold players
    ScrabbleBoard board;         // The Scrabble board
    LetterBag bag;               // The letter bag for tile drawing

public:
    Game();                      // Constructor to initialize the game
    void play_game();             // Main game loop
    int get_pass_count() const;   // Get the number of consecutive passes
    void determine_winner();      // Method to determine the winner based on points
    void determine_turn_order();  // Method to set up the turn order
};

#endif

