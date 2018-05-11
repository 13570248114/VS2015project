#include"Game.h"
#include<iostream>
#include<fstream>

void Game::gameStart() {
	_cardManger = new CardManger();
	_player = new Player();
	_computerPlayer = new ComputerPlayer();
	_player->setHandCard(_cardManger->getGameStartCards(7));
	std::cout << "Game start! Now your cards are as follow: " << std::endl;
	_player->showCards();
	_computerPlayer->setHandCard(_cardManger->getGameStartCards(7));
}

void Game::gamePlaying() {
	std::cout << "Pleause input '1' or '0' to decide who play first." << std::endl;
	std::cout << "1 . You first \t\t0 . Computer first" << std::endl;
	char select;
	std::cin >> select;
	while (select<'0' || select>'1')
	{
		std::cout << "Invaild input , please input again!" << std::endl;
		std::cin >> select;
	}
	bool isEnd = _cardManger->isEmpty() && _player->isEmpty() && _computerPlayer->isEmpty();
	if (select == '1') {
		while (!isEnd) {
			humanAsk();
			computerAsk();
			isEnd = _cardManger->isEmpty() && _player->isEmpty() && _computerPlayer->isEmpty();
		}	
	}
	else {
		while (!isEnd) {
			computerAsk();
			humanAsk();
			isEnd = _cardManger->isEmpty() && _player->isEmpty() && _computerPlayer->isEmpty();
		}
	}
}

void Game::humanAsk() {
	if (!(_cardManger->isEmpty() && _player->isEmpty() && _computerPlayer->isEmpty()))
		std::cout << "\nNow is your round:" << std::endl;
	bool successAsk =false;
	bool remove;
	do {
		if (_cardManger->isEmpty() && _player->isEmpty() && _computerPlayer->isEmpty())
			break;
		std::string num = _player->askCard();
		if (num != "s"&&num != "q") {
			Card *card;
			if ((card = _computerPlayer->respondToAskCard(num)) != nullptr) {
				playerIsEmpty(_computerPlayer);
				std::cout << "success! Now your cards are as follow: " << std::endl;
				_player->getAskCard(card);
				successAsk = true;
			}
			else {
				successAsk = false;
				std::cout << "Go Fish!" << std::endl;
				Card *card = _cardManger->getOneCard();
				if (card != nullptr)
					_player->goFish(card);
				std::cout << "After take a new card ,your cards are as follow:" << std::endl;
			}
			remove = _player->revealAndRemoveCard();
			if (!remove)
				_player->showCards();
			playerIsEmpty(_player);
		}
		else if (num == "s") {
			save();
			std::cout << "Game have been saved" << std::endl;
		}
		else
			break;
		} while (successAsk);	
}

void Game::computerAsk() {
	if (!(_cardManger->isEmpty() && _player->isEmpty() && _computerPlayer->isEmpty()))
		std::cout << "\nNow is the computer's round:" << std::endl;
	bool successAsk =false;
	srand(time(NULL));
	do {
		if (_cardManger->isEmpty() && _player->isEmpty() && _computerPlayer->isEmpty())
			break;
		std::string num = _computerPlayer->randomAskCard();
		std::cout << "Computer player ask for " << num << std::endl;
		Card *card;
		
		if ((card = _player->respondToAskCard(num)) != nullptr) {
			playerIsEmpty(_player);
			std::cout << "Computer ask success! " << std::endl;
			_computerPlayer->getAskCard(card);
			successAsk = true;
			std::cout<< "After being asked, your cards are as follow : " << std::endl;
			_player->showCards();
		}
		else {
			std::cout << "Go Fish!" << std::endl;
			Card *card = _cardManger->getOneCard();
			if (card != nullptr)
				_computerPlayer->goFish(card);
			successAsk = false;
		}
		_computerPlayer->revealAndRemoveCard();
		playerIsEmpty(_computerPlayer);
	} while (successAsk);
}

void Game::gameOver() {
	if (_player->points() > _computerPlayer->points())
		std::cout << "You win!" << std::endl;
	else
		std::cout << "Computer win!" << std::endl;
	std::cout << "Your points is " << _player->points() << std::endl;
	std::cout << "Computer points is " << _computerPlayer->points() << "\n\n"<<std::endl;
}

void Game::playerIsEmpty(Player *player) {
	if (player->isEmpty()) {
		player->setHandCard(_cardManger->getGameStartCards(7));
		if (player->type() == "You"){
			if (!player->isEmpty()) {
				std::cout << "After take  new card ,your cards are as follow:" << std::endl;
				player->showCards();
			}
		}
	}
}

void  Game::save() {
	std::ofstream outCardManger("CardManger.txt");
	std::ofstream outPlayer("Player.txt");
	std::ofstream outComputerPlayer("ComputerPlayer.txt");
	_cardManger->save(outCardManger);
	_player->save(outPlayer);
	_computerPlayer->save(outComputerPlayer);
}
void  Game::recoveGame() {
	std::ifstream inCardManger("CardManger.txt");
	std::ifstream inPlayer("Player.txt");
	std::ifstream inComputerPlayer("ComputerPlayer.txt");
	_cardManger = new CardManger(inCardManger);
	_player = new Player(inPlayer);
	_computerPlayer = new ComputerPlayer(inComputerPlayer);
	std::cout << "Game continu! Now your cards are as follow: " << std::endl;
	_player->showCards();
}


