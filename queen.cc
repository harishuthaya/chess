#include "queen.h"
#include <cmath>

// REMOVE
#include <iostream>
using namespace std;

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
    std::cout << "x and y " << getX() << " " << getY() << endl;
    std::cout << "newx and newy " << newX << " " << newY << endl;
    std::cout << "deltax and deltay " << deltaX << " " << deltaY << endl;

    bool isHorizontalVertical = (deltaX == 0 || deltaY == 0);
    cout << "isHorizontalvert " << isHorizontalVertical << endl;
    bool isDiagonal = (abs(deltaX) == abs(deltaY));
    cout << "isDiagonal " << isDiagonal << endl;
    if (!isHorizontalVertical && !isDiagonal) {
        std::cout << "false" << endl;
        return false;
    }
    cout << "made it here1" << endl;

    int stepX = (deltaX == 0) ? 0 : (deltaX / abs(deltaX));
    int stepY = (deltaY == 0) ? 0 : (deltaY / abs(deltaY));

    int currentX = getX() + stepX;
    int currentY = getY() + stepY;
    cout << "made it here2" << endl;

    while (currentX != newX || currentY != newY) {
        if (board.getPiece(currentX, currentY)->isEmpty()) {
            return false;
        }
        currentX += stepX;
        currentY += stepY;
    }
    cout << "made it here3" << endl;
    Piece* destinationPiece = board.getPiece(newX, newY);
    if (destinationPiece->isEmpty() && destinationPiece->getColour() == this->getColour()) {
        return false;
    }

    return true;

}
