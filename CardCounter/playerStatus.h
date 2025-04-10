#ifndef PLAYERSTATUS_H
#define PLAYERSTATUS_H

#include <string>

namespace PlayerStatus {

enum class PLAYERSTATUS {
    ACTIVE,
    BUST,
    STAND,
    WAITING
};

/**
 * @brief to_string Converts a PLAYERSTATUS to a string
 * @param PLAYERSTATUS The PLAYERSTATUS to convert
 * @return A string of the PLAYERSTATUS provided
 */
inline std::string toString(PLAYERSTATUS PLAYERSTATUS)
{
    switch (PLAYERSTATUS) {
    case PLAYERSTATUS::ACTIVE:
        return "ACTIVE";
    case PLAYERSTATUS::BUST:
        return "BUST";
    case PLAYERSTATUS::WAITING:
        return "WAITING";
    case PLAYERSTATUS::STAND:
        return "STAND";
    }

    return "Unknown PLAYERSTATUS";
}

/**
 * @brief operator << Prints out the string of the PLAYERSTATUS when used with the ostream operator
 * @param os The stream to add the string to
 * @param PLAYERSTATUS The PLAYERSTATUS to convert
 * @return The ostream with the PLAYERSTATUS as a string
 */
inline std::ostream& operator<<(std::ostream& os, PLAYERSTATUS PLAYERSTATUS) {
    return os << toString(PLAYERSTATUS);
}

/**
 * @brief allPLAYERSTATUSs An array of all the PLAYERSTATUS values
 */
inline constexpr PLAYERSTATUS allPLAYERSTATUSs[] = {
    PLAYERSTATUS::STAND,
    PLAYERSTATUS::ACTIVE,
    PLAYERSTATUS::WAITING,
    PLAYERSTATUS::BUST
};

}
#endif // PLAYERSTATUS_H

