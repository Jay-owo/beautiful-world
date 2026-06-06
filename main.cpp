#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <vector>
#include "Tile.h"
#include "Player.h"
#include "Deck.h"

using namespace std;

int main() {
	Deck deck;
	deck.init();
	deck.shuffle();
	int kitacount = 0;
	Player player;

	for (int i = 0; i < 13; i++) {
		player.Draw(deck.draw());
	}
	Tile t = deck.draw();
	cout << "抽牌: " << t.toString() << endl;
	player.Draw(t);


	while (true) {
		cout << "\n====================\n";
		cout << "拔北張數: " << kitacount << endl;
		cout << "副露數: "<< player.getMeldCount()<< endl;
		if (deck.Empty()) {
			cout << "沒牌了，可以按3離開~" << endl;
		}
		player.sortHand();
		player.showHand();

		cout << "1.丟牌 2.拔北 3.自摸 4.離開\n";
		int choice;
		int A = 0;
		int choice2 = 0;
		int round = 0;
		cin >> choice;
		if (choice == 4) break;
		if (choice == 1) {
			int number;
			if (deck.Empty()) {
				cout << "沒牌了!可以按4離開~" << endl;
			}
			cout << "丟牌:";
			cin >> number;
			player.disCard(number);
			while ((A !=1 && A !=2) && round !=2) {
				Tile t = deck.draw();
				cout << "對手丟牌: " << t.toString() << endl;
				cout << "1.碰 2.槓 3.榮和 4.不理\n";
				cin >> A;
				if (A == 4) {
					round++;
					continue;
				}
				if(A == 3){
					if (player.checkRon(t)) {
						cout << " 榮和！" << endl;
						break;
					}
					else {
						cout << "未胡牌！" << endl;
					}
					continue;
				}
				if (A == 1) {
					if (player.canPong(t)) {
						player.pong(t);
						cout << "碰了!" << endl;
						player.sortHand();
						player.showHand();
						cout << "丟牌:";
						cin >> choice2;
						player.disCard(choice2);
					}
					else {
						cout << "不能碰!" << endl;
						round++;
						continue;
					}
				}
				if (A == 2) {
					if (player.canKong(t)) {
						player.kong(t);

						Tile supplement = deck.draw();
						cout << "槓了!" << endl;
						cout << "補牌: "
							<< supplement.toString()
							<< endl;

						player.Draw(supplement);
					}
					else {
						cout << "不能槓!" << endl;
						round++;
						continue;
					}
				}
			}
			if  (A!=2 ) {
				Tile t = deck.draw();
				cout << "抽牌: " << t.toString() << endl;
				player.Draw(t);
			}
		}
		if (choice == 2) {
			int number2;
			if (!player.hasNorth()) {
				cout << "你沒有北" << endl;
				continue;
			}
			player.kita();
			if (deck.Empty()) {
				cout << "沒牌了，可以按4離開~" << endl;
				continue;
			}
			Tile t = deck.draw();
			cout << "抽牌: " << t.toString() << endl;
			player.Draw(t);
			kitacount++;

		}
		if (choice == 3) {

			if (player.checkWin()) {
				cout << " 自摸！胡牌！" << endl;
				break;
			}
			else {
				cout << "未胡牌！" << endl;
			}
		}
	}
}