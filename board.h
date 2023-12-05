#ifndef BOARD_H
#define BOARD_H

#include <stack>
#include <vector>
#include <string>
#include <memory>
#include "piece.h"
#include "queen.h"
#include "nullPiece.h"
#include "bishop.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "king.h"
#include "rook.h"
#include "pawn.h"

class Piece;

enum class WinState { Player1Win, Player2Win, Tie, InProgress };

struct Move {
    int lastOldX;
    int lastOldY;
    Piece* lastMove;
    MoveResult moveResult;
    bool lastMoveHasMoveState;
    bool lastCapturedHasMoveState;
    std::unique_ptr<Piece> lastCaptured;

    Move(int lastOldX, int lastOldY, Piece* lastMove, MoveResult moveResult, bool lastMoveHasMoveState,
    bool lastCapturedHasMoveState, std::unique_ptr<Piece>&& lastCaptured)
        : lastOldX(lastOldX), lastOldY{lastOldY}, lastMove{lastMove}, moveResult(moveResult), 
        lastMoveHasMoveState{lastMoveHasMoveState}, lastCapturedHasMoveState{lastCapturedHasMoveState},
        lastCaptured{std::move(lastCaptured)} {}
};


class Board {
    std::vector<std::vector<std::unique_ptr<Piece>>> board;
    WinState winState;
    const int boardSize = 8;
    TextDisplay *td;
    GraphicsDisplay *gd;
    Piece* whiteKing;
    Piece* blackKing;
    Piece* lastMove;
    int lastOldX;
    int lastOldY;
    std::unique_ptr<Piece> lastCaptured;
    MoveResult lastMoveResult;
    bool lastMoveHasMoveState;
    bool lastCapturedHasMoveState;
    int whiteKingNum = 0;
    int blackKingNum = 0;
    std::stack<Move> movesHistory;

    public:
        Board(TextDisplay *td, GraphicsDisplay *gd);
        void clear();
        void init();
        virtual ~Board() = default;
        bool moveSuccess(int x, int y, int newX, int newY, Colour playerColour);
        bool moveSuccess(int x, int y, int newX, int newY, Colour playerColour, char c);
        WinState getWinState();
        void addPiece(char piece, int x, int y, int playerID);
        void removePiece(int x, int y);
        int getSize() const;
        bool isUnderAttack(int x, int y, Colour playerColour) const;
        bool isCheck(Colour playerColour) const;
        bool isCheckmate(Colour playerColour);
        bool isStalemate(Colour playerColour);
        Piece* getPiece(int x, int y) const;
        Piece* getLastMove() const;
        int getLastOldX() const;
        int getLastOldY() const;
        bool isOneKing() const;
        bool isPawnCorrect() const;
        friend std::ostream &operator<<(std::ostream &out, const Board &b);
        bool simulateMove(int x, int y, int newX, int newY, Colour playerColour);
        bool undoMove(bool realMove);
};

#endif
