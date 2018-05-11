#ifndef PLAYER_H
#define PLAYER_H
#include<iostream>
#include<vector>
#include"CardManger.h"
#include"Card.h"
#include<ctime>
#include<string>
#include<fstream>

class Player {
public:
	static const std::string input[15];
	void showCards();
	std::string askCard(std::string value);
	std::string askCard();
	Card *respondToAskCard(std::string value);
	bool revealAndRemoveCard();
	void getAskCard(Card *);
	void setHandCard(std::vector<Card *> cards);
	void scorePoint();
	void goFish(Card * card);
	unsigned int points();
	bool checkInput(std::string);
	bool isEmpty();
	std::string type();
	Player();
	Player(std::ifstream &in);
	void save(std::ofstream &out);
protected:
	std::vector<Card *> _handCard;
	unsigned int _points;
	std::string _type;
private:
	
};
#endif // !PLAYER_H
