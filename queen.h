#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "board.h"

class Queen : public Piece {
public:
    Queen(int x, int y, Colour playerColour, const Board& board);

    // Returns the MoveResult for a move and executes the move if it is a valid move
    MoveResult moveSuccess(int newX, int newY) override;

    // Returns true if a move is valid and false otherwise
    bool isValidMove(int newX, int newY) const override;
};

#endif
