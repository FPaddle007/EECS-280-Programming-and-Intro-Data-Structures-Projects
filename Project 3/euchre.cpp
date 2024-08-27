// euchre.cpp
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
#include "Pack.h"
#include "Player.h"

using namespace std;

void print_error_statement();
void check_errors_and_print_args(int argc, char* argv[]);

class Game {
public:
	Game(int argc, char* argv[]) {
		string pack_in = argv[1];
		string shuffleType_in = argv[2];
		int winningScore_in = atoi(argv[3]);
		string p1_name = argv[4];
		string p1_type = argv[5];
		string p2_name = argv[6];
		string p2_type = argv[7];
		string p3_name = argv[8];
		string p3_type = argv[9];
		string p4_name = argv[10];
		string p4_type = argv[11];
		const string filename = pack_in;
		ifstream ifs(filename);
		assert(ifs.is_open());
		deck = Pack(ifs);
		shuffleType = shuffleType_in;
		winningScore = winningScore_in;
		team0Score = 0;
		team1Score = 0;
		dealerIndex = 0;
		numHand = 0;
		Player* p1 = Player_factory(p1_name, p1_type);
		Player* p2 = Player_factory(p2_name, p2_type);
		Player* p3 = Player_factory(p3_name, p3_type);
		Player* p4 = Player_factory(p4_name, p4_type);
		playerVector.push_back(p1);
		playerVector.push_back(p2);
		playerVector.push_back(p3);
		playerVector.push_back(p4);
		upcard = Card();
	}


	// REQUIRES deck to have 24 cards, dealer index to be between 0 and 3
	// MODIFIES deck, playerVector
	// EFFECTS Deals 5 cards to each player in sequence outlined in the spec
	void deal_cards(int const dealerIndex) {
		assert(dealerIndex >= 0 && dealerIndex <= 3);
		int cardIndex = (dealerIndex + 1) % 4;
		for (int i = cardIndex; i <= cardIndex + 2; i += 2) {
			for (int numCards = 0; numCards < 3; numCards++) {
				playerVector[i % 4]->add_card(deck.deal_one());
			}
			for (int numCards = 0; numCards < 2; numCards++) {
				playerVector[(i + 1) % 4]->add_card(deck.deal_one());
			}
		}
		for (int i = cardIndex; i <= cardIndex + 2; i += 2) {
			for (int numCards = 0; numCards < 2; numCards++) {
				playerVector[i % 4]->add_card(deck.deal_one());
			}
			for (int numCards = 0; numCards < 3; numCards++) {
				playerVector[(i + 1) % 4]->add_card(deck.deal_one());
			}
		}
		upcard = deck.deal_one();

		cout << "Hand " << numHand << endl;
		cout << *playerVector[dealerIndex] << " deals" << endl;
		cout << upcard << " turned up" << endl;
	}

	// REQUIRES dealIndex to be between 0 and 3
	// MODIFIES teamOrderUp, orderUpSuit
	// EFFECTS Exectue rounds one and two of trump making process until
	// a player orders up a trump suit and then return that value 
	// as well as modify the teamOrder Up
	string make_trump_rounds(int const dealerIndex, Card const upcard, int &teamOrderUp) {
		assert(dealerIndex >= 0 && dealerIndex <= 3);

		string orderUpSuit = "";
		bool trumpSuitMade = false;

		int trumpIndex = dealerIndex + 1;
		int round = 1;
		bool isDealer = false;
		for (int i = trumpIndex; i <= trumpIndex + 3; ++i) {
			if (i % 4 == dealerIndex) {
				isDealer = true;
			}
			trumpSuitMade = playerVector[i % 4]->make_trump(upcard, isDealer, round, orderUpSuit);
			if (trumpSuitMade) {
				cout << *playerVector[i % 4] << " orders up " << orderUpSuit << endl;
				teamOrderUp = i % 2;
				playerVector[dealerIndex]->add_and_discard(upcard);
				cout << endl;
				return orderUpSuit;
			}
			else {
				cout << *playerVector[i % 4] << " passes" << endl;
			}
		}
		round = 2;
		isDealer = false;
		for (int i = trumpIndex; i <= trumpIndex + 3; ++i) {
			if (i % 4 == dealerIndex) {
				isDealer = true;
			}
			trumpSuitMade = playerVector[i % 4]->make_trump(upcard, isDealer, round, orderUpSuit);
			if (trumpSuitMade) {
				teamOrderUp = i % 2;
				cout << *playerVector[i % 4] << " orders up " << orderUpSuit << endl << endl;
				return orderUpSuit;
			}
			else {
				cout << *playerVector[i % 4] << " passes" << endl;
			}
		}
		return orderUpSuit;
	}

