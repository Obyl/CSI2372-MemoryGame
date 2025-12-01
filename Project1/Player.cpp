#include "Player.h"

Player::Player(std::string name, Side side) {
	this->name = name;
	this->side = side;
	this->rubies = 0;
	active = true;
}

std::string Player::getName() const {
	return name;
}

void Player::setActive(bool active) {
	this->active = active;
}

bool Player::isActive() const {
	return active;
}

int Player::getNRubies() const {
	return rubies;
}

void Player::addRubies(const Rubis& r) {
	rubies += int(r);
}

void Player::setDisplayMode(bool displayMode) {
	this->displayMode = displayMode;
}

Side Player::getSide() const {
	return side;
}

void Player::setSide(Side side) {
	this->side = side;
}

std::ostream& operator<<(std::ostream& os, Player& player) {
	os << player.getName() << ": ";

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

	return os;
}