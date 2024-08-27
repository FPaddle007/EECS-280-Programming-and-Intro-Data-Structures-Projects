// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;

TEST(test_card_ctor)
{
    Card twoSpades;
    ASSERT_EQUAL(Card::RANK_TWO, twoSpades.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, twoSpades.get_suit());

    Card aceHeart(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, aceHeart.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, aceHeart.get_suit());
}

TEST(test_get_functions)
{
    Card ace(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card nine(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card rightBower(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card leftBower(Card::RANK_JACK, Card::SUIT_SPADES);
    std::string trump = "Clubs";

    ASSERT_EQUAL(ace.get_rank(), "Ace");
    ASSERT_EQUAL(leftBower.get_rank(), "Jack");

    ASSERT_EQUAL(leftBower.get_suit(), "Spades");
    ASSERT_EQUAL(leftBower.get_suit(trump), "Clubs");
    ASSERT_EQUAL(ace.get_suit(), "Hearts");
}

TEST(test_is_functions)
{
    Card ace(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card nine(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card rightBower(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card leftBower(Card::RANK_JACK, Card::SUIT_SPADES);
    std::string trump = "Clubs";

    ASSERT_TRUE(ace.is_face());
    ASSERT_FALSE(nine.is_face());

    ASSERT_TRUE(rightBower.is_right_bower(trump));
    ASSERT_FALSE(leftBower.is_right_bower(trump));

    ASSERT_FALSE(rightBower.is_left_bower(trump));
    ASSERT_TRUE(leftBower.is_left_bower(trump));

    ASSERT_TRUE(rightBower.is_trump(trump));
    ASSERT_TRUE(leftBower.is_trump(trump));
    ASSERT_TRUE(nine.is_trump(trump));
    ASSERT_FALSE(ace.is_trump(trump));
}

TEST(test_suit_next)
{
    ASSERT_EQUAL("Hearts", Suit_next("Diamonds"));
    ASSERT_EQUAL("Diamonds", Suit_next("Hearts"));
    ASSERT_EQUAL("Spades", Suit_next("Clubs"));
    ASSERT_EQUAL("Clubs", Suit_next("Spades"));
}

TEST(test_operators)
{
    Card threeSpades(Card::RANK_THREE, Card::SUIT_SPADES);
    Card fiveSpades(Card::RANK_FIVE, Card::SUIT_SPADES);
    Card threeHearts(Card::RANK_THREE, Card::SUIT_HEARTS);

    ASSERT_FALSE(threeSpades < threeSpades);
    ASSERT_TRUE(threeSpades <= threeSpades);
    ASSERT_FALSE(threeSpades > threeSpades);
    ASSERT_TRUE(threeSpades >= threeSpades);
    ASSERT_TRUE(threeSpades == threeSpades);
    ASSERT_FALSE(threeSpades != threeSpades);

    ASSERT_FALSE(fiveSpades < threeSpades);
    ASSERT_TRUE(threeSpades < fiveSpades);
    ASSERT_FALSE(fiveSpades <= threeSpades);
    ASSERT_TRUE(threeSpades <= fiveSpades);
    ASSERT_FALSE(threeSpades > fiveSpades);
    ASSERT_TRUE(fiveSpades > threeSpades);
    ASSERT_FALSE(threeSpades > fiveSpades);
    ASSERT_TRUE(fiveSpades > threeSpades);
    ASSERT_FALSE(threeSpades == fiveSpades);
    ASSERT_TRUE(threeSpades != fiveSpades);

    ASSERT_FALSE(threeHearts < threeSpades);
    ASSERT_TRUE(threeSpades < threeHearts);
    ASSERT_FALSE(threeHearts <= threeSpades);
    ASSERT_TRUE(threeSpades <= threeHearts);
    ASSERT_FALSE(threeSpades > threeHearts);
    ASSERT_TRUE(threeHearts > threeSpades);
    ASSERT_FALSE(threeSpades > threeHearts);
    ASSERT_TRUE(threeHearts > threeSpades);
    ASSERT_FALSE(threeSpades == threeHearts);
    ASSERT_TRUE(threeSpades != threeHearts);

    ostringstream oss;
    oss << threeSpades;
    ASSERT_EQUAL(oss.str(), "Three of Spades");
}

TEST(test_card_less)
{
    Card aceHearts(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card nineHearts(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card rightBower(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card leftBower(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card kingTrump(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card queenTrump(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card tenLed(Card::RANK_TEN, Card::SUIT_SPADES);
    Card jackLed(Card::RANK_JACK, Card::SUIT_SPADES);

    Card led_card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    std::string trump = "Diamonds";

    ASSERT_FALSE(Card_less(rightBower, leftBower, trump));
    ASSERT_TRUE(Card_less(leftBower, rightBower, trump));
    ASSERT_FALSE(Card_less(leftBower, kingTrump, trump));
    ASSERT_TRUE(Card_less(kingTrump, leftBower, trump));
    ASSERT_TRUE(Card_less(queenTrump, kingTrump, trump));
    ASSERT_FALSE(Card_less(kingTrump, queenTrump, trump));

    ASSERT_FALSE(Card_less(kingTrump, aceHearts, trump));
    ASSERT_TRUE(Card_less(aceHearts, kingTrump, trump));

    ASSERT_TRUE(Card_less(tenLed, jackLed, led_card, trump));
    ASSERT_FALSE(Card_less(jackLed, tenLed, led_card, trump));

    ASSERT_FALSE(Card_less(jackLed, aceHearts, led_card, trump));
    ASSERT_TRUE(Card_less(aceHearts, jackLed, led_card, trump));

    ASSERT_FALSE(Card_less(aceHearts, nineHearts, trump));
    ASSERT_TRUE(Card_less(nineHearts, aceHearts, trump));
}

TEST_MAIN()