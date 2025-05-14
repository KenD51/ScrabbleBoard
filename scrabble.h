#ifndef SCRABBLE_H
#define SCRABBLE_H

// Include necessary standard library headers
#include <vector>       // For vector container
#include <algorithm>    // For sorting algorithms
#include <random>       // For random number generation
#include <ctime>        // For time functions
#include <iostream>     // For input/output operations
#include <string>       // For string handling
#include <cstdlib>      // For general utilities

// Class representing a single Scrabble tile
class LetterTile {
private:
    char letter;        // The character on the tile (A-Z or * for blank)
    int point_value;    // The point value of the tile
    
public:
    // Constructor to create a tile with specific letter and value
    LetterTile(char the_letter, int the_value);
    
    // Getter for the tile's letter
    char get_letter() const;
    
    // Getter for the tile's point value
    int get_point_value() const;
};

// Class representing the bag of letter tiles
class LetterBag {
public:
    std::vector<LetterTile> Bag;  // Container holding all tiles
    
    LetterBag();  // Constructor initializes all tiles
    
    // Adds specified number of tiles to the bag
    void addTiles(char letter, int count, int value);
    
    // Checks if the bag is empty
    bool is_empty() const;
    
    // Randomly draws a tile from the bag
    LetterTile draw_tile();
};

// Class representing a player's tile rack
class LetterRack {
private:
    static const int SIZE = 7;  // Maximum tiles in rack
    LetterTile rack[SIZE];      // Array holding the tiles
    int tile_count = 0;         // Current number of tiles in rack
    
public:
    LetterRack();  // Default constructor
    
    // Removes a specific letter tile from the rack
    LetterTile remove_letter(char letter);
    
    // Refills the rack with tiles from the bag
    void fill_rack(LetterBag& bag);
    
    // Displays the current tiles in the rack
    void print_rack() const;
    
    // Returns the current number of tiles in rack
    int get_tile_count() const;
};

// Structure representing a single board square
struct Square {
    char letter = ' ';  // Default empty square
};

// Class representing the game board
class GameBoard {
private:
    std::vector<std::vector<Square>> board;  // 2D vector of squares
    static const int BOARD_SIZE = 15;        // Standard Scrabble board size
    
public:
    GameBoard();  // Constructor initializes empty board
    
    // Validates if a word can be placed at given position
    bool isValidPlacement(const std::string& word, int row, int col, char direction) const;
 
    // Prints the current board state
    void printBoard() const;
    
    // Places a word on the board if valid
    bool placeWord(const std::string& word, int row, int col, char direction);
};

// Class representing a player
class Player {
private:
    std::string name;        // Player's name
    LetterRack rack;         // Player's tile rack
    int order_number;        // Player's turn order
    int points;              // Player's current score
    
public:
    Player();  // Default constructor
    
    // Constructor with optional name and starting points
    Player(std::string the_name = "Player", int the_points = 0);
    
    // Getter for turn order
    int get_order_number() const;
    
    // Getter for current points
    int get_points() const;
    
    // Plays a word on the board
    void play_word(GameBoard& board, const std::string& word, int row, int col, bool horizontal);
    
    // Calculates score for a given word
    int calculate_score(const std::string& word);
    
    // Getter for the player's rack
    LetterRack get_rack() const;
    
    // Setter for player name
    void set_name(const std::string& name);
    
    // Getter for player name
    std::string get_name() const;
    
    // Setter for turn order
    void set_order_number(int order);
};

// Class representing the game controller
class Game {
private:
    int pass_count;              // Count of consecutive passes
    int playerNum;               // Number of players
    std::vector<Player> players; // List of players
    GameBoard board;         // Game board
    LetterBag bag;               // Tile bag
    int current_player_index;    // Index of current player
    
public:
    // Constructor with optional player count
    Game(int num_players = 0);
    
    // Main game loop
    void play_game();
    
    // Getter for pass count
    int get_pass_count() const;

    //Calculate the point value of the remaining tiles on the rack 
    int rack_points(LetterRack& rack);
    
    // Determines and announces the winner
    void determine_winner(Game& scrabble);

    // Checks if the word is part of the dictionary
    bool dictionaryCheck(const std::string& word);
    
    // Establishes initial turn order
    void determine_turn_order();
    
    // Advances to next player's turn
    void next_player();
    
    // Returns reference to current player
    Player& get_current_player();
    
    // Checks if game end conditions are met
    bool is_game_over() const;
};

#endif // SCRABBLE_H
