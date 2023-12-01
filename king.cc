#include "king.h"
#include <cmath>
#include <iostream>
using namespace std;

King::King(int x, int y, Colour playerColour, const Board& board):
    Piece(x, y, playerColour, board, Type::King), hasMoved{false} {

}

bool King::getHasMoved() const {
    return this->hasMoved;
}

MoveResult King::moveSuccess(int newX, int newY) {
    if (!isValidMove(newX, newY)) {
        return MoveResult::Failure;
    }
    Piece* targetPiece = board.getPiece(newX, newY);
    this->hasMoved = true;

    if (!targetPiece->isEmpty() && targetPiece->getColour() != this->getColour()) {
        setPosition(newX, newY);
        return MoveResult::Capture;
    }

    setPosition(newX, newY);
    return MoveResult::Move;
}

bool King::isValidMove(int newX, int newY) const {
    int deltaX = newX - getX();
    int deltaY = newY - getY();

    if (abs(deltaX) > 1 || abs(deltaY) > 1) {
        return false;
    }

    Piece *destinationPiece = board.getPiece(newX, newY);
    if (destinationPiece->isEmpty() || destinationPiece->getColour() != this->getColour()) {
        return true;
    }

    return false;
}