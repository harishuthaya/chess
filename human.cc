#include "human.h"
#include "piece.h"
#include <string>
#include <iostream>
using namespace std;

Human::Human(Colour colour):
    Player{colour} {

}

vector<string> Human::getMove() const {
    vector<string> moves{2, ""};
    cin >> moves[0] >> moves[1];
    return moves;
}
