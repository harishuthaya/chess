#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"
#include "board.h"

class Knight : public Piece {
public:
    Knight(int x, int y, Colour playerColour, const Board& board);

    MoveResult moveSuccess(int newX, int newY) override;
    bool isValidMove(int newX, int newY) const override;
};

#endif
