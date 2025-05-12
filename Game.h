//We lack game.h so I created one


#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"
#include "ScrabbleBoard.h"

class Game {
private:
    std::vector<Player> players;  // A list of players in the game
    ScrabbleBoard board;          // The game board
    int currentPlayerIndex;       // Index of the current player

public:
    Game();
    void addPlayer(const Player& player);   // Add a player to the game
    void startGame();                      // Start the game
    void nextTurn();                       // Move to the next player's turn
    void playWord(const std::string& word);  // Play a word on the board
    void endGame();                        // End the game
    void displayBoard();                   // Display the current state of the board
    void displayPlayers();                 // Display players' scores and other info
};

#endif  // GAME_H
