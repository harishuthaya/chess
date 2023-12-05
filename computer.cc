#include "computer.h"
#include "piece.h"
#include <string>
#include <iostream>
using namespace std;

Computer::Computer(Colour colour, int level, Board *board):
    Player{colour}, level{level}, board{board} {

}

string Computer::convertCoords(int x, int y) const {
    string coords;
    coords += y + 'a';
    coords += (board->getSize() - x) + '0';
    return coords;
}

vector<string> Computer::generateLevel1() {
    vector<vector<string>> legalMoves;

    for (int x = 0; x < board->getSize(); ++x) {
        for (int y = 0; y < board->getSize(); ++y) {
            Piece* piece = board->getPiece(x, y);
            if (!piece->isEmpty() && piece->getColour() == getColour()) {
                for (int newX = 0; newX < board->getSize(); newX++) {
                    for (int newY = 0; newY < board->getSize(); newY++) {
                        if (board->simulateMove(x, y, newX, newY, getColour())) {
                            board->undoMove(false);
                            legalMoves.emplace_back(vector<string>{convertCoords(x, y), convertCoords(newX, newY)});
                        }
                    }
                }
            }
        }
    }

    return legalMoves[rand() % legalMoves.size()];
}

vector<string> Computer::generateLevel2() {

}

vector<string> Computer::generateLevel3() {

}

vector<string> Computer::generateLevel4() {

}

vector<string> Computer::getMove() const {

}

char Computer::getPromotion() const {

}
