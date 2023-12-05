#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>
#include "piece.h"
#include "player.h"
#include "board.h"

class Computer: public Player {
    int level;
    Board *board;

    std::string convertCoords(int x, int y) const;
    std::vector<std::string> generateLevel1();
    std::vector<std::string> generateLevel2();
    std::vector<std::string> generateLevel3();
    std::vector<std::string> generateLevel4();
    int evaluateBoard();
    int minimax(int depth, int alpha, int beta, bool maximizingPlayer);
    std::vector<std::vector<std::string>> generateAllMoves();

    public: 
        Computer(Colour colour, int level, Board *board);
        std::vector<std::string> getMove() override;
        char getPromotion() const override;
};

#endif
