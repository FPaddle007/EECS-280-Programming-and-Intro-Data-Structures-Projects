/* Player.cpp
 *
 * Euchre player interface
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
#include <algorithm>
#include "Card.h"
#include "Player.h"

class SimplePlayer : public Player {
public:
	SimplePlayer(string name_in) :name(name_in), hand() {
	}

	const std::string& get_name() const {
		return name;
	}
	void add_card(const Card& c) {
		assert(hand.size() < MAX_HAND_SIZE);
		hand.push_back(c);
	}
	bool make_trump(const Card& upcard, bool is_dealer,
		int round, std::string& order_up_suit) const {
		assert(round == 1 || round == 2);
		string trump = upcard.get_suit();
		if (round == 1) {
			if (num_face_trump(trump) >= 2) {
				order_up_suit = trump;
				return true;
			}
			return false;
		}
		else {
			trump = Suit_next(trump);
			if (num_face_trump(trump) >= 1 || is_dealer) {
				order_up_suit = trump;
				return true;
			}
			return false;
		}
	}
	void add_and_discard(const Card& upcard) {
		assert(hand.size() >= 1);
		hand.push_back(upcard);
		hand.erase(hand.begin() + index_lowest_card(upcard.get_suit()));
	}
	Card lead_card(const std::string& trump) {
		standard_assert(trump);
		int index = 0;
		if (has_non_trump(trump)) {
			index = index_highest_non_trump(trump);
		}
		else {
			index = index_highest_card(trump);
		}
		Card returnCard = hand[index];
		hand.erase(hand.begin() + index);
		return returnCard;
	}
	Card play_card(const Card& led_card, const std::string& trump) {
		standard_assert(trump);
		int index = 0;
		if (has_lead_suit(led_card, trump)) {
			index = index_highest_led_suit(led_card, trump);
		}
		else {
			index = index_lowest_card(trump);
		}
		Card returnCard = hand[index];
		hand.erase(hand.begin() + index);
		return returnCard;
	}
private:
	string name;
	vector<Card> hand;

//EFFECT Calls the assert for the requires clause of having 
// at least one card and trump is a valid suit.
	void standard_assert(string trump) const {
		assert(hand.size() >= 1);
		assert(trump == "Diamonds" || trump == "Clubs" ||
			   trump == "Hearts" || trump == "Spades");
	}

//REQUIRES Player has at at least one card, trump is a valid suit
//EFFECTS Returns the number of trump face cards if the upcard is ordered up.
	int num_face_trump(string trump) const {
		standard_assert(trump);
		int count = 0;
		int handSize = hand.size();
		for (int i = 0; i < handSize; ++i) {
			if (hand[i].is_trump(trump) && hand[i].is_face()) {
				count++;
			}
		}
		return count;
	}

//REQUIRES Player has at least one card, trump is a valid suit
//EFFECT Returns index of the lowest card in the Players' hand.
	int index_lowest_card(string trump) {
		standard_assert(trump);
		int index = 0;
		int handSize = hand.size();
		for (int i = 0; i < handSize; ++i) {
			if (Card_less(hand[i], hand[index], trump)) {
				index = i;
			}
		}
		return index;
	}

//REQUIRES Player has at least one card, trump is a valid suit
//EFFECT Returns true if Player has at least one non trump card in hand.
	bool has_non_trump(string trump) {
		standard_assert(trump);
		int handSize = hand.size();
		for (int i = 0; i < handSize; ++i) {
			if (hand[i].get_suit(trump) != trump) {
				return true;
			}
		}
		return false;
	}

//REQUIRES Player has at least one card, trump is a valid suit,
//		   Player has a non trump card in hand
//EFFECT Returns index of the highest non trump card in the Players' hand.
	int index_highest_non_trump(string trump) {
		standard_assert(trump);
		assert(has_non_trump(trump));
		int index = 0;
		int handSize = hand.size();
		while (hand[index].get_suit(trump) == trump) {
			index++;
		}
		for (int i = index; i < handSize; ++i) {
			if ((hand[i].get_suit(trump) != trump) && (Card_less(hand[index], hand[i], trump))){
					index = i;
			}
				
		}
		return index;
	}

//REQUIRES Player has at least one card, trump is a valid suit
//EFFECT Returns index of the highest card in the Players' hand.
	int index_highest_card(string trump) {
		standard_assert(trump);
		int index = 0;
		int handSize = hand.size();
		for (int i = 0; i < handSize; ++i) {
			if (Card_less(hand[index], hand[i], trump)) {
				index = i;
			}
		}
		return index;
	}

//REQUIRES Player has at least one card, trump is a valid suit
//EFFECT Returns true if Player has at least one non trump card in hand.
	bool has_lead_suit(const Card& led_card, string trump) {
		assert(hand.size() >= 1);
		string ledSuit = led_card.get_suit(trump);
		int handSize = hand.size();
		for (int i = 0; i < handSize; ++i) {
			if (hand[i].get_suit(trump) == ledSuit) {
				return true;
			}
		}
		return false;
	}

//REQUIRES Player has at least one card, trump is a valid suit
// Player has a card with suit of led card
//EFFECT Returns index of the highest led suit card in the Players' hand.
	int index_highest_led_suit(const Card& led_card, string  trump) {
		standard_assert(trump);
		assert(has_lead_suit(led_card, trump));
		string led_suit = led_card.get_suit(trump);
		int index = 0;
		int handSize = hand.size();
		while (hand[index].get_suit(trump) != led_suit) {
			index++;
		}
		for (int i = index; i < handSize; ++i) {
			if (hand[i].get_suit(trump) == led_suit &&
				Card_less(hand[index], hand[i], led_card, trump)) {
				index = i;
			}
		}
		return index;
	}
};

class HumanPlayer : public Player {
public:
	HumanPlayer(string name_in):name(name_in), hand(){
	}
	
	const std::string& get_name() const {
		return name;
	}

	void add_card(const Card& c) {
		assert(hand.size() < MAX_HAND_SIZE);
		hand.push_back(c);
		std::sort(hand.begin(), hand.end());
	}

	bool make_trump(const Card& upcard, bool is_dealer, int round,
		std::string& order_up_suit) const {
		assert(round == 1 || round == 2);
		std::string option;
		print_human_hand(this);
		print_human_player_name(this);
		cout << ", please enter a suit, or \"pass\":" << endl;
		cin >> option;
		assert(option == "pass" || option == "Spades" || option == "Clubs" ||
			   option == "Hearts" || option == "Diamonds");
		if (option == "pass") {
			return false;
		}
		order_up_suit = option;
		return true;
	}

	void add_and_discard(const Card& upcard) {
		assert(hand.size() >= 1);
		int discardChoice = -1;
		print_human_hand(this);
		cout << "Discard upcard: [-1]" << endl;
		print_human_player_name(this);
		cout << ", please select a card to discard:" << endl;
		cin >> discardChoice;
		assert(discardChoice >= -1 && discardChoice < MAX_HAND_SIZE);
		if (discardChoice == -1) {
			return;
		}
		hand[discardChoice] = upcard;
		std::sort(hand.begin(), hand.end());
		return;
	}

	Card lead_card(const std::string& trump) {
		assert(hand.size() >= 1);
		assert(trump == "Diamonds" || trump == "Clubs" ||
			   trump == "Hearts" || trump == "Spades");
		int cardIndex = 0;
		print_human_hand(this);
		print_human_player_name(this);
		cout << ", please select a card:" << endl;
		cin >> cardIndex;
		Card returnCard = hand[cardIndex];
		hand.erase(hand.begin() + cardIndex);
		return returnCard;
	}

	Card play_card(const Card& led_card, const std::string& trump) {
		assert(hand.size() >= 1);
		assert(trump == "Diamonds" || trump == "Hearts" ||
			   trump == "Clubs" || trump == "Spades");
		int cardIndex = 0;
		print_human_hand(this);
		print_human_player_name(this);
		cout << ", please select a card:" << endl;
		cin >> cardIndex;
		Card returnCard = hand[cardIndex];
		hand.erase(hand.begin() + cardIndex);
		return returnCard;
	}

private:
	string name;
	vector<Card> hand;

//REQUIRES Player has at least one card
//EFFECTS Prints out the proper format for printing a human players' hand.
	void print_human_hand(const Player* p) const {
		int handSize = hand.size();
		for (int i = 0; i < handSize; ++i) {
			cout << "Human player " << *p << "'s hand: [" << i << "] "
				 << hand[i] << endl;
		}
	}
//EFFECTS Prints out "Human Player " and then the name of the player.
	void print_human_player_name(const Player* p) const {
		cout << "Human player " << *p;
	}
};

std::ostream& operator<<(std::ostream& os, const Player& p) {
	os << p.get_name();
	return os;
}

Player* Player_factory(const std::string& name, const std::string& strategy) {
	if (strategy == "Simple") {
		return new SimplePlayer(name);
	}
	else if (strategy == "Human") {
		return new HumanPlayer(name);
	}
	return nullptr;
}