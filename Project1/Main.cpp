/*
* Main function
*/

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <random>

#include "Rules.h"
#include "CardDeck.h"
#include "RubisDeck.h"

// Helper function declarations (definitions below)
bool inputBool(std::string);
Card* inputCard(std::string, Game& game, bool turnFaceUp, Letter& letterToUpdate, Number& numberToUpdate);
bool comp(Player a, Player b);

// Store blocked coordinate
Letter blockedLetter = Letter::NULL_LETTER;
Number blockedNumber = Number::NULL_NUMBER;

int main() {
	// Seed randomness
	srand(time(0));

	// Create game and rubies deck
	Game game;
	RubisDeck rubisDeck = RubisDeck::make_RubisDeck();

	// Get rules from user
	bool expertDisplayMode = inputBool("Use expert display mode? (y/n): ");
	bool expertRulesMode = inputBool("Use expert rules mode? (y/n): ");

	Rules rules(expertDisplayMode, expertRulesMode);
	game.getBoard()->setExpertDisplay(rules.isExpertDisplayMode());

	// Get number of players
	bool inputValid = false;
	int numPlayers;
	while (!inputValid) {
		std::cout << "How many players? (2-4): ";
		std::cin >> numPlayers;

		if (numPlayers >= 2 && numPlayers <= 4)
			inputValid = true;
		else
			std::cout << "Invalid input. Please try again." << std::endl;
	}
	
	// Get player names and add to game
	std::cin.ignore();
	for (int i = 0; i < numPlayers; i++) {
		std::string name;
		std::cout << "What is Player " << (i + 1) << "'s name? ";
		std::getline(std::cin, name);

		game.addPlayer(Player(name, (Side) i));
	}

	std::cout << game << std::endl;

	game.newRound();

	while (!rules.gameOver(game)) {
		// Keep track of how long a card has been blocked for
		// (if a card is blocked by a walrus it should only be for the next player)
		int blockedCounter = 0;

		// Turn all faces down and reset current player
		game.getBoard()->allFacesDown();
		rules.resetCurrentPlayer();

		std::cout << std::endl << "Round " << (game.getRound() + 1) << " begins!" << std::endl;

		// Display cards in front of each player
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

			std::cout << game << std::endl;
			std::cout << "Displaying cards in front of " << player.getName() << std::endl;
			std::cout << "Hit enter to continue" << std::endl;
			std::cin.ignore();

			game.getBoard()->allFacesDown();
		}	

		while (!rules.roundOver(game)) {
			// Display current state of game
			std::cout << game << std::endl;

			// Get next player
			const Player& player = rules.getNextPlayer(game);
			rules.setMustPlayAgain(false);
			std::cout << player.getName() << "'s turn." << std::endl;

			// Letter and number of current selection
			Letter letter;
			Number number;
			Card* selectedCard = inputCard("Select a card to turn face up: ", game, true, letter, number);

			// Handle all the expert rule
			if (rules.isExpertRulesMode())
			{
				switch (selectedCard->faceAnimal)
				{
				case FaceAnimal::Octopus:
				{
					int randomNum;
					Card* cardToSwap = nullptr;

					int cardToSwapRow = (int)letter;
					int cardToSwapCol = (int)number;

					while (true)
					{
						// Generate a random "direction" to swap in
						randomNum = std::rand() % 4;

						if (randomNum == 0) cardToSwapRow--;
						else if (randomNum == 1) cardToSwapCol++;
						else if (randomNum == 2) cardToSwapRow++;
						else cardToSwapCol--;

						// Make sure the swap is valid
						// (not going out of bounds or into the centre)
						if ((cardToSwapRow >= 0) && (cardToSwapRow <= 4) && (cardToSwapCol >= 0) && (cardToSwapCol <= 4) && ((cardToSwapRow != 2) || (cardToSwapCol != 2)))
						{
							std::cout << "You flipped an octopus! 2 cards were swapped." << std::endl;
							break;
						}
					}

					game.getBoard()->swapCards((Letter)cardToSwapRow, (Number)cardToSwapCol, letter, number);
					letter = (Letter)cardToSwapRow;
					number = (Number)cardToSwapCol;

					break;
				}	
				case FaceAnimal::Penguin:
				{
					if (game.getBoard()->getNFlippedCards() <= 1) break;

					Letter cardToTurnFaceDownLetter;
					Number cardToTurnFaceDownNumber;
					
					// Get card tp turn face down
					Card* cardToTurnFaceDown = inputCard("You flipped a penguin! Select a card to turn face down: ", 
						game, false, cardToTurnFaceDownLetter, cardToTurnFaceDownNumber);
					game.getBoard()->turnFaceDown(cardToTurnFaceDownLetter, cardToTurnFaceDownNumber);
					break;
				}
				case FaceAnimal::Walrus:
				{
					// Get card to block for next player
					inputCard("You flipped a walrus! Select a card to block for the next player: ", game, true, blockedLetter, blockedNumber);
					blockedCounter = 0;
					break;
				}
				case FaceAnimal::Crab:
				{
					// Make the current player play again
					rules.setMustPlayAgain(true);
					std::cout << "You flipped a crab! You have to play again." << std::endl;
					break;
				}
				case FaceAnimal::Turtle:
					// Skip the next player by invoking rules.getNextPlayer()
					const Player& skippedPlayer = rules.getNextPlayer(game);
					std::cout << "You flipped a turtle! " << skippedPlayer.getName() << " was skipped." << std::endl;
					break;
				}
			}

			// Turn card face up
			game.getBoard()->turnFaceUp(letter, number);
			game.setCurrentCard(selectedCard);

			// Check if the move was valid
			if (!rules.isValid(game))
			{
				game.deactivatePlayer(player.getSide());
				std::cout << player.getName() << " has been eliminated!" << std::endl;
				rules.setMustPlayAgain(false);
			}

			// Increment blockedCounter if there is a blocked card
			// (blockedLetter and blockedNumber will both be null/not null in sync so only need to check one)
			if (blockedLetter != NULL_LETTER) 
				blockedCounter++;

			// If this is the second time the card has been blocked, unblock it
			if (blockedCounter == 2)
			{
				blockedLetter = NULL_LETTER;
				blockedNumber = NULL_NUMBER;
			}
		}

		// Get round winner
		rules.setMustPlayAgain(false);
		const Player& remainingPlayer = rules.getNextPlayer(game);
		Rubis reward = *rubisDeck.getNext();

		// Give rubies
		game.getPlayer(remainingPlayer.getSide()).addRubies(reward);
		std::cout << remainingPlayer.getName() << " obtained " << int(reward) << " rubis." << std::endl;

		// Prepare game for next round
		game.newRound();
	}

	// Sort players from lowest to highest number of rubies
	std::sort(game.getPlayers().begin(), game.getPlayers().end(), comp);

	// Print standings
	std::cout << std::endl << "Game over! Standings:" << std::endl;
	for (Player& player : game.getPlayers()) {
		player.setDisplayMode(true);
		std::cout << player << std::endl;
	}

	// Announce winner
	std::cout << std::endl << "The winner is: " << game.getPlayers()[game.getPlayers().size()-1].getName() << "!" << std::endl;

	exit(0);
}

