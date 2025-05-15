// Game.cpp
#include "scrabble.h"     // Include the header file that defines all the classes and methods used
#include <algorithm>      // For std::sort to sort players based on the drawn tiles
#include <iostream>       // For input and output, e.g., displaying prompts and results
#include <fstream>        // For file handling (e.g., saving/loading game state)
#include <unordered_set>  // For efficient duplicate detection. I don't know how this is used.
#include <cctype>         // For character operations like checking letter cases
#include <sstream>       
#include <string>         // For string operations
#include <cstring>        // For handling C-style strings
#include <direct.h>       // For _getcwd on Windows

//I added a lot of debugging output as there was a lot of things to test.

// Added debugging output to input validation loop in Game constructor. 
Game::Game(int num_players) : pass_count(0), playerNum(num_players), current_player_index(0) {
    std::cout << "Initializing game with " << playerNum << " players." << std::endl;
    while (playerNum < 2 || playerNum > 4) {
        std::cout << "Invalid number of players. Please enter a number between 2 and 4: ";
        std::cin >> playerNum;
        std::cout << "You entered: " << playerNum << std::endl;
    }

    std::cout << "Valid number of players: " << playerNum << std::endl;

    // Initialize players
    for (int i = 0; i < playerNum; ++i) {
        players.emplace_back();
        std::cout << "Enter name for player " << i + 1 << ": ";
        std::string name;
        std::cin >> name;
        players[i].set_name(name);
    }

    // Determine turn order
    determine_turn_order();

    // Debugging output to check LetterBag and racks. 
    std::cout << "Initial LetterBag size: " << bag.Bag.size() << std::endl;

    // Fill racks
    for (auto& player : players) {
        player.rack.fill_rack(bag);
        std::cout << "Rack for player " << player.get_name() << " filled with " << player.rack.get_tile_count() << " tiles." << std::endl;
    }

    std::cout << "Remaining LetterBag size: " << bag.Bag.size() << std::endl;
}

// Determines the turn order of players by drawing unique tiles for each player. This is an incorrect way to do it, but it works for now.
void Game::determine_turn_order() {
    bool unique_tiles = false; //The person who  has the unqiue tile goes first
    std::cout << "Determining turn order..." << std::endl;
    std::vector<char> drawn_tiles;  // Vector to store drawn tiles for each player

    // Keep drawing tiles until all drawn tiles are unique
    while (!unique_tiles) {
        drawn_tiles.clear();  // Clear the previously drawn tiles

        // Draw one tile for each player
        for (auto& player : players) {
            if (!bag.is_empty()) {
                LetterTile tile = bag.draw_tile();  // Draw a tile from the bag
                drawn_tiles.push_back(tile.get_letter());  // Store the letter of the tile
            } else {
                drawn_tiles.push_back('*');  // Use '*' for a blank tile if the bag is empty
            }
        }

        // Check for duplicates in the drawn tiles
        unique_tiles = true;  // Assume uniqueness unless we find duplicates
        
        // Use a nested loop to check for duplicates in the drawn tiles
        for (size_t i = 0; i < drawn_tiles.size(); ++i) {
            for (size_t j = i + 1; j < drawn_tiles.size(); ++j) {
                if (drawn_tiles[i] == drawn_tiles[j]) {  // If duplicates are found
                    unique_tiles = false;  // Set unique_tiles to false and break the loop
                    break;
                }
            }
            if (!unique_tiles) break;  // Exit outer loop if duplicates are found
        }

        // If duplicates were found, return the drawn tiles to the bag and redraw
        if (!unique_tiles) {
            for (char c : drawn_tiles) {
                if (c != '*') {  // Only return non-blank tiles to the bag
                    bag.addTiles(c, 1, LetterTile(c, 0).get_point_value());  // Return tile to bag
                }
            }
        }
    }

    // Sort players based on their first drawn tile in lexicographical order
    // Blank tiles ('*') come first, then tiles are sorted in A-Z order
    std::sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
        const LetterRack& rackA = a.get_rack();
        const LetterRack& rackB = b.get_rack();
        if (rackA[0].get_letter() == '*') return true;
        if (rackB[0].get_letter() == '*') return false;
        return rackA[0].get_letter() < rackB[0].get_letter();
    });
}


