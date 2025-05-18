//I added a lot of debugging output as there was a lot of things to test.
#include "scrabble.h"     // Include the header file that defines all the classes and methods used
#include <algorithm>      // For std::sort to sort players based on the drawn tiles
#include <iostream>       // For input and output, e.g., displaying prompts and results
#include <fstream>        // For file handling (e.g., saving/loading game state)
#include <unordered_set>  // For efficient duplicate detection. I don't know how this is used.
#include <cctype>         // For character operations like checking letter cases
#include <sstream>       
#include <string>         // For string operations
#include <cstring>        // For handling C-style strings
#include <climits>
#include <limits>
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

// Returns the number of consecutive passes
int Game::get_pass_count() const { 
    return pass_count;
}

// Determines the turn order of players by drawing unique tiles for each player. This is an incorrect way to do it, but it works for now.
void Game::determine_turn_order() {
    bool unique_tiles = false;
    std::cout << "Determining turn order..." << std::endl;
    std::vector<char> drawn_tiles;

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

    // Sort players based on their drawn tiles (not rack)
    std::vector<std::pair<char, int>> tile_indices;
    for (size_t i = 0; i < drawn_tiles.size(); ++i) {
        tile_indices.emplace_back(drawn_tiles[i], i);
    }
    std::sort(tile_indices.begin(), tile_indices.end(), [](const auto& a, const auto& b) {
        if (a.first == '*') return true;
        if (b.first == '*') return false;
        return a.first < b.first;
    });
    std::vector<Player> sorted_players;
    for (const auto& ti : tile_indices) {
        sorted_players.push_back(players[ti.second]);
    }
    players = sorted_players;
}


void Game::play_game() {
    bool game_over = false;
    while (!game_over) {
        for (int i = 0; i < players.size() && !game_over; i++) {
            bool valid_turn = false;
            while (!valid_turn) {
                if (is_game_over()) {
                    game_over = true;
                    break;
                }
                std::cout << "\n======= " << players[i].get_name() << "'s turn =======" << std::endl;
                players[i].rack.print_rack();

                std::cout << std::endl << "Pass Count: " << get_pass_count() << std::endl;
    
                print_scores();

                std::cout << "\nCurrent Board State:" << std::endl;
                board.printBoard();

                // Let the player pick what they want to do
                int selection;
                if (get_pass_count() < 6 && !is_game_over()) {
                    std::cout << "\nWhat move would you like to make:\n" << "    1) Play a word      2) Pass      3) Exchange Tiles" << std::endl;
                    std::cout << "Please enter your number selection (1, 2, or 3): ";
                    std::cin >> selection;

                    // Dealing with errors in entering selection number
                    while (selection != 1 && selection != 2 && selection != 3) {
                        // Clear input
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid number selection. Please try again: ";
                        std::cin >> selection;
                    }

                // If end game conditions are met, the player gets an additional selection to end the game
                } else if (get_pass_count() >= 6 || is_game_over()) {
                    std::cout << "What move would you like to make:\n" << "    1) Play a word      2) Pass      3) Exchange Tiles      4) End Game" << std::endl;
                    std::cout << "Enter your number selection (1, 2, 3, or 4): ";
                    std::cin >> selection;

                    // Dealing with errors in entering selection number
                    while (selection != 1 && selection != 2 && selection != 3 && selection != 4) {
                        // Clear input
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid number selection. Please try again: ";
                        std::cin >> selection;
                    }
                }
                if (selection == 4) {
                    game_over = true;
                }
                // Player chooses to play word
                switch (selection) {
                    case 1: {
                        std::string word;
                        int row, col;
                        char direction;
                        std::cout << "Enter word, row, column, and direction (H/V): ";
                        std::cin >> word >> row >> col >> direction;

                        // Convert word to uppercase for consistency
                        std::transform(word.begin(), word.end(), word.begin(), ::toupper);

                        // Dictionary check
                        if (!dictionaryCheck(word)) {
                            std::cout << "Word not found in dictionary. Try again." << std::endl;
                            // Clear the rest of the line to avoid input issues
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            continue;
                        }

                        // Clear the rest of the line to avoid leftover input
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        // Do NOT convert row and col to 0-based indices here! This is super important!!!!
                        // Pass user input (1-based) directly to isValidPlacement
                        bool horizontal = (direction == 'H' || direction == 'h');
                        if (!board.isValidPlacement(word, row, col, horizontal ? 'H' : 'V')) {
                            std::cout << "Invalid placement. Please try again." << std::endl;
                            continue;
                        }

                        // Do NOT convert row and col to 0-based indices here for play_word either!
                        // The play_word and GameBoard::placeWord logic expects 1-based indices for the first word.

                        // Try to play the word
                        players[i].play_word(board, word, row, col, horizontal ? 'H' : 'V');
                        // Remove used letters from rack is handled in play_word
                        players[i].rack.fill_rack(bag);

                        // Bingo bonus
                        if (word.length() == 7) {
                            players[i].add_points(50);
                            std::cout << "Bingo! 50 bonus points added!" << std::endl;
                        }

                        valid_turn = true;
                        pass_count = 0;
                        break;
                    }
                    case 2: {
                        // Player chooses to pass turn
                        valid_turn = true;
                        pass_count++;
                        break;
                    }
                    case 3: {
                        // Player chooses to exchange tiles
                        std::cout << "Please enter the number of tiles you want to exchange: ";
                        int n;
                        std::cin >> n;
                        
                        // Error handling
                        while (n < 1 || n > 7) {
                            std::cout << "Invalid input. The max is 7 tiles. Please try again: ";
                            // Clear input
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cin >> n;
                        }

                        std::cout << "Please enter the letter(s) for the tiles you want to exchange (no spaces between letters): ";
                        std::string exchange;
                        std::cin >> exchange;
                        
                        try {
                            for (int a = 0; a < exchange.length(); a++) {
                                bool found = false;
                                for (int b = 0; b < players[i].rack.get_tile_count() && !found; b++) {
                                    if (exchange[a] == players[i].rack[b].get_letter()) {
                                        found = true;
                                    }
                                }
                                if (!found) {
                                    throw std::invalid_argument("One of the letters is not part of your rack.");
                                }
                            }
                        } catch (const std::invalid_argument& err) {
                            std::cout << "Please try again: ";
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cin >> exchange;
                        }
                        
                        // Process of exchanging letters
                        for (int j = 0; j < exchange.length(); j++) {
                            char letter = exchange[j];
                            players[i].rack.exchange_tile(letter, bag);
                        }                            
                        valid_turn = true;
                        pass_count++;
                        break;
                    }
                    case 4: {
                        // Player chooses to end the game
                        std::cout << "Announcing the winner..." << std::endl;
                        determine_winner();
                        break;
                    }
                }
                // Give the player who just played an update
                if (selection != 4) {
                    std::cout << "\n------- UPDATES -------" << std::endl;
                    if (selection == 3) {
                        std::cout << "New Rack Below: " << std::endl;
                        std::cout << "    ";
                        players[i].rack.print_rack();
                    }
                    std::cout << "Pass Count: " << get_pass_count() << std::endl;
                    print_scores();
                    std::cout << std::endl;
                }
            }
        }
    }
}

