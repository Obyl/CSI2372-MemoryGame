#pragma once

#include <ostream>
#include <vector>
#include "Board.h"
#include "Player.h"
#include "CardDeck.h"

class Game {
private:

	CardDeck* deck_ptr;
	int round;
	Board board;
	std::vector<Player> players;

public:

	Game();
	int getRound();
	void addPlayer(const Player&);
	Player& getPlayer(Side);
	const Card* getPreviousCard();
	const Card* getCurrentCard();
	void setCurrentCard(const Card*);
	Card* getCard(const Letter&, const Number&);
	void setCard(const Letter&, const Number&, Card*);
	friend std::ostream& operator<<(std::ostream&, Game&);
};