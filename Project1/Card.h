#pragma once

#include <assert.h>
#include <string>

enum FaceAnimal { Crab, Penguin, Octopus, Turtle, Walrus };
enum FaceBackground { Red, Green, Blue, Purple, Yellow };

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