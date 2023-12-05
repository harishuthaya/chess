#include "piece.h"
#include "player.h"

Player::Player(Colour colour): colour{colour} {
    
}

Colour Player::getColour() const {
    return colour;
}
