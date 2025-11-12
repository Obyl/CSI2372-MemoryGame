#include "Rubis.h"

Rubis::Rubis(int value)
{
    assert(value >= 1 && value <= 4);
    this->value = value;
}

std::ostream& operator<<(std::ostream& os, Rubis& rubis) {
	os << rubis.value;
	return os;
}

Rubis::operator int() const
{
    return value;
}