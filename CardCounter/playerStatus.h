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
inline std::string toString(PLAYERSTATUS playerStatus)
{
    switch (playerStatus) {
    case PLAYERSTATUS::ACTIVE:
        return "Active";
    case PLAYERSTATUS::BUST:
        return "Bust";
    case PLAYERSTATUS::WAITING:
        return "Waiting";
    case PLAYERSTATUS::STAND:
        return "Stand";
    }

    return "Unknown player status";
}

/**
 * @brief operator << Prints out the string of the PLAYERSTATUS when used with the ostream operator
 * @param os The stream to add the string to
 * @param PLAYERSTATUS The PLAYERSTATUS to convert
 * @return The ostream with the PLAYERSTATUS as a string
 */
inline std::ostream& operator<<(std::ostream& os, PLAYERSTATUS playerStatus) {
    return os << toString(playerStatus);
}

/**
 * @brief allPLAYERSTATUSs An array of all the PLAYERSTATUS values
 */
inline constexpr PLAYERSTATUS allPlayerStatus[] = {
    PLAYERSTATUS::STAND,
    PLAYERSTATUS::ACTIVE,
    PLAYERSTATUS::WAITING,
    PLAYERSTATUS::BUST
};

}
#endif // PLAYERSTATUS_H

