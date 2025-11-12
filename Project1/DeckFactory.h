#pragma once
#include <vector>
#include <random>

template <typename C>
class DeckFactory {

protected:
	std::vector<C> deck;

public:
	void shuffle();
	C* getNext();
	bool isEmpty() const;
};