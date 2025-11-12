#include "CardDeck.h"

CardDeck::CardDeck(){}

CardDeck& CardDeck::make_CardDeck()
{
    CardDeck* cardDeck = new CardDeck();
    for (int color = 0; color < 5; color++)
    {
        for (int animal = 0; animal < 5; animal++)
        {
            Card card((FaceAnimal)animal, (FaceBackground)color);
            cardDeck->deck.push_back(card);
        }
    }
    return *cardDeck;
}