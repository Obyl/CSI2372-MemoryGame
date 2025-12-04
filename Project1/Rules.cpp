/*
* Implementation of the Rules class.
*/

#include "Rules.h"

// Constructor
Rules::Rules(bool expertDisplayMode, bool expertRulesMode) {
	this->expertDisplayMode = expertDisplayMode;
	this->expertRulesMode = expertRulesMode;

	mustPlayAgain = false;

	currentPlayer = -1;
}

// Check if the last move was valid
bool Rules::isValid(const Game& game) {
	if (game.getPreviousCard() == nullptr)
		return true;

	return (game.getPreviousCard()->faceAnimal == game.getCurrentCard()->faceAnimal) ||
		(game.getPreviousCard()->faceBackground == game.getCurrentCard()->faceBackground);
}

// Setter for mustPlayAgain
void Rules::setMustPlayAgain(bool value)
{
	mustPlayAgain = value;
}

// Check if the game is over
bool Rules::gameOver(const Game& game) {
	return game.getRound() > 6;
}

// Getter for expertDisplayMode
bool Rules::isExpertDisplayMode()
{
	return expertDisplayMode;
}

// Getter for expertRulesMode
bool Rules::isExpertRulesMode()
{
	return expertRulesMode;
}

// Reset tracker for current player
void Rules::resetCurrentPlayer()
{
	currentPlayer = -1;
}

// Check if the round is over
bool Rules::roundOver(const Game& game) {
	// Count # of active players
	int activePlayers = 0;
	for (const Player& player : game.getPlayers())
		if (player.isActive())
			activePlayers++;

	return activePlayers == 1;
}

// Get next player
const Player& Rules::getNextPlayer(const Game& game) {
	// Check if the current player must play again
	if (mustPlayAgain) 
		return game.getPlayers()[currentPlayer];

	// Find next active player
	do {
		currentPlayer = (currentPlayer + 1) % game.getPlayers().size();
	} while (!game.getPlayers()[currentPlayer].isActive());

	return game.getPlayers()[currentPlayer];
}