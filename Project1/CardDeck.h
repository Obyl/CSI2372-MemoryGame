/*
* Header file for the CardDeck class.
*/

#pragma once

#include "Card.h"
#include "DeckFactory.h"

class CardDeck : public DeckFactory<Card>{
private:
	CardDeck();
public:
	static CardDeck& make_CardDeck();
};