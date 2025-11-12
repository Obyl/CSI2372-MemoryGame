#include <iostream>

#include "Rules.h"
#include "CardDeck.h"

int main() {

	CardDeck cd = CardDeck::make_CardDeck();
	std::cout << cd.isEmpty() << std::endl;
	// std::cout << cd.getNext() << std::endl;
	// cd.shuffle();
	// std::cout << cd.getNext() << std::endl;

	Game game;

	bool inputValid = false;

	char expertDisplayMode;
	while (!inputValid) {
		std::cout << "Use expert display mode? (y/n): ";
		std::cin >> expertDisplayMode;

		if (expertDisplayMode == 'y' || expertDisplayMode == 'n')
			inputValid = true;
		else
			std::cout << "Invalid output. Please try again." << std::endl;
	}
	
	inputValid = false;
	char expertRulesMode;
	while (!inputValid) {
		std::cout << "Use expert rules mode? (y/n): ";
		std::cin >> expertRulesMode;

		if (expertRulesMode == 'y' || expertRulesMode == 'n')
			inputValid = true;
		else
			std::cout << "Invalid output. Please try again." << std::endl;
	}
	

	Rules rules(expertDisplayMode == 'y', expertRulesMode == 'y');

	inputValid = false;
	int numPlayers;
	while (!inputValid) {
		std::cout << "How many players? (2-4): ";
		std::cin >> numPlayers;

		if (numPlayers >= 2 && numPlayers <= 4)
			inputValid = true;
		else
			std::cout << "Invalid output. Please try again." << std::endl;
	}
	
	std::cin.ignore();
	for (int i = 0; i < numPlayers; i++) {
		std::string name;
		std::cout << "What is Player " << (i + 1) << "'s name? ";
		std::getline(std::cin, name);

		game.addPlayer(Player(name, (Side) i));
	}

	std::cout << game << std::endl;
}