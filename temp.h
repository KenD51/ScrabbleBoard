// scrabble.h
#ifndef SCRABBLE_H
#define SCRABBLE_H

#include <vector>
#include <string>

class LetterTile {
private:
    char letter;
    int point_value;
public:
    LetterTile(char the_letter, int the_value) : letter(the_letter), point_value(the_value) {}
    char get_letter() const;
    int get_point_value() const;
};

class LetterBag {
private:
    std::vector<LetterTile> bag;
    std::vector<LetterTile> original_bag; // Store for resetting
public:
    LetterBag();
    void addTiles(char letter, int count, int value);
    bool is_empty() const;
    LetterTile draw_tile();
};

class LetterRack {
private:
    static const int SIZE = 7;
    LetterTile rack[SIZE];
public:
    LetterRack();
    LetterTile remove_letter(char letter);
    void fill_rack(LetterBag& bag);
    void print_rack() const;
    bool is_empty() const;
    int get_size() const;
    int get_tile_point_value(int index) const;
};

struct Square {
    char letter = ' ';
};

class ScrabbleBoard {
private:
    std::vector<std::vector<Square>> board;
    static const int BOARD_SIZE = 15;
public:
    ScrabbleBoard();
    bool is_valid_placement(const std::string& word, int row, int col, char direction, bool first_move) const;
    void print_board() const;
    bool placeWord(const std::string& word, int row, int col, char direction);
    int get_board_size() const { return BOARD_SIZE; }
};

class Player {
private:
    std::string name;
    LetterRack rack;
    int points;
public:
    Player(std::string the_name, LetterRack the_rack);
    void play_word(ScrabbleBoard& board, const std::string& word, int row, int col, char direction);
    int calculate_score(const std::string& word);
    LetterRack get_rack() const;
    std::string get_name() const;
    int get_points() const;
    void add_points(int p);
};

class EndGame : public Player {
private:
    std::vector<std::string> winner;
public:
    EndGame(std::string the_name, LetterRack the_rack);
    int compute_final_score(const LetterRack& rack) const;
    void determine_winner(class Game& scrabble);
};

class Game {
private:
    int playerNum;
    std::vector<Player> players;
    ScrabbleBoard board;
    LetterBag bag;
    LetterBag original_bag; // Store for resetting
public:
    Game();
    void play_game();
    void determine_turn_order();
    const std::vector<Player>& get_players() const;
};

#endif
