#include "Game.h"

Game::Game()
{
	round = 0;
	deck_ptr = &CardDeck::make_CardDeck();
}

void Game::addPlayer(const Player& player) {
	players.push_back(player);
}

std::ostream& operator<<(std::ostream& os, Game& game) {
	os << "pls";

	return os;
}

int Game::getRound()
{
	return round;
}

Player& Game::getPlayer(Side side)
{
	for (Player& player : players)
	{
		if (player.getSide() == side)
		{
			return player;
		}
	}
	
	throw std::runtime_error("Error, player not found");
}

// const Card* Game::getPreviousCard()
// {
	
// }

