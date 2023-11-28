#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "board.h"

class Queen : public Piece {
public:
    Queen(int x, int y, Colour playerColour, const Board& board);

    MoveResult moveSuccess(int newX, int newY) override;
    bool isValidMove(int newX, int newY) const override;
};

#endif
