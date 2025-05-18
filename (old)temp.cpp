/* #include "scrabble.h"
#include <fstream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept> // For std::runtime_error and std::domain_error

// LetterTile implementation
int LetterTile::get_point_value() const {
    return point_value;
}

char LetterTile::get_letter() const {
    return letter;
}

// LetterBag implementation
void LetterBag::addTiles(char letter, int count, int value) {
    for (int i = 0; i < count; ++i) {
        bag.emplace_back(letter, value); // Corrected: using 'bag'
    }
}

bool LetterBag::is_empty() const {
    return bag.empty(); // Corrected: using 'bag'
}

LetterTile LetterBag::draw_tile() {
    if (bag.empty()) {
        throw std::runtime_error("Bag is empty");
    }

    // Randomly select a tile
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, bag.size() - 1);
    int index = dist(gen);
    LetterTile tile = bag[index];
    bag.erase(bag.begin() + index);
    return tile;
}

// LetterRack implementation
LetterTile LetterRack::remove_letter(char letter) {
    for (int i = 0; i < SIZE; i++) {
        if (rack[i].get_letter() == letter) { // Access letter using getter
            LetterTile tmp = rack[i];
            rack[i] = LetterTile(' ', 0); // Using space as a filler
            return tmp;
        }
    }
    throw std::domain_error("The rack does not contain that letter.");
}

bool LetterRack::is_empty() const { // Added const
    for (int i = 0; i < SIZE; i++) {
        if (rack[i].get_letter() != ' ') { // Check if letter is not space
            return false;
        }
    }
    return true;
}

void LetterRack::fill_rack(LetterBag& bag) {
    for (int i = 0; i < SIZE; i++) {
        if (rack[i].get_letter() == ' ' && !bag.is_empty()) { // Check if letter is space
            try {
                rack[i] = bag.draw_tile();
            } catch (const std::runtime_error& err) {
                // Handle empty bag if it occurs during fill
                break;
            }
        }
    }
}

void LetterRack::print_rack() const {
    std::cout << "Your rack contains: ";
    for (int i = 0; i < SIZE; i++) {
        std::cout << rack[i].get_letter() << " ";
    }
    std::cout << std::endl;
}

// ScrabbleBoard implementation
bool ScrabbleBoard::is_valid_placement(const std::string& word, int row, int col, char direction, bool first_move) const { // Changed direction to char
    int dimension = BOARD_SIZE; // Use the static constant

    // Check boundaries
    if (row < 0 || row >= dimension || col < 0 || col >= dimension) {
        return false;
    }

    if (direction == 'h') {
        if (col + word.length() > dimension) return false;
    } else if (direction == 'v') {
        if (row + word.length() > dimension) return false;
    } else {
        return false; // Invalid direction
    }

    // Check for center tile on first move
    if (first_move) {
        bool covers_center = false;
        for (size_t i = 0; i < word.length(); ++i) {
            int r = (direction == 'h') ? row : row + i;
            int c = (direction == 'h') ? col + i : col;
            if (r == dimension / 2 && c == dimension / 2) {
                covers_center = true;
                break;
            }
        }
        if (!covers_center) return false;
    }

    // Check for overlaps with existing tiles
    for (size_t i = 0; i < word.length(); ++i) {
        int r = (direction == 'h') ? row : row + i;
        int c = (direction == 'h') ? col + i : col;

        if (board[r][c].letter != ' ' && board[r][c].letter != word[i]) { // Access letter member
            return false;
        }
    }

    return true;
}

void ScrabbleBoard::print_board() const {
    std::cout << "  ";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::cout << i + 1 << (i < 9 ? "  " : " ");
    }
    std::cout << std::endl;
    std::cout << "  ";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::cout << "---";
    }
    std::cout << std::endl;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::cout << char('A' + i) << " |";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << board[i][j].letter << "  ";
        }
        std::cout << std::endl;
    }
}

bool ScrabbleBoard::placeWord(const std::string& word, int row, int col, char direction) {
    if (direction == 'h') {
        for (size_t i = 0; i < word.length(); ++i) {
            board[row][col + i].letter = word[i];
        }
    } else if (direction == 'v') {
        for (size_t i = 0; i < word.length(); ++i) {
            board[row + i][col].letter = word[i];
        }
    }
    return true; // Assume placement was valid before calling this
}


// Player implementation
int Player::calculate_score(const std::string& word) {
    int score = 0;
    for (char c : word) {
        switch (c) {
            case 'A': case 'E': case 'I': case 'L': case 'N': case 'O': case 'R': case 'S': case 'T': case 'U': score += 1; break;
            case 'D': case 'G': score += 2; break;
            case 'B': case 'C': case 'M': case 'P': score += 3; break;
            case 'F': case 'H': case 'V': case 'W': case 'Y': score += 4; break;
            case 'K': score += 5; break;
            case 'J': case 'X': score += 8; break; // Corrected apostrophes
            case 'Q': case 'Z': score += 10; break; // Corrected apostrophes
            case '*': score += 0; break; // Blank tile score
            default: score += 0; break;
        }
    }
    return score;
}

int Player::get_order_number() const {
    return order_number;
}

LetterRack Player::get_rack() const { // Added const
    return rack;
}

void Player::play_word(ScrabbleBoard& board, const std::string& word, int row, int col, char horizontal) { // Changed bool to char for direction
    // Place tiles on board
    for (size_t i = 0; i < word.length(); ++i) {
        int r = (horizontal == 'h') ? row : row + i;
        int c = (horizontal == 'h') ? col + i : col;
        board.board[r][c].letter = word[i];
    }

    // Calculate and add score
    points += calculate_score(word);

    // Check for bingo (using all tiles - assuming rack size is 7)
    if (word.length() == rack.get_size()) { // Use getter for size
        points += 50;
        std::cout << "Bingo! 50 bonus points added!" << std::endl;
    }
}

// Game implementation
Game::Game() : board(), bag() { // Initialize board and bag in constructor initializer list
    std::cout << "How many players are going to be in the game? (2-4): ";
    std::cin >> playerNum;
    while (playerNum < 2 || playerNum > 4) {
        std::cout << "Invalid number of players. Please enter a number between 2 and 4: ";
        std::cin >> playerNum;
    }

    // Initialize players
    players.resize(playerNum); // Resize the vector first
    for (int i = 0; i < playerNum; ++i) {
        std::cout << "Enter name for player " << i + 1 << ": ";
        std::cin >> players[i].name;
        // Racks are initialized when players are default-constructed
    }

    // Determine turn order
    determine_turn_order();

    // Fill racks
    for (auto& player : players) {
        player.rack.fill_rack(bag);
    }
}

void Game::determine_turn_order() {
    std::vector<std::pair<char, int>> drawn_tiles(players.size());
    bool unique_tiles = false;
    std::random_device rd;
    std::mt19937 gen(rd());

    while (!unique_tiles) {
        drawn_tiles.clear();
        bag = original_bag; // Reset the bag for redrawing

        // Each player draws one tile
        for (int i = 0; i < players.size(); ++i) {
            if (!bag.is_empty()) {
                LetterTile tile = bag.draw_tile();
                drawn_tiles.push_back({tile.get_letter(), i}); // Store letter and player index
            } else {
                drawn_tiles.push_back({'*', i}); // Blank tile has highest precedence
            }
        }

        // Check if all drawn tiles are unique
        std::unordered_set<char> seen_tiles;
        unique_tiles = true;
        for (const auto& pair : drawn_tiles) {
            if (seen_tiles.count(pair.first)) {
                unique_tiles = false;
                break;
            }
            seen_tiles.insert(pair.first);
        }
    }

    // Sort players based on drawn tile precedence (Blank > A > B > ...)
    std::sort(drawn_tiles.begin(), drawn_tiles.end(), [](const auto& a, const auto& b) {
        if (a.first == '*') return true;
        if (b.first == '*') return false;
        return a.first < b.first;
    });

    std::vector<Player> sorted_players;
    for (const auto& pair : drawn_tiles) {
        sorted_players.push_back(players[pair.second]);
    }
    players = sorted_players;
}

void Game::play_game() {
    int turn = 0;
    bool first_move = true;

    // Load dictionary
    std::unordered_set<std::string> dictionary;
    std::ifstream dict_file("/usr/share/dict/words");
    if (dict_file) {
        std::string word;
        while (dict_file >> word) {
            std::transform(word.begin(), word.end(), word.begin(), ::toupper);
            dictionary.insert(word);
        }
    } else {
        std::cerr << "Warning: Could not load dictionary file" << std::endl;
    }

    while (true) {
        int playerIndex = turn % playerNum;
        Player& current = players[playerIndex];

        std::cout << "\n=== " << current.get_name() << "'s turn ===" << std::endl;
        std::cout << "Current score: " << current.get_points() << std::endl;
        current.get_rack().print_rack();
        board.print_board();

        std::
*/