// Game.cpp
#include "scrabble.h"     // Include the header file that defines all the classes and methods used
#include <algorithm>      // For std::sort to sort players based on the drawn tiles
#include <iostream>       // For input and output, e.g., displaying prompts and results
#include <fstream>        // For file handling (e.g., saving/loading game state)
#include <unordered_set>  // For efficient duplicate detection
#include <cctype>         // For character operations like checking letter cases

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
        player.rack.fill_rack(bag);
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
                drawn_tiles.push_back('');  // Use '' for a blank tile if the bag is empty
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
        if (a.rack[0].get_letter() == '*') return true;  // Blank tile goes first
        if (b.rack[0].get_letter() == '*') return false; // Blank tile goes first
        return a.rack[0].get_letter() < b.rack[0].get_letter();  // Sort based on A-Z order
    });
}
// Main game loop that controls the flow of the game, prompting players for actions and checking conditions.
void Game::play_game() {
    bool game_over = false;

    // Continue the game as long as it is not over
    while (!game_over) {
        for (auto& player : players) {
            // Display the player's rack of tiles
            player.rack.print_rack();
            
            // Prompt the player for a word to play
            std::string word;
            std::cout << player.get_name() << ", it's your turn! Enter a word to play: ";
            std::cin >> word;

            // Check if the word entered by the player is valid (implementation needed)
            if (is_valid_word(word)) {
                // If the word is valid, play the word on the board and update the player's score
                player.play_word(board, word);
                player.rack.fill_rack(bag);
                pass_count = 0;
                
                // Check if the player passed their turn or played a valid word
                if (word.empty()) {
                    pass_count++;  // Increase pass count if no word was played
                    // End the game if there are 6 consecutive passes
                    if (pass_count >= 6) {
                        game_over = true;  // End the game after 6 passes
                    }
                }
            } else {
                std::cout << "Invalid word. Try again." << std::endl;
            }

            // Check if the game is over (additional game-over condition implementation needed)
            if (is_game_over()) {
                game_over = true;
            }
        }
    }

    // Announce the winner after the game is over (additional logic needed)
    announce_winner();
}
