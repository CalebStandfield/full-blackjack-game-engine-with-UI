#ifndef STATISTICS_H
#define STATISTICS_H

#include <QObject>

namespace Move
{
enum class MOVE {
    HIT,
    DOUBLE,
    SPLIT,
    STAND
};

/**
 * @brief toString Converts a MOVE to a string
 * @param move The MOVE to convert
 * @return A string of the MOVE provided
 */
inline std::string toString(MOVE move)
{
    switch (move) {
    case MOVE::HIT:
        return "Hit";
    case MOVE::DOUBLE:
        return "Double";
    case MOVE::SPLIT:
        return "Split";
    case MOVE::STAND:
        return "Stand";
    }

    return "Unknown move";
}
}

using Move::MOVE;

class Statistics : public QObject
{
    Q_OBJECT
public:
    explicit Statistics(QObject *parent = nullptr);

    static const MOVE HardTable[17][10];

    static const MOVE SoftTable[9][10];

    static const MOVE PairTable[10][10];
};

#endif // STATISTICS_H
