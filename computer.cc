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
                            if (board->isCheck(playerColour)) board->undoMove(false);
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
    vector<vector<string>> capturesAndChecks;
    vector<vector<string>> otherLegalMoves;

    Colour playerColour = getColour();
    Colour enemyColour = (playerColour == Colour::White) ? Colour::Black : Colour::White;
    int size = board->getSize();
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            Piece* piece = board->getPiece(x, y);
            if (!piece->isEmpty() && piece->getColour() == playerColour) {
                for (int newX = 0; newX < size; ++newX) {
                    for (int newY = 0; newY < size; ++newY) {
                        if (board->simulateMove(x, y, newX, newY, playerColour)) {
                            if (board->isCheck(playerColour)) {
                                board->undoMove(false);
                                continue;
                            }
                            bool enemyChecked = board->isCheck(enemyColour);
                            board->undoMove(false);

                            MoveResult result = piece->moveSuccess(newX, newY);
                            if (result != MoveResult::Failure) piece->setPosition(x, y);
                            if (enemyChecked || result == MoveResult::Capture) {
                                capturesAndChecks.emplace_back(vector<string>{convertCoords(x, y), convertCoords(newX, newY)});
                            } else {
                                otherLegalMoves.emplace_back(vector<string>{convertCoords(x, y), convertCoords(newX, newY)});
                            }
                        } 
                    }
                }
            }
        }
    }
    if (capturesAndChecks.size() > 0) return capturesAndChecks[rand() % capturesAndChecks.size()];
    return otherLegalMoves[rand() % otherLegalMoves.size()];

}

vector<string> Computer::generateLevel3() {
    vector<vector<string>> capturesChecksAndAvoids;
    vector<vector<string>> otherLegalMoves;

    Colour playerColour = getColour();
    Colour enemyColour = (playerColour == Colour::White) ? Colour::Black : Colour::White;
    int size = board->getSize();
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            Piece* piece = board->getPiece(x, y);
            if (!piece->isEmpty() && piece->getColour() == playerColour) {
                bool beforeUnderAttack = board->isUnderAttack(x, y, playerColour);
                for (int newX = 0; newX < size; ++newX) {
                    for (int newY = 0; newY < size; ++newY) {
                        if (board->simulateMove(x, y, newX, newY, playerColour)) {
                            if (board->isCheck(playerColour)) {
                                board->undoMove(false);
                                continue;
                            }
                            bool afterUnderAttack = board->isUnderAttack(newX, newY, playerColour);
                            bool enemyChecked = board->isCheck(enemyColour);
                            board->undoMove(false);
                            MoveResult result = piece->moveSuccess(newX, newY);
                            if (result != MoveResult::Failure) piece->setPosition(x, y);
                            if (enemyChecked || result == MoveResult::Capture || (beforeUnderAttack && !afterUnderAttack)) {
                                capturesChecksAndAvoids.emplace_back(vector<string>{convertCoords(x, y), convertCoords(newX, newY)});
                            } else {
                                otherLegalMoves.emplace_back(vector<string>{convertCoords(x, y), convertCoords(newX, newY)});
                            }
                        } 
                    }
                }
            }
        }
    }
    if (capturesChecksAndAvoids.size() > 0) return capturesChecksAndAvoids[rand() % capturesChecksAndAvoids.size()];
    return otherLegalMoves[rand() % otherLegalMoves.size()];
}

vector<string> Computer::generateLevel4() {

}

vector<string> Computer::getMove() {
    switch (level) {
        case 1:
            return generateLevel1();
            break;
        case 2:
            return generateLevel2();
            break;
        case 3:
            return generateLevel3();
            break;
        case 4:
            break;
    }
}

char Computer::getPromotion() const {
    return (getColour() == Colour::White) ? 'Q' : 'q';
}