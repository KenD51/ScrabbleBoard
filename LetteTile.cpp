LetterTile.cpp
#include "LetterTile.h"

// Constructor: Initializes a letter tile with given letter and point value
LetterTile::LetterTile(char the_letter, int the_value) 
    : letter(the_letter), point_value(the_value) {}

// Returns the letter on this tile
char LetterTile::get_letter() const {
    return letter;
}

// Returns the point value of this tile
int LetterTile::get_point_value() const {
    return point_value;
}

