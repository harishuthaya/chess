#ifndef NULLPIECE_H
#define NULLPIECE_H

#include "piece.h"

class NullPiece : public Piece {
public:
    NullPiece(int x, int y, const Board& board);

    MoveResult moveSuccess(int newX, int newY) override;
    bool isValidMove(int newX, int newY) const override;
};

#endif
