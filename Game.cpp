// Game.cpp
#include "scrabble.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <cctype>

// Constructor: Sets up game with players
Game::Game() : pass_count(0) {
    // Get number of players (2-4)
    std::cout << "How many players are going to be in the game? (2-4): ";
    std::cin >> playerNum;
    while (playerNum < 2 || playerNum > 4) {
        std::cout << "Invalid number. Please enter between 2 and 4: ";
        std::cin >> playerNum;
    }
    
    // Initialize players with names
    for (int i = 0; i < playerNum; ++i) {
        players.emplace_back();
        std::cout << "Enter name for player " << i+1 << ": ";
        std::string name;
        std::cin >> name;
        players[i].set_name(name);
    }
    
    // Determine turn order
    determine_turn_order();
    
    // Fill each player's rack
    for (auto& player : players) {
        player.rack.fill_rack(bag);
    }
}

// Determines player order based on drawn tiles
void Game::determine_turn_order() {
    bool unique_tiles = false;
    std::vector<char> drawn_tiles;
    
    // Keep drawing until all players have unique tiles
    while (!unique_tiles) {
        drawn_tiles.clear();
        
        // Each player draws one tile
        for (auto& player : players) {
            if (!bag.is_empty()) {
                LetterTile tile = bag.draw_tile();
                drawn_tiles.push_back(tile.get_letter());
            } else {
                drawn_tiles.push_back('*'); // Use blank if bag is empty
            }
        }
        
        // Check for duplicates
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
        
        // Return tiles if duplicates found
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
        if (a.rack[0].get_letter() == '*') return true; // Blank first
        if (b.rack[0].get_letter() == '*') return false;
        return a.rack[0].get_letter() < b.rack[0].get_letter(); // A-Z order
    });
}

// Main game loop
void Game::play_game() {
    // ... (implementation as previously shown)
}

