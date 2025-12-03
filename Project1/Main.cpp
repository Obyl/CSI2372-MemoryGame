#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <random>

#include "Rules.h"
#include "CardDeck.h"
#include "RubisDeck.h"

bool comp(Player a, Player b);
Card* inputCard(std::string, Game& game, bool turnFaceUp, Letter& letterToUpdate, Number& numberToUpdate);

Letter blockedLetter = NULL_LETTER;
Number blockedNumber = NULL_NUMBER;

int main() {

	srand(time(0));

	Game game;
	RubisDeck rubisDeck = RubisDeck::make_RubisDeck();

	bool inputValid = false;

	char expertDisplayMode;
	while (!inputValid) {
		std::cout << "Use expert display mode? (y/n): ";
		std::cin >> expertDisplayMode;

		if (expertDisplayMode == 'y' || expertDisplayMode == 'n')
			inputValid = true;
		else
			std::cout << "Invalid input. Please try again." << std::endl;
	}
	
	inputValid = false;
	char expertRulesMode;
	while (!inputValid) {
		std::cout << "Use expert rules mode? (y/n): ";
		std::cin >> expertRulesMode;

		if (expertRulesMode == 'y' || expertRulesMode == 'n')
			inputValid = true;
		else
			std::cout << "Invalid input. Please try again." << std::endl;
	}
	

	Rules rules(expertDisplayMode == 'y', expertRulesMode == 'y');
	game.getBoard()->setExpertDisplay(rules.isExpertDisplayMode());

	inputValid = false;
	int numPlayers;
	while (!inputValid) {
		std::cout << "How many players? (2-4): ";
		std::cin >> numPlayers;

		if (numPlayers >= 2 && numPlayers <= 4)
			inputValid = true;
		else
			std::cout << "Invalid input. Please try again." << std::endl;
	}
	
	std::cin.ignore();
	for (int i = 0; i < numPlayers; i++) {
		std::string name;
		std::cout << "What is Player " << (i + 1) << "'s name? ";
		std::getline(std::cin, name);

		game.addPlayer(Player(name, (Side) i));
	}

	std::cout << game << std::endl;

	// system("cls");

	game.getDeckPtr()->shuffle();
	for (int row = 0; row < 5; row++) {
		for (int col = 0; col < 5; col++) {
			game.setCard((Letter)row, (Number)col, game.getDeckPtr()->getNext());
		}
	}

	while (!rules.gameOver(game)) {

		int blockedRoundTimer = 0;

		game.getBoard()->allFacesDown();
		game.resetStartOfRound();
		rules.resetCurrentPlayer();

		for (Player& player : game.getPlayers()) {

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

			// system("cls");

			std::cout << "Round " << game.getRound() << " begins!" << std::endl;

			std::cout << game << std::endl;
			std::cout << "Hit enter to continue" << std::endl;
			std::cin.ignore();

			game.getBoard()->allFacesDown();
		}	

		while (!rules.roundOver(game)) {
			//system("cls");
			std::cout << game << std::endl;
			

			const Player& player = rules.getNextPlayer(game);

			rules.setMustPlayAgain(false);
			std::cout << player.getName() << "'s turn." << std::endl;

			Letter letter;
			Number number;

			inputValid = false;

			Card* selectedCard = inputCard("Select a card to turn face up: ", game, true, letter, number);
			game.getBoard()->turnFaceUp(letter, number);
			game.setCurrentCard(selectedCard);

			if (rules.isExpertRulesMode())
			{
				switch (selectedCard->faceAnimal)
				{
					case Octopus:
					{
						int randomNum;
						Card* cardToSwap = nullptr;

						int cardToSwapRow = (int)letter;
						int cardToSwapCol = (int)number;

						while (true)
						{
							randomNum = std::rand() % 4;

							if (randomNum == 0) cardToSwapRow--;
							else if (randomNum == 1) cardToSwapCol++;
							else if (randomNum == 2) cardToSwapRow++;
							else cardToSwapCol--;

							if ((cardToSwapRow < 0) || (cardToSwapRow > 4) || (cardToSwapCol < 0) || (cardToSwapCol > 4) || 
							((cardToSwapRow == 2) && (cardToSwapCol == 2)))
							{
								// invalid
							}
							else
							{
								std::cout << "You flipped an octopus! 2 cards were swapped." << std::endl;
								break;
							}
						}

						game.getBoard()->swapCards((Letter)cardToSwapRow, (Number)cardToSwapCol, letter, number);

						break;
					}
						
					case Penguin:
					{
						if (game.getBoard()->getUnflippedCardsSequenceSize() <= 1) break;

						Letter cardToTurnFaceDownLetter;
						Number cardToTurnFaceDownNumber;
			
						Card* cardToTurnFaceDown = inputCard("You flipped a penguin! Select a card to turn face down: ", 
							game, false, cardToTurnFaceDownLetter, cardToTurnFaceDownNumber);
						game.getBoard()->turnFaceDown(cardToTurnFaceDownLetter, cardToTurnFaceDownNumber);
						break;
					}

					case Walrus:
					{
						inputCard("You flipped a walrus! Select a card to block for the next player: ", game, true, blockedLetter, 
						blockedNumber);
						blockedRoundTimer = 0;
					}

					case Crab:
					{
						rules.setMustPlayAgain(true);
						std::cout << "You flipped a crab! You have to play again." << std::endl;
						break;
					}
						
					case Turtle:
						const Player& skippedPlayer = rules.getNextPlayer(game);
						std::cout << "You flipped a turtle! " << skippedPlayer.getName() << " was skipped." << std::endl;
						break;
				}
			}

			

			if (!rules.isValid(game))
			{
				game.deactivatePlayer(player.getSide());
				std::cout << player.getName() << " has been eliminated!" << std::endl;
			}

			if (blockedLetter != NULL_LETTER) blockedRoundTimer++;
			if (blockedRoundTimer == 2)
			{
				blockedLetter = NULL_LETTER;
				blockedNumber = NULL_NUMBER;
			}
				
		}

		rules.setMustPlayAgain(false);
		const Player& remainingPlayer = rules.getNextPlayer(game);
		Rubis reward = *rubisDeck.getNext();

		game.getPlayer(remainingPlayer.getSide()).addRubies(reward);

		std::cout << remainingPlayer.getName() << " obtained " << int(reward) << " rubis." << std::endl;

		game.incrementRound();

	}

	// system("cls");

	std::sort(game.getPlayers().begin(), game.getPlayers().end(), comp);

	std::cout << "Game over! Standings:" << std::endl;
	for (Player& player : game.getPlayers()) {
		std::cout << player.getName() << ": " << player.getNRubies() << std::endl;
	}

	std::cout << std::endl << "The winner is: " << game.getPlayers()[game.getPlayers().size()-1].getName() << "!" << std::endl;
}

