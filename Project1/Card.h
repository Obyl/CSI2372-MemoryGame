#pragma once

#include <string>

enum FaceAnimal { Crab, Penguin, Octopus, Turtle, Walrus };
enum FaceBackground { Red, Green, Blue, Purple, Yellow };

class Card {
private:
	Card(FaceAnimal, FaceBackground);
public:
	int getNRows();
	std::string operator() ();
};