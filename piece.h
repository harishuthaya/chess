#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <vector>
#include "observer.h"

class Board;

enum class Colour { Black = 1, White, Green, Blue, NullColour };
enum class MoveResult { Move, Capture, Failure, Replace, EnPassant };
enum class Type { Queen, King, Bishop, Knight, Rook, Pawn, Nullpiece };

class Piece {
  protected:
    int x, y;
    Colour playerColour;
    const Board& board;
    Type pieceType;
    std::vector<Observer*> observers;

  public:
    Piece(int x, int y, Colour playerColour, const Board& board, Type pieceType);
    virtual ~Piece() = default;

    int getX() const;
    int getY() const;
    void setPosition(int newX, int newY);
    Colour getColour() const;
    bool isEmpty() const;
    Type getType() const;
    void attach(Observer *o);
    void notifyObservers(int oldX, int oldY) const;

    // Virtual methods for move validation and success
    virtual MoveResult moveSuccess(int newX, int newY) = 0;
    virtual bool isValidMove(int newX, int newY) const = 0;
};

#endif
