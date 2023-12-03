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

void Game::move() {
    vector<string> move;
    if (turn == Colour::White) {
        move = players[0]->getMove();
    } else if (turn == Colour::Black) {
        move = players[1]->getMove();
    }
}

void Game::resign() {

}

void Game::verifySetup() const {
    return true;
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

ostream &operator<<(ostream &out, const Game &g) {
  return out << *(g.td);
}