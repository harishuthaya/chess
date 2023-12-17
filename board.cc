#include "board.h"
#include <iostream>
using namespace std;

Board::Board(TextDisplay *td, GraphicsDisplay *gd): board{}, winState{WinState::InProgress}, td{td}, gd{gd}, whiteKing{nullptr}, 
    blackKing{nullptr}, lastMove{nullptr}, lastOldX{-1}, lastOldY{-1}, lastCaptured{nullptr}, 
    lastMoveResult{MoveResult::Failure}, lastMoveHasMoveState{false}, lastCapturedHasMoveState{false} {
    // Initializes an empty board
    board.resize(boardSize);
    for (int i = 0; i < boardSize; ++i) {
        board[i].resize(boardSize);

        for (int j = 0; j < boardSize; ++j) {
            board[i][j] = make_unique<NullPiece>(i, j, *this);
            board[i][j]->attach(td);
            board[i][j]->attach(gd);
        }
    }
}

void Board::init() {
    // Adds the black pieces
    this->addPiece('r', 0, 0);
    this->addPiece('n', 0, 1);
    this->addPiece('b', 0, 2);
    this->addPiece('q', 0, 3);
    this->addPiece('k', 0, 4);
    this->addPiece('b', 0, 5);
    this->addPiece('n', 0, 6);
    this->addPiece('r', 0, 7);

    // Add black pawns
    for (int i = 0; i < boardSize; ++i) {
        this->addPiece('p', 1, i);
    }

    // Adds the white pieces
    this->addPiece('R', boardSize - 1, 0);
    this->addPiece('N', boardSize - 1, 1);
    this->addPiece('B', boardSize - 1, 2);
    this->addPiece('Q', boardSize - 1, 3);
    this->addPiece('K', boardSize - 1, 4);
    this->addPiece('B', boardSize - 1, 5);
    this->addPiece('N', boardSize - 1, 6);
    this->addPiece('R', boardSize - 1, 7);

    // Add white pawns
    for (int i = 0; i < boardSize; ++i) {
        this->addPiece('P', boardSize - 2, i);
    }
}

bool Board::moveSuccess(int x, int y, int newX, int newY, Colour playerColour, char c) {
    Colour pieceColour = board[x][y]->getColour();
    
    // Checks for invalid pawn promotions
    if (pieceColour != playerColour) {
        return false;
    }

    if (c == 'k' || c == 'K') {
        cerr << "Pawn promotion is king is illegal" << endl;
        return false;
    }

    if (playerColour == Colour::White && (c != 'Q' && c != 'B' && c != 'N' && c != 'R')) {
        cerr << "Invalid promotion - Pawn must be promoted to a White Piece" << endl;
        return false;
    }

    if (playerColour == Colour::Black && (c != 'q' && c != 'b' && c != 'n' && c != 'r')) {
        cerr << "Invalid promotion - Pawn must be promoted to a Black Piece" << endl;
        return false;
    }
    
    // Performs the move and makes sure it was successful
    bool success = moveSuccess(x, y, newX, newY, playerColour);
    if (!success) {
        return false;
    }
    
    // Updates previous move
    lastMove = board[newX][newY].get();
    lastOldX = x;
    lastOldY = y;
    lastMoveResult = MoveResult::Promote;
    if (board[newX][newY]->getType() == Type::Pawn) {
        this->addPiece(c, newX, newY);
    }

    Colour opponentColour = (pieceColour == Colour::White) ? Colour::Black : Colour::White;

    // Checks if game ended
    if(isCheckmate(Colour::White)) {
        cout << "Checkmate! Black wins!" << endl;
        winState = WinState::Player2Win;
        return true;
    }  else if (isCheckmate(Colour::Black)) {
        cout << "Checkmate! White wins!" << endl;
        winState = WinState::Player1Win;
        return true;
    } else if (isStalemate(Colour::White) || isStalemate(Colour::Black)) {
        cout << "Stalemate!" << endl;
        winState = WinState::Tie;
        return true;
    } 

    // Checks if opponent is now in check
    if (isCheck(opponentColour)) {
        string s = (opponentColour == Colour::Black) ? "Black" : "White";
        cout << s + " is in check." << endl;
    }

    return true;
}


