//Fixed code?????

#ifndef SCRABBLE_H
#define SCRABBLE_H

#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>
#include <string>
#include <cstdlib> // Needed for std::rand, std::srand. Not sure why we didn't use <random>

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
private:
    std::vector<LetterTile> bag; // Renamed to 'bag' to avoid conflict with class name
public:
    LetterBag() {
        // Initialize the letter bag with the standard Scrabble distribution
        addTiles('A', 9, 1);//(letter, amount, score)
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
    bool is_empty() const { return bag.empty(); }
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
    bool is_empty() const; // Added const, error otherwise
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

class Player {
private:
    std::string name;
    LetterRack rack;
public:
    int points = 0;
    Player (std::string the_name, LetterRack the_rack) : name(the_name), rack(the_rack), points(0) {} //fixed syntax and set initial points to 0
    void play_word(ScrabbleBoard& board, char tile, int row, int col, bool horizontal); // Changed std::char& to char.]
    int calculate_score(const std::string& word);
    //IDK but this class has a bunch of accessing errors, so I added accessors.
    LetterRack get_rack() const { return rack; } // Added const to getter
    std::string get_name() const { return name; } // Added getter for name
    int get_points() const { return points; } // Added getter for points
    void add_points(int p) { points += p; } // Added function to add points
};

class EndGame : public Player {
private:
    std::vector<std::string> winner;
public:
    EndGame(std::string the_name, LetterRack the_rack) : Player(the_name, the_rack) {} // Corrected the constructor to call the player base class now.
    void compute_final_score(LetterRack& rack);
    void determine_winner(class Game& scrabble); // Forward declaration of Game
};

class Game {
private:
    int pass_count = 0;
public:
    int playerNum;
    std::vector<Player> players;
    ScrabbleBoard board;
    LetterBag bag;
    int get_pass_count() const { return pass_count; }
    Game();
    void play_game();
    bool isValidPlacement(const std::vector<std::vector<Square>>& board, const std::string& word, int row, int col, char direction);
    void determine_turn_order();
};

#endif
