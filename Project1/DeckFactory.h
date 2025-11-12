#pragma once

template <typename C>
class DeckFactory {
public:
	void shuffle();
	C* getNext();
	bool isEmpty() const;
};