bool Board::moveSuccess(int x, int y, int newX, int newY, Colour playerColour) {
    // New move is within board boundaries
    if (newX < 0 || newX >= boardSize || newY < 0 || newY >= boardSize ||
        x < 0 || x >= boardSize || y < 0 || y >= boardSize) {
        return false;
    }

    // Piece moved to same spot
    if (x == newX && y == newY) {
        return false;
    }

    // Piece is different colour than player's colour
    Colour pieceColour = board[x][y]->getColour();
    if (pieceColour != playerColour) {
        return false;
    }

    // If last move successful, add it to history before making another move, if not, don't add it
    if (lastMoveResult != MoveResult::Failure) {
        movesHistory.push(Move(lastOldX, lastOldY, lastMove, lastMoveResult, lastMoveHasMoveState, lastCapturedHasMoveState, std::move(lastCaptured)));
        lastMoveResult = MoveResult::Failure;
    }
    
    lastMoveHasMoveState = board[x][y]->getHasMoved();
    lastCapturedHasMoveState = board[newX][newY]->getHasMoved();
    MoveResult result = board[x][y]->moveSuccess(newX, newY);      
    if (result == MoveResult::Failure) {
        lastMoveResult = result;
        return false;
    }

    // Update display if move is successful
    board[x][y]->notifyObservers(x, y);

    if (result == MoveResult::Castle) {
        int rookY = (newY > y) ? boardSize - 1 : 0;
        int rookNewY = (newY > y) ? newY - 1 : newY + 1;
        board[x][rookNewY] = std::move(board[x][rookY]);
        board[newX][newY] = std::move(board[x][y]);
        board[x][y] = make_unique<NullPiece>(x, y, *this);
        board[x][rookY] = make_unique<NullPiece>(x, rookY, *this);
        if (isCheck(pieceColour)) {
            cerr << "can't castle" << endl;
            board[x][y] = std::move(board[newX][newY]);
            board[newX][newY] = make_unique<NullPiece>(newX, newY, *this);
            board[x][rookY] = std::move(board[x][rookNewY]);
            board[x][rookNewY] = make_unique<NullPiece>(x, rookNewY, *this);
            board[x][y]->setHasMoved(false);
            board[x][rookY]->setHasMoved(false);
            board[x][y]->setPosition(x, y);
            board[x][y]->notifyObservers(x, y);
            board[x][rookY]->setPosition(x, rookY);
            board[x][rookY]->notifyObservers(x, rookY);
            lastMoveResult = MoveResult::Failure;
            return false;
        }
        board[x][rookNewY]->attach(td);
        board[x][rookNewY]->attach(gd);
        board[x][rookY]->attach(td);
        board[x][rookY]->attach(gd);
        lastCaptured = nullptr;
        lastMoveResult = MoveResult::Castle;
        lastMove = board[newX][newY].get();
        lastOldX = x;
        lastOldY = y;
        return true;
    }

    if (result == MoveResult::EnPassant) {
        int capturedPawnX = x;
        int capturedPawnY = newY;
        auto tempDest = std::move(board[capturedPawnX][capturedPawnY]);
        board[capturedPawnX][capturedPawnY] = make_unique<NullPiece>(capturedPawnX, capturedPawnY, *this);
        board[newX][newY] = std::move(board[x][y]);
        board[x][y] = make_unique<NullPiece>(x, y, *this);
        if (isCheck(pieceColour)) {
            board[x][y] = std::move(board[newX][newY]);
            board[x][y]->setPosition(x, y);
            board[x][y]->notifyObservers(x, y);
            board[newX][newY] = make_unique<NullPiece>(newX, newY, *this);
            board[capturedPawnX][capturedPawnY] = std::move(tempDest);
            board[newX][newY]->attach(td);
            board[newX][newY]->attach(gd);
            board[capturedPawnX][capturedPawnY]->attach(td);
            board[capturedPawnX][capturedPawnY]->attach(gd);
            cerr << "illegal move to put the king in check" << endl;
            lastMoveResult = MoveResult::Failure;
            return false;
        }

        board[capturedPawnX][capturedPawnY]->attach(td);
        board[capturedPawnX][capturedPawnY]->attach(gd);
        board[x][y]->attach(td);
        board[x][y]->attach(gd);
        lastCaptured = std::move(tempDest);
        lastMove = board[newX][newY].get();
        lastOldX = x;
        lastOldY = y;
        lastMoveResult = MoveResult::EnPassant;
        return true;
    }

    auto tempDest = std::move(board[newX][newY]);
    board[newX][newY] = std::move(board[x][y]);
    board[x][y] = make_unique<NullPiece>(x, y, *this);
    if (isCheck(pieceColour)) {
        board[newX][newY]->setPosition(x, y);
        board[x][y] = std::move(board[newX][newY]);
        board[newX][newY] = std::move(tempDest);
        cerr << "illegal move to put the king in check" << endl;
        board[newX][newY]->attach(td);
        board[newX][newY]->attach(gd);
        lastMoveResult = MoveResult::Failure;
        return false;
    }
    
    board[x][y]->attach(td);
    board[x][y]->attach(gd);
    lastCaptured = std::move(tempDest);
    lastMove = board[newX][newY].get();
    lastOldX = x;
    lastOldY = y;
    if (lastCaptured && lastCaptured->getType() != Type::Nullpiece) {
        lastMoveResult = MoveResult::Capture;
    } else {
        lastMoveResult = MoveResult::Move;
    }

    // Check if game ended
    if(isCheckmate(Colour::White)) {
        cout << "Checkmate! Black wins!" << endl;
        winState = WinState::Player2Win;
        return true;
    }  else if (isCheckmate(Colour::Black)) {
        cout << "Checkmate! White wins!" << endl;
        winState = WinState::Player1Win;
        return true;
    } else if (isStalemate(Colour::White) || isStalemate(Colour::Black)) {
        cout << "Stalemate!" << endl;
        winState = WinState::Tie;
        return true;
    } 

    // Checks if opponent is in check
    Colour opponentColour = (pieceColour == Colour::White) ? Colour::Black : Colour::White;
    if (isCheck(opponentColour)) {
        string s = (opponentColour == Colour::Black) ? "Black" : "White";
        cout << s + " is in check." << endl;
    } 

    return true;
}

