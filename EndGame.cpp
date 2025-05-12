#include<"Endgame.h">
#include <climits>
#include <iostream>

// Calculates final score by subtracting remaining tile points
int EndGame::compute_final_score(LetterRack& rack) {
    int total_tile_points = 0;
    for (int i = 0; i < rack.SIZE; i++) {
        total_tile_points += rack[i].get_point_value();
    }
    return total_tile_points;
}

// Determines and displays the winner(s)
void EndGame::determine_winner(Game& scrabble) {
    std::vector<std::string> winners;
    int highest_score = INT_MIN;
    
    // Calculate each player's final score
    for (auto& player : scrabble.players) {
        int final_score = player.get_points() - compute_final_score(player.rack);
        
        // Track highest score and winners
        if (final_score > highest_score) {
            highest_score = final_score;
            winners.clear();
            winners.push_back(player.get_name());
        } else if (final_score == highest_score) {
            winners.push_back(player.get_name());
        }
    }
    
    // Display results
    std::cout << "\n=== Game Over ===" << std::endl;
    for (auto& player : scrabble.players) {
        int final_score = player.get_points() - compute_final_score(player.rack);
        std::cout << player.get_name() << ": " << final_score << " points" << std::endl;
    }
    
    // Announce winner(s)
    std::cout << "\nWinner(s): ";
    for (const auto& winner : winners) {
        std::cout << winner << " ";
    }
    std::cout << std::endl;
}



