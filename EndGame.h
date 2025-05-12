//Adding endgame.h as this is also missing
#ifndef ENDGAME_H
#define ENDGAME_H

#include "Game.h"

class EndGame {
public:
    EndGame();  // Constructor
    void showResults(const Game& game);  // Display results at the end of the game
    void displayWinner(const Game& game);  // Display the winner of the game
    void displayScores(const Game& game);  // Display all players' scores
};

#endif  // ENDGAME_H
