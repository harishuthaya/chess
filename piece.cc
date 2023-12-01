#include "piece.h"
#include "observer.h"
using namespace std;

Piece::Piece(int x, int y, Colour playerColour, const Board& board, Type pieceType) 
    : x{x}, y{y}, playerColour{playerColour}, board{board}, pieceType{pieceType}, observers{} {}

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
    int oldX = x;
    int oldY = y;
    x = newX;
    y = newY;
    notifyObservers(oldX, oldY);
}

bool Piece::isEmpty() const {
    return pieceType == Type::Nullpiece;
};

Type Piece::getType() const {
    return pieceType;
}

void Piece::attach(Observer *o) {
    observers.emplace_back(o);
    o->notify(*this, x, y);
}

void Piece::notifyObservers(int oldX, int oldY) const {
    for (auto ob : observers) {
        ob->notify(*this, oldX, oldY);
    }
}
