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

        // Virtual method to get a list of valid moves.
        virtual std::vector<std::string> getMove() = 0;

        // Virtual method for getting pawn promotion choice
        virtual char getPromotion() const = 0;

        // Getters
        Colour getColour() const;
};

#endif
