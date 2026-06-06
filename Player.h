#ifndef Player_H
#define Player_H
#include "Tile.h"
#include<vector>

class Player {
private:
	vector<Tile> hand;
	int kitacount;
	int meldCount = 0; // 紀錄碰和槓的數量
public:
	int getMeldCount();
	void Draw(Tile t);
	void sortHand();
	void showHand();
	void disCard(int index);
	bool hasNorth();
	void kita();
	int tileToIndex(const Tile& t);
	void pong(const Tile& t);
	bool canPong(const Tile& t);
	void kong(const Tile& t);
	bool canKong(const Tile& t);
	bool canFormSets(vector<int>& counts,int needSets);
	bool checkWin();
	bool checkRon(Tile t);
	};
#endif