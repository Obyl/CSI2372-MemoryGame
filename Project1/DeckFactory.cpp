#include "DeckFactory.h"

template <typename C>
void DeckFactory<C>::shuffle()
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

template <typename C>
C* DeckFactory<C>::getNext()
{
    C card = deck.back();
    deck.pop_back();
    return card;
}

template <typename C>
bool DeckFactory<C>::isEmpty() const
{
    return deck.size() == 0;
}