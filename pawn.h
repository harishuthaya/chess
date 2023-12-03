#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include "board.h"

class Pawn : public Piece {
    public:
        Pawn(int x, int y, Colour playerColour, const Board& board);

        MoveResult moveSuccess(int newX, int newY) override;
        bool isValidMove(int newX, int newY) const override;
};

#endif
