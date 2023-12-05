#include "queen.h"
#include <cmath>
#include <iostream>
using namespace std;

Queen::Queen(int x, int y, Colour playerColour, const Board& board) 
    : Piece(x, y, playerColour, board, Type::Queen) {}

MoveResult Queen::moveSuccess(int newX, int newY) {
    // Check if the move is valid for a Queen
    if (!isValidMove(newX, newY)) {
        return MoveResult::Failure;
    }
    Piece* targetPiece = board.getPiece(newX, newY);

    // If the target piece is an enemy, capture it
    if (!targetPiece->isEmpty() && targetPiece->getColour() != this->getColour()) {
        setPosition(newX, newY);
        return MoveResult::Capture;
    }

    setPosition(newX, newY);
    return MoveResult::Move;
}

bool Queen::isValidMove(int newX, int newY) const {
    int deltaX = newX - getX();
    int deltaY = newY - getY();

    // Check if the move is horizontal/vertical or diagonal
    bool isHorizontalVertical = (deltaX == 0 || deltaY == 0);
    bool isDiagonal = (abs(deltaX) == abs(deltaY));
    if (!isHorizontalVertical && !isDiagonal) {
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
    Piece* destinationPiece = board.getPiece(newX, newY);
    
    // Move is valid if the destination is empty or contains an enemy piece
    if (destinationPiece->isEmpty() || destinationPiece->getColour() != this->getColour()) {    
        return true;
    }

    return false;
}
