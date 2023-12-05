#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include "piece.h"
#include "player.h"

class Human: public Player {
    public:
        Human(Colour colour);

        // Returns a move
        std::vector<std::string> getMove() override;

        // Returns a piece option for pawn position
        char getPromotion() const override;
};

#endif
