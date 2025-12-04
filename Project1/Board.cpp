/*
* Implementation of the Board class.
*/

#include "Board.h"

// Constructor
Board::Board(CardDeck& deck) {
    // Add cards to board from deck
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            Card* toAdd = deck.getNext();

            if (toAdd)
                setCard((Letter)row, (Number)col, toAdd);
            else
                throw NoMoreCards();
        }
    }
}

// Destructor
Board::~Board() {
    delete[] cards;
    delete[] face_up_flags;
}

// Get card at coordinate
Card* Board::getCard(const Letter& letter, const Number& number)
{
    return cards[letter][number];
}

// Set card at coordinate
void Board::setCard(const Letter& letter, const Number& number, Card* card)
{
    cards[letter][number] = card;
}

// Flip all card faces down
void Board::allFacesDown()
{
    for (int letter = 0; letter<BOARD_HEIGHT; letter++)
        for (int number =0; number<BOARD_WIDTH; number++)
            face_up_flags[letter][number] = 0;

    flippedCards.clear();
}

// Getter for if card at coordiate is face up
bool Board::isFaceUp(const Letter& letter, const Number& number) const
{
    return face_up_flags[letter][number];
}

// Set card at coordinate face up
bool Board::turnFaceUp(const Letter& letter, const Number& number)
{
    flippedCards.push_back(getCard(letter, number));
    return face_up_flags[letter][number] = 1;
}

// Set card at coordiate face down
bool Board::turnFaceDown(const Letter& letter, const Number& number)
{
    Card* cardToFaceDown = getCard(letter, number);
    
    // Find index of card to flip down
    int index = -1;
    for (Card* card : flippedCards)
    {
        index++;
        if ((card->faceAnimal == cardToFaceDown->faceAnimal) 
            && (card->faceBackground == cardToFaceDown->faceBackground)) break;
    }
    // Remove card from list of flipped cards
    flippedCards.erase(flippedCards.begin() + index);

    return face_up_flags[letter][number] = 0;
}

// Setter for expert display
void Board::setExpertDisplay(bool value)
{
    isExpertDisplay = value;
}

// Swap cards at coordinates
void Board::swapCards(const Letter& letter1, const Number& number1, const Letter& letter2, const Number& number2)
{
    std::swap(cards[letter1][number1], cards[letter2][number2]);
    std::swap(face_up_flags[letter1][number1], face_up_flags[letter2][number2]);
}

// Get number of flipped cards
int Board::getNFlippedCards()
{
    return flippedCards.size();
}

// Standard print mode
std::ostream& nonExpertDisplay(std::ostream& os, Board& board)
{
    for (int letter = 0; letter < BOARD_HEIGHT; letter++)
    {
        for (int letterRow = 0; letterRow<3; letterRow++)
        {  
            // Print letter at beginning of each row
            if (letterRow == 1) 
                os << LETTERS[letter] << "   ";
            else 
                os << "    ";

            for (int number = 0; number < BOARD_WIDTH; number++)
            {
                // Skip middle of board
                if (letter == 2 && number == 2) {
                    os << "    ";
                    continue;
                }

                // Get card at coordinate from board
                Card* card = board.getCard((Letter)letter, (Number)number);

                // If card is face up, print it. Else just print zs.
                if (board.isFaceUp((Letter)letter, (Number)number))
                    os << (*card)(letterRow) << " ";
                else
                    os << "zzz ";
            }
            os << std::endl;
        }
        os << std::endl;  
    }

    // Print numbers at bottom
    os << "    ";
    for (int i=0; i<5; i++)
        os << NUMBERS[i] << "   ";
    os << std::endl;

    return os;
}

// Expert display mode
std::ostream& expertDisplay(std::ostream& os, Board& board)
{
    // Don't print anything if no cards have been flipped
    if (board.flippedCards.empty()) 
        return os;

    for (int line=0; line<4; line++)
    {
        for (Card* card : board.flippedCards)
        {
            // First three lines, print the card
            if (line < 3)
            {
                os << (*card)(line) << " ";
            }
            // Last line, find the card then print the coordinate
            else
            {
                for (int letter = 0; letter < BOARD_HEIGHT; letter++)
                {
                    for (int number = 0; number < BOARD_WIDTH; number++)
                    {
                        if (board.cards[letter][number] == card)
                        {
                            os << LETTERS[letter] << NUMBERS[number] << "  ";
                            break;
                        }
                    }
                }
            }
        }
        os << std::endl;
    }

    return os;
}

// Print operator overload
std::ostream& operator<<(std::ostream& os, Board& board)
{
    // Branch depending on display mode
    if (board.isExpertDisplay)
        return expertDisplay(os, board);
    else
        return nonExpertDisplay(os, board);
    
}