/*
* Implementation of the Card class.
*/

#include "Card.h"

// Constructor
Card::Card(FaceAnimal faceAnimal, FaceBackground faceBackground)
{
    this->faceAnimal = faceAnimal;
    this->faceBackground = faceBackground;
}

// Return # of rows in card for printing (constant)
int Card::getNRows()
{
    return N_ROWS;
}

// Return row for printing when invoked with obj(row)
std::string Card::operator()(int row)
{   
    // For first and last rows, return 3 color letters
    if (row == 0 || row == 2)
    {
        return std::string(3, COLOR_LETTERS[faceBackground]);
    }
    // For middle row, return color letters with animal letter in between
    else
    {
        return std::string(1, COLOR_LETTERS[faceBackground]) +
            std::string(1, ANIMAL_LETTERS[faceAnimal]) + 
            std::string(1, COLOR_LETTERS[faceBackground]);
    }
}

// Conversion operator to FaceAnimal
Card::operator FaceAnimal() const
{
    return faceAnimal;
}

// Conversion operator to FaceBackground
Card::operator FaceBackground() const
{
    return faceBackground;
}