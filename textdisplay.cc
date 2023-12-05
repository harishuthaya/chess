#include <iostream>
#include "textdisplay.h"
#include "piece.h"
using namespace std;

TextDisplay::TextDisplay(int n): gridSize{n} {
	for (int r = 0; r < gridSize; ++r) {
		theDisplay.emplace_back();
		for (int c = 0; c < gridSize; ++c) {
			// Initialize the board with a checker pattern
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

	// Reset the old position of the piece on the display
	theDisplay[oldX][oldY] = ((oldX + oldY) % 2 == 0) ? ' ' : '_';
	
	// Handle the Nullpiece type, which represents an empty grid
	if (type == Type::Nullpiece) {
		c = ((x + y) % 2 == 0) ? ' ' : '_';
	}
		else {
			// Set the character for different piece types
			switch(type) {
				case Type::Pawn:
					c = 'P';
					break;
				case Type::Queen:
					c = 'Q';
					break;
				case Type::King:
					c = 'K';
					break;
				case Type::Bishop:
					c = 'B';
					break;
				case Type::Knight:
					c = 'N';
					break;
				case Type::Rook:
					c = 'R';
					break;
				default: 
					break;
			}
			if (colour == Colour::Black) {
				// convert to lower case character.
				c += 'a' - 'A';
			}
		}
	theDisplay[x][y] = c;
}

TextDisplay::~TextDisplay() {}

ostream &operator<<(ostream &out, const TextDisplay &td) {
	int rowCount = td.gridSize;
	for (auto r : td.theDisplay) {
		out << rowCount << " ";
		--rowCount;
		for (auto c : r) {
			out << c;
		}
    	out << endl;
  	}
	out << endl << "  ";
	for (char i = 'a'; i < 'a' + td.gridSize; ++i) {
		out << i;
	}
	out << endl;
	return out;
}
