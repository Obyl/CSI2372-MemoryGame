/*
* Header file for the Board class.
* Definition of Letter and Number enums
* Definition of NoMoreCards exception
*/

#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "Card.h"
#include "CardDeck.h"

// Include NULL options for both letters and numbers
enum Letter { A, B, C, D, E, NULL_LETTER };
enum Number { one, two, three, four, five, NULL_NUMBER};

// Static const variables for printing
static const int BOARD_WIDTH = 5;
static const int BOARD_HEIGHT = 5;
static const std::string LETTERS = "ABCDE";
static const std::string NUMBERS = "12345";

class NoMoreCards : public std::exception {
public:
	const char* what() const noexcept {
		return "No more cards available to construct board!";
	}
};

class Board {
private:
	bool isExpertDisplay = false;
	Card* cards[BOARD_WIDTH][BOARD_HEIGHT] = {nullptr};
	bool face_up_flags[BOARD_WIDTH][BOARD_HEIGHT] = {0};
	std::vector<Card*> flippedCards;

public:
	Board(CardDeck& deck);
	~Board();
	bool isFaceUp(const Letter&, const Number&) const;
	bool turnFaceUp(const Letter&, const Number&);
	bool turnFaceDown(const Letter&, const Number&);
	void swapCards(const Letter&, const Number&, const Letter&, const Number&);
	Card* getCard(const Letter&, const Number&);
	void setCard(const Letter&, const Number&, Card*);
	void allFacesDown();
	friend std::ostream& operator<<(std::ostream&, Board&);
	friend std::ostream& nonExpertDisplay(std::ostream& os, Board& board);
	friend std::ostream& expertDisplay(std::ostream& os, Board& board);
	void setExpertDisplay(bool value);
	int getNFlippedCards();
	
};