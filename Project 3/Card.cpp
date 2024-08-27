// Project UID 1d9f47bfc76643019cfbf037641defe1

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



// rank and suit names
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

//declare helper function
static bool Card_less_trump(const Card& a, const Card& b, const std::string& trump);

Card::Card() {
	rank = "Two";
	suit = "Spades";
}

Card::Card(const std::string& rank_in, const std::string& suit_in) {
	assert(rank_in == "Ace" || rank_in == "King" || rank_in == "Queen" ||
		rank_in == "Jack" || rank_in == "Ten" || rank_in == "Nine" ||
		rank_in == "Eight" || rank == "Seven" || rank_in == "Six" ||
		rank_in == "Five" || rank_in == "Four" || rank_in == "Three" ||
		rank_in == "Two");
	assert(suit_in == "Spades" || suit_in == "Clubs" ||
		   suit_in == "Diamonds" || suit_in == "Hearts");
	rank = rank_in;
	suit = suit_in;
}

std::string Card::get_rank() const {
	return rank;
}

std::string Card::get_suit() const {
	return suit;
}

std::string Card::get_suit(const std::string& trump) const {
	assert(trump == "Spades" || trump == "Clubs" ||
		trump == "Diamonds" || trump == "Hearts");
	if (is_left_bower(trump)){
		return trump;
	}
	return suit;
}

bool Card::is_face() const {
	return (rank == "Ace" || rank == "King" || rank == "Queen" || rank == "Jack");
}

bool Card::is_right_bower(const std::string& trump) const {
	assert(trump == "Spades" || trump == "Clubs" ||
		trump == "Diamonds" || trump == "Hearts");
	return (rank == "Jack" && suit == trump);
}

bool Card::is_left_bower(const std::string& trump) const {
	assert(trump == "Spades" || trump == "Clubs" ||
		trump == "Diamonds" || trump == "Hearts");
	return (rank == "Jack" && suit == Suit_next(trump));
}

bool Card::is_trump(const std::string& trump) const {
	assert(trump == "Spades" || trump == "Clubs" ||
		trump == "Diamonds" || trump == "Hearts");
	return (get_suit(trump) == trump);
}

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec (see the appendices) before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=

bool operator<(const Card& lhs, const Card& rhs) {
	if (lhs.get_rank() == rhs.get_rank()) {
		if (lhs.get_suit() == rhs.get_suit()) {
			return false;
		}
		for (int i = 0; i < NUM_SUITS; ++i) {
			if (SUIT_NAMES_BY_WEIGHT[i] == lhs.get_suit()) {
				return true;
			}
			if (SUIT_NAMES_BY_WEIGHT[i] == rhs.get_suit()) {
				return false;
			}
		}
	}
	for (int i = 0; i < NUM_RANKS; ++i) {
		if (RANK_NAMES_BY_WEIGHT[i] == lhs.get_rank()) {
			return true;
		}
		if (RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()) {
			return false;
		}
	}
	return false;
}

bool operator<=(const Card& lhs, const Card& rhs) {
	if (lhs == rhs) {
		return true;
	}
	if (lhs < rhs) {
		return true;
	}
	else {
		return false;
	}
}

bool operator>(const Card& lhs, const Card& rhs) {
	if (lhs <= rhs) {
		return false;
	}
	else {
		return true;
	}
}

bool operator>=(const Card& lhs, const Card& rhs) {
	if (lhs == rhs) {
		return true;
	}
	if (lhs > rhs) {
		return true;
	}
	else {
		return false;
	}
}

bool operator==(const Card& lhs, const Card& rhs) {
	return ((lhs.get_rank() == rhs.get_rank()) && (lhs.get_suit() == rhs.get_suit()));
}

bool operator!=(const Card& lhs, const Card& rhs) {
	return (!(lhs == rhs));
}

std::string Suit_next(const std::string& suit) {
	assert(suit == "Spades" || suit == "Clubs" ||
		suit == "Diamonds" || suit == "Hearts");
	if (suit == "Diamonds") {
		return "Hearts";
	}
	if (suit == "Hearts") {
		return "Diamonds";
	}
	if (suit == "Spades") {
		return "Clubs";
	}
	return "Spades";
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
	os << card.get_rank() << " of " << card.get_suit();
	return os;
}

bool Card_less(const Card& a, const Card& b, const std::string& trump) {
	assert(trump == "Spades" || trump == "Clubs" ||
		   trump == "Diamonds" || trump == "Hearts");
	if (a.is_trump(trump) || b.is_trump(trump)) {
		return Card_less_trump(a, b, trump);
	}
	return a < b;
}

bool Card_less(const Card& a, const Card& b, const Card& led_card,
	const std::string& trump) {
	assert(trump == "Spades" || trump == "Clubs" ||
		trump == "Diamonds" || trump == "Hearts");
	if (a.is_trump(trump) || b.is_trump(trump)) {
		return Card_less_trump(a, b, trump);
	}
	if (a.get_suit(trump) == led_card.get_suit(trump) && 
		b.get_suit(trump) == led_card.get_suit(trump)) {
		return a < b;
	}
	if (a.get_suit(trump) == led_card.get_suit(trump) && 
		b.get_suit(trump) != led_card.get_suit(trump)) {
		return false;
	}
	if (a.get_suit(trump) != led_card.get_suit(trump) && 
		b.get_suit(trump) == led_card.get_suit(trump)) {
		return true;
	}
	return a < b;
}

// REQUIRES trump is a valid suit, a or b is a trump card
// EFFECT Compares two cards if one of them is a trump card

static bool Card_less_trump(const Card& a, const Card& b, const std::string& trump) {
	assert(trump == "Spades" || trump == "Clubs" ||
		trump == "Diamonds" || trump == "Hearts");
	assert(a.is_trump(trump) || b.is_trump(trump));
	if (a.get_suit(trump) == trump && b.get_suit(trump) == trump) {
		if (a.is_right_bower(trump)) {
			return false;
		}
		if (b.is_right_bower(trump)) {
			return true;
		}
		if (a.is_left_bower(trump)) {
			return false;
		}
		if (b.is_left_bower(trump)) {
			return true;
		}
		return a < b;
	}
	if (a.get_suit(trump) == trump && b.get_suit(trump) != trump) {
		return false;
	}
	return true;
}
