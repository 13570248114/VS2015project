#include"ComputerPlayer.h"
#include<ctime>
#include<map>

ComputerPlayer::ComputerPlayer() :Player(){
	_type = "computer";
}

ComputerPlayer::ComputerPlayer(std::ifstream &in):Player(in){}

std::string ComputerPlayer::randomAskCard() {
	if (_handCard.size() != 0) {
		int i = rand() % _handCard.size();
		return _handCard[i]->getCardNum();
	}
	else
		return "randomAskError";
}

