/*
* Header file for the RubisDeck class.
*/

#pragma once

#include "Rubis.h"
#include "DeckFactory.h"

class RubisDeck : public DeckFactory<Rubis> {
private:
	RubisDeck();
public:
	static RubisDeck& make_RubisDeck();
};