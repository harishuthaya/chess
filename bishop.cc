#include "bishop.h"
#include <cmath>
#include <iostream>
using namespace std;

Bishop::Bishop(int x, int y, Colour playerColour, const Board& board) 
    : Piece(x, y, playerColour, board, Type::Bishop) {}

MoveResult Bishop::moveSuccess(int newX, int newY) {
    // Check if mvoe is valid
    if (!isValidMove(newX, newY)) {
        return MoveResult::Failure;
    }

    Piece* targetPiece = board.getPiece(newX, newY);
    // Check if move is a capture move
    if (!targetPiece->isEmpty() && targetPiece->getColour() != this->getColour()) {
        setPosition(newX, newY);
        return MoveResult::Capture;
    }

    setPosition(newX, newY);
    return MoveResult::Move;
}

bool Bishop::isValidMove(int newX, int newY) const {
    int deltaX = newX - getX();
    int deltaY = newY - getY();

    // Check if the move is diagonal
    if (abs(deltaX) != abs(deltaY)) {
        return false;
    }

    int stepX = (deltaX / abs(deltaX));
    int stepY = (deltaY / abs(deltaY));

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

    // Check if there is piece on end point or if it is opposite color piece
    Piece* destinationPiece = board.getPiece(newX, newY);
    if (destinationPiece->isEmpty() || destinationPiece->getColour() != this->getColour()) {  
        return true;
    }

    return false;
}
