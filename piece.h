#ifndef PIECE_H
#define PIECE_H

#include <string>
#include "subject.h"

class Board;

enum class Colour { Black = 1, White, Green, Blue, NullColor };
enum class MoveResult { Move, Capture, Failure };
enum class Type { Queen, King, Bishop, Nullpiece };

class Piece: public Subject {
  protected:
    int x, y;
    Colour playerColour;
    const Board& board;
    Type pieceType;

  public:
    Piece(int x, int y, Colour playerColour, const Board& board, Type pieceType);
    virtual ~Piece() = default;

    int getX() const;
    int getY() const;
    void setPosition(int newX, int newY);
    Colour getColour() const;
    bool isEmpty() const;
    Type getType() const;

    // Virtual methods for move validation and success
    virtual MoveResult moveSuccess(int newX, int newY) = 0;
    virtual bool isValidMove(int newX, int newY) const = 0;
};

#endif
