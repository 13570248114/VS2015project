#ifndef CARD_H
#define CARD_H
#include<string>

class Card {
public:
	enum CardType {
		Spade = 0,                  //����
		Heart = 1,                  //����
		Club = 2,                   //÷��
		Diamond = 3,                //����
	};
	static const std::string num[13] ;
	static const  std::string type[4] ;
	CardType getCardType();
	std::string getCardNum();
	std::string showCard();
	Card();
	Card(int carNum, CardType cardType);
	unsigned int cardRealNum();
private:
	int _carNum;
	CardType _cardType;
};
#endif // !CARD_H

