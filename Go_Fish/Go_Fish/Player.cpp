#include"Player.h"
#include<map>
#include<iostream>

const std::string Player::input[15] = { "s","q","A","2","3","4","5","6","7","8","9","10","J","Q","K" };
void Player::showCards() {
	for (auto card : _handCard)
		std::cout << card -> showCard() << "  ";
	std::cout << std::endl;
}

std::string Player::askCard(std::string value) {
	std::string flag = "N";
	for (auto v : _handCard)
		if (value == v -> getCardNum())
			flag = value;
	return flag;
}

Card* Player::respondToAskCard(std::string value)
{
	Card *temp = nullptr;
	for (auto it = _handCard.begin();it != _handCard.end();it++)
		if ((*it)->getCardNum() == value){
			temp = *it;
			_handCard.erase(it);
			return temp;
		}
	return temp;
}

bool Player::revealAndRemoveCard() {
	bool remove= false;
	std::map<std::string, int> count;
	for (auto c : _handCard)
		++count[c->getCardNum()];
	for (auto m : count)
		if (m.second == 4)
		{
			remove = true;
			std::cout << _type<<" have 4 cards of  " << m.first <<" : "<< std::endl;
			auto it = _handCard.begin();
			while (it != _handCard.end())
				if ((*it)->getCardNum() == m.first) {
					std::cout << (*it)->showCard() << "  ";
					it = _handCard.erase(it);
				}
				else
					++it;
			if (_type == "You") {
				std::cout << " \nRemove this 4 cards and now your cards are as follow:" << std::endl;
				showCards();
			}
			scorePoint();
			std::cout << "\n" <<_type<<" get " << _points << " points." << std::endl;
		}
	return remove;
}

void Player::getAskCard(Card *card){
	_handCard.push_back(card);
	revealAndRemoveCard();
}

Player::Player(){
	_points = 0;
	_handCard.clear();
	_type = "You";
}

void Player::setHandCard(std::vector<Card *>  cards) {
	_handCard = cards;
}

std::string Player::askCard() {
	std::cout << "\nYou can input 's' to save the game ," << std::endl;
	std::cout << "or input 'q' to stop the game and return to main menu,"<<std::endl;
	std::cout<<"or input the number which you want to ask and continue the game:" << std::endl;
	std::cout << "please input  s  ,  q  or [A,2...K]" << std::endl;
	std::string num;
	bool flag = false;
	do {
		std::cin >> num;
		flag = checkInput(num);
		if (flag) {
			std::cout << "Invaild input! Please input again : " << std::endl;
			continue;
		}
		num = askCard(num);
		if (num == "N")
			std::cout << "The number you ask dosen't in you hand, please input the number which is in you hand: " << std::endl;
	} while (num == "N"||flag);
	return num;
}

void Player::scorePoint() {
	++_points;
}

void Player::goFish(Card *card) {
	_handCard.push_back(card);
}

unsigned int Player::points() {
	return _points;
}

bool  Player::checkInput(std::string num) {
	bool flag = true;
	if (num.size() > 1 && num != "10")
		flag = true;
	for (int i = 0;i < 15;i++)
		if (num == input[i])
			flag = false;
	return flag;
}

bool  Player::isEmpty() {
	return _handCard.empty();
}

std::string Player::type() {
	return _type;
}

Player::Player(std::ifstream &in) {
	unsigned int size, cardRealNum;
	_handCard.clear();
	in >> size;
	for (unsigned int i = 0;i < size;i++) {
		in >> cardRealNum;
		Card* card = new Card(cardRealNum % 13, static_cast<Card::CardType>(cardRealNum % 4));
		_handCard.push_back(card);
	}
	in >> _points >> _type;
}

void Player::save(std::ofstream &out) {
	out << _handCard.size() << std::endl;
	for (auto c : _handCard)
		out << c->cardRealNum() << " ";
	out << std::endl;
	out << _points << std::endl;
	out << _type << std::endl;
}