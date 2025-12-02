#include "Rules.h"

Rules::Rules(bool expertDisplayMode, bool expertRulesMode) {
	this->expertDisplayMode = expertDisplayMode;
	this->expertRulesMode = expertRulesMode;

	currentPlayer = -1;
}

bool Rules::isValid(const Game& game) {
	if (game.getPreviousCard() == nullptr) {
		return true;
	}

	std::cout << ((game.getPreviousCard()->faceAnimal == game.getCurrentCard()->faceAnimal) ||
		(game.getPreviousCard()->faceBackground == game.getCurrentCard()->faceBackground)) << std::endl;

	return (game.getPreviousCard()->faceAnimal == game.getCurrentCard()->faceAnimal) ||
		(game.getPreviousCard()->faceBackground == game.getCurrentCard()->faceBackground);
}

bool Rules::gameOver(const Game& game) {
	return game.getRound() == 7;
}

bool Rules::roundOver(const Game& game) {
	int activePlayers = 0;
	for (const Player& player : game.getPlayers()) {
		if (player.isActive())
			activePlayers++;
	}
	
	return activePlayers == 1;
}

const Player& Rules::getNextPlayer(const Game& game) {
	do {
		currentPlayer = (currentPlayer + 1) % game.getPlayers().size();
	} while (!game.getPlayers()[currentPlayer].isActive());

	return game.getPlayers()[currentPlayer];
}