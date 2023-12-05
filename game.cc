#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "game.h"
#include "piece.h"
#include "human.h"
#include "computer.h"

using namespace std;

Game::Game(Xwindow &xw): turn{Colour::White}, gameActive{false}, xw{xw} {

}

vector<int> Game::convertCoords(string coords) const {
    int col = coords[0] - 'a';
    int row = chessboard->getSize() - (coords[1] - '0');
    return vector<int>{row, col};
}

void Game::addPlayer(string player, Colour colour) {
  if (player == "human") {
    players.emplace_back(make_unique<Human>(colour));
  } else if (player == "computer1") {
    players.emplace_back(make_unique<Computer>(colour, 1, chessboard.get()));
  } else if (player == "computer2") {
    players.emplace_back(make_unique<Computer>(colour, 2, chessboard.get()));
  } else if (player == "computer3") {
    players.emplace_back(make_unique<Computer>(colour, 3, chessboard.get()));
  } else if (player == "computer4") {
    players.emplace_back(make_unique<Computer>(colour, 4, chessboard.get()));
  }
}

void Game::move(Colour curTurn) {
    vector<string> move = (turn == Colour::White) ? players[0]->getMove() : players[1]->getMove();
    vector<int> oldCoords = convertCoords(move[0]);
    vector<int> newCoords = convertCoords(move[1]);
    Piece* isPawn = chessboard->getPiece(oldCoords[0], oldCoords[1]);
    bool moveSuccess;
    if (isPawn->getType() == Type::Pawn) 
    {
      if (((curTurn == Colour::White) && (newCoords[0] == 0))||
         ((curTurn == Colour::Black) && (newCoords[0] == chessboard->getSize() - 1)))
         {
          char c = (turn == Colour::White) ? players[0]->getPromotion() : players[1]->getPromotion();
          moveSuccess = chessboard->moveSuccess(oldCoords[0], oldCoords[1], newCoords[0], newCoords[1], curTurn, c);
      } else {
        moveSuccess = chessboard->moveSuccess(oldCoords[0], oldCoords[1], newCoords[0], newCoords[1], curTurn);
      }
    } else {
      moveSuccess = chessboard->moveSuccess(oldCoords[0], oldCoords[1], newCoords[0], newCoords[1], curTurn);
    }
    if (moveSuccess) {
        if (curTurn == Colour::White) {
            turn = Colour::Black;
        } else {
            turn = Colour::White;
        }
    }
    WinState currentState = chessboard->getWinState();
    if (currentState == WinState::Player1Win) {
      players.at(0)->incrementScore(1);
      gameActive = false;
      setupUsed = false;
    }
    else if (currentState == WinState::Player2Win) {
      players.at(1)->incrementScore(1);
      gameActive = false;
      setupUsed = false;
    }
    else if (currentState == WinState::Tie) {
      players.at(0)->incrementScore(0.5);
      players.at(1)->incrementScore(0.5);
      gameActive = false;
      setupUsed = false;
    }
}

void Game::resign(Colour curTurn) {
    if (curTurn == Colour::White) {
        players[1]->incrementScore(1);
        cout << "Black wins!" << endl;
    } else {
        players[0]->incrementScore(1);
        cout << "White wins!" << endl;
    }
    gameActive = false;

}

bool Game::verifySetup() const {
    return this->chessboard->isOneKing() && this->chessboard->isPawnCorrect() && !this->chessboard->isCheck(Colour::White) && !this->chessboard->isCheck(Colour::Black);
}

void Game::addPiece(char piece, string coords) {
  vector<int> intCoords = convertCoords(coords);
  chessboard->addPiece(piece, intCoords[0], intCoords[1], 1);
}

void Game::undo() {
  bool result = chessboard->undoMove(true);
  if (result) {
    turn = (turn == Colour::White) ? Colour::Black : Colour::White;
  }
}

void Game::setUp() {
  td = make_unique<TextDisplay>(8);
  gd = make_unique<GraphicsDisplay>(9, xw);
  chessboard = make_unique<Board>(td.get(), gd.get());
  setupUsed = true;
}

void Game::removePiece(string coords) {
  vector<int> intCoords = convertCoords(coords);
  chessboard->removePiece(intCoords[0], intCoords[1]);
}

void Game::init(string p1, string p2) {
  if (!td) {
    td = make_unique<TextDisplay>(8);
  }
  if (!gd) {
    gd = make_unique<GraphicsDisplay>(9, xw);
  }
  if (!chessboard || !setupUsed) {
    chessboard = make_unique<Board>(td.get(), gd.get());
    chessboard->init();
  } else if (chessboard && !setupUsed) chessboard->clear();
  players.clear();
  this->addPlayer(p1, Colour::White);
  this->addPlayer(p2, Colour::Black);
  
  gameActive = true;
}

void Game::setTurn(string colour) {
  if (colour == "white") {
    turn = Colour::White;
  } else if (colour == "black") {
    turn = Colour::Black;
  }
}

Colour Game::getTurn() const {
    return this->turn;
}

vector<float> Game::getScores() const {
    if (players.empty() || players[0] == nullptr || players[1] == nullptr) {
      return vector<float>{0, 0};
    }
    return vector<float>{players[0]->getScore(), players[1]->getScore()};
}

bool Game::isGameActive() const {
  return gameActive;
}

ostream &operator<<(ostream &out, const Game &g) {
  return out << *(g.td);
}