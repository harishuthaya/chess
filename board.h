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


class Board {
    struct Move {
        int lastOldX;
        int lastOldY;
        Piece* lastMove;
        MoveResult moveResult;
        bool lastMoveHasMoveState;
        bool lastCapturedHasMoveState;
        std::unique_ptr<Piece> lastCaptured;

        Move(int lastOldX, int lastOldY, Piece* lastMove, MoveResult moveResult, bool lastMoveHasMoveState, bool lastCapturedHasMoveState, std::unique_ptr<Piece>&& lastCaptured): 
            lastOldX(lastOldX), lastOldY{lastOldY}, lastMove{lastMove}, moveResult(moveResult), lastMoveHasMoveState{lastMoveHasMoveState}, lastCapturedHasMoveState{lastCapturedHasMoveState}, lastCaptured{std::move(lastCaptured)} {

        }
    };
    std::vector<std::vector<std::unique_ptr<Piece>>> board;
    WinState winState;
    const int boardSize = 8;
    TextDisplay *td;
    GraphicsDisplay *gd;
    Piece* whiteKing;
    Piece* blackKing;
    Piece* lastMove;            // last piece moved
    int lastOldX;               // last move's old X coordinate
    int lastOldY;               // last move's old Y coorindate
    std::unique_ptr<Piece> lastCaptured;  // last piece cpatured
    MoveResult lastMoveResult;          // last moveResult
    bool lastMoveHasMoveState;          // last moved piece's previous move state
    bool lastCapturedHasMoveState;      // last captured piece's previous move state
    int whiteKingNum = 0;
    int blackKingNum = 0;
    std::stack<Move> movesHistory;      // history of moves
    
    public:
        Board(TextDisplay *td, GraphicsDisplay *gd);
        void clear();
        
        // Initializes the board with the standard board setup
        void init();
        virtual ~Board() = default;

        // Attempts to perform a move and return whether successful or not
        bool moveSuccess(int x, int y, int newX, int newY, Colour playerColour);

        // Attemps to perform a move, including pawn promotion, and return whether successful or not
        bool moveSuccess(int x, int y, int newX, int newY, Colour playerColour, char c);

        // Add or remove pieces on the board
        void addPiece(char piece, int x, int y);
        void removePiece(int x, int y);
        
        // Returns true if a piece is under attack, false otherwise
        bool isUnderAttack(int x, int y, Colour playerColour) const;

        // Returns true if check, false otherwise
        bool isCheck(Colour playerColour) const;

        // Returns true if checkmate, false otherwise
        bool isCheckmate(Colour playerColour);

        // Returns true if stalemate, false otherwise
        bool isStalemate(Colour playerColour);
        
        // Used for proper setup intialization, determine correct placement of pawns and number of kings
        bool isOneKing() const;
        bool isPawnCorrect() const;
        
        // Simulate a move (dummy move)
        bool simulateMove(int x, int y, int newX, int newY, Colour playerColour);

        // Undos previous move
        bool undoMove(bool realMove);

        // Getters
        MoveResult getLastMoveResult() const;
        WinState getWinState();
        int getLastOldX() const;
        int getLastOldY() const;
        Piece* getPiece(int x, int y) const;
        Piece* getLastMove() const;
        int getSize() const;

        friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif
