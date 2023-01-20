// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "Card.h"
#include <sstream>
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}
TEST(test_player_get_name_edge) {
    Player * alice = Player_factory("", "Simple");
    ASSERT_EQUAL("", alice->get_name());

    delete alice;
}
TEST(test_simple_player_lead_card_edge) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card jack_diamonds(Card::RANK_JACK, Card::SUIT_DIAMONDS);
  ASSERT_EQUAL(card_led, jack_diamonds); //check led card

  delete bob;
}
TEST(test_simple_player_lead_card_edge4) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
  );
    

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_led, jack_hearts); //check led card

  delete bob;
}
TEST(test_simple_player_lead_card_edge5) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card queen_clubs(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    ASSERT_EQUAL(card_led, queen_clubs); //check led card

  delete bob;
}
TEST(test_simple_player_lead_card_edge2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card ace_clubs(Card::RANK_ACE, Card::SUIT_CLUBS);
  ASSERT_EQUAL(card_led, ace_clubs); //check led card

  delete bob;
}
TEST(test_simple_player_play_card_edge) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
  );

  // Bob leads
    Card led_card(Card::RANK_ACE, Card::SUIT_CLUBS);
  Card play_card = bob->play_card(led_card, Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card ten_hearts(Card::RANK_TEN, Card::SUIT_HEARTS);
  ASSERT_EQUAL(play_card, ten_hearts); //check led card

  delete bob;
}
TEST(test_simple_player_play_card_edge2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
  );

  // Bob leads
    Card led_card(Card::RANK_JACK, Card::SUIT_HEARTS);
  Card play_card = bob->play_card(led_card, Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card jack_diamonds(Card::RANK_JACK, Card::SUIT_DIAMONDS);
  ASSERT_EQUAL(play_card, jack_diamonds); //check led card

  delete bob;
}
TEST(test_simple_player_play_card_edge3) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
  );

  // Bob leads
    Card led_card(Card::RANK_JACK, Card::SUIT_SPADES);
  Card play_card = bob->play_card(led_card, Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card queen_spades(Card::RANK_QUEEN, Card::SUIT_SPADES);
  ASSERT_EQUAL(play_card, queen_spades); //check led card

  delete bob;
}
TEST(test_simple_player_play_card_edge5) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
  );

  // Bob leads
    Card led_card(Card::RANK_JACK, Card::SUIT_SPADES);
  Card play_card = bob->play_card(led_card, Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card queen_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
  ASSERT_EQUAL(play_card, queen_diamonds); //check led card

  delete bob;
}
TEST(test_simple_player_play_card_edge4) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
  );

  // Bob leads
    Card led_card(Card::RANK_JACK, Card::SUIT_SPADES);
  Card play_card = bob->play_card(led_card, Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card queen_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
  ASSERT_EQUAL(play_card, queen_diamonds); //check led card

  delete bob;
}



TEST(test_simple_player_make_trump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob makes tump
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
}

TEST(test_simple_player_lead_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob adds a card to his hand and discards one card
    bob->add_and_discard(
      Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
    );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete bob;
}

TEST(test_simple_player_play_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(nine_diamonds, "Hearts"        // Trump suit
  );

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_SPADES));
    
    Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card card_played_2 = bob ->play_card(nine_hearts, "Hearts");
    
    ASSERT_EQUAL(card_played_2, Card(Card::RANK_TEN, Card::SUIT_SPADES));
    
  delete bob;
}
TEST (test_simple_player_make_trump_all) {
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    
    Card upcard(Card::RANK_JACK, Card::SUIT_SPADES);
    string trump;
    ASSERT_FALSE(bob->make_trump(upcard, false, 1, trump));
    ASSERT_FALSE(bob->make_trump(upcard, false, 2, trump));
    ASSERT_TRUE(bob->make_trump(upcard, true, 2, trump));
    ASSERT_FALSE(bob->make_trump(upcard, true, 1, trump));
    
    Card card(Card::RANK_NINE, Card::SUIT_HEARTS);
    ASSERT_TRUE(bob->make_trump(card, false, 1, trump));
    ASSERT_TRUE(bob->make_trump(card, false, 2, trump));
    
    delete bob;
}
TEST (test_simple_player_make_trump_bowers) {
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    
    Card upcard(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    string trump;
    ASSERT_TRUE(bob->make_trump(upcard, false, 1, trump));
    ASSERT_TRUE(bob->make_trump(upcard, false, 2, trump));
    ASSERT_TRUE(bob->make_trump(upcard, true, 2, trump));
    ASSERT_TRUE(bob->make_trump(upcard, true, 1, trump));
    
    delete bob;
}
TEST (test_simple_player_make_trump_farmers) {
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    
    Card upcard(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    string trump;
    ASSERT_FALSE(bob->make_trump(upcard, false, 1, trump));
    ASSERT_FALSE(bob->make_trump(upcard, false, 2, trump));
    ASSERT_TRUE(bob->make_trump(upcard, true, 2, trump));
    ASSERT_FALSE(bob->make_trump(upcard, true, 1, trump));
    
    delete bob;
}
TEST (test_simple_player_lead_farmers) {
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    
    
    Card card_led = bob->lead_card(Card::SUIT_HEARTS);

    Card ten_diamonds(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(card_led, ten_diamonds); //check led card
    
    Card card_led_twice = bob->lead_card(Card::SUIT_HEARTS);
    Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(card_led_twice, nine_diamonds);
    
    Card card_led_three = bob->lead_card(Card::SUIT_HEARTS);
    Card nine_clubs(Card::RANK_NINE, Card::SUIT_CLUBS);
    ASSERT_EQUAL(card_led_three, nine_clubs);
    
    Card card_led_four = bob->lead_card(Card::SUIT_HEARTS);
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led_four, nine_spades);
    
    Card card_led_five = bob->lead_card(Card::SUIT_HEARTS);
    Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(card_led_five, nine_hearts);
    
    delete bob;
}


// Add more tests here

TEST_MAIN()
