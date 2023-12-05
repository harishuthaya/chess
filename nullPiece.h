#ifndef NULLPIECE_H
#define NULLPIECE_H

#include "piece.h"

class NullPiece : public Piece {
public:
    NullPiece(int x, int y, const Board& board);

    // Always returns Failure since nullPiece cannot move
    MoveResult moveSuccess(int newX, int newY) override;
        
    // Always returns false since nullPiece cannot move
    bool isValidMove(int newX, int newY) const override;
};

#endif
