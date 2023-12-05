#include "pawn.h"
#include <cmath>
#include <iostream>

using namespace std;

Pawn::Pawn(int x, int y, Colour playerColour, const Board& board, bool hasMoved) :
    Piece(x, y, playerColour, board, Type::Pawn, hasMoved) {
}

MoveResult Pawn::moveSuccess(int newX, int newY) {
    int forwardDirection = (getColour() == Colour::White) ? -1 : 1;
    int deltaX = newX - getX();
    int deltaY = newY - getY();

    // Invalid move, return failure.
    if (!isValidMove(newX, newY)) {
        return MoveResult::Failure;
    }

    setPosition(newX, newY);
    hasMoved = true;


    if (deltaX == forwardDirection && abs(deltaY) == 1) {
        // Attempting to move diagonally
        Piece* targetPiece = board.getPiece(newX, newY);
        if (!targetPiece->isEmpty()) {
            // Capturing a piece.
            return MoveResult::Capture;
        } else {
            // En passant move.
            return MoveResult::EnPassant;
        }
    }
    
    return MoveResult::Move;
}

bool Pawn::isValidMove(int newX, int newY) const {
    int forwardDirection = (getColour() == Colour::White) ? -1 : 1;
    int deltaX = newX - getX();
    int deltaY = newY - getY();

    // Standard forward move (1 square)
    if (deltaY == 0 && deltaX == forwardDirection) {
        return board.getPiece(newX, newY)->isEmpty();
    }

    // Double forward move on first move (2 squares)
    if (!hasMoved && deltaY == 0 && deltaX == 2 * forwardDirection) {
        // Check if both squares are empty
        return board.getPiece(getX() + forwardDirection, getY())->isEmpty() &&
               board.getPiece(newX, newY)->isEmpty();
    }

    // Capture move
    if (deltaX == forwardDirection && abs(deltaY) == 1) {
        // Capture move
        if (board.getPiece(newX, newY)->getColour() != Colour::NullColour && 
            board.getPiece(newX, newY)->getColour() != getColour()) {
                return true;
        }

        // En passant
        Piece* adjacentPawn = board.getPiece(getX(), getY() + deltaY);
        if (!adjacentPawn->isEmpty() && adjacentPawn->getType() == Type::Pawn && 
            adjacentPawn == board.getLastMove() && 
            board.getLastOldX() == getX() + (2 * forwardDirection) && 
            board.getLastOldY() == getY() + deltaY) {
                return true;
            }

    }

    return false;
}
