// scrabble.h
#ifndef SCRABBLE_H
#define SCRABBLE_H

#include <vector>
#include <string>

// Class to represent a single letter tile.
class LetterTile {
private:
    char letter;       // The letter on the tile.
    int point_value;  // The point value of the tile.
public:
    // Constructor for a LetterTile.
    LetterTile(char the_letter, int the_value) : letter(the_letter), point_value(the_value) {}

    // Returns the letter on the tile.
    char get_letter() const;

    // Returns the point value of the tile.
    int get_point_value() const;
};

// Class to represent the bag of letter tiles.
class LetterBag {
private:
    std::vector<LetterTile> bag;          // The current tiles in the bag.
    std::vector<LetterTile> original_bag; // Store for resetting the bag.
public:
    // Constructor for a LetterBag.  Initializes the bag with all the tiles.
    LetterBag();

    // Adds a specified number of tiles of a given letter and value to the bag.
    void addTiles(char letter, int count, int value);

    // Checks if the bag is empty.
    bool is_empty() const;

    // Draws a random tile from the bag and removes it.
    LetterTile draw_tile();
};

// Class to represent a player's rack of letter tiles.
class LetterRack {
private:
    static const int SIZE = 7;       // The maximum number of tiles in a rack.
    LetterTile rack[SIZE];         // Array to hold the tiles in the rack.
public:
    // Constructor for a LetterRack.  Initializes the rack to be empty.
    LetterRack();

    // Removes a letter from the rack.
    LetterTile remove_letter(char letter);

    // Fills the rack with tiles from the letter bag.
    void fill_rack(LetterBag& bag);

    // Prints the letters in the rack.
    void print_rack() const;

    // Checks if the rack is empty.
    bool is_empty() const;

    // Returns the size of the rack.
    int get_size() const;

    // Returns the point value of the tile at the given index.
    int get_tile_point_value(int index) const;
};

// Struct to represent a single square on the Scrabble board.
struct Square {
    char letter = ' ';  // The letter on the square, ' ' if empty.
};

// Class to represent the Scrabble board.
class ScrabbleBoard {
private:
    std::vector<std::vector<Square>> board; // 2D vector representing the board.
    static const int BOARD_SIZE = 15;         // The size of the board (15x15).
public:
    // Constructor for a ScrabbleBoard.  Initializes the board to be empty.
    ScrabbleBoard();

    // Checks if a word can be placed on the board at the given position and direction.
    bool is_valid_placement(const std::string& word, int row, int col, char direction, bool first_move) const;

    // Prints the current state of the Scrabble board.
    void print_board() const;

    // Places a word on the board at the given position and direction.
    bool placeWord(const std::string& word, int row, int col, char direction);

     // Returns the board size
    int get_board_size() const { return BOARD_SIZE; }
};

// Class to represent a player in the game.
class Player {
private:
    std::string name;     // The player's name.
    LetterRack rack;    // The player's letter rack.
    int points;         // The player's score.
public:
    // Constructor for a Player.
    Player(std::string the_name, LetterRack the_rack);

    // Plays a word on the board.
    void play_word(ScrabbleBoard& board, const std::string& word, int row, int col, char direction);

    // Calculates the score for a given word.
    int calculate_score(const std::string& word);

    // Returns the player's letter rack.
    LetterRack get_rack() const;

    // Returns the player's name.
    std::string get_name() const;

    // Returns the player's score.
    int get_points() const;

    // Adds points to the player's score.
    void add_points(int p);
};

// Class to represent the end-game scenario and determine the winner.
class EndGame : public Player { // Inherits from Player to access common data
private:
    std::vector<std::string> winner; // Vector to store the names of the winner(s).
public:
    // Constructor for EndGame.
    EndGame(std::string the_name, LetterRack the_rack);

    // Computes the final score of a player (score minus points of remaining tiles).
    int compute_final_score(const LetterRack& rack) const;

    // Determines the winner(s) of the game.
    void determine_winner(class Game& scrabble);
};

// Class to manage the overall Scrabble game.
class Game {
private:
    int playerNum;            // The number of players in the game.
    std::vector<Player> players; // Vector of Player objects.
    ScrabbleBoard board;       // The Scrabble board.
    LetterBag bag;           // The letter bag.
    LetterBag original_bag;  // Store for resetting.
public:
    // Constructor for a Game.  Initializes the game.
    Game();

    // Plays the Scrabble game.
    void play_game();

    // Determines the initial turn order of the players.
    void determine_turn_order();

    // Returns the vector of players.
    const std::vector<Player>& get_players() const;
};

#endif
