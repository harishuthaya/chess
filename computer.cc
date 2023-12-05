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
                            if (board->isCheck(playerColour)) board->undoMove(false);
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
    // Go thru first vector, then second vector, and choose random element based on size. 

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
                for (int newX = 0; newX < size; ++newX) {
                    for (int newY = 0; newY < size; ++newY) {
                        if (board->simulateMove(x, y, newX, newY, playerColour)) {
                            if (board->isCheck(playerColour)) board->undoMove(false);
                            bool enemyChecked = board->isCheck(enemyColour);
                            bool enemyCapturePossible = false;
                            for (int enemyX = 0; enemyX < size && !enemyCapturePossible; ++enemyX) {
                                for (int enemyY = 0; enemyY < size && !enemyCapturePossible; ++enemyY) {
                                    Piece* enemyPiece = board->getPiece(enemyX, enemyY);
                                    if (!enemyPiece->isEmpty() && enemyPiece->getColour() == enemyColour) {
                                        for (int newEnemyX = 0; newEnemyX < size && !enemyCapturePossible; ++newEnemyX) {
                                            for (int newEnemyY = 0; newEnemyY < size && !enemyCapturePossible; ++newEnemyY) {
                                                if (board->simulateMove(enemyX, enemyY, newEnemyX, newEnemyY, enemyColour)) {
                                                    if (board->isCheck(enemyColour)) board->undoMove(false);
                                                    board->undoMove(false);
                                                    MoveResult result = enemyPiece->moveSuccess(newEnemyX, newEnemyY);
                                                    if (result != MoveResult::Failure) enemyPiece->setPosition(enemyX, enemyY);
                                                    if(result == MoveResult::Capture) {
                                                        enemyCapturePossible = true;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            board->undoMove(false);
                            MoveResult result = piece->moveSuccess(newX, newY);
                            if (result != MoveResult::Failure) piece->setPosition(x, y);
                            if (enemyChecked || result == MoveResult::Capture || enemyCapturePossible) {
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
}

vector<string> Computer::generateLevel4() {

}

vector<string> Computer::getMove() {
    switch (level) {
        case 1:
            return generateLevel1();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
    }
}

char Computer::getPromotion() const {

}