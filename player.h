#ifndef PLAYER_H
#define PLAYER_H

#include "piece.h"
#include <string>
#include <vector>

class Player {
    Colour colour;

    public:
        Player(Colour colour);
        virtual ~Player() = default;
        virtual std::vector<std::string> getMove() = 0;
        Colour getColour() const;
        virtual char getPromotion() const = 0;
};

#endif
