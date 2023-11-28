#include "piece.h"
using namespace std;

Piece::Piece(int x, int y, Colour playerColour, const Board& board) 
    : x{x}, y{x}, playerColour{playerColour}, board{board} {}

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
