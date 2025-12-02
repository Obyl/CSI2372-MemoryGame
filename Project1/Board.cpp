#include "Board.h"

Card* Board::getCard(const Letter& letter, const Number& number)
{
    return cards[letter][number];
}

void Board::setCard(const Letter& letter, const Number& number, Card* card)
{
    cards[letter][number] = card;
}

void Board::allFacesDown()
{
    for (int letter = 0; letter<5; letter++)
    {
        for (int number =0; number<5; number++)
        {
            face_up_flags[letter][number] = 0;
        }
    }
    unflippedCardsSequence.clear();
}

bool Board::isFaceUp(const Letter& letter, const Number& number) const
{
    return face_up_flags[letter][number];
}

bool Board::turnFaceUp(const Letter& letter, const Number& number)
{
    unflippedCardsSequence.push_back(getCard(letter, number));
    return face_up_flags[letter][number] = 1;
}

bool Board::turnFaceDown(const Letter& letter, const Number& number)
{
   
    return face_up_flags[letter][number] = 0;
}

void Board::setExpertDisplay(bool value)
{
    isExpertDisplay = value;
}

std::ostream& nonExpertDisplay(std::ostream& os, Board& board)
{

    for (int letter = 0; letter < 5; letter++)
    {
        for (int letterRow = 0; letterRow<3; letterRow++)
        {  

            if (letterRow == 1) os << letters[letter] << "   ";
            else os << "    ";

            for (int number = 0; number < 5; number++)
            {
                if (letter == 2 && number == 2) {
                    os << "    ";
                    continue;
                }

                Card* card = board.getCard((Letter)letter, (Number)number);
                if (board.isFaceUp((Letter)letter, (Number)number))
                {
                    os << (*card)(letterRow) << " ";
                }
                else
                {
                    os << "zzz ";
                }
            }
            os << std::endl;
        }
        os << std::endl;  
    }
    os << "    ";
    for (int i=0; i<5; i++)
    {
        os << numbers[i] << "   ";
    }
    os << std::endl;
    return os;
}

std::ostream& expertDisplay(std::ostream& os, Board& board)
{

    if (board.unflippedCardsSequence.empty()) return os;

    for (int line=0; line<4; line++)
    {
        for (Card* card : board.unflippedCardsSequence)
        {
            if (line < 3 && line >= 0)
            {
                os << (*card)(line) << " ";
            }
            else
            {
                for (int letter = 0; letter < 5; letter++)
                {
                    for (int number = 0; number < 5; number++)
                    {
                        if (board.cards[letter][number] == card)
                        {
                            os << letters[letter] << numbers[number] << "  ";
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

std::ostream& operator<<(std::ostream& os, Board& board)
{
    if (!board.isExpertDisplay)
    {
        return nonExpertDisplay(os, board);
    }
    else
    {
        return expertDisplay(os, board);
    }
    
}