void Board::addPiece(char piece, int x, int y) {
    // If piece is outside of board boundaries, don't add
    if (x < 0 || x >= boardSize || y < 0 || y >= boardSize) {
        return;
    }

    Piece* currPiece = getPiece(x, y);
    if (currPiece->getType() == Type::King && currPiece->getColour() == Colour::Black) {
        blackKingNum--;
    } else if (currPiece->getType() == Type::King && currPiece->getColour() == Colour::White) {
        whiteKingNum--;
    }

    board[x][y].reset();

    // Add the piece
    switch(piece) {
        case 'r':
            board[x][y] = make_unique<Rook>(x, y, Colour::Black, *this);
            break;
        case 'n':
            board[x][y] = make_unique<Knight>(x, y, Colour::Black, *this);
            break;
        case 'b':
            board[x][y] = make_unique<Bishop>(x, y, Colour::Black, *this);
            break;
        case 'q':
            board[x][y] = make_unique<Queen>(x, y, Colour::Black, *this);
            break;
        case 'k':
            board[x][y] = make_unique<King>(x, y, Colour::Black, *this);
            blackKing = board[x][y].get();
            blackKingNum++;
            break;
        case 'p':
            board[x][y] = make_unique<Pawn>(x, y, Colour::Black, *this);
            break;
        case 'R':
            board[x][y] = make_unique<Rook>(x, y, Colour::White, *this);
            break;
        case 'N':
            board[x][y] = make_unique<Knight>(x, y, Colour::White, *this);
            break;
        case 'B':
             board[x][y] = make_unique<Bishop>(x, y, Colour::White, *this);
            break;
        case 'Q':
            board[x][y] = make_unique<Queen>(x, y, Colour::White, *this);
            break;
        case 'K':
            board[x][y] = make_unique<King>(x, y, Colour::White, *this);
            whiteKing = board[x][y].get();
            whiteKingNum++;
            break;
        case 'P':
            board[x][y] = make_unique<Pawn>(x, y, Colour::White, *this);
            break;
        default: 
            board[x][y] = make_unique<NullPiece>(x, y, *this);
            break;
    }
    
    // Attach observers to the piece
    board[x][y]->attach(td);
    board[x][y]->attach(gd);
}

