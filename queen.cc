#include "queen.h"
#include <cmath>
#include <iostream>

Queen::Queen(int x, int y, Colour playerColour, const Board& board) 
    : Piece(x, y, playerColour, board, Type::Queen) {}

MoveResult Queen::moveSuccess(int newX, int newY) {
    if (!isValidMove(newX, newY)) {
        return MoveResult::Failure;
    }

    Piece* targetPiece = board.getPiece(newX, newY);
    if (targetPiece->isEmpty() && targetPiece->getColour() != this->getColour()) {
        setPosition(newX, newY);
        return MoveResult::Capture;
    }

    setPosition(newX, newY);
    return MoveResult::Move;

}

bool Queen::isValidMove(int newX, int newY) const {
    int deltaX = newX - getX();
    int deltaY = newY - getY();
    std::cout << getX() << " " << getY();

    bool isHorizontalVertical = (deltaX == 0 || deltaY == 0);
    bool isDiagonal = (abs(deltaX) == abs(deltaY));
    if (!isHorizontalVertical && !isDiagonal) {
        std::cout << "false";
        return false;
    }

    int stepX = (deltaX == 0) ? 0 : (deltaX / abs(deltaX));
    int stepY = (deltaY == 0) ? 0 : (deltaY / abs(deltaY));

    int currentX = getX() + stepX;
    int currentY = getY() + stepY;

    while (currentX != newX || currentY != newY) {
        if (board.getPiece(currentX, currentY)->isEmpty()) {
            return false;
        }
        currentX += stepX;
        currentY += stepY;
    }

    Piece* destinationPiece = board.getPiece(newX, newY);
    if (destinationPiece->isEmpty() && destinationPiece->getColour() == this->getColour()) {
        return false;
    }

    return true;

}
