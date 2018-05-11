#ifndef GAME_H
#define GAME_H
#include "CardManger.h"
#include "Player.h"
#include"ComputerPlayer.h"

class Game {
public:
	void gameStart();
	void gamePlaying();
	void gameOver();
	void playerIsEmpty(Player *player);
	void save();
	void recoveGame();
private:
	CardManger *_cardManger;
	Player *_player;
	ComputerPlayer *_computerPlayer;
	void humanAsk();
	void computerAsk();
};
#endif // !GAME_H

