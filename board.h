#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <memory>
#include "piece.h"
#include "queen.h"
#include "nullPiece.h"
#include "bishop.h"
#include "textdisplay.h"
#include "king.h"
#include "rook.h"

class Piece;

enum class WinState { Win, Lose, Tie };

class Board {
    std::vector<std::vector<std::unique_ptr<Piece>>> board;
    WinState winState;
    const int boardSize = 8;
    TextDisplay *td;
    Piece* whiteKing;
    Piece* blackKing;

    public:
        Board(TextDisplay *td);
        virtual ~Board() = default;

        bool moveSuccess(int x, int y, int newX, int newY, Colour playerColour);
        WinState getWinState();
        void addPiece(char piece, int x, int y, int playerID);
        void removePiece(int x, int y);
        int getSize() const;
        bool isUnderAttack(int x, int y, Colour playerColour) const;
        bool isCheck(Colour playerColour) const;
        bool isCheckmate(Colour playerColour) const;
        Piece* getPiece(int x, int y) const;
        bool isOneKing() const;
        bool isPawnCorrect() const;
        friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif