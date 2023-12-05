#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>
#include "piece.h"
#include "player.h"
#include "board.h"

class Computer: public Player {
    int level;
    Board &board;

    std::vector<std::string> generateLevel1();
    std::vector<std::string> generateLevel2();
    std::vector<std::string> generateLevel3();
    std::vector<std::string> generateLevel4();

    public: 
        Computer(Colour colour, int level);
        std::vector<std::string> getMove() const override;
        char getPromotion() const override;
};

#endif