// Utility function to trim whitespace from both ends of a string
static std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

 // Checks if the word is part of the dictionary
bool Game::dictionaryCheck(const std::string& word) {
    // Try both "words.txt" and "words" for compatibility
    std::ifstream input_file("words.txt");
    if (input_file.fail()) {
        input_file.clear();
        input_file.open("words");
    }
    if (input_file.fail()) {
        std::cerr << "[DEBUG] Cannot open 'words'." << std::endl;
        throw std::ios_base::failure("Cannot open dictionary file.");
    }
    std::string word_upper = word;
    std::transform(word_upper.begin(), word_upper.end(), word_upper.begin(), ::toupper);

    std::string word_check;
    while (std::getline(input_file, word_check)) {
        // Remove whitespace and convert to uppercase for comparison
        word_check.erase(word_check.find_last_not_of(" \n\r\t") + 1);
        std::transform(word_check.begin(), word_check.end(), word_check.begin(), ::toupper);
        if (word_upper == word_check) {
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

// Computes the final score of a player by subtracting the points of remaining tiles in their rack.
// It takes the LetterRack of the player as input and returns the computed score after subtracting tile points.
int Game::rack_points(LetterRack& rack) {
    int total_tile_points = 0;  // Initialize variable to accumulate the total points of remaining tiles

    // Loop through each tile in the rack to sum up their points
    for (int i = 0; i < rack.SIZE; i++) {
        total_tile_points += rack[i].get_point_value();  // Add the point value of the tile to total
    }

    // Return the total points of remaining tiles in the player's rack
    return total_tile_points;
}
// Determines the winner(s) of the game based on their final scores and displays the results.
void Game::determine_winner() {
    std::vector<std::string> winners;    // Vector to hold the names of the winners
    int highest_score = INT_MIN;         // Initialize the highest score to the smallest possible integer value

    // Loop through each player to calculate their final score
    for (auto& player : players) {
        // Compute the player's final score: their total points minus the points of remaining tiles in their rack
        int final_score = player.get_points() - rack_points(player.rack);

        // If the current player's final score is higher than the highest score so far, update the highest score
        // and clear the list of winners to only include the current player
        if (final_score > highest_score) {
            highest_score = final_score;
            winners.clear();        // Clear previous winners
            winners.push_back(player.get_name());  // Add the current player as the only winner
        } 
        // If the current player's final score equals the highest score, add them to the list of winners
        else if (final_score == highest_score) {
            winners.push_back(player.get_name());
        }
    }

    // Display the end game results
    std::cout << "\n====== Game Over ======" << std::endl;
    
    // Print each player's name along with their final score
    for (auto& player : players) {
        int final_score = player.get_points() - rack_points(player.rack);
        std::cout << player.get_name() << ": " << final_score << " points" << std::endl;
    }

    // Announce the winner(s)
    std::cout << "\nWinner(s): ";
    for (const auto& winner : winners) {
        std::cout << winner << " ";   // Print all players with the highest score
    }
    std::cout << std::endl;  // Print newline at the end of the winner list
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
        std::cout << player.get_name() << " - " << player.get_points() << " points" << std::endl;
    }
}
