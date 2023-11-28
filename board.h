#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <memory>
#include "piece.h"

enum class WinState { Win, Lose, Tie };

const int BOARD_SIZE = 8;

class Board {
    std::vector<std::vector<std::unique_ptr<Piece>>> board;
    WinState winState;
    public:
        Board();
        virtual ~Board() = default;

        bool moveSuccess(int newX, int newY);
        WinState getWinState();
        void addPiece(char piece, int x, int y, int playerID);
        void removePiece(int x, int y);
};

#endif