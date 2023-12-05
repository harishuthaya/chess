#include "king.h"
#include <cmath>
#include <iostream>
using namespace std;

King::King(int x, int y, Colour playerColour, const Board& board):
    Piece(x, y, playerColour, board, Type::King) {

}

MoveResult King::moveSuccess(int newX, int newY) {
    int deltaX = newX - getX();
    int deltaY = newY - getY();

    // Check for castling move.
    if (deltaX == 0 && (deltaY == 2 || deltaY == -2)) {
        if (canCastle(newY)) {
            int rookY = (deltaY == 2) ? board.getSize() - 1 : 0;
            int rookNewY = (deltaY == 2) ? newY - 1 : newY + 1;
            Piece* rook = board.getPiece(getX(), rookY);
            rook->setPosition(newX, rookNewY);
            rook->setHasMoved(true);

            setPosition(newX, newY);
            this->hasMoved = true;
            return MoveResult::Castle;
        } else {
            return MoveResult::Failure;
        }
    }

    // Check for other standard moves.
    if (!isValidMove(newX, newY)) {
        return MoveResult::Failure;
    }
    Piece* targetPiece = board.getPiece(newX, newY);
    this->hasMoved = true;

    // Check for capturing move
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

    // King can move at most one square in any direction.
    if (abs(deltaX) > 1 || abs(deltaY) > 1) {
        return false;
    }

    Piece *destinationPiece = board.getPiece(newX, newY);
    // Valid move to an empty square or to capture an opponent's piece.
    if (destinationPiece->isEmpty() || destinationPiece->getColour() != this->getColour()) {
        return true;
    }

    return false;
}

bool King::canCastle(int newY) const {
    // Cannot castle if the king has moved or is in check.
    if (hasMoved || board.isCheck(getColour())) {
        return false;
    }

    int direction = (newY - getY()) > 0 ? 1 : -1;
    int rookY = (direction == 1) ? board.getSize() - 1 : 0;
    Piece* rook = board.getPiece(getX(), rookY);

    // Check if there's a rook at the expected position and it hasn't moved.
    if (rook->getType() == Type::Rook && !rook->getHasMoved()) {

        // Check if the squares between the king and rook are empty and not put king under attack.
        for (int y = getY() + direction; y != rookY; y += direction) {
            if (!board.getPiece(getX(), y)->isEmpty()) {
                return false;
            }
        }

        for (int y = getY(); y != newY + direction; y += direction) {
            if (board.isUnderAttack(getX(), y, getColour())) {
                return false;
            }
        }
        return true;
    }
    return false;
}
