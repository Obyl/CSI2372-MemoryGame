#pragma once

#include <string>
#include <ostream>
#include "Card.h"

enum Letter { A, B, C, D, E, };
enum Number { one, two, three, four, five};

class Board {
private:

	Card* cards[5][5] = {nullptr};
	bool face_up_flags[5][5] = {0};

public:
	bool isFaceUp(const Letter&, const Number&) const;
	bool turnFaceUp(const Letter&, const Number&);
	bool turnFaceDown(const Letter&, const Number&);
	Card* getCard(const Letter&, const Number&);
	void setCard(const Letter&, const Number&, Card*);
	void allFacesDown();
	friend std::ostream& operator<<(std::ostream&, Board&);
};