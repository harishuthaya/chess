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
        virtual std::vector<std::string> getMove() const = 0;
        int getScore() const;
        void incrementScore(float i);
        virtual char getPromotion() const = 0;
};

#endif