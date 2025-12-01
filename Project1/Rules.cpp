#include "Rules.h"

Rules::Rules(bool expertDisplayMode, bool expertRulesMode) {
	this->expertDisplayMode = expertDisplayMode;
	this->expertRulesMode = expertRulesMode;

	currentPlayer = -1;
}

bool Rules::isValid(const Game& game) {
	return (game.getPreviousCard()->faceAnimal == game.getCurrentCard()->faceAnimal) ||
		(game.getPreviousCard()->faceBackground == game.getCurrentCard()->faceBackground);
}

bool Rules::gameOver(const Game& game) {
	return game.getRound() == 7;
}

bool Rules::roundOver(const Game& game) {
	/*int activePlayers = 0;
	for (Player& player : game.getPlayers()) {
		if (player.isActive())
			activePlayers++;
	}
	
	return activePlayers == 1; */
	return false;
}

const Player& Rules::getNextPlayer(const Game& game) {
	currentPlayer = (currentPlayer + 1) % game.getPlayers().size();
	return game.getPlayers()[currentPlayer];
}