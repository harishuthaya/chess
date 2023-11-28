#include "board.h"
#include <iostream>
#include <string>
using namespace std;

void printBoard(Board &chessBoard) {
    for (int i = 0; i < chessBoard.getSize(); i++) {
        for (int j = 0; j < chessBoard.getSize(); j++) {
            Piece* piece = chessBoard.getPiece(i, j);
            if (!piece) {
                cout << '_';
            } else {
                if (piece->getColour() == Colour::Black) {
                    cout << 'Q';
                } else {
                    cout << 'q';
                }
            }
        }
    }
}

int main() {
    Board chessBoard;
    chessBoard.addPiece('Q', 0, 0, 1);
    chessBoard.addPiece('q', 2, 2, 2);

    printBoard(chessBoard);
}