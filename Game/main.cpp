#include "game.h"
#include "card.h"
#include "stdlib.h"

int main() {
	system("Chcp 1251");
	int amount_players = 4;
	Game game = Game(amount_players);
	Card* card = new Card();
	game.GameStart();
	
}