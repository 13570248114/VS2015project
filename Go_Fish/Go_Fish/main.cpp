#include"Game.h"

void menu();
int main() {
	while (1)
		menu();
}

void menu() {
	std::cout << "\t\tGo Fish\n\n\n";
	std::cout << "   1. Continue to play the game" << std::endl;
	std::cout << "   2.start new game\n\n" << std::endl;

	char choice;
	do {
		std::cin >> choice;
		if (choice<'1' || choice>'2')
			std::cout << "Invaild input ! please input again!" << std::endl;
	} while (choice<'1' || choice>'2');

	if (choice == '2'){
		Game game;
		game.gameStart();
		game.gamePlaying();
		game.gameOver();
	}
}