#ifndef SCRABBLE_H
#define SCRABBLE_H

#include <vector>
#include <string>
#include <iostream>
#include <ctime>

//Changed to add some header definitions that were missing.

// Class to represent a single letter tile.
class LetterTile {
private:
    char letter;
    int point_value;

public:
    // Constructor for a LetterTile.
    LetterTile(char the_letter, int the_value) : letter(the_letter), point_value(the_value) {}

    // Returns the letter on the tile.
    char get_letter() const {
        return letter;
    }

    // Returns the point value of the tile.
    int get_point_value() const {
        return point_value;
    }
};

// Class to represent the bag of letter tiles.
class LetterBag {
private:
    std::vector<LetterTile> bag;

public:
    // Constructor to initialize the letter bag with tiles.
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
    }

    // Adds multiple tiles to the bag for a specific letter.
    void addTiles(char letter, int count, int value) {
        for (int i = 0; i < count; ++i) {
            bag.push_back(LetterTile(letter, value));
        }
    }

    // Returns true if the bag is empty.
    bool is_empty() const {
        return bag.empty();
    }

    // Draws a tile from the bag and returns it.
    LetterTile draw_tile() {
        if (!is_empty()) {
            srand(time(0));
            int index = rand() % bag.size();
            LetterTile tile = bag[index];
            bag.erase(bag.begin() + index);
            return tile;
        }
        return LetterTile(' ', 0);  // Return an empty tile if the bag is empty.
    }
};

// Class to represent a player's rack of letter tiles.
class LetterRack {
private:
    static const int SIZE = 7;
    LetterTile rack[SIZE];

public:
    // Constructor initializes an empty rack.
    LetterRack() {}

    // Removes a letter from the rack and returns it.
    LetterTile remove_letter(char letter) {
        for (int i = 0; i < SIZE; ++i) {
            if (rack[i].get_letter() == letter) {
                LetterTile tile = rack[i];
                rack[i] = LetterTile(' ', 0);  // Replace the letter with an empty tile.
                return tile;
            }
        }
        return LetterTile(' ', 0);  // Return an empty tile if the letter was not found.
    }

    // Fills the rack with new tiles from the bag.
    void fill_rack(LetterBag& bag) {
        for (int i = 0; i < SIZE; ++i) {
            if (rack[i].get_letter() == ' ') {
                rack[i] = bag.draw_tile();
            }
        }
    }

    // Prints out the contents of the rack.
    void print_rack() const {
        for (int i = 0; i < SIZE; ++i) {
            std::cout << rack[i].get_letter() << " ";
        }
        std::cout << std::endl;
    }

    // Checks if the rack is empty.
    bool is_empty() const {
        for (int i = 0; i < SIZE; ++i) {
            if (rack[i].get_letter() != ' ') {
                return false;
            }
        }
        return true;
    }

    // Returns the size of the rack.
    int get_size() const {
        return SIZE;
    }

    // Returns the point value of the tile at the specified index.
    int get_tile_point_value(int index) const {
        return rack[index].get_point_value();
    }
};

// Struct to represent a single square on the Scrabble board.
struct Square {
    char letter = ' ';
};

// Class to represent the Scrabble board.
class ScrabbleBoard {
private:
    std::vector<std::vector<Square>> board;
    static const int BOARD_SIZE = 15;

public:
    // Constructor initializes an empty board.
    ScrabbleBoard() : board(BOARD_SIZE, std::vector<Square>(BOARD_SIZE)) {}

    // Checks if the word placement is valid on the board.
    bool is_valid_placement(const std::string& word, int row, int col, char direction, bool first_move) const {
        int length = word.length();
        if (direction == 'H') {
            if (col + length > BOARD_SIZE) return false;
        } else if (direction == 'V') {
            if (row + length > BOARD_SIZE) return false;
        }
        return true;
    }

    // Prints the current state of the board.
    void print_board() const {
        for (const auto& row : board) {
            for (const auto& square : row) {
                std::cout << (square.letter == ' ' ? '.' : square.letter) << " ";
            }
            std::cout << std::endl;
        }
    }

    // Places a word on the board at the specified position.
    bool placeWord(const std::string& word, int row, int col, char direction) {
        int length = word.length();
        if (direction == 'H') {
            for (int i = 0; i < length; ++i) {
                board[row][col + i].letter = word[i];
            }
        } else if (direction == 'V') {
            for (int i = 0; i < length; ++i) {
                board[row + i][col].letter = word[i];
            }
        }
        return true;
    }

    // Returns the size of the board.
    int get_board_size() const {
        return BOARD_SIZE;
    }
};

// Class to represent a player in the game.
class Player {
private:
    std::string name;
    LetterRack rack;
    int points;
    int order_number;

public:
    // Constructor for the Player.
    Player(std::string the_name, LetterRack the_rack) : name(the_name), rack(the_rack), points(0), order_number(0) {}

    // Returns the order number of the player.
    int get_order_number() const {
        return order_number;
    }

    // Makes the player play a word on the board.
    void play_word(ScrabbleBoard& board, const std::string& word, int row, int col, char direction) {
        if (board.is_valid_placement(word, row, col, direction, true)) {
            board.placeWord(word, row, col, direction);
            points += calculate_score(word);  // Add points for the word played.
        }
    }

    // Calculates the score for a word.
    int calculate_score(const std::string& word) {
        int score = 0;
        for (char c : word) {
            score += get_tile_point_value(c);  // Simplified, each letter has its own point value.
        }
        return score;
    }

    // Returns the point value of a tile based on the letter.
    int get_tile_point_value(char letter) const {
        switch (letter) {
            case 'A': case 'E': case 'I': case 'L': case 'N': case 'O': case 'R': case 'S': case 'T': case 'U': return 1;
            case 'D': case 'G': return 2;
            case 'B': case 'C': case 'M': case 'P': return 3;
            case 'F': case 'H': case 'V': case 'W': case 'Y': return 4;
            case 'K': return 5;
            case 'J': case 'X': return 8;
            case 'Q': case 'Z': return 10;
            default: return 0;  // Handle unknown letters.
        }
    }

    // Returns the player's rack.
    LetterRack get_rack() const {
        return rack;
    }

    // Returns the player's name.
    std::string get_name() const {
        return name;
    }

    // Returns the player's points.
    int get_points() const {
        return points;
    }

    // Adds points to the player's score.
    void add_points(int p) {
        points += p;
    }
};

// Class to manage the overall Scrabble game.
class Game {
private:
    int playerNum;
    std::vector<Player> players;
    ScrabbleBoard board;
    LetterBag bag;

public:
    // Constructor for the Game.
    Game() : playerNum(0) {}

    // Starts the game and handles turns.
    void play_game() {
        std::cout << "Welcome to Scrabble!" << std::endl;
        while (true) {
            for (auto& player : players) {
                std::cout << player.get_name() << "'s turn!" << std::endl;
                player.play_word(board, "EXAMPLE", 7, 7, 'H');
                board.print_board();
            }
            break;  // End of the game loop (this is just a placeholder).
        }
    }

    // Determines the turn order by randomizing player scores (simplified).
    void determine_turn_order() {
        srand(time(0));
        for (int i = 0; i < players.size(); ++i) {
            players[i].add_points(rand() % 10);
        }
    }

    // Returns the list of players.
    const std::vector<Player>& get_players() const {
        return players;
    }
};

#endif
