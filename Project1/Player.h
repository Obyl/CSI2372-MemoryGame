/*
* Header file for the Player class.
* Also includes the Side enum.
*/

#pragma once

#include <string>
#include "Rubis.h"

enum Side { top, bottom, left, right };

class Player {
private:
	std::string name;
	Side side;
	int rubies;
	bool active;
	bool endOfGame;
public:
	Player(std::string, Side);
	std::string getName() const;
	void setActive(bool);
	bool isActive() const;
	int getNRubies() const;
	void addRubies(const Rubis&);
	void setDisplayMode(bool);
	Side getSide() const;
	void setSide(Side);
	friend std::ostream& operator<<(std::ostream&, Player&);
};