void Game::play_game() {
    bool game_over = false;

    while (!game_over) {
        std::cout << "\nChecking if the game is over..." << std::endl;
        if (is_game_over()) {
            std::cout << "Game over condition met." << std::endl;
            game_over = true;
            break;
        }

        for (auto& player : players) {
            bool valid_turn = false;
            while (!valid_turn) {
                std::cout << "\n=== " << player.get_name() << "'s turn ===" << std::endl;
                player.rack.print_rack();

                std::cout << "\nCurrent Board State:" << std::endl;
                board.printBoard();

                // Inform user about the center position
                std::cout << "Note: The center star is at row 7, column 7." << std::endl;

                std::string input_line;
                std::cout << "Enter word, row, column, and direction (H/V): ";
                std::getline(std::cin >> std::ws, input_line); // Read the whole line

                std::istringstream iss(input_line);
                std::string word;
                int row, col;
                char direction;
                if (!(iss >> word >> row >> col >> direction)) {
                    std::cout << "Invalid input format. Please try again." << std::endl;
                    continue;
                }

                // Convert row and col to 0-based indices
                row -= 1;
                col -= 1;

                // Convert word to uppercase for consistency
                std::transform(word.begin(), word.end(), word.begin(), ::toupper);

                // Dictionary check
                if (!dictionaryCheck(word)) {
                    std::cout << "Word not found in dictionary. Try again." << std::endl;
                    continue;
                }

                // Validate placement
                bool horizontal = (direction == 'H' || direction == 'h');
                if (!board.isValidPlacement(word, row, col, horizontal ? 'H' : 'V')) {
                    std::cout << "Invalid placement. Please try again." << std::endl;
                    continue;
                }

                // Try to play the word
                if (player.play_word(board, word, row, col, horizontal)) {
                    // Remove used letters from rack
                    for (char c : word) {
                        player.rack.remove_letter(c);
                    }
                    player.rack.fill_rack(bag);

                    // Bingo bonus
                    if (word.length() == 7) {
                        player.add_points(50);
                        std::cout << "Bingo! 50 bonus points added!" << std::endl;
                    }

                    // Print scores after a successful turn
                    print_scores();

                    valid_turn = true;
                    pass_count = 0;

                    // Check for game over condition
                    if (player.get_rack().get_tile_count() == 0 && bag.is_empty()) {
                        game_over = true;
                        break;
                    }
                } else {
                    std::cout << "Failed to place word. Try again.\n";
                }
            }

            if (game_over) break;
        }
    }

    std::cout << "Announcing the winner..." << std::endl;
    announce_winner();
}

// Utility function to trim whitespace from both ends of a string
static std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

 // Checks if the word is part of the dictionary
bool Game::dictionaryCheck(const std::string& word) {
    std::ifstream input_file("words");
    if (input_file.fail()) {
        throw std::ios_base::failure("Cannot open dictionary file.");
    }
    while (!input_file.eof()) {
        std::string word_check;
        std::getline(input_file, word_check);
        if (word == word_check) {
            return true;
        }
    }
    return false;
}


// Added definitions for is_valid_word and announce_winner becuse they didn't exist apparently.
bool Game::is_valid_word(const std::string& word) {
    // Placeholder implementation: Assume all words are valid
    return !word.empty();
}

void Game::announce_winner() {
    // Placeholder implementation: Announce the first player as the winner
    if (!players.empty()) {
        std::cout << "The winner is " << players[0].get_name() << "!" << std::endl;
    }
}

// Updated is_game_over. 
bool Game::is_game_over() const {
    std::cout << "Checking if the game is over..." << std::endl;
    for (const auto& player : players) {
        std::cout << "Player " << player.get_name() << " has " << player.rack.get_tile_count() << " tiles in their rack." << std::endl;
    }
    std::cout << "LetterBag has " << bag.Bag.size() << " tiles remaining." << std::endl;

    for (const auto& player : players) {
        if (player.rack.get_tile_count() == 0 && bag.is_empty()) {
            std::cout << "Game over condition met: Player " << player.get_name() << " has an empty rack and the bag is empty." << std::endl;
            return true;
        }
    }
    return false; // Game continues otherwise
}

void Game::print_scores() const {
    std::cout << "Current Scores:" << std::endl;
    for (const auto& player : players) {
        std::cout << "Player " << player.get_order_number() << ": " << player.get_name() << " - " << player.get_points() << " points" << std::endl;
    }
}
