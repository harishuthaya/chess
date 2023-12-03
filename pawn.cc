#include "pawn.h"
#include <cmath>
#include <iostream>
using namespace std;

// Existing code is for Knight.
// Can move one forward, two forward, diagonal, and can only move forward in one way. 
// Once it reaches other end, needs to be able to swap to another type of piece. 
// Start by just coding the regular movement, then add en passant and switching its piece type once it reaches other end

// Only allowed to move forward one if nothing obstructing
// Only allowed to move forward two if nothing obstructing and hasn't moved yet. 
// Only allowed to move one diagonal one if enemy is there

// Then we have en passant and replacing with rook, knight, bishop, or queen. 

Pawn::Pawn(int x, int y, Colour playerColour, const Board& board) 
    : Piece(x, y, playerColour, board, Type::Pawn) {}

MoveResult Pawn::moveSuccess(int newX, int newY) {
    if (!isValidMove(newX, newY)) {
        cout << "invalid move!" << endl;
        return MoveResult::Failure;
    }
    Piece* targetPiece = board.getPiece(newX, newY);
    if (!targetPiece->isEmpty() && targetPiece->getColour() != this->getColour()) {
        setPosition(newX, newY);
        setHasMoved(true);
        // Make sure only works with correct side
        return (newX == 0 || newX == board.getSize() - 1) ? MoveResult::Replace : MoveResult::Move;
    }

    setPosition(newX, newY);
    setHasMoved(true);
    int directionY = (getColour() == Colour::White) ? -1 : 1;
    cout << "Good before the check " << endl;
    if (board.getLastMove()) cout << "Hello" << endl;
    cout << "Good after this" << endl;
    if (newY == 0 || newY == board.getSize() - 1) return MoveResult::Replace;
    else if (board.getPiece(newX, newY)->isEmpty() && board.getLastMove()->getX() == newX && board.getLastMove()->getY() == getY() 
            && board.getLastOldY() == newY && board.getLastOldX() == newX + directionY && board.getLastMove() && board.getLastMove()->getType() == Type::Pawn) {
                cout << "crashing here" << endl;
                return MoveResult::EnPassant;
                
    }
    else return MoveResult::Move;
}

bool Pawn::isValidMove(int newX, int newY) const {
    // White pawns start at the bottom of the board and can only move up (-1)
    int directionY = (getColour() == Colour::White) ? -1 : 1; // Rename to something relating to Y. 
    int deltaX = newX - getX();
    int deltaY = newY - getY();
    Piece* destinationPiece = board.getPiece(newX, newY);

    // Make this simplified and more readable
    // Better style to just have one for true and one for false? 
    if (deltaX / abs(deltaX) != directionY) {
        cout << "False cuz not right direction" << endl;
        return false;
    } else if (abs(deltaY) == 1 && deltaX == directionY && ((!destinationPiece->isEmpty() && !(destinationPiece->getColour() == this->getColour()))
        || (destinationPiece->isEmpty() && board.getLastMove()->getX() == newX && board.getLastMove()->getY() == getY() 
            && board.getLastOldY() == newY && board.getLastOldX() == newX + directionY && board.getLastMove()->getType() == Type::Pawn))) {
        // Need to check for enpassant here.
        // Need to check the old and new X and Y and the piecetype. 
        return true;
    } else if (deltaY == 0 && deltaX == 2 && !getHasMoved() && destinationPiece->isEmpty()) {
        Piece* inBetween = board.getPiece(x, y + directionY);
        cout << "Cuz in between its false" << endl;
        return inBetween->isEmpty();
        // This is a move forward by 2 attempt
        // Then need to check the pos they are going through as well
    } else if (deltaY == 0 && abs(deltaX) == 1 && destinationPiece->isEmpty()) {
        return true;
    } else {
        // Find out if there is a way to add conditions to first if and can move else to the one above
        cout << "Ended up in this else case somehow" << endl;
        return false;
    }

    // Knight's code below:
    // int deltaX = abs(newX - getX());
    // int deltaY = abs(newY - getY());

    // Piece* destinationPiece = board.getPiece(newX, newY);
    // if (!destinationPiece->isEmpty() && destinationPiece->getColour() == this->getColour()) {    
    //     return false;
    // }

    // return (deltaX == 2 && deltaY == 1) || (deltaX == 1 && deltaY == 2);
}