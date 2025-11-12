#pragma once
#include <assert.h>
#include <iostream>

class Rubis {
public:
	int value;
	Rubis(int);
public:
	operator int() const;
	friend std::ostream& operator<<(std::ostream& os, Rubis& rubis);
};

