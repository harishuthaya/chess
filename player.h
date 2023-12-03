#ifndef PLAYER_H
#define PLAYER_H

#include "piece.h"
#include <string>
#include <vector>

class Player {
    Colour colour;
    int score;

    public:
        Player(Colour colour);
        virtual ~Player() = default;
        virtual std::vector<std::string> getMove() const = 0;
        int getScore() const;
        void incrementScore();
};

#endif