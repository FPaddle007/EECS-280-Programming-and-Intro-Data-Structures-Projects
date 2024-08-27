/* Pack.cpp
 *
 * Represents a pack of playing cards
 * Project UID 1d9f47bfc76643019cfbf037641defe1
 *
 * by Andrew DeOrio <awdeorio@umich.edu>
 * 2014-12-21
 */

using namespace std;

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <string>
#include <array>
#include <vector>
#include <sstream>
#include "Card.h"
#include "Pack.h"

Pack::Pack() {
	Pack::next = 0;
	for (int i = 0; i < PACK_SIZE; ++i) {
		Card currentCard(RANK_NAMES_BY_WEIGHT[(i+7) - (6 * (i/6))], SUIT_NAMES_BY_WEIGHT[i/6]);
		cards[i] = currentCard;
	}
}

Pack::Pack(std::istream& pack_input) {
	Pack::next = 0;

	assert(!pack_input.bad());

	string rank;
	string strJunk;
	string suit;
	int index = 0;

	while (pack_input >> rank >> strJunk >> suit) {
		Pack::cards[index] = Card(rank, suit);
		index++;
	}
}

Card Pack::deal_one() {
	assert(!empty());
	return cards[next++];
}

void Pack::reset() {
	Pack::next = 0;
}

void Pack::shuffle() {
	array<Card, PACK_SIZE> storage;
	const int NUM_SHUFFLES = 7;
	for (int i = 0; i < NUM_SHUFFLES; ++i) {
		for (int i = 0; i < PACK_SIZE; ++i) {
			storage[i] = cards[i];
		}
		int cardsIndex = 0;
		for (int storIndex = PACK_SIZE / 2; storIndex < PACK_SIZE; ++storIndex) {
			cards[cardsIndex] = storage[storIndex];
			cardsIndex += 2;
		}
		cardsIndex = 1;
		for (int storIndex = 0; storIndex < PACK_SIZE / 2; ++storIndex) {
			cards[cardsIndex] = storage[storIndex];
			cardsIndex += 2;
		}
	}
	reset();
}

 bool Pack::empty() const {
	return (next >= PACK_SIZE);
}