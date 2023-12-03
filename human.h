#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include "piece.h"
#include "player.h"

class Human: public Player {
    public:
        Human(Colour colour);
        std::vector<std::string> getMove() const override;
};

#endif
