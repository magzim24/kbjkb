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
	vector<Card*> cards_on_desk;
	GameDeck* deck; // колода
	Player* current_fighting_player;
	int indexOfVectorElem(Player*);
	void AddPlayersToArrayPlayers();
	void ClearGameDeskOfCards();
	void DistributionCards(Player*);
	void SetFirstAttackingPlayer();
	void MoveByPlayers();
public:
	static const map<string, int> value_level;
	const int MAX_CARDS_TO_REPULSE = 6;
	Game(int amount_players);
	void GameStart();
};