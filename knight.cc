#include "knight.h"
#include <cmath>
#include <iostream>
using namespace std;

Knight::Knight(int x, int y, Colour playerColour, const Board& board) 
    : Piece(x, y, playerColour, board, Type::Knight) {}

MoveResult Knight::moveSuccess(int newX, int newY) {
    if (!isValidMove(newX, newY)) {
        return MoveResult::Failure;
    }
    Piece* targetPiece = board.getPiece(newX, newY);
    if (!targetPiece->isEmpty() && targetPiece->getColour() != this->getColour()) {
        setPosition(newX, newY);
        return MoveResult::Capture;
    }

    setPosition(newX, newY);
    return MoveResult::Move;
}

bool Knight::isValidMove(int newX, int newY) const {
    int deltaX = abs(newX - getX());
    int deltaY = abs(newY - getY());
    
    Piece* destinationPiece = board.getPiece(newX, newY);
    if (!destinationPiece->isEmpty() && destinationPiece->getColour() == this->getColour()) {    
        return false;
    }

    return (deltaX == 2 && deltaY == 1) || (deltaX == 1 && deltaY == 2);
}
