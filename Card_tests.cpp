// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}
TEST(test_def_ctor) {
    Card c;
    ASSERT_EQUAL(Card::RANK_TWO, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, c.get_suit());
    ASSERT_FALSE(c.is_face_or_ace());
    ASSERT_FALSE(c.is_right_bower("Spades"));
    ASSERT_FALSE(c.is_left_bower("Spades"));
    ASSERT_TRUE(c.is_trump("Spades"));
    ASSERT_FALSE(c.is_trump("Hearts"));
}
TEST(test_LBR) {
    Card t(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(t.get_suit("Clubs"), Card::SUIT_CLUBS);
    ASSERT_TRUE(t.is_face_or_ace());
    ASSERT_TRUE(t.is_left_bower("Clubs"));
    ASSERT_TRUE(t.is_trump("Clubs"));
    ASSERT_EQUAL(Suit_next("Clubs"), Card::SUIT_SPADES);
}
TEST(test_RBR) {
    Card t(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(t.get_suit("Spades"), Card::SUIT_SPADES);
    ASSERT_TRUE(t.is_face_or_ace());
    ASSERT_FALSE(t.is_left_bower("Spades"));
    ASSERT_TRUE(t.is_right_bower("Spades"));
    ASSERT_TRUE(t.is_trump("Spades"));
}
TEST(card_less_edge) {
    Card a(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card b(Card::RANK_KING, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(Card_less(a, b, "Clubs"));
    ASSERT_TRUE(Card_less(a, b, "Spades"));
    ASSERT_FALSE(Card_less(a, b, "Diamonds"));
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(Card_less(a, b, c, "Diamonds"));
}
TEST(Suit_next) {
    ASSERT_EQUAL(Suit_next("Clubs"), Card::SUIT_SPADES);
    ASSERT_EQUAL(Suit_next("Hearts"), Card::SUIT_DIAMONDS);
}
TEST(test_operator) {
    Card a(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card b(Card::RANK_KING, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(a < b);
    ASSERT_TRUE(a <= b);
    ASSERT_FALSE(a > b);
    ASSERT_FALSE(a >= b);
    ASSERT_FALSE(a == b);
    ASSERT_TRUE(a != b);
    
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card d(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(c < d);
    ASSERT_TRUE(c <= d);
    ASSERT_FALSE(c > d);
    ASSERT_FALSE(c >= d);
    ASSERT_FALSE(c == d);
    ASSERT_TRUE(c != d);
    
    Card e(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(e < d);
    ASSERT_TRUE(e <= d);
    ASSERT_FALSE(e > d);
    ASSERT_TRUE(e >= d);
    ASSERT_TRUE(e == d);
    ASSERT_FALSE(e != d);
}

TEST_MAIN()
