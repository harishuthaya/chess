#include "computer.h"
#include "piece.h"
#include <string>
#include <iostream>
#include <climits>
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


vector<vector<string>> Computer::generateAllMoves() {
    vector<vector<string>> legalMoves;
    for (int x = 0; x < board->getSize(); ++x) {
        for (int y = 0; y < board->getSize(); ++y) {
            Piece* piece = board->getPiece(x, y);
            if (!piece->isEmpty() && piece->getColour() == getColour()) {
                for (int newX = 0; newX < board->getSize(); newX++) {
                    for (int newY = 0; newY < board->getSize(); newY++) {
                        if (board->simulateMove(x, y, newX, newY, getColour())) {
                            if (board->isCheck(getColour())) {
                                board->undoMove(false);
                                continue;
                            };
                            board->undoMove(false);
                            legalMoves.emplace_back(vector<string>{convertCoords(x, y), convertCoords(newX, newY)});
                        }
                    }
                }
            }
        }
    }
    return legalMoves;

}
 
vector<string> Computer::generateLevel1() {
    vector<vector<string>> legalMoves = generateAllMoves();

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
                            MoveResult result = board->getLastMoveResult();
                            board->undoMove(false);

                            // MoveResult result = piece->moveSuccess(newX, newY);
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
                            MoveResult result = board->getLastMoveResult();
                            board->undoMove(false);
                            // MoveResult result = piece->moveSuccess(newX, newY);
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

vector<int> convert(const string& coords) {
    int col = coords[0] - 'a';
    int row = 8 - (coords[1] - '0');
    return vector<int>{row, col};
}

vector<string> Computer::generateLevel4() {
    vector<vector<string>> legalMoves = generateAllMoves();
    int maxScore = INT_MIN;
    vector<vector<string>> bestMove;

    for (const auto& move : legalMoves) {
        vector<int> start = convert(move[0]);
        vector<int> end = convert(move[1]);

        int score = scoreMove(start[0], start[1], end[0], end[1]);

        if (score > maxScore) {
            bestMove.clear();
            bestMove.emplace_back(move);
            maxScore = score;
        } else if (score == maxScore) {
            bestMove.emplace_back(move);
        }
    }

    return bestMove.empty() ? generateLevel1() : bestMove[rand() % bestMove.size()]; // Fallback to Level 1 if no moves found
}

int Computer::scoreMove(int startX, int startY, int endX, int endY) {
    int score = 0;

    board->simulateMove(startX, startY, endX, endY, getColour());
    Colour enemyColour = (getColour() == Colour::White) ? Colour::Black : Colour::White;

    // Checkmate has the highest priority
    if (board->isCheckmate(enemyColour)) {
        score += 1000;
    }
    // Safe check
    else if (board->isCheck(enemyColour)) {
        score += 100;
    }

    MoveResult result = board->getLastMoveResult();
    // Captures, prioritize by piece value
    if (result == MoveResult::EnPassant) {
        score += 20;
    }

    if (result == MoveResult::Promote) {
        score += 100;
    }

    if (result == MoveResult::Castle) {
        score += 50;
    }

    if (result == MoveResult::Capture) {
        Piece* capturedPiece = board->getPiece(endX, endY);
        score += getPieceValue(capturedPiece);
    } else {
        score += 10; // Small score for a regular move
    }

    if (!board->isUnderAttack(endX, endY, getColour())) {
        score += score + 100;
    }

    board->undoMove(false);

    return score;
}

int Computer::getPieceValue(Piece* piece) {
    if (piece == nullptr || piece->isEmpty()) {
        return 0; // No value for empty squares or null pointers
    }

    switch (piece->getType()) {
        case Type::Pawn:
            return 10;
        case Type::Knight:
            return 30;
        case Type::Bishop:
            return 30;
        case Type::Rook:
            return 50;
        case Type::Queen:
            return 90;
        case Type::King:
            return 900; // King has a high value, typically used to indicate checkmate scenarios
        default:
            return 0; // In case of an unrecognized piece type
    }
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
            return generateLevel4();
            break;
        default:
            return generateLevel1();
            break;
    }
}

char Computer::getPromotion() const {
    return (getColour() == Colour::White) ? 'Q' : 'q';
}
