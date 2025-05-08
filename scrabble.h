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
    std::vector<LetterTile> LetterBag;
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
    void addTiles(char letter, int count, int value;
    bool is_empty() const;
    LetterTile draw_tile();
};

class LetterRack {
private:
    const int SIZE = 7;
    LetterTile rack[SIZE];
public:
    LetterTile remove_letter(const char letter); 
    void fill_rack();
    void print_rack() const;
};

class ScrabbleBoard {
private:
    static const int dimension = 15; // Fixed size for the Scrabble board
    char board[dimension][dimension]; // 2D array to represent the board
public:
    ScrabbleBoard() {
        // Initialize the board with spaces
        for (int i = 0; i < dimension; ++i) {
            for (int j = 0; j < dimension; ++j) {
                board[i][j] = ' ';
            }
        }
    }
    void print_board() const;
    bool is_valid_placement(const std::string& word, int row, int col, bool horizontal);
};

class Player {
private:
    std::string name;
    LetterRack rack;
public:
    int points = 0;
    Player (the_name, the_rack, the_points) : name(the_name), rack(the_rack), points(the_points) {}
    void play_word(ScrabbleBoard& board, const std::char& tile, int row, int col, bool horizontal);
    int calculate_score(const std::string& word);
};

class EndGame : public Player {
private:
    std::vector<string> winner;
public:
    void compute_final_score(LetterRack& rack);
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
    int get_pass_count() const;
    Game();
    void play_game();
    bool isValidPlacement(const vector<vector<Square>>& board, const string& word, int row, int col, char direction);
    void determine_turn_order();
};

#endif
