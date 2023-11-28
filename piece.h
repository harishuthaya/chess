#ifndef PIECE_H
#define PIECE_H

#include <string>
#include "board.h"

enum class Colour { Black = 1, White, Green, Blue };

class Piece {
    int x, y;
    Colour playerColour;
    const Board& board;

  public:
    Piece(int x, int y, Colour playerColour, const Board& board);
    virtual ~Piece() = default;

    int getX() const;
    int getY() const;
    void setPosition(int newX, int newY);
    Colour getColour() const;

    // Virtual methods for move validation and success
    virtual bool moveSuccess(int newX, int newY) = 0;
    virtual bool isValidMove(int newX, int newY) const = 0;
};

#endif
