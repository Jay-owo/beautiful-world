#include"Tile.h"

Tile::Tile(int s, int v) :suit(s), value(v) {}

string Tile::toString() const {
	if(suit == 0) return to_string(value) + "萬";
	if(suit == 1) return to_string(value) + "條";
	if(suit == 2) return to_string(value) + "筒";
	string honors[] = { "東","南","西","北","白","發","中" };
	return honors[value-1];
}