void Board::removePiece(int x, int y) {
    // If piece to be removed outside of baord boundaries, don't remove
    if (x < 0 || x >= boardSize || y < 0 || y >= boardSize) {
        return;
    }

    Piece* piece = board[x][y].get();

    // Reduce number of kings if necessary
    if (piece->getType() == Type::King) {
        if (piece->getColour() == Colour::White) {
            whiteKingNum--;
        } else {
            blackKingNum--;
        }
    }
    
    // Swap piece to empty piece
    if (piece->getType() != Type::Nullpiece) {
        board[x][y] = make_unique<NullPiece>(x, y, *this);
        board[x][y]->attach(td);
        board[x][y]->attach(gd);
    }
}

bool Board::simulateMove(int x, int y, int newX, int newY, Colour playerColour) {
    if (newX < 0 || newX >= boardSize || newY < 0 || newY >= boardSize ||
        x < 0 || x >= boardSize || y < 0 || y >= boardSize) {
        return false;
    }

    if (x == newX && y == newY) {
        return false;
    }

    Colour pieceColour = board[x][y]->getColour();

    if (pieceColour != playerColour) {
        return false;
    }

    // update move history
    if (lastMoveResult != MoveResult::Failure) {
        movesHistory.push(Move(lastOldX, lastOldY, lastMove, lastMoveResult, lastMoveHasMoveState, lastCapturedHasMoveState, std::move(lastCaptured)));
        lastMoveResult = MoveResult::Failure;
    }
    
    lastMoveHasMoveState = board[x][y]->getHasMoved();
    lastCapturedHasMoveState = board[newX][newY]->getHasMoved();
    MoveResult result = board[x][y]->moveSuccess(newX, newY);      
    if (result == MoveResult::Failure) {
        lastMoveResult = result;
        return false;
    }

    if (result == MoveResult::Castle) {
        int rookY = (newY > y) ? boardSize - 1 : 0;
        int rookNewY = (newY > y) ? newY - 1 : newY + 1;
        board[x][rookNewY] = std::move(board[x][rookY]);
        board[newX][newY] = std::move(board[x][y]);
        board[x][y] = make_unique<NullPiece>(x, y, *this);
        board[x][rookY] = make_unique<NullPiece>(x, rookY, *this);

        // illegal move if put own king in check
        if (isCheck(pieceColour)) {
            board[x][y] = std::move(board[newX][newY]);
            board[newX][newY] = make_unique<NullPiece>(newX, newY, *this);
            board[x][rookY] = std::move(board[x][rookNewY]);
            board[x][rookNewY] = make_unique<NullPiece>(x, rookNewY, *this);
            board[x][y]->setHasMoved(false);
            board[x][rookY]->setHasMoved(false);
            board[x][y]->setPosition(x, y);
            board[x][rookY]->setPosition(x, rookY);
            lastMoveResult = MoveResult::Failure;
            return false;
        }

        // update move history fields
        lastCaptured = nullptr;
        lastMoveResult = MoveResult::Castle;
        lastMove = board[newX][newY].get();
        lastOldX = x;
        lastOldY = y;
        return true;
    }

    if (result == MoveResult::EnPassant) {
        int capturedPawnX = x;
        int capturedPawnY = newY;
        auto tempDest = std::move(board[capturedPawnX][capturedPawnY]);
        board[capturedPawnX][capturedPawnY] = make_unique<NullPiece>(capturedPawnX, capturedPawnY, *this);
        board[newX][newY] = std::move(board[x][y]);
        board[x][y] = make_unique<NullPiece>(x, y, *this);

        // illegal move to put own king in check
        if (isCheck(pieceColour)) {
            board[x][y] = std::move(board[newX][newY]);
            board[x][y]->setPosition(x, y);
            board[newX][newY] = make_unique<NullPiece>(newX, newY, *this);
            board[capturedPawnX][capturedPawnY] = std::move(tempDest);
            lastMoveResult = MoveResult::Failure;
            return false;
        }
        // update move history fields
        lastCaptured = std::move(tempDest);
        lastMove = board[newX][newY].get();
        lastOldX = x;
        lastOldY = y;
        lastMoveResult = MoveResult::EnPassant;
        return true;
    }

    auto tempDest = std::move(board[newX][newY]);
    board[newX][newY] = std::move(board[x][y]);
    board[x][y] = make_unique<NullPiece>(x, y, *this);
    // illagal move to put own king in check
    if (isCheck(pieceColour)) {
        board[newX][newY]->setPosition(x, y);
        board[x][y] = std::move(board[newX][newY]);
        board[newX][newY] = std::move(tempDest);
        lastMoveResult = MoveResult::Failure;
        return false;
    }
    
    // update move history fields
    lastCaptured = std::move(tempDest);
    lastMove = board[newX][newY].get();
    lastOldX = x;
    lastOldY = y;
    if (lastCaptured && lastCaptured->getType() != Type::Nullpiece) {
        lastMoveResult = MoveResult::Capture;
    } else {
        lastMoveResult = MoveResult::Move;
    }
    return true;
}

