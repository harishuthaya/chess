#include "board.h"
using namespace std;

Board::Board(): board{} {
    board.resize(boardSize, vector<unique_ptr<Piece>>(boardSize, nullptr));
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

    MoveResult result = board[x][y].get()->moveSuccess(newX, newY);
    if (result == MoveResult::Failure) {
        return false;
    } else if (result == MoveResult::Move) {
        swap(board[x][y], board[newX][newY]);
    } else {
        board[newX][newY] = std::move(board[x][y]);
        board[x][y] = nullptr;
    }

    return true;
}

WinState Board::getWinState() {
    return this->winState;
}

void Board::addPiece(char piece, int x, int y, int playerID) {
    switch(piece) {
        case 'r':
        case 'n':
        case 'b':
        case 'q':
        case 'k':
        case 'p':
        case 'R':
        case 'N':
        case 'B':
        case 'Q':
            board[x][y] = make_unique<Queen>(x, y, playerID, *this);
        case 'K':
        case 'P':
    }
}

void Board::removePiece(int x, int y) {
    board[x][y].reset(nullptr);
}

int Board::getSize() const {
    return boardSize;
}

Piece* Board::getPiece(int x, int y) const {
    if (x >= 0 && x < boardSize && y >= 0 && y < boardSize) {
        return board[x][y].get();
    }
    return nullptr;
}
