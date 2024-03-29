#include <map>
#include <iostream>
#include "card.h"
#include "game.h"
#include "player.h"
#include "bot.h"
#include "user.h"
using namespace std;

const map<string, int> Game::value_level = {
		{"6", 1}, {"7", 2}, {"8", 3},
		{"9", 4}, {"10", 5}, {"Jack", 6},
		{"Queen", 7}, {"King", 8}, {"Ace", 9}
};
Game::Game(int amount_players) {
	this->amount_players = amount_players;
	this->current_fighting_player = nullptr;
	if(this->amount_players >1 && this->amount_players <6){
		this->deck = new GameDeck();
		this->players = vector<Player*>();
		AddPlayersToArrayPlayers();
		this->deck->SetTrumpCard();
		SetFirstAttackingPlayer();
	}
	else {
		this->deck = nullptr;
		this->players = vector<Player*>();
	}
}

void Game::AddPlayersToArrayPlayers() {
	for (int i = 0; i < this->amount_players - 1; i++) {
		Bot* bot = new Bot();
		DistributionCards(bot);
	}
	User* user = new User();
	DistributionCards(user);
}
void Game::DistributionCards(Player* player) {
	for (int j = 0; j < 6; j++) {
		Card* card = this->deck->GetCard();
		player->TakeCard(card);
	}
	this->players.push_back(player);
}
void Game::ClearGameDeskOfCards() {

}

void Game::SetFirstAttackingPlayer() {
	Card* current_trump_card = nullptr;
	string trump_suit = this->deck->trump_card->suit;
	for (Player* player : this->players) {
		Card* card = player->GetMinTrumpCard(trump_suit);
		if (current_trump_card != nullptr) {
			
			if (card != nullptr) {
				if (value_level.at(card->value) <
					value_level.at(current_trump_card->value)) {
					current_trump_card = card;
					this->current_fighting_player = player;
				}
			}
		}
		else {
			current_trump_card = card;
			this->current_fighting_player = player;
		}
	}
}
int Game::indexOfVectorElem(Player* player) {
	return distance(this->players.begin(), find(this->players.begin(), this->players.end(), player));
}
void Game::MoveByPlayers(int index, int& step) {
	for (int j = index; j < this->amount_players; j++, step++) {
		cout << this->players[j]->GetMinTrumpCard(this->deck->trump_card->suit)->value << "\n";
	}
}
void Game::GameStart(){
	int step = 0;
	while (true) {
		if (step > 0) {
			MoveByPlayers(0, step);
			break;
		}
		else {
			int index = indexOfVectorElem(this->current_fighting_player);
			MoveByPlayers(index, step);
		}
	}
}

// 