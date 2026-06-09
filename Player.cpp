#include "Player.h"
#include "Deck.h"
#include "Tile.h"
#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;

int kitacount = 0;
int Player::getMeldCount() {
	return meldCount;
}
void Player::Draw(Tile t) {
	hand.push_back(t);
}
void Player::sortHand() {
	sort(hand.begin(), hand.end(), [](Tile a, Tile b) {
		if (a.suit != b.suit) {
			return a.suit < b.suit;
		}
		return a.value < b.value;
		});
}
void Player::showHand() {
	cout << "手牌 : ";
	for (int i = 0; i < hand.size();i++) {
		cout << "(" << i << ")" << hand[i].toString() << " ";
	}
	cout << endl;
}
void Player::disCard(int index) {
	if (index >= 0 && index < hand.size()){
		cout<<"丟牌: " << hand[index].toString() << endl;
		hand.erase(hand.begin() + index);
	}
}
bool Player::hasNorth() {
	for (auto &t : hand) {
		if (t.suit == 3 && t.value == 4) {
			return true;
		}
	}
	return false;
}
void Player::kita() {
	for (int i = 0;i < hand.size();i++) {
		if (hand[i].suit == 3 && hand[i].value == 4) {
			cout << "拔北" << endl;
			hand.erase(hand.begin() + i);
			kitacount++;
			return;
		}
	}
}
int Player::tileToIndex(const Tile& t) {
	if (t.suit == 0) {
		return t.value - 1;
	}
	if (t.suit == 1) {
		return 9 + t.value - 1;
	}
	if (t.suit == 2) {
		return 18 + t.value - 1;
	}
	if (t.suit == 3) {
		return 27 + t.value - 1;
	}
}
bool Player::canPong(const Tile& t) {
	int count = 0;
	for (auto& tile : hand) {
		if (tile.suit == t.suit && tile.value == t.value) {
			count++;
		}
	}
	return count >= 2;
}
void Player::pong(const Tile& t) {
	int removed = 0;

	for (auto it = hand.begin(); it != hand.end();) {

		if (it->suit == t.suit &&
			it->value == t.value) {

			it = hand.erase(it);
			removed++;

			if (removed == 2)
				break;
		}
		else {
			++it;
		}
	}

	meldCount++;
}
void Player::kong(const Tile& t) {

	int removed = 0;

	for (auto it = hand.begin(); it != hand.end();) {

		if (it->suit == t.suit &&
			it->value == t.value) {

			it = hand.erase(it);
			removed++;

			if (removed == 3)
				break;
		}
		else {
			++it;
		}
	}

	meldCount++;
}
bool Player::canKong(const Tile& t) {
	int count = 0;
	for (auto& tile : hand) {
		if (tile.suit == t.suit && tile.value == t.value) {
			count++;
		}
	}
	return count >= 3;
}
bool Player::canFormSets(vector <int>& counts,int needSets) {
	int i;
	if (needSets == 0) {

		for (int x : counts) {

			if (x != 0)
				return false;
		}

		return true;
	}
	for (i = 0; i < 34; i++) {
		if (counts[i] > 0) {
			break;
		}
	}

	if (i == 34) {
		return true;
	}
	if (counts[i] >= 3) {
		counts[i] -= 3;
		if (canFormSets(counts, needSets - 1)) {
			return true;
		}
		counts[i] += 3;
	}
	if (i < 27 && i % 9 <= 6 && counts[i + 1]>0 && counts[i + 2] > 0) {
		counts[i]--;
		counts[i + 1]--;
		counts[i + 2]--;

		if (canFormSets(counts, needSets - 1)) {
			return true;
		}
		counts[i]++;
		counts[i + 1]++;
		counts[i + 2]++;
	}
	return false;
}
bool Player::checkWin() {
	vector<int> counts(34, 0);
	for (const auto& t : hand) {
		int index = tileToIndex(t);
		counts[index]++;
	}
	for (int i = 0; i < 34; i++) {
		if (counts[i] >= 2) {
			counts[i] -= 2;
			if (canFormSets(counts,4 - meldCount)) {
				return true;
			}
			counts[i] += 2;
		}
	}
	return false;
}
bool Player::checkRon(Tile t)
{
	hand.push_back(t);

	bool result = checkWin();

	hand.pop_back();

	return result;
}