	// REQUIRES dealIndex to be between 0 and 3, trump is a valid suit
	// EFFECTS Executes five tricks and returns the number of tricks team 0 wins.
	int make_five_tricks(int dealerIndex, string trump) {
		assert(dealerIndex >= 0 && dealerIndex <= 3);
		assert(trump == "Diamonds" || trump == "Hearts" ||
			   trump == "Clubs" || trump == "Spades");

		const int NUM_TRICKS = 5;
		int team0TricksWon = 0;
		int leadPlayerIndex = dealerIndex + 1;

		for (int i = 0; i < NUM_TRICKS; ++i) {
			Card led_card = playerVector[leadPlayerIndex % 4]->lead_card(trump);
			cout << led_card << " led by " 
				 << *playerVector[leadPlayerIndex % 4] << endl;
			Card play1_card = 
				playerVector[(leadPlayerIndex + 1) % 4]->play_card(led_card, trump);
			cout << play1_card << " played by " 
				 << *playerVector[(leadPlayerIndex + 1) % 4] << endl;
			Card play2_card = 
				playerVector[(leadPlayerIndex + 2) % 4]->play_card(led_card, trump);
			cout << play2_card << " played by "
				<< *playerVector[(leadPlayerIndex + 2) % 4] << endl;
			Card play3_card =
				playerVector[(leadPlayerIndex + 3) % 4]->play_card(led_card, trump);
			cout << play3_card << " played by "
				<< *playerVector[(leadPlayerIndex + 3) % 4] << endl;

			Card winningCard = led_card;
			int winnerIndex = leadPlayerIndex % 4;
			if (Card_less(led_card, play1_card, led_card, trump)) {
				winningCard = play1_card;
				winnerIndex = (leadPlayerIndex + 1) % 4;
			}
			if (Card_less(winningCard, play2_card, led_card, trump)) {
				winningCard = play2_card;
				winnerIndex = (leadPlayerIndex + 2) % 4;
			}
			if (Card_less(winningCard, play3_card, led_card, trump)) {
				winningCard = play3_card;
				winnerIndex = (leadPlayerIndex + 3) % 4;
			}

			if (winnerIndex % 2 == 0) {
				team0TricksWon++;
			}
			leadPlayerIndex = winnerIndex;
			cout << *playerVector[leadPlayerIndex] 
				 << " takes the trick" << endl << endl;
		}
		return team0TricksWon;
	}

// REQUIRES team0TricksWon is between 0 and 5, teamOrderUp is either 0 or 1
// MOFIDIES teamScore0, teamScore1
// EFFECTS Updates both team scores based on 
// the number of tricks won and the team that ordered up
	void update_score(int teamOrderUp, int team0TricksWon) {
		assert(team0TricksWon >= 0 && team0TricksWon <= 5);
		assert(teamOrderUp == 0 || teamOrderUp == 1);
		if (teamOrderUp == 0) {
			if (team0TricksWon == 3 || team0TricksWon == 4) {
				team0Score++;
				cout << *playerVector[0] << " and " << *playerVector[2] 
					 << " win the hand" << endl;
			}
			else if (team0TricksWon == 5) {
				team0Score += 2;
				cout << *playerVector[0] << " and " << *playerVector[2]
					 << " win the hand" << endl;
				cout << "march!" << endl;
			}
			else {
				team1Score += 2;
				cout << *playerVector[1] << " and " << *playerVector[3]
					 << " win the hand" << endl;
				cout << "euchred!" << endl;
			}
		}
		else if (teamOrderUp == 1) {
			if (team0TricksWon == 1 || team0TricksWon == 2) {
				team1Score++;
				cout << *playerVector[1] << " and " << *playerVector[3]
					 << " win the hand" << endl;
			}
			else if (team0TricksWon == 0) {
				team1Score += 2;
				cout << *playerVector[1] << " and " << *playerVector[3]
					 << " win the hand" << endl;
				cout << "march!" << endl;
			}
			else {
				team0Score += 2;
				cout << *playerVector[0] << " and " << *playerVector[2]
					 << " win the hand" << endl;
				cout << "euchred!" << endl;
			}
		}
		cout << *playerVector[0] << " and " << *playerVector[2]
			 << " have " << team0Score << " points" << endl;
		cout << *playerVector[1] << " and " << *playerVector[3]
			<< " have " << team1Score << " points" << endl << endl;
	}


// EFFECTS Executes a round of euchre
	void execute_game() {
		while (team0Score < winningScore && team1Score < winningScore) {
			if (shuffleType == "shuffle") {
				deck.shuffle();
			}
			else {
				deck.reset();
			}
			deal_cards(dealerIndex);
			int teamOrderUp = 0;
			string orderUpSuit = make_trump_rounds(dealerIndex, upcard, teamOrderUp);
			int team0TricksWon = make_five_tricks(dealerIndex, orderUpSuit);
			update_score(teamOrderUp, team0TricksWon);
			dealerIndex = (dealerIndex + 1) % 4;
			numHand++;
		}
		if (team0Score >= winningScore) {
			cout << *playerVector[0] << " and " << *playerVector[2] << " win!" << endl;
		}
		if (team1Score >= winningScore) {
			cout << *playerVector[1] << " and " << *playerVector[3] << " win!" << endl;
		}
		for (int i = 0; i < int(playerVector.size()); ++i) {
			delete playerVector[i];
		}
	}

private:
	vector<Player*> playerVector;
	Pack deck;
	int team0Score;
	int team1Score;
	int winningScore;
	string shuffleType;
	int dealerIndex;
	int numHand;
	Card upcard;
};

int main(int argc, char* argv[]) {
	check_errors_and_print_args(argc, argv);
	Game game = Game(argc, argv);
	game.execute_game();
	return 0;
}

// MODIFIES cout
// EFFECTS Prints out the error statement
void print_error_statement() {
	cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
		<< "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
		<< "NAME4 TYPE4" << endl;
}

// MODIFIES cout
// EFFECTS Prints out the command line arguments and the error statement 
//if there is any errors in input and 
void check_errors_and_print_args(int argc, char* argv[]) {
	if (argc != 12) {
		print_error_statement();
	}
	if (atoi(argv[3]) < 1 || atoi(argv[3]) > 100) {
		print_error_statement();
	}
	string shuffleType = argv[2];
	if (shuffleType != "shuffle" && shuffleType != "noshuffle") {
		print_error_statement();
	}
	string playerType = argv[5];
	for (int i = 5; i < argc; i += 2) {
		playerType = argv[i];
		if (playerType != "Simple" && playerType != "Human") {
			print_error_statement();
		}
	}
	for (int i = 0; i < argc; ++i) {
		cout << argv[i] << " ";
	}
	cout << endl;
}