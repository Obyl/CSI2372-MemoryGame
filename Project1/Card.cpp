#include "Card.h"

Card::Card(FaceAnimal faceAnimal, FaceBackground faceBackground)
{
    this->faceAnimal = faceAnimal;
    this->faceBackground = faceBackground;
}

int Card::getNRows()
{
    return 3;
}

std::string Card::operator()(int row)
{
    assert(row >= 0 && row < 3);

    std::string colors = "rgbpy";
    std::string animals = "CPOTW";
    
    if (row == 0 || row == 2)
    {
        return std::string(3, colors[faceBackground]);
    }
    else
    {
        return std::string(1, colors[faceBackground]) + 
            std::string(1, animals[faceAnimal]) + 
            std::string(1, colors[faceBackground]);
    }
}