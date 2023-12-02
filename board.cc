#include "board.h"
#include <iostream>
using namespace std;

Board::Board(TextDisplay *td): board{}, td{td} {
    board.resize(boardSize);
    for (int i = 0; i < boardSize; ++i) {
        board[i].resize(boardSize);

        for (int j = 0; j < boardSize; ++j) {
            board[i][j] = make_unique<NullPiece>(i, j, *this);
            board[i][j]->attach(td);
        }
    }
    // Adds the black pieces
    this->addPiece('r', 0, 0, 1);
    this->addPiece('n', 0, 1, 1);
    this->addPiece('b', 0, 2, 1);
    this->addPiece('q', 0, 3, 1);
    this->addPiece('k', 0, 4, 1);
    this->addPiece('b', 0, 5, 1);
    this->addPiece('n', 0, 6, 1);
    this->addPiece('r', 0, 7, 1);
    for (int i = 0; i < boardSize - 1; ++i) {
        this->addPiece('p', 1, i, 1);
    }

    // Adds the white pieces
    this->addPiece('R', boardSize - 1, 0, 2);
    this->addPiece('N', boardSize - 1, 1, 2);
    this->addPiece('B', boardSize - 1, 2, 2);
    this->addPiece('Q', boardSize - 1, 3, 2);
    this->addPiece('K', boardSize - 1, 4, 2);
    this->addPiece('B', boardSize - 1, 5, 2);
    this->addPiece('N', boardSize - 1, 6, 2);
    this->addPiece('R', boardSize - 1, 7, 2);
    for (int i = 0; i < boardSize - 1; ++i) {
        this->addPiece('P', boardSize - 2, i, 2);
    }
}

bool Board::moveSuccess(int x, int y, int newX, int newY) {
    if (newX < 0 || newX >= boardSize || newY < 0 || newY >= boardSize ||
        x < 0 || x >= boardSize || y < 0 || y >= boardSize) {
        return false;
    }

    if (x == newX && y == newY) {
        return false;
    }
    
    MoveResult result = board[x][y]->moveSuccess(newX, newY);
    if (result == MoveResult::Failure) {
        return false;
    } else {
        board[newX][newY] = std::move(board[x][y]);
        board[x][y] = make_unique<NullPiece>(x, y, *this);
        board[x][y]->attach(td);
    }

    return true;
}

WinState Board::getWinState() {
    return this->winState;
}

void Board::addPiece(char piece, int x, int y, int playerID) {
    if (x < 0 || x >= boardSize || y < 0 || y >= boardSize) {
        return;
    }
    board[x][y].reset();
    switch(piece) {
        case 'r':
            board[x][y] = make_unique<Rook>(x, y, Colour::Black, *this);
            break;
        case 'n':
            board[x][y] = make_unique<Knight>(x, y, Colour::Black, *this);
            break;
        case 'b':
            board[x][y] = make_unique<Bishop>(x, y, Colour::Black, *this);
            break;
        case 'q':
            board[x][y] = make_unique<Queen>(x, y, Colour::Black, *this);
            break;
        case 'k':
            board[x][y] = make_unique<King>(x, y, Colour::Black, *this);
            blackKing = board[x][y].get();
            break;
        case 'p':
            board[x][y] = make_unique<NullPiece>(x, y, *this);
            break;
        case 'R':
            board[x][y] = make_unique<Rook>(x, y, Colour::White, *this);
            break;
        case 'N':
            board[x][y] = make_unique<Knight>(x, y, Colour::White, *this);
            break;
        case 'B':
             board[x][y] = make_unique<Bishop>(x, y, Colour::White, *this);
            break;
        case 'Q':
            board[x][y] = make_unique<Queen>(x, y, Colour::White, *this);
            break;
        case 'K':
            board[x][y] = make_unique<King>(x, y, Colour::White, *this);
            whiteKing = board[x][y].get();
            break;
        case 'P':
            board[x][y] = make_unique<NullPiece>(x, y, *this);
            break;
        default: 
            board[x][y] = make_unique<NullPiece>(x, y, *this);
            break;
    }
    board[x][y]->attach(td);
}

void Board::removePiece(int x, int y) {
    if (x < 0 || x >= boardSize || y < 0 || y >= boardSize) {
        return;
    }
    
    if (board[x][y].get()->getType() != Type::Nullpiece) {
        board[x][y] = make_unique<NullPiece>(x, y, *this);
        board[x][y]->attach(td);
    }
}

int Board::getSize() const {
    return boardSize;
}

bool Board::isUnderAttack(int x, int y, Colour playerColour) const {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            Piece* piece = getPiece(i, j);
            if (!piece->isEmpty() && piece->getColour() != playerColour) {
                // Check if the opponent's piece can legally move to the (x, y) position
                if (piece->isValidMove(x, y)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::isCheck(Colour playerColour) const {
    Piece* king = (playerColour == Colour::White) ? whiteKing : blackKing;
    if (king) {
        return isUnderAttack(king->getX(), king->getY(), playerColour);
    }
    return false;
}

bool Board::isCheckmate(Colour playerColour) const {
    if (!isCheck(playerColour)) {
        return false;
    }

    Piece* king = (playerColour == Colour::White) ? whiteKing : blackKing;
    if (!king) {
        return false;
    }

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue; // Skip the current position of the king

            int newX = king->getX() + dx;
            int newY = king->getY() + dy;

            if (newX >= 0 && newX < boardSize && newY >= 0 && newY < boardSize && king->isValidMove(newX, newY)) {
                return false;
            }
        }
    }

    // If all possible moves still result in check, then it's checkmate
    return true;
}


Piece* Board::getPiece(int x, int y) const {
    if (x >= 0 && x < boardSize && y >= 0 && y < boardSize) {
        return board[x][y].get();
    }
    return nullptr;
}

ostream &operator<<(ostream &out, const Board &b) {
  out << *b.td;
  return out;
}
