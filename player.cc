#include "piece.h"
#include "player.h"

Player::Player(Colour colour): colour{colour}, score{0} {
    
}

void Player::incrementScore() {
    ++score;
}
