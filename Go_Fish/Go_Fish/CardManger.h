#ifndef CARDMANGER_H
#define CARDMANGER_H
#include"Card.h"
#include<vector>
#include<fstream>

class CardManger {
public: 
	static const int CardNumber = 52;//һ��52����
	Card* getOneCard();//ѡһ����
	std::vector<Card *> getGameStartCards(int gameStartCards);
	bool isEmpty();
	CardManger();
	CardManger(std::ifstream &in);
	void showCard();
	void save(std::ofstream &out);
private:
	void refreshAllCards();//ϴ��  
	std::vector<Card *> _recycleCardsVec;
	std::vector<Card *> _remainCardsVec;
};
#endif // !CARDMANGER_H

