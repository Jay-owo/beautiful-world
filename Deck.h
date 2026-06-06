#ifndef Deck_H
#define Deck_H
#include "Tile.h"
#include<vector>
using namespace std;
class Deck {
private:
	vector<Tile> tiles;
public:
	void init();// initialize the deck with 136 tiles,but our porgram is only for 3 players,so we will only use 108 tiles
	void shuffle();// shuffle the deck
	Tile draw();
	bool Empty();//check if the deck is empty
};

#endif

