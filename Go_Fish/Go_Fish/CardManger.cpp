#include"CardManger.h"
#include<ctime>
#include<iostream>

void CardManger::refreshAllCards() {

	while (!_recycleCardsVec.empty())
	{
		Card* pOld = _recycleCardsVec.back();
		_recycleCardsVec.pop_back();
		_remainCardsVec.push_back(pOld);
	}
	srand(time(NULL));
	for (int i = 0; i< 100; ++i)
	{
		int a = rand() % CardNumber;
		int b = rand() % CardNumber;
		Card* temp;
		temp = _remainCardsVec[a];
		_remainCardsVec[a] = _remainCardsVec[b];
		_remainCardsVec[b] = temp;
	}
}

Card* CardManger::getOneCard() {
	if (_remainCardsVec.empty())
		return nullptr;
	Card* selectCard = _remainCardsVec.back();
	_remainCardsVec.pop_back();
	_recycleCardsVec.push_back(selectCard);
	return selectCard;
}

CardManger::CardManger(){
	_remainCardsVec.clear();
	_recycleCardsVec.clear();
	for (int i = 0;i < CardNumber;i++)
	{
		Card* card = new Card(i % 13, static_cast<Card::CardType>(i % 4));
		_remainCardsVec.push_back(card);
	}
	refreshAllCards();
}

std::vector<Card *> CardManger::getGameStartCards(int gameStartCards) {
	std::vector<Card *> cardVec;
	for (int i = 0;i != gameStartCards;i++) {
		Card* card;
		if ((card = getOneCard() )!= nullptr)
			cardVec.push_back(card);
	}
	return cardVec;	
}

bool CardManger::isEmpty() {
	return _remainCardsVec.empty();
}

void  CardManger::showCard() {
	int i = 0;
	for (auto card : _remainCardsVec) {
		std::cout << card->showCard() << "  ";
		i++;
		if (i == 13) {
			std::cout << std::endl;
			i = 0;
		}
	}
}

void CardManger::save(std::ofstream &out) {
	out << _remainCardsVec.size() << std::endl;
	for (auto c : _remainCardsVec)
		out << c->cardRealNum() << " ";
	out << std::endl;
	out << _recycleCardsVec.size() << std::endl;
	for (auto c : _recycleCardsVec)
		out << c->cardRealNum() << " ";
}

CardManger::CardManger(std::ifstream &in) {
	unsigned int size1, size2,cardRealNum;
	_remainCardsVec.clear();
	_recycleCardsVec.clear();
	in >> size1;
	for (unsigned int i = 0;i < size1;i++){
		in >> cardRealNum;
		Card* card = new Card(cardRealNum % 13, static_cast<Card::CardType>(cardRealNum % 4));
		_remainCardsVec.push_back(card);
	}
	in >> size2;
	for (unsigned int i = 0;i < size2;i++) {
		in >> cardRealNum;
		Card* card = new Card(cardRealNum % 13, static_cast<Card::CardType>(cardRealNum % 4));
		_recycleCardsVec.push_back(card);
	}
}

