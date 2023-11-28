#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <memory>
#include "piece.h"
#include "queen.h"

class Piece;

enum class WinState { Win, Lose, Tie };

class Board {
    std::vector<std::vector<std::unique_ptr<Piece>>> board;
    WinState winState;
    const int boardSize = 8;
    public:
        Board();
        virtual ~Board() = default;

        bool moveSuccess(int x, int y, int newX, int newY);
        WinState getWinState();
        void addPiece(char piece, int x, int y, int playerID);
        void removePiece(int x, int y);
        int getSize() const;
        Piece* getPiece(int x, int y) const;
};

#endif