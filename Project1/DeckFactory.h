/*
* Header file for the DeckFactory class.
*/

#pragma once

#include <algorithm>
#include <vector>
#include <random>

template <typename C>
class DeckFactory {

protected:
	std::vector<C> deck;

// Methods are defined inline as this is a template class
public:
	// Shuffle the deck
	void shuffle()
	{
		std::random_device rd;
		std::mt19937 g(rd());

		std::shuffle(deck.begin(), deck.end(), g);
	}

	// Get next item in deck
	C* getNext()
	{
		C* card = &deck.back();
		deck.pop_back();
		return card;
	}

	// Getter for if the deck is empty
	bool isEmpty() const
	{
		return deck.size() == 0;
	}
};