#include "game.h"
#include "card.h"

int main() {
	int amount_players = 4;
	Game game = Game(amount_players);
	Card* card = new Card();
	game.GameStart();
	
}