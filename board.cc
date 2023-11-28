#include "board.h"
using namespace std;

Board::Board(): board{} {
    board.resize(BOARD_SIZE, vector<Piece*>(BOARD_SIZE, nullptr));
    // Adds the black pieces
    this->addPiece('r', 0, 0);
    this->addPiece('n', 1, 0);
    this->addPiece('b', 2, 0);
    this->addPiece('q', 3, 0);
    this->addPiece('k', 4, 0);
    this->addPiece('b', 5, 0);
    this->addPiece('n', 6, 0);
    this->addPiece('r', 7, 0);
    for (int i = 0; i < BOARD_SIZE - 1; ++i) {
        this->addPiece('p', i, 1);
    }

    // Adds the white pieces
    this->addPiece('R', 0, BOARD_SIZE - 1);
    this->addPiece('N', 1, BOARD_SIZE - 1);
    this->addPiece('B', 2, BOARD_SIZE - 1);
    this->addPiece('Q', 3, BOARD_SIZE - 1);
    this->addPiece('K', 4, BOARD_SIZE - 1);
    this->addPiece('B', 5, BOARD_SIZE - 1);
    this->addPiece('N', 6, BOARD_SIZE - 1);
    this->addPiece('R', 7, BOARD_SIZE - 1);
    for (int i = 0; i < BOARD_SIZE - 1; ++i) {
        this->addPiece('P', i, BOARD_SIZE - 2)
    }
}

bool Board::moveSuccess(int newX, int newY) {

}

WinState Board::getWinState() {
    return this->winState;
}

void Board::addPiece(char piece, int x, int y) {
    switch(piece):
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
            board[y][x] = new Queen(x, y);
        case 'K':
        case 'P':
}

void Board::removePiece(int x, int y) {
    board[y][x] = nullptr;
}
