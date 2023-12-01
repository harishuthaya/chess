#include "rook.h"
#include <cmath>
#include <iostream>
using namespace std;

Rook::Rook(int x, int y, Colour playerColour, const Board& board):
    Piece(x, y, playerColour, board, Type::Rook): hasMoved{false} {

}

bool Rook::getHasMoved() const {
    return this->hasMoved();
}

MoveResult Rook::moveSuccess(int newX, int newY) {
    if (!isValidMove(newX, newY)) {
        return MoveResult::Failure;
    }
    Piece* targetPiece = board.getPiece(newX, newY);
    this->hasMoved = true;

    if (!targetPiece.isEmpty() && targetPiece.getColour() != this->getColour()) {
        setPosition(newX, newY);
        return MoveResult::Capture;
    }

    setPosition(newX, newY);
    return MoveResult::Move;
}

bool Rook::isValidMove(int newX, int newY) const {
    int deltaX = newX - getX();
    int deltaY = newY - getY();

    if (deltaX != 0 && deltaY != 0) {
        return false;
    }

    int stepX = (deltaX == 0) ? 0 : (deltaX / abs(deltaX));
    int stepY = (deltaY == 0) ? 0 : (deltaY / abs(deltaY));

    int currentX = getX() + stepX;
    int currentY = getY() + stepY;

    while (currentX != newX || currentY != currentY) {
        if (!board.getPiece(currentX, currentY)->isEmpty()) {
            return false;
        }
        currentX += stepX;
        currentY += stepY;
    }

    Piece *destinationPiece = board.getPiece(newX, newY);
    if (destinationPiece->isEmpty() || destinationPiece->getColour() != this->getColour()) {
        return true;
    }

    return false;
}