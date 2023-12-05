#include "piece.h"
#include "observer.h"
using namespace std;

Piece::Piece(int x, int y, Colour playerColour, const Board& board, Type pieceType, bool hasMoved) 
    : x{x}, y{y}, playerColour{playerColour}, board{board}, pieceType{pieceType}, observers{}, hasMoved{hasMoved} {}

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

void Piece::attach(Observer *o) {
    observers.emplace_back(o);
    o->notify(*this, x, y);
}

void Piece::notifyObservers(int oldX, int oldY) const {
    // notify all observers
    for (auto ob : observers) {
        ob->notify(*this, oldX, oldY);
    }
}

bool Piece::getHasMoved() const {
    return this->hasMoved;
}

void Piece::setHasMoved(bool flag) {
    hasMoved = flag;
}
