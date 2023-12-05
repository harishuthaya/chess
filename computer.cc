#include "computer.h"
#include "piece.h"
#include <string>
#include <iostream>
using namespace std;

Computer::Computer(Colour colour, int level, Board *board):
    Player{colour}, level{level}, board{board} {

}

std::vector<std::string> Computer::generateLevel1() {
    vector<vector<string>> legalMoves;
    
}

std::vector<std::string> Computer::generateLevel2() {

}

std::vector<std::string> Computer::generateLevel3() {

}

std::vector<std::string> Computer::generateLevel4() {

}

vector<string> Computer::getMove() const {

}

char Computer::getPromotion() const {

}
