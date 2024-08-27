// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"
#include "Card.h"
#include <sstream>

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    delete alice;

    Player* bob = Player_factory("Bob", "Human");
    ASSERT_EQUAL("Bob", bob->get_name());
    delete bob;

    Player* null = Player_factory("", "Simple");
    ASSERT_EQUAL("", null->get_name());
    delete null;
}

TEST(test_player_insertion) {
    Player* human = Player_factory("NotRobot", "Human");
    ostringstream oss1;
    oss1 << *human;
    ASSERT_EQUAL(oss1.str(), "NotRobot");
    delete human;


    Player* alice = Player_factory("Alice", "Simple");
    ostringstream oss2;
    oss2 << *alice;
    ASSERT_EQUAL(oss2.str(), "Alice");
    delete alice;
}

TEST(test_simple_player_make_trump) {
    // 3 trump face R1
    Player* bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));

    Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
    string trump_bob;
    bool orderup_bob = bob->make_trump(jack_spades, true, 1, trump_bob);
    ASSERT_TRUE(orderup_bob);
    ASSERT_EQUAL(trump_bob, Card::SUIT_SPADES);

    delete bob;

    // 1 trump face R1 and 1 trump face R2
    Player* alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

    Card jack_diamonds(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    string trump_alice = "";
    bool orderup_alice = alice->make_trump(jack_diamonds, false, 1, trump_alice);
    ASSERT_FALSE(orderup_alice);
    ASSERT_EQUAL(trump_alice, "");
    orderup_alice = alice->make_trump(jack_diamonds, false, 2, trump_alice);
    ASSERT_TRUE(orderup_alice);
    ASSERT_EQUAL(trump_alice, Card::SUIT_HEARTS);

    delete alice;

    // 0 trump face in R1 and R2
    Player* chris = Player_factory("Chris", "Simple");
    chris->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    chris->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    chris->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    chris->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    chris->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));

    Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
    string trump_chris = "";
    bool orderup_chris = chris->make_trump(jack_clubs, false, 1, trump_chris);
    ASSERT_FALSE(orderup_chris);
    ASSERT_EQUAL(trump_chris, "");
    orderup_chris = chris->make_trump(jack_clubs, false, 2, trump_chris);
    ASSERT_FALSE(orderup_chris);
    ASSERT_EQUAL(trump_chris, "");

    delete chris;

    // 0 trump face is R1 & R2 but is dealer
    Player* matt = Player_factory("Matt", "Simple");
    matt->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    matt->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    matt->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    matt->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    matt->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));


    string trump_matt = "";
    bool orderup_matt = matt->make_trump(jack_clubs, true, 1, trump_matt);
    ASSERT_FALSE(orderup_matt);
    ASSERT_EQUAL(trump_matt, "");
    orderup_matt = matt->make_trump(jack_clubs, true, 2, trump_matt);
    ASSERT_TRUE(orderup_matt);
    ASSERT_EQUAL(trump_matt, Card::SUIT_SPADES);

    delete matt;

    // 2 trump face (1 is left bower) in R1
    Player* juett = Player_factory("Juett", "Simple");
    juett->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    juett->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    juett->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    juett->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    juett->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));


    string trump_juett = "";
    bool orderup_juett = juett->make_trump(jack_diamonds, false, 1, trump_juett);
    ASSERT_TRUE(orderup_juett);
    ASSERT_EQUAL(trump_juett, Card::SUIT_DIAMONDS);

    delete juett;

    // Left bower in R1 and Right Bower in R2
    Player* brian = Player_factory("Brian", "Simple");
    brian->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    brian->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    brian->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    brian->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    brian->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));

    string trump_brian = "";
    bool orderup_brian = brian->make_trump(jack_diamonds, false, 1, trump_brian);
    ASSERT_FALSE(orderup_brian);
    ASSERT_EQUAL(trump_brian, "");
    orderup_brian = brian->make_trump(jack_diamonds, false, 2, trump_brian);
    ASSERT_TRUE(orderup_brian);
    ASSERT_EQUAL(trump_brian, Card::SUIT_HEARTS);

    delete brian;
}

TEST(test_simple_player_lead_card) {
    Player* bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));


    Card card_led_1 = bob->lead_card(Card::SUIT_HEARTS);
    Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led_1, ace_spades);

    Card card_led_2 = bob->lead_card(Card::SUIT_HEARTS);
    Card ten_diamonds(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(card_led_2, ten_diamonds);

    Card card_led_3 = bob->lead_card(Card::SUIT_HEARTS);
    Card ten_spades(Card::RANK_TEN, Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led_3, ten_spades);

    Card card_led_4 = bob->lead_card(Card::SUIT_HEARTS);
    Card left_bower(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(card_led_4, left_bower);

    Card card_led_5 = bob->lead_card(Card::SUIT_HEARTS);
    Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    ASSERT_EQUAL(card_led_5, queen_hearts);

    delete bob;
}

TEST(test_add_and_discard) {
    Player* bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    
    Card upcard(Card::RANK_ACE, Card::SUIT_SPADES);
    string trump = upcard.get_suit();
    bob->add_and_discard(upcard);

    Card card_led_1 = bob->lead_card(trump);
    Card right_bower(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led_1, right_bower);

    Card card_led_2 = bob->lead_card(trump);
    Card left_bower(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_EQUAL(card_led_2, left_bower);

    Card card_led_3 = bob->lead_card(trump);
    Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led_3, ace_spades);

    Card card_led_4 = bob->lead_card(trump);
    Card queen_spades(Card::RANK_QUEEN, Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led_4, queen_spades);

    Card card_led_5 = bob->lead_card(trump);
    Card ten_spades(Card::RANK_TEN, Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led_5, ten_spades);

    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));

    Card new_upcard(Card::RANK_NINE, Card::SUIT_SPADES);
    trump = upcard.get_suit();
    bob->add_and_discard(new_upcard);

    Card card_led_6 = bob->lead_card(trump);
    ASSERT_EQUAL(card_led_6, right_bower);

    Card card_led_7 = bob->lead_card(trump);
    ASSERT_EQUAL(card_led_7, left_bower);

    Card card_led_8 = bob->lead_card(trump);
    ASSERT_EQUAL(card_led_8, ace_spades);

    Card card_led_9 = bob->lead_card(trump);
    ASSERT_EQUAL(card_led_9, queen_spades);

    Card card_led_10 = bob->lead_card(trump);
    ASSERT_EQUAL(card_led_10, ten_spades);

    delete bob;
}

TEST(test_simple_player_play_card) 
{
    Player* bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    

    Card upcard(Card::RANK_TEN, Card::SUIT_HEARTS);
    string trump = Card::SUIT_SPADES;

    Card card_played_1 = bob->play_card(upcard, trump);
    ASSERT_EQUAL(card_played_1, Card(Card::RANK_ACE, Card::SUIT_HEARTS));

    Card card_played_2 = bob->play_card(upcard, trump);
    ASSERT_EQUAL(card_played_2, Card(Card::RANK_NINE, Card::SUIT_HEARTS));

    Card card_played_3 = bob->play_card(upcard, trump);
    ASSERT_EQUAL(card_played_3, Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));

    Card card_played_4 = bob->play_card(upcard, trump);
    ASSERT_EQUAL(card_played_4, Card(Card::RANK_KING, Card::SUIT_SPADES));

    Card card_played_5 = bob->play_card(upcard, trump);
    ASSERT_EQUAL(card_played_5, Card(Card::RANK_JACK, Card::SUIT_CLUBS));

    delete bob;
}

TEST_MAIN()
