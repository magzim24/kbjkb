#include <algorithm>
#include "battle.h"
#include "player.h"
#include "card.h"
using namespace ::std;

bool Battle::IsCardsRepulsed() {
	for (Action* action : this->actions) {
		if (!(action->IsRepulsed())) {
			return false;
		}
	}
	return true;
}
Battle::Battle() {
	this->currentCardValue = vector<string>();
}
int Battle::AmountOfActions() {
	return this->actions.end() - this->actions.begin();
}
bool Battle::IsCardValueExists(string value) {
	if (find(this->currentCardValue.begin(), 
			 this->currentCardValue.end(), value) 
		!= this->currentCardValue.end()) {
		return true;
	}
	return false;
}
void Battle::AddValueToCardValueVector(string value) {
	if (!IsCardValueExists(value)) {
		this->currentCardValue.push_back(value);
	}
}
vector<string> Battle::GetCurrentCardValue() {
	return currentCardValue;
}
void Battle::AddAction(Action* action) {
	this->actions.push_back(action);
}