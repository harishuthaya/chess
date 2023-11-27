#include "piece.h"

Piece::Piece(int x, int y, Colour playerColour) 
    : x{x}, y{x}, playerColour{playerColour} {}

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
