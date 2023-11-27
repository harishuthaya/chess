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

    int getX() const;
    int getY() const;
    void setPosition(int newX, int newY);
    Colour getColour() const;

    // Virtual methods for move validation and success
    virtual bool moveSuccess(const std::string& direction, int steps) = 0;
    virtual bool isValidMove(int newX, int newY) const = 0;
};

#endif