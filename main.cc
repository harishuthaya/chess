#include "board.h"
#include "queen.h"
#include <iostream>
#include <string>
using namespace std;

void printBoard(Board &chessBoard) {
    for (int i = 0; i < chessBoard.getSize(); i++) {
        for (int j = 0; j < chessBoard.getSize(); j++) {
            Piece* piece = chessBoard.getPiece(i, j);
            if (piece->getType() == Type::Nullpiece) {
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
    char command; // m for move and a for add and p for print
    while (cin >> command) {
        if (command == 'm') {
            int a, b, c, d;
            cin >> a >> b >> c >> d;

            bool y = chessBoard.moveSuccess(a, b, c, d);
        } else if (command == 'p') {
            printBoard(chessBoard);
        } else {
            char d;
            int a, b, c;
            cin >> d >> a >> b;
            chessBoard.addPiece(d, a, b, c);
            printBoard(chessBoard);
        }
    }
}