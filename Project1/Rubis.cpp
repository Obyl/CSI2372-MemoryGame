/*
* Implementation of the Rubis class.
*/

#include "Rubis.h"

// Constructor
Rubis::Rubis(int value)
{
    this->value = value;
}

// Print operator overload
std::ostream& operator<<(std::ostream& os, Rubis& rubis) {
	os << rubis.value;
	return os;
}

// Integer casting overload
Rubis::operator int() const
{
    return value;
}