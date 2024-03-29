#pragma once
#include "action.h"
#include "player.h"
#include "card.h"
#include "game.h"

Action::Action(Player* attacker, Player* defender, Card* attacker_card) {
	this->attacker_card = attacker_card;
}
bool Action::IsRepulsed() {
	if (Game::value_level.at(this->defending_card->value) >= Game::value_level.at(this->attacker_card->value) &&
		this->defending_card->suit == this->attacker_card->suit) {
		return true;
	}
	return false;
}
void Action::SetDefendingCard(Card* card) {
	this->defending_card = card;
}