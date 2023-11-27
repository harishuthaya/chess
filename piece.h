#ifndef PIECE_H
#define PIECE_H

#include <string>

enum class Colour { Black, White, Green, Blue };

class Piece {
    int x, y;
    Colour playerColour;

  public:
    Piece(int x, int y, Colour playerColour);
    virtual ~Piece() = default;
    virtual bool moveSuccess(const std::string& direction, int steps) = 0;
};

