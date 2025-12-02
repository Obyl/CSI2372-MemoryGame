#include "RubisDeck.h"

RubisDeck::RubisDeck() {}

RubisDeck& RubisDeck::make_RubisDeck() 
{
	RubisDeck* rubisDeck = new RubisDeck();
	
	rubisDeck->deck.push_back(Rubis(1));
	rubisDeck->deck.push_back(Rubis(1));
	rubisDeck->deck.push_back(Rubis(1));
	rubisDeck->deck.push_back(Rubis(2));
	rubisDeck->deck.push_back(Rubis(2));
	rubisDeck->deck.push_back(Rubis(3));
	rubisDeck->deck.push_back(Rubis(4));

	rubisDeck->shuffle();

	return *rubisDeck;
}