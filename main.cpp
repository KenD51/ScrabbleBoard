// main.cpp 
// Group 1
// CS 116
// Spring 2025

#include "scrabble.h"
#include <iostream>
#include <stdexcept>

int main() {
    try {
        std::cout << "========================================\n";
        std::cout << "       WELCOME TO SCRABBLE!\n";
        std::cout << "========================================\n";
        std::cout << "Game Rules:\n";
        std::cout << "1. First word must cover the center tile (H8)\n";
        std::cout << "2. Subsequent words must connect to existing words\n";
        std::cout << "3. Blank tiles (*) can represent any letter\n";
        std::cout << "4. Using all 7 tiles earns a 50-point bonus\n";
        std::cout << "5. Game ends when:\n";
        std::cout << "   - A player uses all tiles and the bag is empty\n";
        std::cout << "   - Six consecutive passes occur\n";
        std::cout << "========================================\n\n";

        Game scrabbleGame;
        scrabbleGame.play_game();
        
        std::cout << "\n========================================\n";
        std::cout << "   THANK YOU FOR PLAYING SCRABBLE!\n";
        std::cout << "========================================\n";
        
        return 0;
    } 
    catch (const std::exception& e) {
        std::cerr << "\nERROR: " << e.what() << std::endl;
        std::cerr << "The game has ended unexpectedly.\n";
        return 1;
    }
    catch (...) {
        std::cerr << "\nUNKNOWN ERROR: The game has crashed.\n";
        return 2;
    }
}
