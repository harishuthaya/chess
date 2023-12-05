#include "human.h"
#include "piece.h"
#include <string>
#include <iostream>
using namespace std;

Human::Human(Colour colour):
    Player{colour} {

}

vector<string> Human::getMove() {
    vector<string> moves{2, ""};
    cin >> moves[0] >> moves[1];
    return moves;
}

char Human::getPromotion() const {
    char c;
    cin >> c;
    return c;
}
