#include "temp.h"
#include <fstream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>
#include <string>
#include <cstdlib>

// LetterTile implementation
int LetterTile::get_point_value() const {
    return point_value;
}

int LetterTile::get_letter() const {
    return letter;
}

// LetterBag implementation
void LetterBag::addTiles(char letter, int count, int value) {
    for (int i = 0; i < count; ++i) {
        letter_bag.emplace_back(letter, value);
    }
}

bool LetterBag::is_empty() const {
    return LetterBag.empty();
}

LetterTile LetterBag::draw_tile() {
    try {
	if (LetterBag.empty()) {
            throw std::runtime_error("Bag is empty");
    catch (std::runtime_error& err) {
        if (player.get_rack().is_empty() == true) {
            EndGame end;
	    end.determinewinner(*this);
	}
    }
    
    // Randomly select a tile
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, letter_bag.size() - 1);
    int index = dist(gen);
    LetterTile tile = LetterBag[index];
    LetterBag.erase(LetterBag.begin() + index);
    return tile;
}

// LetterRack implementation
LetterTile LetterRack::remove_letter(char letter) {
    for (int i = 0; i < SIZE; i++) {
        if (rack[i].letter == letter) {
            LetterTile tmp = rack[i];
            rack[i] = LetterTile('?', 0); // filler tile
            return tmp;
        }
    }
    throw std::domain_error("The rack does not contain that letter.");
}

bool LetterRack::is_empty() {
    for (int i = 0; i < 7; i++) {
        if (rack[i] != ?) {
            return false;
}

void LetterRack::fill_rack(LetterBag& bag) {
    for (int i = 0; i < SIZE; i++) {
        if (rack[i].letter == ? && !bag.is_empty()) {
            rack[i] = bag.draw_tile();
        }
    }
}

void LetterRack::print_rack() const {
    std::cout << "Your rack contains: ";
    for (int i = 0; i < SIZE; i++) {
        std::cout << rack[i].letter << " ";
    }
    std::cout << std::endl;
}

// ScrabbleBoard implementation
bool ScrabbleBoard::is_valid_placement(const std::string& word, int row, int col, bool horizontal, bool first_move) {
    // Check boundaries
    if (row < 0 || row >= dimension || col < 0 || col >= dimension) {
        return false;
    }
    
    if (horizontal) {
        if (col + word.length() > dimension) return false;
    } else {
        if (row + word.length() > dimension) return false;
    }
    
    // Check for center tile on first move
    if (first_move) {
        bool covers_center = false;
        for (size_t i = 0; i < word.length(); ++i) {
            int r = horizontal ? row : row + i;
            int c = horizontal ? col + i : col;
            if (r == dimension/2 && c == dimension/2) {
                covers_center = true;
                break;
            }
        }
        if (!covers_center) return false;
    }
    
    // Check for overlaps with existing tiles
    for (size_t i = 0; i < word.length(); ++i) {
        int r = horizontal ? row : row + i;
        int c = horizontal ? col + i : col;
        
        if (board[r][c] != ' ' && board[r][c] != word[i]) {
            return false;
        }
    }
    
    return true;
}

// Player implementation
int Player::calculate_score(const std::string& word) {
    int score = 0;
    for (char c : word) {
        switch (c) { /* switch statement select one of many code blocks to be executed; the value of the expression is compared with the values of each case; if there is a match, the associated block of code is executed */
            case 'A': case 'E': case 'I': case 'L': case 'N': case 'O': case 'R': case 'S': case 'T': case 'U': score += 1; break;
            case 'D': case 'G': score += 2; break;
            case 'B': case 'C': case 'M': case 'P': score += 3; break;
            case 'F': case 'H': case 'V': case 'W': case 'Y': score += 4; break;
            case 'K': score += 5; break;
            case 'J': case ‘X’: score += 8; break;
            case 'Q': case ‘Z’: score += 10; break;
            default: score += 0; break;
        }
    }
    return score;
}

LetterRack Player::get_rack() {
    return rack;
}

void Player::play_word(ScrabbleBoard& board, const std::string& word, int row, int col, bool horizontal) {
    // Place tiles on board
    for (size_t i = 0; i < word.length(); ++i) {
        int r = horizontal ? row : row + i;
        int c = horizontal ? col + i : col;
        board.board[r][c] = word[i];
    }
    
    // Calculate and add score
    points += calculate_score(word);
    
    // Check for bingo (using all tiles)
    if (word.length() == 7) {
        points += 50;
        std::cout << "Bingo! 50 bonus points added!" << std::endl;
    }
}

// Game implementation
int Game::get_pass_count() const {
    return pass_count;
}

Game::Game() {
    std::cout << "How many players are going to be in the game? (2-4): ";
    std::cin >> playerNum;
    while (playerNum < 2 || playerNum > 4) {
        std::cout << "Invalid number of players. Please enter a number between 2 and 4: ";
        std::cin >> playerNum;
    }
    
    // Initialize players
    for (int i = 0; i < playerNum; ++i) {
        players.emplace_back();
        std::cout << "Enter name for player " << i+1 << ": ";
        std::cin >> players[i].name;
    }
    
    // Determine turn order
    determine_turn_order();
    
    // Fill racks
    for (auto& player : players) {
        player.rack.fill_rack(bag);
    }
}

void Game::determine_turn_order() {
    bool unique_tiles = false;
    std::vector<char> drawn_tiles;
    
    while (!unique_tiles) {
        drawn_tiles.clear();
        
        // Each player draws one tile
        for (auto& player : players) {
            if (!bag.is_empty()) {
                LetterTile tile = bag.draw_tile();
                drawn_tiles.push_back(tile.letter);
            } else {
                drawn_tiles.push_back('*'); // blank tile has highest precedence
            }
        }
        
        // Check if all tiles are unique
        unique_tiles = true;
        for (size_t i = 0; i < drawn_tiles.size(); ++i) {
            for (size_t j = i + 1; j < drawn_tiles.size(); ++j) {
                if (drawn_tiles[i] == drawn_tiles[j]) {
                    unique_tiles = false;
                    break;
                }
            }
            if (!unique_tiles) break;
        }
        
        // Return tiles to bag if not unique
        if (!unique_tiles) {
            for (char c : drawn_tiles) {
                if (c != '*') {
                    bag.addTiles(c, 1, LetterTile(c, 0).get_point_value());
                }
            }
        }
    }
    
    // Sort players based on tile precedence
    std::sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
        // Blank tile has highest precedence
        if (a.rack[0].letter == '*') return true;
        if (b.rack[0].letter == '*') return false;
        return a.rack[0].letter < b.rack[0].letter;
    });
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
            // Convert to uppercase and add to dictionary
            std::transform(word.begin(), word.end(), word.begin(), ::toupper);
            dictionary.insert(word);
        }
    } else {
        std::cerr << "Warning: Could not load dictionary file" << std::endl;
    }
    
    while (true) {
        int playerIndex = turn % playerNum;
        Player& current = players[playerIndex];
        
        std::cout << "\n=== " << current.name << "'s turn ===" << std::endl;
        std::cout << "Current score: " << current.points << std::endl;
        current.rack.print_rack();
        board.print_board();
        
        std::cout << "Options:\n"
                  << "1. Play word\n"
                  << "2. Pass\n"
                  << "3. Exchange tiles\n"
                  << "4. End game\n"
                  << "Enter choice: ";
        
        int choice;
        std::cin >> choice;
        
        switch (choice) {
            case 1: { // Play word
                std::string word;
                int row, col;
                char dir;
                std::cout << "Enter word: ";
                std::cin >> word;
                std::cout << "Enter row (1-15) and column (1-15): ";
                std::cin >> row >> col;
                std::cout << "Direction (h for horizontal, v for vertical): ";
                std::cin >> dir;
                
                // Convert to uppercase and validate
                std::transform(word.begin(), word.end(), word.begin(), ::toupper);
                row--; col--; // Convert to 0-based index
                
                if (board.is_valid_placement(word, row, col, dir == 'h', first_move) && 
                    dictionary.find(word) != dictionary.end()) {
                    
                    current.play_word(board, word, row, col, dir == 'h');
                    first_move = false;
                    pass_count = 0;
                    
                    // Remove played letters from rack and draw new ones
                    for (char c : word) {
                        try {
                            current.rack.remove_letter(c);
                        } catch (...) {
                            // Handle blank tiles or errors
                        }
                    }
                    current.rack.fill_rack(bag);
                } else {
                    std::cout << "Invalid word or placement!" << std::endl;
                }
                break;
            }
            case 2: // Pass
                pass_count++;
                break;
            case 3: { // Exchange tiles
                std::string letters;
                std::cout << "Enter letters to exchange: ";
                std::cin >> letters;
                
                for (char c : letters) {
                    try {
                        LetterTile tile = current.rack.remove_letter(c);
                        bag.addTiles(tile.letter, 1, tile.get_point_value());
                    } catch (...) {
                        std::cout << "Couldn't exchange " << c << std::endl;
                    }
                }
                current.rack.fill_rack(bag);
                break;
            }
            case 4: // End game
                EndGame end;
                end.determine_winner(*this);
                return;
            default:
                std::cout << "Invalid choice!" << std::endl;
        }
        
        // Check end game conditions
        if (pass_count >= 6) {
            std::cout << "Game ended due to 6 consecutive passes." << std::endl;
            EndGame end;
            end.determine_winner(*this);
            return;
        }
        
        turn++;
    }
}

// EndGame implementation
int EndGame::compute_final_score(LetterRack& rack) {
    int total_tile_points = 0;
    for (int i = 0; i < rack.SIZE; i++) {
        total_tile_points += rack[i].get_point_value();
    }
    return total_tile_points;
}

void EndGame::determine_winner(Game& scrabble) {
    std::vector<std::string> winners;
    int highest_score = INT_MIN;
    
    // Calculate final scores
    for (auto& player : scrabble.players) {
        int final_score = player.points - compute_final_score(player.rack);
        
        if (final_score > highest_score) {
            highest_score = final_score;
            winners.clear();
            winners.push_back(player.name);
        } else if (final_score == highest_score) {
            winners.push_back(player.name);
        }
    }
    
    // Display results
    std::cout << "\n=== Game Over ===" << std::endl;
    for (auto& player : scrabble.players) {
        int final_score = player.points - compute_final_score(player.rack);
        std::cout << player.name << ": " << final_score << " points" << std::endl;
    }
    
    std::cout << "\nWinner(s): ";
    for (const auto& winner : winners) {
        std::cout << winner << " ";
    }
    std::cout << std::endl;
}
