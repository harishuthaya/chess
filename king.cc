#include "rook.h"
#include <cmath>
#include <iostream>
using namespace std;

King::Rook(int x, int y, Colour playerColour, const Board& board):
    Piece(x, y, playerColour, board, Type::King), hasMoved{false} {

}

bool King::getHasMoved() const {
    return this->hasMoved();
}

MoveResult King::moveSuccess(int newX, int newY) {
    if (!isValidMove(newX, newY)) {
        return MoveResult::Failure;
    }
    Piece* targetPiece = board.getPiece(newX, newY);
    this->hasMoved = true;

    if (!targetPiece.isEmpty() && targetPiece.getColour() != this->getColour()) {
        int oldX = x;
        int oldY = y;
        setPosition(newX, newY);
        notifyObservers(oldX, oldY);
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

    int stepX = (deltaX == 0) ? 0 : (deltaX / abs(deltaX));
    int stepY = (deltaY == 0) ? 0 : (deltaY / abs(deltaY));

    Piece *destinationPiece = board.getPiece(newX, newY);
    if (destinationPiece->isEmpty() || destinationPiece->getColour() != this->getColour()) {
        return true;
    }

    return false;
}