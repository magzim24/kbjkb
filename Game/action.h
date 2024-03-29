#pragma once
#include "player.h"
#include "card.h"
using namespace std;

class Player;
class Action {
public:
	Action(Player*, Player*, Card*);
	void SetDefendingCard(Card*);
	bool IsRepulsed();
private:
	Card* attacker_card;
	Card* defending_card;
};
