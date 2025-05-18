#ifndef SCRABBLE_H
#define SCRABBLE_H

#include <vector>       // For vector container
#include <algorithm>    // For sorting algorithms
#include <random>       // For random number generation
#include <ctime>        // For time functions
#include <iostream>     // For input/output operations
#include <string>       // For string handling
#include <cstdlib>      // For general utilities


// Forward declare LetterBag to avoid circular dependency
class LetterBag;

// Class representing a single Scrabble tile
class LetterTile {
private:
    char letter;        // The character on the tile (A-Z or * for blank)
    int point_value;    // The point value of the tile
    
public:
    // Default constructor
    LetterTile() : letter(' '), point_value(0) {}

    // Constructor to create a tile with specific letter and value
    LetterTile(char the_letter, int the_value);
    
    // Getter for the tile's letter
    char get_letter() const;
    
    // Getter for the tile's point value
    int get_point_value() const;
};

// Class representing a player's tile rack
class LetterRack {
public:
    static const int SIZE = 7;  // Made SIZE public for accessibility
    LetterTile rack[SIZE];      // Made rack public for accessibility
    int tile_count = 0;         // Made tile_count public for accessibility

    LetterRack();  // Default constructor
    
    // Removes a specific letter tile from the rack
    LetterTile remove_letter(char letter);
    
    // Refills the rack with tiles from the bag
    void fill_rack(LetterBag& bag);

    // Exchange tile
    void exchange_tile(const char letter, LetterBag& bag);
    
    // Displays the current tiles in the rack
    void print_rack() const;
    
    // Returns the current number of tiles in rack
    int get_tile_count() const;

    // Access operator for tiles in the rack
    const LetterTile& operator[](int index) const;

    // Check if the rack has a specific letter
    bool has_letter(char letter) const;
};

// Class representing the tile bag
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

// Structure representing a single board square
struct Square {
    char letter = ' ';  // Default empty square
};

// Forward declaration to resolve circular dependency
class Game;

// Class representing the game board
class GameBoard {
public:
    GameBoard(); // Add this constructor declaration
    // Validates if a word can be placed at given position
    bool isValidPlacement(const std::string& word, int row, int col, char direction) const;
    
    // Prints the current board state
    void printBoard() const;
    
    // Places a word on the board if valid
    bool placeWord(const std::string& word, int row, int col, char direction);

    // Initializes the board
    std::vector<std::vector<Square>> initializeBoard();

    // Gets the tile at the specified position
    char getTile(int row, int col) const; // Returns the letter at the given position
<<<<<<< HEAD
    std::vector<std::string> getAllWordsFormed(const std::string& word, int row, int col, bool horizontal) const;
    bool allAdjacentWordsValid(const std::string& word, int row, int col, bool horizontal, Game& game) const;
=======
>>>>>>> 66a62017c2906d85956b6e83de90e344fecd494e
private:
    std::vector<std::vector<Square>> board;  // 2D vector to represent the game board
};

// Class representing a player
class Player {
private:
    std::string name;        // Player's name
    int order_number;        // Player's turn order
    int points;              // Player's current score

public:
    LetterRack rack;         // Player's tile rack (moved to public for accessibility)

    Player() : name("Player"), points(0), order_number(0) {}  // Explicit default constructor
    Player(std::string the_name, int the_points = 0) : name(the_name), points(the_points), order_number(0) {}  // Parameterized constructor

    // Getter for turn order
    int get_order_number() const;

    // Getter for current points
    int get_points() const;

    // Plays a word on the board
    bool play_word(GameBoard& board, const std::string& word, int row, int col, bool horizontal);

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

    // Adds points to the player's score
    void add_points(int additional_points);
};

// Class representing the game controller
class Game {
public:
    std::vector<Player> players; // Made players public for accessibility

private:
    int pass_count;              // Count of consecutive passes
    int playerNum;               // Number of players
    GameBoard board;             // Game board
    LetterBag bag;               // Tile bag
    int current_player_index;    // Index of current player
    
public:
    // Constructor with optional player count and pass count
    Game(int num_players = 0);
    
    // Main game loop
    void play_game();
    
    // Getter for pass count
    int get_pass_count() const;
    
    // Determines and announces the winner
    void determine_winner();

    // Compute the number of points remaining on the player's rack
    int rack_points(LetterRack& rack);    
    
    // Establishes initial turn order
    void determine_turn_order();
    
    // Advances to next player's turn
    void next_player();
    
    // Returns reference to current player
    Player& get_current_player();
    
    // Checks if game end conditions are met
    bool is_game_over() const;

     // Checks if the word is part of the dictionary
    bool dictionaryCheck(const std::string& word);
    

    // Validates if a word is valid
    bool is_valid_word(const std::string& word);

    // Announces the winner of the game
    void announce_winner();

    void print_scores() const;
};

#endif // SCRABBLE_H