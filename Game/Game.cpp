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
	this->battle = new Battle();
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
		FirstDistributionCards(bot);
	}
	User* user = new User();
	FirstDistributionCards(user);
}
void Game::FirstDistributionCards(Player* player) {
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
bool Game::HandleUserSelectedChoice(int& posCursor, int indexPlayer,
	Battle* battle, const map<int, Card*>& cards, bool currentFighterIsUser, Action* currentAction = nullptr) {
	if (posCursor != cards.size()) {
		if (currentFighterIsUser) {
			currentAction->SetDefendingCard(next(cards.begin(), posCursor)->second);
			battle->AddValueToCardValueVector(next(cards.begin(), posCursor)->second);
			this->current_fighting_player->RemoveCardFromSetCards(next(cards.begin(), posCursor)->first);
		}
		else {
			Action* action = new Action(this->players[indexPlayer], this->current_fighting_player, next(cards.begin(), posCursor)->second);
			battle->AddValueToCardValueVector(next(cards.begin(), posCursor)->second);
			battle->AddAction(action);
		}
		return true;
	}
	else return false;
}
int Game::HandleClickedButton(int button, int& posCursor, int cards_size) {
	if (button == 13) {
		return 0;
	}
	else if (button == 224) {
		switch (_getch()) {
		case 75:
			if (posCursor > 0) posCursor--;
			break;
		case 77:
			if (posCursor < cards_size) posCursor++;
			break;
		}
		return 1;
	}return -1;
}
void Game::PrintAllAvailableCardOfUser(const map<int, Card*>& cards, int& lenStr, int* indexesOfStrings, int lenCards, int posCursor) {
	int i = 1;
	string str;
	indexesOfStrings[0] = 0;
	for (auto& card : cards) {
		Card* card_ = card.second;
		str = card_->value + " " + card_->suit + "   ";
		cout << str;
		if (i == 1)
		{
			lenStr = str.length();
			indexesOfStrings[1] = lenStr;
		}
		else {
			lenStr += str.length();
			indexesOfStrings[i] = indexesOfStrings[i - 1] + str.length();
		}
		i++;
	}
	cout << "Пасс" << endl;
	indexesOfStrings[lenCards] = lenStr + 3;
	cout << string(indexesOfStrings[posCursor], ' ') << "^" << posCursor <<endl;
}
void Game::FillUserAndDeskCardsContainers(int step, Player* player, map<int, Card*>& cards) {
	if (step == 0) {
		this->cardsOnDesk = CardsOnDesk(vector<Card*>());
		cards = player->GetAvailableCardToAttack(vector<Card*>());
	}
	else {
		this->cardsOnDesk = CardsOnDesk(this->battle->GetCurrentCardsOnDesk());
		cards = player->GetAvailableCardToAttack(this->battle->GetCurrentCardsOnDesk());
	}
}
void Game::DisplayTextOfMenu(const map<int, Card*>& avCardsOfCurFightPlayer,
	int lenStr, int indOfStrings[], int lenCards, int posCur) {
	system("cls");
	cout << "Козырь: " << this->deck->trump_card->suit << " " << this->deck->trump_card->value << endl;
	cout << "Ваши карты: ";
	for (auto& card : this->current_fighting_player->GetAvailableCardToAttack(vector<Card*>()))
		cout << card.second->value << " " << card.second->suit << " ";
	cout << "\nКарты, которыми вы сможете отбиться от " << currentAction->GetAttackingCard()->suit << " " << currentAction->GetAttackingCard()->value<<":" << endl;
	PrintAllAvailableCardOfUser(avCardsOfCurFightPlayer, lenStr, indOfStrings, lenCards, posCur);
	
}
void Game::DisplayMenu(const map<int, Card*>& cards, const bool curFighterIsUser,
	bool& tookCards, int j) {
	int button, posCursor = 0, lenCards = cards.size(), lenStr = 0;
	int* indexesOfStrings = new int[lenCards];

	while (this->battle->AmountOfActions() < Game::MAX_CARDS_TO_REPULSE) {
		currentAction = players[j]->MakeDecisionAboutAttack(this->cardsOnDesk.GetCardsOnDesk(), this->current_fighting_player);

		if (currentAction == nullptr) break;
		this->battle->AddValueToCardValueVector(currentAction->GetAttackingCard());
		this->battle->AddAction(currentAction);
		map<int, Card*> availableCardOfCurFightPlayer = this->current_fighting_player->GetAvailableCardToDefend(currentAction->GetAttackingCard(), this->deck->trump_card);
		while (availableCardOfCurFightPlayer.size() > 0) {
			DisplayTextOfMenu(availableCardOfCurFightPlayer, lenStr, indexesOfStrings, lenCards, posCursor);
			button = _getch();
			int result = HandleClickedButton(button, posCursor, availableCardOfCurFightPlayer.size());
			if (result == 0) {
				if (!HandleUserSelectedChoice(posCursor, j, this->battle, availableCardOfCurFightPlayer,
					curFighterIsUser, currentAction = currentAction)) {
					tookCards = true;
				}
				break;
			}
		}
		posCursor = 0;
		if (this->current_fighting_player->GetLenghtSetCards() > 0 && availableCardOfCurFightPlayer.size() == 0)
		{
			tookCards = true;
			return;
		}
		else break;
	}
}
char Game::UserDefendDecision(int step, int& j, map<int, Card*>& cards,
	bool curFightIsUser, bool tookCards){
	if (this->battle->AmountOfActions() < Game::MAX_CARDS_TO_REPULSE) {
		FillUserAndDeskCardsContainers(step, this->players[j], cards);
		DisplayMenu(cards, curFightIsUser, tookCards, j);
		if (j == amount_players - 1) j = -1;
		return 0;
	}
	else return -1;
	
}
int Game::indexOfVectorElem(Player* player) {
	return distance(this->players.begin(), find(this->players.begin(), this->players.end(), player));
}
void Game::GenActionsWithOnlyBotCard(int j) {
	if (this->battle->AmountOfActions() < Game::MAX_CARDS_TO_REPULSE) {
		while (true) {
			currentAction = players[j]->MakeDecisionAboutAttack(this->cardsOnDesk.GetCardsOnDesk(), this->current_fighting_player);
			if (currentAction == nullptr) break;
			this->battle->AddAction(currentAction);
		}
	}
}

Player* Game::GetLoser() {
	vector<Player*> playersWithCards = vector<Player*>();
	for (Player* player : this->players) {
		if (player->GetLenghtSetCards() > 0) {
			playersWithCards.push_back(player);
		}
	}
	if (playersWithCards.size() == 1)
		return playersWithCards[0];
	else
		return this->current_fighting_player;
}

void Game::DistributeCards() {
	int lenDeck = this->deck->GetLengthStack();
	if (lenDeck > 0) {
		int index = indexOfVectorElem(this->current_fighting_player);
		for (int j = index + 1 == amount_players ? 0 : index + 1; j != index; j == amount_players - 1 ? j = 0 : j++) {
			for (int i = 0; i < lenDeck; ++i) {
				if (this->players[j]->GetLenghtSetCards() < this->MAX_CARDS_TO_REPULSE) {
					this->players[j]->TakeCard(this->deck->GetCard());
				}
				else break;
			}

		}
		for (int i = 0; i < lenDeck; ++i) {
			if (this->players[index]->GetLenghtSetCards() < this->MAX_CARDS_TO_REPULSE) {
				this->players[index]->TakeCard(this->deck->GetCard());
			}
			else break;
		}
	}
}

void Game::PrintInfoForAttackByUser(const map<int, Card*>& cards, Player* player, int lenStr, int indOfStrings[], int lenCards, int posCur) {
	system("cls");
	cout << "Козырь: " << this->deck->trump_card->suit << " " << this->deck->trump_card->value << endl;
	cout << "Ваши карты: ";
	for (auto& card : player->GetAvailableCardToAttack(vector<Card*>()))
		cout << card.second->value << " " << card.second->suit << " ";
	cout << "\nКарты, которыми вы сможете атаковать оппонента: " << lenStr <<endl;
	PrintAllAvailableCardOfUser(cards, lenStr, indOfStrings, lenCards, posCur);
}

Action* Game::HandleUserAttack(const int& posCursor, map<int, Card*>& cards,
	bool curFighterIsUser, int indexPlayer) {
	if (posCursor != cards.size()) {
		
		Action* action = new Action(this->players[indexPlayer], this->current_fighting_player, next(cards.begin(), posCursor)->second);
		battle->AddValueToCardValueVector(next(cards.begin(), posCursor)->second);
		battle->AddAction(action);
		return action;
	}
	else return nullptr;
}

void Game::DisplayAttackMenu(const map<int, Card*>& cards, const bool curFighterIsUser,
	bool& tookCards, int j) {
	int button, posCursor = 0, lenCards = cards.size(), lenStr = 0;
	int* indexesOfStrings = new int[lenCards];

	while (this->battle->AmountOfActions() < Game::MAX_CARDS_TO_REPULSE) {
		map<int, Card*> availableCards = this->players[j]->GetAvailableCardToAttack(this->battle->GetCurrentCardsOnDesk());
		while (availableCards.size() > 0) {
			PrintInfoForAttackByUser(availableCards, this->players[j], lenStr, indexesOfStrings, lenCards, posCursor);
			button = _getch();
			int result = HandleClickedButton(button, posCursor, availableCards.size());
			if (result == 0) {
				Action* action = HandleUserAttack(posCursor, availableCards,
					curFighterIsUser, j);
				Action* botResponse = this->current_fighting_player->MakeDecisionAboutDefend(action, this->deck->trump_card);
				if (!botResponse->GetDefendingCard()) {
					tookCards = true;
				}
				else {
					battle->AddValueToCardValueVector(botResponse->GetDefendingCard());
				}
				break;
			}
		}
		posCursor = 0;
	}
}

void Game::HandleBotAttackToBot(Player* player) {
	Action* decision = player->MakeDecisionAboutAttack(battle->GetCurrentCardsOnDesk(), this->current_fighting_player);
	if (decision) {
		Action* defenseDecision = this->current_fighting_player->MakeDecisionAboutDefend(decision, this->deck->trump_card);
		battle->AddAction(defenseDecision);
		battle->AddValueToCardValueVector(defenseDecision->GetAttackingCard());
		if (defenseDecision->GetDefendingCard()) {
			battle->AddValueToCardValueVector(defenseDecision->GetDefendingCard());
		}
		else {
			this->current_fighting_player->TakeCard(defenseDecision->GetAttackingCard());
		}
	}	
}

void Game::MoveByPlayers(int& indexOfCurFightPlayer) {
	int index = indexOfCurFightPlayer;
	bool currentFighterIsUser = this->current_fighting_player->type ==  TypePlayer::User_t;
	this->battle = new Battle();
	map<int, Card*> cards;
	
	bool tookCards = false;
	int step = 0;
	if (currentFighterIsUser) {
		for (int j = index + 1 == amount_players ? 0 : index + 1; j != index; j == amount_players - 1 ? j = 0 : j++) {
			if (!tookCards) {
				char userDecision = UserDefendDecision(step, j, cards, currentFighterIsUser, tookCards);
				if (userDecision == -1) break;
				step++;
			}
			else {
				GenActionsWithOnlyBotCard(j);
				break;
			}
		}
		if (tookCards) {
			for (Card* card : this->battle->GetCurrentCardsOnDesk()) {
				this->current_fighting_player->TakeCard(card);
			}
		}
	}
	else {
		for (int j = index + 1 == amount_players ? 0 : index + 1; j != index; j == amount_players - 1 ? j = 0 : j++) {
			if (this->players[j]->type == TypePlayer::User_t) {
				DisplayAttackMenu(cards, currentFighterIsUser, tookCards, j);
			}
			else {
				HandleBotAttackToBot(players[j]);
			}
		}
	}
}

void Game::GameStart(){
	Player* loser;
	int index = indexOfVectorElem(this->current_fighting_player);
	for (int j = index + 1 == amount_players ? 0 : index; ; j == amount_players - 1 ? j = 0:j++) {
		
		MoveByPlayers(j);
		DistributeCards();
		this->current_fighting_player = this->players[j == amount_players - 1 ? j = 0 : j++];
	}
	loser = GetLoser();
	if (loser != nullptr) {
		cout << "Дурак: " << loser->Name;
	}
}

// 