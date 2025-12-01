#include <iostream>
#include <cstdlib>

#include "Rules.h"
#include "CardDeck.h"

int main() {

	srand(time(0));

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

	system("cls");

	while (!rules.gameOver(game)) {
		game.getBoard()->allFacesDown();

		game.getDeckPtr()->shuffle();
		for (int row = 0; row < 5; row++) {
			for (int col = 0; col < 5; col++) {
				game.setCard((Letter)row, (Number)col, game.getDeckPtr()->getNext());
			}
		}

		for (Player& player : game.getPlayers()) {
			player.setActive(true);

			switch (player.getSide()) {
			case top:
				game.getBoard()->turnFaceUp(Letter::A, Number::two);
				game.getBoard()->turnFaceUp(Letter::A, Number::three);
				game.getBoard()->turnFaceUp(Letter::A, Number::four);
				break;
			case bottom:
				game.getBoard()->turnFaceUp(Letter::E, Number::two);
				game.getBoard()->turnFaceUp(Letter::E, Number::three);
				game.getBoard()->turnFaceUp(Letter::E, Number::four);
				break;
			case left:
				game.getBoard()->turnFaceUp(Letter::B, Number::one);
				game.getBoard()->turnFaceUp(Letter::C, Number::one);
				game.getBoard()->turnFaceUp(Letter::D, Number::one);
				break;
			case right:
				game.getBoard()->turnFaceUp(Letter::B, Number::five);
				game.getBoard()->turnFaceUp(Letter::C, Number::five);
				game.getBoard()->turnFaceUp(Letter::D, Number::five);
				break;
			}

			system("cls");
			std::cout << game << std::endl;
			std::cout << "Hit enter to continue" << std::endl;
			std::cin.ignore();

			game.getBoard()->allFacesDown();
		}

		while (!rules.roundOver(game)) {
			Player player = rules.getNextPlayer(game);
			std::cout << player.getName() << "'s turn." << std::endl;

			inputValid = false;
			while (!inputValid) {
				std::cout << "Please enter a card to turn face up." << std::endl;

				std::string card;
				std::getline(std::cin, card);

				//two chars, letter then number
				//within bounds of the board
				//not the centre
				//not already turned up

				if (card.size() > 2) {
					std::cout << "Invalid format. Enter card as: [A-E][1-5]" << std::endl;
					continue;
				}

				Letter letter = (Letter) (card[0] - 'A');
				Number number = (Number) (card[1] - '1');

				if (letter < 'A' || letter > 'E' || number < 0 || number > 5) {
					std::cout << "Invalid format. Enter card as: [A-E][1-5]" << std::endl;
					continue;
				}
				if (letter == 'C' && number == 3) {
					std::cout << "Cannot select centre. Please enter a different card." << std::endl;
					continue;
				}
				if (game.getBoard()->isFaceUp(letter, number)) {
					std::cout << "That card is already face up. Please enter a different card." << std::endl;
					continue;
				}
			}
		}
	}
}