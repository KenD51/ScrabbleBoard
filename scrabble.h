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
    LetterTile(char the_letter, int the_value);
    char get_letter() const;
    int get_point_value() const;
};

class LetterRack {
private:
    static const int SIZE = 7;
    LetterTile rack[SIZE];
    int tile_count = 0;
public:
    LetterRack(); // Default constructor
    LetterTile remove_letter(char letter); // Consistent parameter type
    void fill_rack(LetterBag& bag); // Takes LetterBag&
    void print_rack() const;
    int get_tile_count() const;
};

class LetterBag {
public:
    std::vector<LetterTile> Bag;
    LetterBag();
    void addTiles(char letter, int count, int value);
    bool is_empty() const;
    LetterTile draw_tile();
};

struct Square {
    char letter = ' ';
};

class GameBoard {
private:
    std::vector<std::vector<Square>> board; //2D Vector
    static const int BOARD_SIZE = 15; //Scrabble board has a length and width of 15 tiles. For error checking.
public:
    // Constructor to initialize the board
    ScrabbleBoard();

    // Function to check if the given word placement is valid
    bool isValidPlacement(const std::string& word, int row, int col, char direction) const;

    //Function to print the board
    void printBoard() const;

    // Function to place a word on the board (if placement is valid)
    bool placeWord(const std::string& word, int row, int col, char direction); // Consistent direction type
};

// Player Class
class Player {
private:
    std::string name;
    LetterRack rack;
    int order_number;
    int points; // Private member
public:
    // Default Constructor
    Player();
    // Constructor
    Player(std::string the_name = "Player", int the_points = 0);
    int get_order_number() const;
    int get_points() const;
    void play_word(ScrabbleBoard& board, const std::string& word, int row, int col, bool horizontal);
    int calculate_score(const std::string& word);
    LetterRack get_rack() const;
    void set_name(const std::string& name);
    std::string get_name() const;
    void set_order_number(int order);
};

// Game Class
class Game {
private:
    int pass_count;         // To track the number of consecutive passes
    int playerNum;          // Number of players in the game
    std::vector<Player> players; // Vector to hold players
    ScrabbleBoard board;      // The Scrabble board
    LetterBag bag;          // The letter bag for tile drawing
    int current_player_index; // To track the current player's turn

public:
    Game(int num_players = 0);         // Constructor to initialize the game
    void play_game();                 // Main game loop
    int get_pass_count() const;       // Get the number of consecutive passes
    void determine_winner();           // Method to determine the winner based on points
    void determine_turn_order();       // Method to set up the turn order
    void next_player();
    Player& get_current_player();
    bool is_game_over() const;
};

#endif
