# Scrabble Game (C++)

A simplified command-line version of Scrabble implemented in C++ as a project for Ohlone College.

## Group Members
- Kenshin Drona
- Shanni Lian
- Le Hoang Anh Nguyen
- Nicole Wu
- Naga Harini Yadavalli

## Compiler
Clang (Any C++ Compiler Should work)

## Project Structure
- `main.cpp` - Entry point of the game
- `Game.cpp/.h` - Handles main game logic and turn-based control
- `GameBoard.cpp/.h` - Represents the Scrabble board
- `Player.cpp/.h` - Player logic and score tracking
- `LetterBag.cpp/.h` - Manages the bag of tiles
- `LetterRack.cpp/.h` - Each player's letter rack
- `LetterTile.cpp/.h` - Individual letter tile representation

## Compilation Instructions

1. Create a new folder called "Scrabble Project"
2. Download our zip folder called "scrabble.zip"
3. Right-click the zipped file and extract all
   a. You should get a folder called "ScrabbleBoard-main" after extracting 
5. Open the Clang terminal
6. Change the directory to wherever you chose to store the "ScrabbleBoard-main" folder
   a. Typing ls shows you the contents of your current directory
   b. Typing pwd shows you where you are
   c. Typing cd ______ changes your directory to the one you specificed.
7. Compile by typing: c++ -o play main.cpp Player.cpp Game.cpp GameBoard.cpp LetterBag.cpp LetterRack.cpp LetterTile.cpp
8. Run the executable by typing: ./play
9. Read the scrabble instructions printed out to the screen.
10. Start playing the game by pressing enter.

## Disclaimer
This project is for educational purposes only. Redistribution of this code for academic credit or without permission from all group members is prohibited.
