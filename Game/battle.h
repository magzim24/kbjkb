#pragma once
#include <vector>
#include "card.h"
#include "player.h"
using namespace ::std;

class Battle {
private:
	vector<Action*> actions;
public:
	Player* attacker;
	Player* defender;
	Battle(Player*, Player*);
	bool IsCardsRepulsed();
	void AttackCard(int , Card*); // index_card, card 
	void DefenseCard(int index_card, Card* card);
	void TossCard();
};