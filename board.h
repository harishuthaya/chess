#ifndef BOARD_H
#define BOARD_H

#include <vector.h>
#include <string.h>
#include "piece.h"

enum class WinState { Win, Lose, Tie };

const int BOARD_SIZE = 8;

class Board {
    std::vector<std::vector<Piece*>> board;
    WinState winState;
    public:
        Board();
        virtual ~Board() = default;

        bool moveSuccess(int newX, int newY);
        WinState getWinState();
        void addPiece(char piece, int x, int y);
        void removePiece(int x, int y);
};

#endif