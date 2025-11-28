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
}

bool Board::isFaceUp(const Letter& letter, const Number& number) const
{
    return face_up_flags[letter][number];
}

bool Board::turnFaceUp(const Letter& letter, const Number& number)
{
    return face_up_flags[letter][number] = 1;
}

bool Board::turnFaceDown(const Letter& letter, const Number& number)
{
    return face_up_flags[letter][number] = 0;
}

std::ostream& operator<<(std::ostream& os, Board& board)
{
    const std::string letters = "ABCDE";
    const std::string numbers = "12345";

    for (int letter = 0; letter < 5; letter++)
    {
        for (int letterRow = 0; letterRow<3; letterRow++)
        {  

            if (letterRow == 1) os << letters[letter] << "   ";
            else os << "    ";

            for (int number = 0; number < 5; number++)
            {    
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