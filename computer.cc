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
    int maxDepth = 3;
    int alpha = INT_MIN;
    int beta = INT_MAX;
    int bestScore = INT_MIN;
    vector<string> bestMove;

    vector<vector<string>> legalMoves = generateAllMoves();
    for (const auto& move : legalMoves) {
        vector<int> start = convert(move[0]);
        vector<int> end = convert(move[1]);

        board->simulateMove(start[0], start[1], end[0], end[1], getColour());  // Apply the move
        int score = minimax(maxDepth - 1, alpha, beta, false);  // Call Minimax
        board->undoMove(false);  // Revert the move

        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }

    return bestMove;
}


int Computer::minimax(int depth, int alpha, int beta, bool isMaximizingPlayer) {
    if (depth == 0) {
        return evaluateBoard();
    }

    if (isMaximizingPlayer) {
        int maxEval = INT_MIN;
        for (const auto& move : generateAllMoves()) {
            vector<int> start = convert(move[0]);
            vector<int> end = convert(move[1]);
            if (board->simulateMove(start[0], start[1], end[0], end[1], getColour())) {
                int eval = minimax(depth - 1, alpha, beta, false);
                board->undoMove(false);
                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);
                if (beta <= alpha)
                    break;  // Alpha cutoff
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (const auto& move : generateAllMoves()) {
            vector<int> start = convert(move[0]);
            vector<int> end = convert(move[1]);
            if (board->simulateMove(start[0], start[1], end[0], end[1], getColour() == Colour::White ? Colour::Black : Colour::White)) {
                int eval = minimax(depth - 1, alpha, beta, true);
                board->undoMove(false);
                minEval = std::min(minEval, eval);
                beta = std::min(beta, eval);
                if (beta <= alpha)
                    break;  // Beta cutoff
            }
        }
        return minEval;
    }
}

int Computer::evaluateBoard() {
    int score = 0;

    const int pawnValue = 1;
    const int knightValue = 3;
    const int bishopValue = 3;
    const int rookValue = 5;
    const int queenValue = 9;
    const int kingValue = 0; // King's value is often set to 0 since the game is over if the king is lost

    for (int x = 0; x < board->getSize(); ++x) {
        for (int y = 0; y < board->getSize(); ++y) {
            Piece* piece = board->getPiece(x, y);
            if (!piece->isEmpty()) {
                int value = 0;
                switch (piece->getType()) {
                    case Type::Pawn:   value = pawnValue; break;
                    case Type::Knight: value = knightValue; break;
                    case Type::Bishop: value = bishopValue; break;
                    case Type::Rook:   value = rookValue; break;
                    case Type::Queen:  value = queenValue; break;
                    case Type::King:   value = kingValue; break;
                    default: break;
                }

                // Adjust score based on the color of the piece
                score += (piece->getColour() == this->getColour()) ? value : -value;
            }
        }
    }

    return score;
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
