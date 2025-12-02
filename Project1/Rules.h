#pragma once

#include "Game.h"

class Rules {
private:
	bool expertDisplayMode;
	bool expertRulesMode;
	int currentPlayer;
public:
	Rules(bool, bool);
	bool isValid(const Game&);
	bool gameOver(const Game&);
	bool roundOver(const Game&);
	const Player& getNextPlayer(const Game&);
	void resetCurrentPlayer();
	bool isExpertDisplayMode();
};