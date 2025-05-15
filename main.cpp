// main.cpp
// Group 1
// CS 116
// Spring 2025

#include "scrabble.h" // Include the header file that defines all the classes and methods used
#include <iostream>   // For input and output operations
#include <stdexcept>  // For exception handling
#include <limits>     // For std::numeric_limits

int main() {
    try {
        // Display a welcome message and game rules
        std::cout << "========================================\n";
        std::cout << "         WELCOME TO SCRABBLE!\n";
        std::cout << "========================================\n";
        std::cout << "Game Rules:\n";
        std::cout << "1. First word must cover the center tile (H8)\n";
        std::cout << "2. Subsequent words must connect to existing words\n";
        std::cout << "3. Blank tiles (*) can represent any letter\n";
        std::cout << "4. Using all 7 tiles earns a 50-point bonus\n";
        std::cout << "5. '?' are blank tiles that can represent any letter\n";
        std::cout << "6. Game ends when:\n";
        std::cout << "   - A player uses all tiles and the bag is empty\n";
        std::cout << "   - Six consecutive passes occur\n";
        std::cout << "========================================\n\n";

        int num_players;
        // Loop to get a valid number of players (2-4) from the user
        do {
            std::cin.clear(); // Clear any error flags from previous input attempts
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard any invalid input left in the buffer
            std::cout << "Enter the number of players (2-4): ";
            std::cin >> num_players;

            // Check if the input was valid and within the allowed range
            if (std::cin.fail() || num_players < 2 || num_players > 4) {
                std::cout << "Invalid input. Please enter a number between 2 and 4." << std::endl;
            }
        } while (std::cin.fail() || num_players < 2 || num_players > 4);

        // Create a Game object with the specified number of players
        Game scrabbleGame(num_players);
        // Start the main game loop
        scrabbleGame.play_game();

        // Display a thank you message at the end of the game
        std::cout << "\n========================================\n";
        std::cout << "   THANK YOU FOR PLAYING SCRABBLE!\n";
        std::cout << "========================================\n";

        return 0; // Indicate successful program execution
    }
    // Catch any standard exceptions that might occur during game execution
    catch (const std::exception& e) {
        std::cerr << "\nERROR: " << e.what() << std::endl;
        std::cerr << "An exception occurred during the game initialization or execution." << std::endl;
        std::cerr << "Exception message: " << e.what() << std::endl;
        std::cerr << "The game has ended unexpectedly.\n";
        return 1; // Indicate program execution with an error
    }
    // Catch any other unexpected exceptions
    catch (...) {
        std::cerr << "\nUNKNOWN ERROR: The game has crashed.\n";
        return 2; // Indicate program execution with an unknown error
    }
}
