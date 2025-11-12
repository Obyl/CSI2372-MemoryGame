#pragma once

#include <string>
#include "Rubis.h"

enum Side { top, bottom, left, right };

class Player {
private:
	std::string name;
	Side side;
	int rubies;
public:
	Player(std::string, Side);
	std::string getName() const;
	void setActive(bool);
	bool isActive();
	int getNRubies() const;
	void addRubies(const Rubis&);
	void setDisplayMode(bool);
	Side getSide();
	void setSide(Side);
};