bool Board::undoMove(bool realMove) {
    if (lastMoveResult == MoveResult::Promote) {
        int newX = lastMove->getX();
        int newY = lastMove->getY();
        Colour pieceColour = board[newX][newY]->getColour();
        board[lastOldX][lastOldY] = make_unique<Pawn>(lastOldX, lastOldY, pieceColour, *this);
        if (realMove) board[lastOldX][lastOldY]->attach(td);
        if (realMove) board[lastOldX][lastOldY]->attach(gd);
        board[newX][newY] = std::move(lastCaptured);
        board[newX][newY]->setPosition(newX, newY);
        if (realMove) board[newX][newY]->notifyObservers(newX, newY); 
        board[lastOldX][lastOldY]->setHasMoved(lastMoveHasMoveState);
        board[newX][newY]->setHasMoved(lastCapturedHasMoveState);
        // update last move if movehistory isn't empty
        if (!movesHistory.empty()) {
            lastOldX = movesHistory.top().lastOldX;
            lastOldY = movesHistory.top().lastOldY;
            lastMove = movesHistory.top().lastMove;
            lastCapturedHasMoveState = movesHistory.top().lastCapturedHasMoveState;
            lastMoveHasMoveState = movesHistory.top().lastMoveHasMoveState;
            lastMoveResult = movesHistory.top().moveResult;
            lastCaptured = std::move(movesHistory.top().lastCaptured);
            movesHistory.pop();
        } else {
            lastMoveResult = MoveResult::Failure;
        }
        return true;
    }

    if ((lastMoveResult == MoveResult::Move) || (lastMoveResult == MoveResult::Capture)) {
        int newX = lastMove->getX();
        int newY = lastMove->getY();
        board[lastOldX][lastOldY] = std::move(board[newX][newY]);
        board[newX][newY] = std::move(lastCaptured);
        board[lastOldX][lastOldY]->setPosition(lastOldX, lastOldY);
        if (realMove) board[lastOldX][lastOldY]->notifyObservers(lastOldX, lastOldY);
        board[newX][newY]->setPosition(newX, newY);
        if (realMove) board[newX][newY]->notifyObservers(newX, newY);
        board[lastOldX][lastOldY]->setHasMoved(lastMoveHasMoveState);
        board[newX][newY]->setHasMoved(lastCapturedHasMoveState);
        // update last move if movehistory isn't empty
        if (!movesHistory.empty()) {
            lastOldX = movesHistory.top().lastOldX;
            lastOldY = movesHistory.top().lastOldY;
            lastMove = movesHistory.top().lastMove;
            lastCapturedHasMoveState = movesHistory.top().lastCapturedHasMoveState;
            lastMoveHasMoveState = movesHistory.top().lastMoveHasMoveState;
            lastMoveResult = movesHistory.top().moveResult;
            lastCaptured = std::move(movesHistory.top().lastCaptured);
            movesHistory.pop();
        } else {
            lastMoveResult = MoveResult::Failure;
        }
        return true;
    }


    if (lastMoveResult == MoveResult::EnPassant) {
        int newX = lastMove->getX();
        int newY = lastMove->getY();
        int capturedPawnX = lastOldX;
        int capturedPawnY = newY;
        board[lastOldX][lastOldY] = std::move(board[newX][newY]);
        board[lastOldX][lastOldY]->setPosition(lastOldX, lastOldY);
        if (realMove)board[lastOldX][lastOldY]->notifyObservers(lastOldX, lastOldY);
        board[lastOldX][lastOldY]->setHasMoved(lastMoveHasMoveState);
        board[newX][newY] = make_unique<NullPiece>(newX, newY, *this);
        if (realMove)board[newX][newY]->attach(td);
        if (realMove)board[newX][newY]->attach(gd);
        board[capturedPawnX][capturedPawnY] = std::move(lastCaptured);
        board[capturedPawnX][capturedPawnY]->setPosition(capturedPawnX, capturedPawnY);
        if (realMove)board[capturedPawnX][capturedPawnY]->notifyObservers(capturedPawnX, capturedPawnY);
        board[capturedPawnX][capturedPawnY]->setHasMoved(lastCapturedHasMoveState);
        // update last move if movehistory isn't empty
        if (!movesHistory.empty()) {
            lastOldX = movesHistory.top().lastOldX;
            lastOldY = movesHistory.top().lastOldY;
            lastMove = movesHistory.top().lastMove;
            lastCapturedHasMoveState = movesHistory.top().lastCapturedHasMoveState;
            lastMoveHasMoveState = movesHistory.top().lastMoveHasMoveState;
            lastMoveResult = movesHistory.top().moveResult;
            lastCaptured = std::move(movesHistory.top().lastCaptured);
            movesHistory.pop();
        } else {
            lastMoveResult = MoveResult::Failure;
        }
        return true;
    }
    if (lastMoveResult == MoveResult::Castle) {
        int newX = lastMove->getX();
        int newY = lastMove->getY();
        int rookY = (newY > lastOldY) ? boardSize - 1 : 0;
        int rookNewY = (newY > lastOldY) ? newY - 1 : newY + 1;
        board[lastOldX][lastOldY] = std::move(board[newX][newY]);
        board[lastOldX][lastOldY]->setHasMoved(false);
        board[lastOldX][lastOldY]->setPosition(lastOldX, lastOldY);
        if (realMove)board[lastOldX][lastOldY]->notifyObservers(lastOldX, lastOldY);
        board[lastOldX][rookY] = std::move(board[lastOldX][rookNewY]);
        board[lastOldX][rookY]->setHasMoved(false);
        board[lastOldX][rookY]->setPosition(lastOldX, rookY);
        if (realMove)board[lastOldX][rookY]->notifyObservers(lastOldX, rookY);
        board[newX][newY] = make_unique<NullPiece>(newX, newY, *this);
        board[lastOldX][rookNewY] = make_unique<NullPiece>(lastOldX, rookNewY, *this);
        // update last move if movehistory isn't empty
        if (!movesHistory.empty()) {
            lastOldX = movesHistory.top().lastOldX;
            lastOldY = movesHistory.top().lastOldY;
            lastMove = movesHistory.top().lastMove;
            lastCapturedHasMoveState = movesHistory.top().lastCapturedHasMoveState;
            lastMoveHasMoveState = movesHistory.top().lastMoveHasMoveState;
            lastMoveResult = movesHistory.top().moveResult;
            lastCaptured = std::move(movesHistory.top().lastCaptured);
            movesHistory.pop();
        } else {
            lastMoveResult = MoveResult::Failure;
        }
        return true;
    } 
        
    // update last move if movehistory isn't empty
    if (!movesHistory.empty()) {
        lastOldX = movesHistory.top().lastOldX;
        lastOldY = movesHistory.top().lastOldY;
        lastMove = movesHistory.top().lastMove;
        lastCapturedHasMoveState = movesHistory.top().lastCapturedHasMoveState;
        lastMoveHasMoveState = movesHistory.top().lastMoveHasMoveState;
        lastMoveResult = movesHistory.top().moveResult;
        lastCaptured = std::move(movesHistory.top().lastCaptured);
        movesHistory.pop();
        undoMove(true);
    }

    return false;
}

