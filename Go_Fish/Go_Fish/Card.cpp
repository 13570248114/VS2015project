#include"Card.h"

const std::string Card::num[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
const  std::string  Card::type[4] = { "Spade","Heart","Club","Diamond" };

Card::Card(int carNum, CardType cardType):_carNum(carNum),_cardType(cardType){}

Card::CardType Card::getCardType() {
	return _cardType;
}

std::string Card::getCardNum() {
	return num[_carNum];
}

Card::Card() {

}

std::string Card::showCard() {
	std::string card(type[_cardType]);
	card +='_';
	card += num[_carNum];
	return card;
}

unsigned int Card::cardRealNum() {
	return _carNum + static_cast<unsigned int>(_cardType) * 13;
}