bool comp(Player a, Player b) {
	return a.getNRubies() < b.getNRubies();
}

Card* inputCard(std::string requestMessage, Game& game, bool turnFaceUp, Letter& letterToUpdate, Number& numberToUpdate)
{
	bool inputValid = false;
	Letter letter;
	Number number;
	while (!inputValid) {

		std::cout << requestMessage << std::endl;	

		std::string card;
		std::getline(std::cin, card);

		if (card.size() > 2) {
			std::cout << "Invalid format. Enter card as: [A-E][1-5]" << std::endl;
			continue;
		}

		if (card[0] < 'A' || card[0] > 'E' || card[1] < '0' || card[1] > '5') {
			std::cout << "Invalid format. Enter card as: [A-E][1-5]" << std::endl;
			continue;
		}

		letter = (Letter) (card[0] - 'A');
		number = (Number) (card[1] - '1');

		if (letter == Letter::C && number == Number::three) {
			std::cout << "Cannot select centre. Please enter a different card." << std::endl;
			continue;
		}

		if ((blockedLetter == letter) && (blockedNumber == number))
		{
			std::cout << "That card has been blocked by another player. Please enter a different card." << std::endl;
			continue;
		}

		if (turnFaceUp && game.getBoard()->isFaceUp(letter, number)) {

			std::cout << "That card is face up. Please enter a face down card." << std::endl;
			continue;
		} 
		else if (!turnFaceUp && !game.getBoard()->isFaceUp(letter, number))
		{
			std::cout << "That card is face down. Please enter a face up card." << std::endl;
			continue;
		}

		inputValid = true;
	}

	letterToUpdate = letter;
	numberToUpdate = number;

	return game.getCard(letter, number);	 
}