void Board::clear() {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            // Replace existing piece with a NullPiece
            board[i][j] = make_unique<NullPiece>(i, j, *this);
            // Re-attach the TextDisplay observer
            board[i][j]->attach(td);
            board[i][j]->attach(gd);
        }
    }

    winState = WinState::InProgress;
    lastMove = nullptr;
    lastOldX = -1;
    lastOldY = -1;
    lastCaptured = nullptr;
    lastMoveResult = MoveResult::Failure;
    lastMoveHasMoveState = false;
    lastCapturedHasMoveState = false;
    while (!movesHistory.empty()) {
        movesHistory.pop();
    }
    whiteKing = nullptr;
    blackKing = nullptr;
    whiteKingNum = 0;
    blackKingNum = 0;
}

bool Board::isUnderAttack(int x, int y, Colour playerColour) const {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            Piece* piece = getPiece(i, j);
            if (!piece->isEmpty() && piece->getColour() != playerColour) {
                 // Check if the opponent's piece can legally move to the (x, y) position
                if (piece->isValidMove(x, y)) {
                        return true;
                }
            }
        }
    }
    return false;
}

bool Board::isCheck(Colour playerColour) const {
    Piece* king = (playerColour == Colour::White) ? whiteKing : blackKing;
    if (king) {
        return isUnderAttack(king->getX(), king->getY(), playerColour);
    }
    return false;
}

