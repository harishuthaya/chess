#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"
#include "board.h"
#include "knight.h"

class Bishop : public Piece {
public:
    Bishop(int x, int y, Colour playerColour, const Board& board);

    MoveResult moveSuccess(int newX, int newY) override; // moveSucess returns the state of move
                                                         // (Move, Capture, Failure) for Pawn Piece
                                                         // and executes the move if it is valid

    bool isValidMove(int newX, int newY) const override; // isValidMove returns whether a move is
                                                         // valid for Pawn Piece.
};

#endif
