#include "piece.h"
using namespace std;

Piece::Piece(int x, int y, Colour playerColour, const Board& board, Type pieceType) 
    : x{x}, y{x}, playerColour{playerColour}, board{board}, pieceType{pieceType} {}

int Piece::getX() const {
    return x;
}

int Piece::getY() const {
    return y;
}

Colour Piece::getColour() const {
    return playerColour;
}

void Piece::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

bool Piece::isEmpty() const {
    return pieceType == Type::Nullpiece;
};

Type Piece::getType() const {
    return pieceType;
}
