#include "Deck.h"
#include "Tile.h"
#include <algorithm>// 洗牌用 
#include <random>
#include <ctime>
void Deck::init() {
	tiles.clear();
	for (int i = 0; i < 4; i++) {
		tiles.emplace_back(0, 1);
		tiles.emplace_back(0, 9);//for 1m and 9m
	}
	for (int s = 1;s <= 2;s++) {
		for (int v = 1;v <= 9;v++) {
			for (int i = 0;i < 4;i++) {
				tiles.emplace_back(s, v);//for 1~9s,1~9p
			}
		}
	}
	for (int v = 1; v <= 7;v++) {
		for (int i = 0;i < 4;i++) {
			tiles.emplace_back(3, v);// 字牌
		}
	}
}
void Deck::shuffle() {
	std::mt19937 rng(time(0));
	std::shuffle( tiles.begin(), tiles.end(), rng);
}
Tile Deck::draw() {
	Tile t = tiles.back();
	tiles.pop_back();
	return t;
}
bool Deck::Empty() {
	return tiles.empty();
}

	