bool Board::isCheckmate(Colour playerColour) {
    if (!isCheck(playerColour)) {
        return false;
    }

    for (int x = 0; x < boardSize; x++) {
        for (int y = 0; y < boardSize; y++) {
            Piece* piece = getPiece(x, y);
            if (!piece->isEmpty() && piece->getColour() == playerColour) {
                for (int newX = 0; newX < boardSize; newX++) {
                    for (int newY = 0; newY < boardSize; newY++) {
                        if (simulateMove(x, y, newX, newY, playerColour)) {
                            if (!isCheck(playerColour)) {
                                undoMove(false);
                                return false;
                            }
                            undoMove(false);
                        }
                    }
                }
            }
        }
    }

    return true;
}

bool Board::isStalemate(Colour playerColour) {
    for (int x = 0; x < boardSize; x++) {
        for (int y = 0; y < boardSize; y++) {
            Piece* piece = getPiece(x, y);
            if (!piece->isEmpty() && piece->getColour() == playerColour) {
                for (int newX = 0; newX < boardSize; newX++) {
                    for (int newY = 0; newY < boardSize; newY++) {
                        if (simulateMove(x, y, newX, newY, playerColour)) {
                            undoMove(false);
                            return false;
                        }
                    }
                }
            }
        }
    }

    return true;
}

bool Board::isOneKing() const {
    if (whiteKingNum == 1 && blackKingNum == 1) {
        return true;
    } else {
        cerr << "board must contain exactly one white king and one black king." << endl;
        return false;
    }
}

bool Board::isPawnCorrect() const {
    for (int i = 0; i < boardSize; i++) {
        if ((board[0][i]->getType() == Type::Pawn) || (board[boardSize - 1][i]->getType() == Type::Pawn)) {
            cerr << "no pawns are allowed on the first and last row." << endl;
            return false;
        }
    }
    return true;

}

Piece* Board::getPiece(int x, int y) const {
    if (x >= 0 && x < boardSize && y >= 0 && y < boardSize) {
        return board[x][y].get();
    }
    return nullptr;
}

Piece* Board::getLastMove() const {
    return lastMove;
}

int Board::getLastOldX() const {
    return lastOldX;
}

int Board::getLastOldY() const {
    return lastOldY;
}

WinState Board::getWinState() {
    return this->winState;
}

int Board::getSize() const {
    return boardSize;
}

MoveResult Board::getLastMoveResult() const {
    return lastMoveResult;
}

ostream &operator<<(ostream &out, const Board &b) {
  out << *b.td;
  return out;
}
