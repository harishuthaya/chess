#ifndef PLAYER_H
#define PLAYER_H

#include "piece.h"
#include <string>
#include <vector>

class Player {
    Colour colour;
    float score;

    public:
        Player(Colour colour);
        virtual ~Player() = default;
        virtual std::vector<std::string> getMove() = 0;
        float getScore() const;
        Colour getColour() const;
        void incrementScore(float i);
        virtual char getPromotion() const = 0;
};

#endif