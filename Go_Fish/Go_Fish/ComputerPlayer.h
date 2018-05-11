#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include"Player.h"
#include<fstream>
#include<string>

class ComputerPlayer :public Player {
public:
	ComputerPlayer();
	ComputerPlayer(std::ifstream &in);
	//void revealAndRemoveCard();
	std::string randomAskCard();
};
#endif // !COMPUTERPLAYER_H

