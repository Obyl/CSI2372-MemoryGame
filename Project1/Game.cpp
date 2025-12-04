/*
* Implementation of the Game class.
*/

#include "Game.h"

// Constructor
Game::Game()
{
	currentCard = nullptr;
	previousCard = nullptr;

	round = -1;

	board = new Board(CardDeck::make_CardDeck());
}

// Destructor
Game::~Game() {
	delete board;

	delete currentCard;
	delete previousCard;
}

// Add player to player list
void Game::addPlayer(const Player& player) {
	players.push_back(player);
}

// Print game
std::ostream& operator<<(std::ostream& os, Game& game) {
	os << std::endl;

	// Print each player
	for (Player& player : game.players)
		os << player << std::endl;

	// Print board
	os << std::endl;
	os << *(game.board);

	return os;
}

// Get game ready for new round
void Game::newRound() 
{
	// Reset card tracking
	currentCard = nullptr;
	previousCard = nullptr;

	// Activate all players
	for (Player& player : players)
		player.setActive(true);

	// Increment round number
	round++;
}

// Get round number (0-6)
int Game::getRound() const
{
	return round;
}

// Get player on given side
Player& Game::getPlayer(Side side)
{
	for (Player& player : players)
		if (player.getSide() == side)
			return player;
	
	throw std::runtime_error("Error, player not found");
}

// Get previous card
const Card* Game::getPreviousCard() const
{
	return previousCard;
}

// Get current card
const Card* Game::getCurrentCard() const
{
	return currentCard;
}

// Set current card
void Game::setCurrentCard(const Card* card) 
{
	// Set previous card to current card
	if (currentCard != nullptr) {
		delete previousCard;
		previousCard = new Card(*currentCard, *currentCard);
	}

	// Update current card
	delete currentCard;
	currentCard = new Card(*card, *card);
}

// Get card at coordinate
Card* Game::getCard(const Letter& letter, const Number& number) 
{
	return board->getCard(letter, number);
}

// Set card at coordinate
void Game::setCard(const Letter& letter, const Number& number, Card* card) 
{
	board->setCard(letter, number, card);
}

// Deactivate player on given side
void Game::deactivatePlayer(Side side)
{
	Player& playerToDeactivate = getPlayer(side);
	playerToDeactivate.setActive(false);
}

// Get list of all players
std::vector<Player>& Game::getPlayers() {
	return players;
}

// Get list of all players
const std::vector<Player>& Game::getPlayers() const {
	return players;
}

// Get board
Board* Game::getBoard() {
	return board;
}