#pragma once
#include <vector>
#include "card.h"
#include "action.h"
using namespace ::std;


class Player {
private:
	vector<Card*> set_cards;
public:
	void TakeCard(Card*);
	Card* GetMinTrumpCard(string suit_trump);
	Card* Attack(int);
	vector<Card*> GetAvailableCardToAttack(vector<string>);
};