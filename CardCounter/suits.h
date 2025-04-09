#ifndef SUITS_H
#define SUITS_H

#include <string>

enum class SUIT {
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
};

/**
 * @brief to_string Converts a SUIT to a string
 * @param suit The SUIT to convert
 * @return A string of the SUIT provided
 */
inline std::string toString(SUIT suit)
{
    switch (suit) {
    case SUIT::HEARTS:
        return "Hearts";
    case SUIT::DIAMONDS:
        return "Diamonds";
    case SUIT::CLUBS:
        return "Clubs";
    case SUIT::SPADES:
        return "Spades";
    }
}

inline std::ostream& operator<<(std::ostream& os, SUIT suit) {
    return os << toString(suit);
}

#endif // SUITS_H

