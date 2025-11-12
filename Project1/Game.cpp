#include "Game.h"

void Game::addPlayer(const Player& player) {
	players.push_back(player);
}

std::ostream& operator<<(std::ostream& os, Game& game) {
	os << "pls";

	return os;
}