// Get a boolean input from the user
bool inputBool(std::string message) {
	bool inputValid = false;

	std::string input;
	while (!inputValid) {
		std::cout << message;
		std::getline(std::cin, input);

		if (input == "y" || input == "n")
			inputValid = true;
		else
			std::cout << "Invalid input. Please try again." << std::endl;
	}

	return input == "y";
}

// Get a card input from the user.
// Return coordinates via letterToUpdate and numberToUpdate references
Card* inputCard(std::string requestMessage, Game& game, bool turnFaceUp, Letter& letterToUpdate, Number& numberToUpdate)
{
	bool inputValid = false;
	Letter letter;
	Number number;
	while (!inputValid) {
		std::cout << requestMessage << std::endl;	

		std::string card;
		std::getline(std::cin, card);

		// Make sure the input string is only two characters long
		if (card.size() > 2) {
			std::cout << "Invalid format. Enter card as: [A-E][1-5]" << std::endl;
			continue;
		}

		// Make sure the input is within the bounds of the board
		if (card[0] < 'A' || card[0] > 'E' || card[1] < '1' || card[1] > '5') {
			std::cout << "Invalid format. Enter card as: [A-E][1-5]" << std::endl;
			continue;
		}

		letter = (Letter) (card[0] - 'A');
		number = (Number) (card[1] - '1');

		// Make sure the selection is not the centre
		if (letter == Letter::C && number == Number::three) {
			std::cout << "Cannot select centre. Please enter a different card." << std::endl;
			continue;
		}

		// Make sure the selection has not been blocked
		if (blockedLetter == letter && blockedNumber == number)
		{
			std::cout << "That card has been blocked by another player. Please enter a different card." << std::endl;
			continue;
		}

		// Make sure the selection is not already turned face up/face down (depending on turnFaceUp parameter)
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

// Comparator function for sorting players from lowest to highest number of rubies
bool comp(Player a, Player b) {
	return a.getNRubies() < b.getNRubies();
}
