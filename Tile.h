#ifndef Tile_H
#define Tile_H

#include<string>
using namespace std;

class Tile {
public:
	int suit;  //0:萬,1:條,2:筒,3:自牌
	int value;//1~9 for m,s,p; 1~7 for honor

	Tile(int s, int v);
	string toString() const;

};

#endif