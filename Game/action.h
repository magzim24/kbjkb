#pragma once
#include "card.h"
#include "player.h"
using namespace std;

class Action {
public:
	Action(Player*, Player*, Card*);
	void SetDefendingCard(Card*);
	bool IsRepulsed();
private:
	Card* attacker_card;
	Card* defending_card;
};
