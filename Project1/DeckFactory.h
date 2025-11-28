#pragma once
#include <vector>
#include <random>

template <typename C>
class DeckFactory {

protected:
	std::vector<C> deck;

public:
	void shuffle()
	{
		std::vector<C> new_deck = deck;
		int index = 0;
		while (new_deck.size() > 0)
		{
			int random_index = std::rand() % new_deck.size();
			deck[index++] = new_deck[random_index];
			new_deck.erase(new_deck.begin() + random_index);
		}
	}

	C* getNext()
	{
		C* card = &deck.back();
		deck.pop_back();
		return card;
	}

	bool isEmpty() const
	{
		return deck.size() == 0;
	}
};