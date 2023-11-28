#include "board.h"
using namespace std;

Board::Board(): board{} {
    board.resize(BOARD_SIZE, vector<unique_ptr<Piece>>(BOARD_SIZE, nullptr));
    // Adds the black pieces
    this->addPiece('r', 0, 0, 1);
    this->addPiece('n', 0, 1, 1);
    this->addPiece('b', 0, 2, 1);
    this->addPiece('q', 0, 3, 1);
    this->addPiece('k', 0, 4, 1);
    this->addPiece('b', 0, 5, 1);
    this->addPiece('n', 0, 6, 1);
    this->addPiece('r', 0, 7, 1);
    for (int i = 0; i < BOARD_SIZE - 1; ++i) {
        this->addPiece('p', 1, i, 1);
    }

    // Adds the white pieces
    this->addPiece('R', BOARD_SIZE - 1, 0, 2);
    this->addPiece('N', BOARD_SIZE - 1, 1, 2);
    this->addPiece('B', BOARD_SIZE - 1, 2, 2);
    this->addPiece('Q', BOARD_SIZE - 1, 3, 2);
    this->addPiece('K', BOARD_SIZE - 1, 4, 2);
    this->addPiece('B', BOARD_SIZE - 1, 5, 2);
    this->addPiece('N', BOARD_SIZE - 1, 6, 2);
    this->addPiece('R', BOARD_SIZE - 1, 7, 2);
    for (int i = 0; i < BOARD_SIZE - 1; ++i) {
        this->addPiece('P', BOARD_SIZE - 2, i, 2);
    }
}

bool Board::moveSuccess(int newX, int newY) {

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
            board[y][x] = make_unique<Queen>(x, y, playerID);
        case 'K':
        case 'P':
    }
}

void Board::removePiece(int x, int y) {
    board[y][x].reset(nullptr);
}
