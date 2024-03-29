#pragma once
#include <vector>
#include "card.h"
#include "player.h"
using namespace ::std;

class Battle {
private:
	vector<Action*> actions;
	vector<string> currentCardValue;
	bool IsCardValueExists(string);
public:
	Battle();
	bool IsCardsRepulsed();
	int AmountOfActions();
	void AddValueToCardValueVector(string);
	vector<string> GetCurrentCardValue();
	void AddAction(Action*);
};