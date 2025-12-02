#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "Card.h"

enum Letter { A, B, C, D, E, };
enum Number { one, two, three, four, five};

const std::string letters = "ABCDE";
const std::string numbers = "12345";

class Board {
private:

	bool isExpertDisplay = false;
	Card* cards[5][5] = {nullptr};
	bool face_up_flags[5][5] = {0};
	std::vector< Card*> unflippedCardsSequence;

public:
	bool isFaceUp(const Letter&, const Number&) const;
	bool turnFaceUp(const Letter&, const Number&);
	bool turnFaceDown(const Letter&, const Number&);
	Card* getCard(const Letter&, const Number&);
	void setCard(const Letter&, const Number&, Card*);
	void allFacesDown();
	friend std::ostream& operator<<(std::ostream&, Board&);
	friend std::ostream& nonExpertDisplay(std::ostream& os, Board& board);
	friend std::ostream& expertDisplay(std::ostream& os, Board& board);
	void setExpertDisplay(bool value);
	
};