#ifndef CARDMANGER_H
#define CARDMANGER_H
#include"Card.h"
#include<vector>
#include<fstream>

class CardManger {
public: 
	static const int CardNumber = 52;//一共52张牌
	Card* getOneCard();//选一张牌
	std::vector<Card *> getGameStartCards(int gameStartCards);
	bool isEmpty();
	CardManger();
	CardManger(std::ifstream &in);
	void showCard();
	void save(std::ofstream &out);
private:
	void refreshAllCards();//洗牌  
	std::vector<Card *> _recycleCardsVec;
	std::vector<Card *> _remainCardsVec;
};
#endif // !CARDMANGER_H

