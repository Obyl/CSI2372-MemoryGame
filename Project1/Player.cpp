/*
* Implementation of the Player class.
*/

#include "Player.h"

// Constructor
Player::Player(std::string name, Side side) {
	this->name = name;
	this->side = side;
	this->rubies = 0;
	active = true;
	endOfGame = false;
}

// Name getter
std::string Player::getName() const {
	return name;
}

// Active setter
void Player::setActive(bool active) {
	this->active = active;
}

// Active getter
bool Player::isActive() const {
	return active;
}

// # of rubies getter
int Player::getNRubies() const {
	return rubies;
}

// Adds the value of a given Rubis object to the player's rubies.
void Player::addRubies(const Rubis& r) {
	rubies += int(r);
}

// Display mode setter
void Player::setDisplayMode(bool endOfGame) {
	this->endOfGame = endOfGame;
}

// Side getter
Side Player::getSide() const {
	return side;
}

// Side setter
void Player::setSide(Side side) {
	this->side = side;
}

// Print operator for Player
std::ostream& operator<<(std::ostream& os, Player& player) {
	os << player.getName() << ": ";

	// Display rubies or active status depending on if it's the end of the game.
	if (player.endOfGame) {
		os << player.getNRubies() << " rubies";
	}
	else {
		switch (player.getSide()) {
		case top:
			os << "top";
			break;
		case bottom:
			os << "bottom";
			break;
		case left:
			os << "left";
			break;
		case right:
			os << "right";
			break;
		}

		os << " ";

		if (player.isActive())
			os << "(active)";
		else
			os << "(not active)";
	}

	return os;
}