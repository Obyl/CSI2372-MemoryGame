/*
* Header file for the Card class.
* Also includes the FaceAnimal and FaceBackground enums.
*/

#pragma once

#include <assert.h>
#include <string>

enum FaceAnimal { Crab, Penguin, Octopus, Turtle, Walrus };
enum FaceBackground { Red, Green, Blue, Purple, Yellow };

// Static const variables used for printing 
static const int N_ROWS = 3;
static const std::string COLOR_LETTERS = "rgbpy";
static const std::string ANIMAL_LETTERS = "CPOTW";

class Card {
public:
	FaceAnimal faceAnimal;
	FaceBackground faceBackground;
	Card(FaceAnimal, FaceBackground);
	int getNRows();
	std::string operator() (int row);
	operator FaceAnimal() const;
	operator FaceBackground() const;
};