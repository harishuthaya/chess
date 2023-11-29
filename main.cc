#include "board.h"
#include "queen.h"
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
        cout << endl;
    }
}

int main() {
    Board chessBoard;
    bool y = chessBoard.moveSuccess(0, 3, 4, 3);
    if (y) {
        cout << "moved" << endl;
    }

    printBoard(chessBoard);
}