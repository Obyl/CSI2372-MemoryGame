#include "Game.h"

Game::Game()
{

	currentCard = nullptr;
	previousCard = nullptr;

	round = 1;
	deck_ptr = &CardDeck::make_CardDeck();
	board = new Board();
}

Game::~Game() {
	delete deck_ptr;
	delete board;

	delete currentCard;
	delete previousCard;

}

void Game::resetStartOfRound()
{
	currentCard = nullptr;
	previousCard = nullptr;

	for (Player& player : players)
	{
		player.setActive(true);
	}

}

void Game::addPlayer(const Player& player) {
	players.push_back(player);
}

std::ostream& operator<<(std::ostream& os, Game& game) {
	os << std::endl;

	for (Player& player : game.players) {
		os << player << std::endl;
	}

	os << std::endl;
	os << *(game.board);

	return os;
}

void Game::incrementRound() 
{
	round++;
}

int Game::getRound() const
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

const Card* Game::getPreviousCard() const
{
	return previousCard;
}

const Card* Game::getCurrentCard() const
{
	return currentCard;
}

void Game::setCurrentCard(const Card* card) 
{
	if (currentCard != nullptr) {

		delete previousCard;
		previousCard = new Card(*currentCard, *currentCard);
	}

	delete currentCard;
	currentCard = new Card(*card, *card);
}

Card* Game::getCard(const Letter& letter, const Number& number) 
{
	return board->getCard(letter, number);
}

void Game::setCard(const Letter& letter, const Number& number, Card* card) 
{
	board->setCard(letter, number, card);
}

void Game::deactivatePlayer(Side side)
{
	Player& playerToDeactivate = getPlayer(side);
	playerToDeactivate.setActive(false);

}

std::vector<Player>& Game::getPlayers() {
	return players;
}

const std::vector<Player>& Game::getPlayers() const {
	return players;
}

Board* Game::getBoard() {
	return board;
}

CardDeck* Game::getDeckPtr() {
	return deck_ptr;
}