#include "player.h"
#include "game.h"
#include "card.h"
#include <string>
using namespace ::std;

Card* Player::GetMinTrumpCard(string suit_trump) {
	Card* current_min_trump_card = nullptr;
	for (Card* card : this->set_cards) {
		if (card->suit == suit_trump) {
			string value = card->value;
			if (current_min_trump_card != nullptr) {
				if (Game::value_level.at(current_min_trump_card->value) >
					Game::value_level.at(card->value)) {
					current_min_trump_card = card;
				}
			}
			else current_min_trump_card = card;
		}
	}
	return current_min_trump_card;
}
void Player::TakeCard(Card* inserting_card){
	this->set_cards.push_back(inserting_card);
}