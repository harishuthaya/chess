#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "game.h"
#include "piece.h"
#include "human.h"

using namespace std;

vector<int> Game::convertCoords(string coords) const {
    int row = chessboard->getSize() - (coords[1] - '0');
    int col = coords[0] - 'a';
    return vector<int>{row, col};
}

void Game::addPlayer(string player, Colour colour) {
  if (player == "human") {
    players.emplace_back(make_unique<Human>(colour));
  } else if (player == "computer1") {
    
  } else if (player == "computer2") {

  } else if (player == "computer3") {

  } else if (player == "computer4") {

  }
}

void Game::move(Colour curTurn) {
    vector<string> move = players[0]->getMove();
    vector<int> oldCoords = convertCoords(move[0]);
    vector<int> newCoords = convertCoords(move[1]);
    if (chessboard->moveSuccess(oldCoords[0], oldCoords[1], newCoords[0], newCoords[1])) {
        if (curTurn == Colour::White) {
            turn = Colour::Black;
        } else {
            turn = Colour::White;
        }
    }
}

void Game::resign(Colour curTurn) {
    if (curTurn == Colour::White) {
        players[1]->incrementScore();
    } else {
        players[0]->incrementScore();
    }

}

bool Game::verifySetup() const {
    return this->chessboard->isOneKing() && this->chessboard->isPawnCorrect();
}

void Game::addPiece(char piece, string coords) {
  vector<int> intCoords = convertCoords(coords);
  chessboard->addPiece(piece, intCoords[0], intCoords[1], 1);
}

void Game::removePiece(string coords) {
  vector<int> intCoords = convertCoords(coords);
  chessboard->removePiece(intCoords[0], intCoords[1]);
}

void Game::init(string p1, string p2) {
  this->addPlayer(p1, Colour::White);
  this->addPlayer(p2, Colour::Black);
  
  td = make_unique<TextDisplay>(8);
  chessboard = make_unique<Board>(td.get());
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

vector<int> Game::getScores() const {
    return vector<int>{players[0]->getScore(), players[1]->getScore()};
}

ostream &operator<<(ostream &out, const Game &g) {
  return out << *(g.td);
}