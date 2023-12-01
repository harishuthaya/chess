#include <iostream>
#include "textdisplay.h"
#include "piece.h"
using namespace std;

TextDisplay::TextDisplay(int n): gridSize{n} {
	for (int r = 0; r < gridSize; ++r) {
		theDisplay.emplace_back();
		for (int c = 0; c < gridSize; ++c) {
			char spot = ((r + c) % 2 == 0) ? ' ' : '_';
			theDisplay.at(r).emplace_back(spot);
		}
  	}
}

void TextDisplay::notify(const Piece &p, int oldX, int oldY) {
	char c;
	Type type = p.getType();
	Colour colour = p.getColour();
	int x = p.getX();
	int y = p.getY();
	theDisplay[oldX][oldY] = ((oldX + oldY) % 2 == 0) ? ' ' : '_';
	
	if (type == Type::Nullpiece) {
		c = ((x + y) % 2 == 0) ? ' ' : '_';
	}
		else {
			switch(type) {
			case Type::Queen:
				c = 'Q';
				break;
			case Type::King:
				c = 'K';
				break;
			case Type::Bishop:
				c = 'B';
				break;
			default: 
				break;
			}
			if (colour == Colour::Black) {
				c += 'a' - 'A'; // convert to lower case character.
			}
		}
	theDisplay[x][y] = c;
}

TextDisplay::~TextDisplay() {}

ostream &operator<<(ostream &out, const TextDisplay &td) {
	for (auto r : td.theDisplay) {
		for (auto c : r) {
			out << c;
		}
    	out << endl;
  	}
	return out;
}
