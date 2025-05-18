// EndGame.cpp
#include "scrabble.h"    // Include the header file containing necessary class and function declarations
#include <climits>        // For using INT_MIN (minimum integer value)
#include <iostream>       // For input/output operations

// Computes the final score of a player by subtracting the points of remaining tiles in their rack.
// It takes the LetterRack of the player as input and returns the computed score after subtracting tile points.
int compute_final_score(const LetterRack& rack) {
    int total_tile_points = 0;  // Initialize variable to accumulate the total points of remaining tiles

    // Loop through each tile in the rack to sum up their points
    for (int i = 0; i < rack.SIZE; i++) {
        total_tile_points += rack[i].get_point_value();  // Add the point value of the tile to total
    }

    // Return the total points of remaining tiles in the player's rack
    return total_tile_points;
}
// Determines the winner(s) of the game based on their final scores and displays the results.
void announce_winner(const std::vector<Player>& players) {
    std::vector<std::string> winners;    // Vector to hold the names of the winners
    int highest_score = INT_MIN;         // Initialize the highest score to the smallest possible integer value

    // Loop through each player to calculate their final score
    for (const auto& player : players) {
        // Compute the player's final score: their total points minus the points of remaining tiles in their rack
        int final_score = player.get_points() - compute_final_score(player.rack);

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
    for (const auto& player : players) {
        int final_score = player.get_points() - compute_final_score(player.rack);
        std::cout << player.get_name() << ": " << final_score << " points" << std::endl;
    }

    // Announce the winner(s)
    std::cout << "\nWinner(s): ";
    for (const auto& winner : winners) {
        std::cout << winner << " ";   // Print all players with the highest score
    }
    std::cout << std::endl;  // Print newline at the end of the winner list
}

// Function to handle the end of the game
void end_game(Game& game) {
    // Compute final scores and determine winners
    announce_winner(game.players);

    // Additional end game procedures can be added here
}
