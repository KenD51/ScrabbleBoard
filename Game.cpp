// Game.cpp
#include "scrabble.h"     // Include the header file that defines all the classes and methods used
#include <algorithm>      // For std::sort to sort players based on the drawn tiles
#include <iostream>       // For input and output, e.g., displaying prompts and results
#include <fstream>        // For file handling (e.g., saving/loading game state)
#include <unordered_set>  // For efficient duplicate detection
#include <cctype>         // For character operations like checking letter cases
#include <climits>        // For using INT_MIN (minimum integer value)

// Constructor for the Game class. It initializes the number of players, player names,
// determines the turn order, and fills each player's rack with tiles from the letter bag.
Game::Game() : pass_count(0) {
    // Ask the user for the number of players (between 2 and 4 players are allowed)
    std::cout << "How many players are going to be in the game? (2-4): ";
    std::cin >> playerNum;

    // Ensure the number of players is between 2 and 4, if not, prompt the user again
    while (playerNum < 2 || playerNum > 4) {
        std::cout << "Invalid number. Please enter between 2 and 4: ";
        std::cin >> playerNum;
    }
    
    // Loop through each player and get their name. Create Player objects and set their names.
    for (int i = 0; i < playerNum; ++i) {
        players.emplace_back();  // Add a new player to the players vector
        std::cout << "Enter name for player " << i + 1 << ": ";
        std::string name;
        std::cin >> name;  // Read player name
        players[i].set_name(name);  // Set the name of the player
    }

    // Call function to determine the turn order based on drawn tiles.
    determine_turn_order();
    
    // Fill each player's rack with tiles drawn from the bag
    for (auto& player : players) {
        player.get_rack().fill_rack(bag);
    }
}
// Determines the turn order of players by drawing unique tiles for each player
void Game::determine_turn_order() {
    bool unique_tiles = false;
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
                drawn_tiles.push_back('*');  // Use '' for a blank tile if the bag is empty
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
        if (a.get_rack()[0].get_letter() == '*') return true;  // Blank tile goes first
        if (b.get_rack()[0].get_letter() == '*') return false; // Blank tile goes first
        return a.get_rack()[0].get_letter() < b.get_rack()[0].get_letter();  // Sort based on A-Z order
    });
}

// Computes the final score of a player by subtracting the points of remaining tiles in their rack.
// It takes the LetterRack of the player as input and returns the computed score after subtracting tile points.
int Game::rack_points(const LetterRack& rack) {
    int total_tile_points = 0;  // Initialize variable to accumulate the total points of remaining tiles

    // Loop through each tile in the rack to sum up their points
    for (int i = 0; i < rack.get_tile_count(); i++) {
        total_tile_points += rack[i].get_point_value();  // Add the point value of the tile to total
    }

    // Return the total points of remaining tiles in the player's rack
    return total_tile_points;
}

// Determines the winner(s) of the game based on their final scores and displays the results.
void Game::determine_winner(Game& scrabble) {
    std::vector<std::string> winners;    // Vector to hold the names of the winners
    int highest_score = INT_MIN;         // Initialize the highest score to the smallest possible integer value

    // Loop through each player to calculate their final score
    for (auto& player : scrabble.players) {
        // Compute the player's final score: their total points minus the points of remaining tiles in their rack
        int final_score = player.get_points() - rack_points(player.get_rack());
         print_scores();

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
    std::cout << "\n=== Game Over ===" << std::endl;
    
    // Print each player's name along with their final score
    for (auto& player : scrabble.players) {
        int final_score = player.get_points() - rack_points(player.get_rack());
        std::cout << player.get_name() << ": " << final_score << " points" << std::endl;
    }

    // Announce the winner(s)
    std::cout << "\nWinner(s): ";
    for (const auto& winner : winners) {
        std::cout << winner << " ";   // Print all players with the highest score
    }
    std::cout << std::endl;  // Print newline at the end of the winner list
}

// Main game loop that controls the flow of the game, prompting players for actions and checking conditions.
void Game::play_game() {

    bool game_over = false;

    // Continue the game as long as it is not over
    while (!game_over) {
        for (auto& player : players) {
            // Display the player's rack of tiles
            player.get_rack().print_rack();
            
            print_scores();
            
            // Prompt the player for a word to play
            std::string word;
            std::cout << player.get_name() << ", it's your turn! Enter a word to play: ";
            std::cin >> word;
            
            // Prompt the player for the location they want to place the word
            int row, col;
            char direction;
            std::cout << "Enter the row, col, and direction of word placement: ";
            std::cin >> row >> col >> direction;
            
            // Check if the word entered by the player is valid (implementation needed)
            if (dictionaryCheck(word)) {
                // If the word is valid, play the word on the board and update the player's score
                player.play_word(board, word, row, col, direction);
                // Check if the rack and bag are empty (one of the game-over conditions)
                if (player.get_rack().get_tile_count() == 0 && bag.is_empty()) {
                    game_over = true;
                } else {
                    player.get_rack().fill_rack(bag);
                    pass_count = 0;
                }
            
                // Check if the player passed their turn or played a valid word
                if (word.empty()) {
                    pass_count++;  // Increase pass count if no word was played
                    // End the game if there are 6 consecutive passes
                    if (pass_count >= 6) {
                        game_over = true;  // End the game after 6 passes in a row
                    }
                }
            } else {
                std::cout << "Invalid word. Try again." << std::endl;
            }
        }
    }
    determine_winner(*this);
    return;
}

// Function to print the scores of all players
void Game::print_scores() const {
    std::cout << "Current Scores:" << std::endl;
    for (const auto& player : players) {
        std::cout << "Player " << player.get_order_number() << ": " << player.get_name() << " - " << player.get_points() << " points" << std::endl;
    }
}
