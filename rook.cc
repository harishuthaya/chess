#include "rook.h"
#include <cmath>
#include <iostream>
using namespace std;

Rook::Rook(int x, int y, Colour playerColour, const Board& board):
    Piece(x, y, playerColour, board, Type::Rook) {

}

MoveResult Rook::moveSuccess(int newX, int newY) {
    // Check if the move is valid for a Rook
    if (!isValidMove(newX, newY)) {
        return MoveResult::Failure;
    }

    // Get the target piece at the new position
    Piece* targetPiece = board.getPiece(newX, newY);
    this->hasMoved = true;

    // If the target spot is occupied by an enemy piece, capture it
    if (!targetPiece->isEmpty() && targetPiece->getColour() != this->getColour()) {
        setPosition(newX, newY);
        return MoveResult::Capture;
    }

    setPosition(newX, newY);
    return MoveResult::Move;
}

bool Rook::isValidMove(int newX, int newY) const {
    int deltaX = newX - getX();
    int deltaY = newY - getY();

    // Rook moves must be either horizontal or vertical, not diagonal
    if (deltaX != 0 && deltaY != 0) {
        return false;
    }

    int stepX = (deltaX == 0) ? 0 : (deltaX / abs(deltaX));
    int stepY = (deltaY == 0) ? 0 : (deltaY / abs(deltaY));

    int currentX = getX() + stepX;
    int currentY = getY() + stepY;

    // Check for blocking pieces
    while (currentX != newX || currentY != newY) {
        if (!board.getPiece(currentX, currentY)->isEmpty()) {
            return false;
        }
        currentX += stepX;
        currentY += stepY;
    }

    Piece *destinationPiece = board.getPiece(newX, newY);

    // Check the destination square is empty or opposite colour
    if (destinationPiece->isEmpty() || destinationPiece->getColour() != this->getColour()) {
        return true;
    }

    return false;
}
