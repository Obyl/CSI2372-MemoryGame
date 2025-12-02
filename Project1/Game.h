#pragma once

#include <ostream>
#include <vector>
#include "Board.h"
#include "Player.h"
#include "CardDeck.h"

class Game {
private:

	CardDeck* deck_ptr;
	Card *previousCard, *currentCard;
	int round;
	Board* board;
	std::vector<Player> players;

public:

	Game();
	~Game();
	void incrementRound();
	void resetStartOfRound();
	int getRound() const;
	void addPlayer(const Player&);
	void deactivatePlayer(Side);
	Player& getPlayer(Side);
	const Card* getPreviousCard() const;
	const Card* getCurrentCard() const;
	void setCurrentCard(const Card*);
	Card* getCard(const Letter&, const Number&);
	void setCard(const Letter&, const Number&, Card*);
	friend std::ostream& operator<<(std::ostream&, Game&);
	std::vector<Player>& getPlayers();
	const std::vector<Player>& getPlayers() const;
	Board* getBoard();
	CardDeck* getDeckPtr();
};