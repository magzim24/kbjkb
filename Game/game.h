#pragma once
#include <vector>
#include "battle.h"
#include "deck.h"
#include "player.h"
#include "card.h"
#include "CardsOnDesk.h"
#include <map>
using namespace ::std;

class Player;
class Card;

class Game {
private:
	int amount_players;
	
	vector<Player*> players;
	CardsOnDesk cardsOnDesk;
	GameDeck* deck; // колода
	Player* current_fighting_player;
	Battle* battle;
	Action* currentAction;
	int indexOfVectorElem(Player*);
	void AddPlayersToArrayPlayers();
	void ClearGameDeskOfCards();
	void FirstDistributionCards(Player*);
	void SetFirstAttackingPlayer();
	void MoveByPlayers(int& indexOfCurFightPlayer);
	int HandleClickedButton(int, int&, int);
	void PrintAllAvailableCardOfUser(const map<int, Card*>&, int&, int*, int, int);
	bool HandleUserSelectedChoice(int&, int, Battle*,
		const map<int, Card*>&, bool, Action*);
	Player* GetLoser();
	void FillUserAndDeskCardsContainers(int step, Player* player, map<int, Card*>& cards);
	void DisplayMenu(const map<int, Card*>& cards, const bool curFighterIsUser,
		bool& tookCards, int j);
	void DisplayTextOfMenu(const map<int, Card*>& avCardsOfCurFightPlayer,
		int lenStr, int indOfStrings[], int lenCards, int posCur);
	char UserDefendDecision(int step, int& j, map<int, Card*>& cards,
		bool curFightIsUser, bool tookCards);
	void GenActionsWithOnlyBotCard(int j);
	void DistributeCards();
	void PrintInfoForAttackByUser(const map<int, Card*>& cards, Player* player,
		int lenStr, int indOfStrings[], int lenCards, int posCur);
	Action* HandleUserAttack(const int& posCursor, map<int, Card*>& cards,
		bool curFighterIsUser, int indexPlayer);
	void DisplayAttackMenu(const map<int, Card*>& cards, const bool curFighterIsUser,
		bool& tookCards, int j);
	void HandleBotAttackToBot(Player* player);
public:
	static const map<string, int> value_level;
	const int MAX_CARDS_TO_REPULSE = 6;
	Game(int amount_players);
	void GameStart();
	
};