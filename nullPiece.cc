#include "nullPiece.h"

NullPiece::NullPiece(int x, int y, const Board& board) 
    : Piece(x, y, Colour::NullColour, board, Type::Nullpiece) {}

bool NullPiece::isValidMove(int newX, int newY) const {
    return false;
}

MoveResult NullPiece::moveSuccess(int newX, int newY) {
    return MoveResult::Failure;
}
