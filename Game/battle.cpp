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
Battle::Battle(Player* attacker, Player* defender) {
	this->attacker = attacker;
	this->defender = defender;
}
void Battle::AttackCard(int index_card, Card* card) {

}
void Battle::DefenseCard(int index_card, Card* card) {

}