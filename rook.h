#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include "board.h"

class Rook: public Piece {
    bool hasMoved;
    
    Rook(int x, int y, Colour playerColour, const Board& board);

    MoveResult moveSuccess(int newX, int newY) override;
    bool isValidMove(int newX, int newY) const override;
    bool getHasMoved() const;
};
#endif
