#include <map>
#include <conio.h>
#include <iostream>
#include "card.h"
#include "game.h"
#include "player.h"
#include "bot.h"
#include "user.h"
#include "battle.h"
using namespace ::std;


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
void Game::MoveByPlayers() {
	int index = indexOfVectorElem(this->current_fighting_player);
	Battle* battle = new Battle();
	for (int j = index + 1 == amount_players ? 0 : index + 1; j != index; j++) {
		//cout << this->players[j]->GetMinTrumpCard("Hearts")->value<< " "<< j << endl;
		if (battle->AmountOfActions() < 6) {
			vector<Card*> cards = this->players[j]->GetAvailableCardToAttack(battle->GetCurrentCardValue());
			int posCursor = 0;
			int button;
			int lenCards = cards.end() - cards.begin();
			int* indexesOfStrings = new int[lenCards];

			int lenStr = 0;
			while (true) {
				if (battle->AmountOfActions() < 6) {
					system("cls");
					cout << "Вы можете воспользоваться этими картами" << endl;
					int i = 0;
					for (Card* card : cards) {
						string str = card->value + " " + card->suit + "   ";
						cout << str;
						if (i == 0)
						{
							lenStr = str.length();
							indexesOfStrings[0] = 0;
						}
						else {
							lenStr += str.length();
							indexesOfStrings[i] = indexesOfStrings[i - 1] + str.length();
						}
						i++;
					}
					cout << "Пасс" << endl;
					indexesOfStrings[lenCards] = lenStr + 3;
					cout << string(indexesOfStrings[posCursor] + 3, ' ') << "^";

					cout << posCursor + 1;
					button = _getch();
					if (button == 13) {
						if (posCursor != 7) {
							Action* action = new Action(this->players[j], this->current_fighting_player, cards[posCursor]);
							battle->AddValueToCardValueVector(cards[posCursor]->value);
							battle->AddAction(action);

						}
						else break;
					}
					else if (button == 224) {
						switch (_getch()) {
						case 75:
							cout << "ArrowLeft";
							if (posCursor > 0) posCursor--;
							break;
						case 77:
							cout << "ArrowRight";
							if (posCursor < 6) posCursor++;
							break;
						}
					}
				}
				else {
					break;
				}

			}
			if (j == amount_players - 1) j = -1;
		}
		else break;
	}
}
void Game::GameStart(){

	while (true) {
		
		MoveByPlayers();
	}
}

// 