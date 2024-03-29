#pragma once
#include <vector>
#include "battle.h"
#include "deck.h"
#include "player.h"
#include "card.h"
#include <map>
using namespace ::std;

class Player;
class Card;

class Game {
private:
	int amount_players;
	vector<Player*> players;
	Battle* battle; 
	vector<Card*> cards_on_desk;
	GameDeck* deck; // колода
	Player* current_fighting_player;
	int indexOfVectorElem(Player*);
	void AddPlayersToArrayPlayers();
	void ClearGameDeskOfCards();
	void DistributionCards(Player*);
	void SetFirstAttackingPlayer();
	void MoveByPlayers(int, int&);
public:
	static const map<string, int> value_level;
	Game(int amount_players);
	void GameStart();
};