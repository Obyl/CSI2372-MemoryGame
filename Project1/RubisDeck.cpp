/*
* Implementation of the RubisDeck class.
*/

#include "RubisDeck.h"

// Private constructor
RubisDeck::RubisDeck() {}

// Factory method for RubisDeck
RubisDeck& RubisDeck::make_RubisDeck() 
{
	RubisDeck* rubisDeck = new RubisDeck();
	
	// Add all values of rubies as given in assignment
	// (3 cards of value 1, 2 of value 2, 1 of value 3, 1 of value 4
	rubisDeck->deck.push_back(Rubis(1));
	rubisDeck->deck.push_back(Rubis(1));
	rubisDeck->deck.push_back(Rubis(1));
	rubisDeck->deck.push_back(Rubis(2));
	rubisDeck->deck.push_back(Rubis(2));
	rubisDeck->deck.push_back(Rubis(3));
	rubisDeck->deck.push_back(Rubis(4));

	// Shuffle deck
	rubisDeck->shuffle();

	return *rubisDeck;
}