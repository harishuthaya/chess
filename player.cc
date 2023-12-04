#include "piece.h"
#include "player.h"

Player::Player(Colour colour): colour{colour}, score{0} {
    
}

int Player::getScore() const {
    return score;
}

void Player::incrementScore(float i) {
    score += i;
}

Colour Player::getColour() const {
    return colour;
}
