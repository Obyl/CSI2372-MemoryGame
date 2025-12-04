/*
* Implementation of the CardDeck class.
*/

#include "CardDeck.h"
#include <iostream>

// Private constructor
CardDeck::CardDeck(){}

// Factory method for CardDeck
CardDeck& CardDeck::make_CardDeck()
{
    CardDeck* cardDeck = new CardDeck();

    // Add all combinations of colors & animals as cards
    for (int color = 0; color < 5; color++)
    {
        for (int animal = 0; animal < 5; animal++)
        {
            Card card((FaceAnimal)animal, (FaceBackground)color);
            cardDeck->deck.push_back(card);
        }
    }

    // Shuffle deck
    cardDeck->shuffle();

    return *cardDeck;
}