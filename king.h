#ifndef KING_H
#define KING_H

#include "piece.h"
#include "board.h"

class King: public Piece {
    bool hasMoved;
    
    King(int x, int y, Colour playerColour, const Board& board);

    MoveResult moveSuccess(int newX, int newY) override;
    bool isValidMove(int newX, int newY) const override;
    bool getHasMoved() const;
};
#endif
