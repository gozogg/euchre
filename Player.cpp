// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include "Player.h"


class SimplePlayer : public Player {
private:
    std::string player_name;
    std::vector<Card> hand;
public:
    SimplePlayer(std::string name) : Player() {
        player_name = name;
    }
//EFFECTS returns player's name
    const std::string & get_name() const {
        return player_name;
    }

//REQUIRES player has less than MAX_HAND_SIZE cards
//EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) {
        assert(hand.size() < MAX_HAND_SIZE);
        hand.push_back(c);
    }

//REQUIRES round is 1 or 2
//MODIFIES order_up_suit
//EFFECTS If Player wishes to order up a trump suit then return true and
//  change order_up_suit to desired suit.  If Player wishes to pass, then do
//  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, std::string &order_up_suit) const {
        int count = 0;
        if (round == 1) {
            for(int i = 0; i < MAX_HAND_SIZE; i++) {
                if (hand[i].get_suit(upcard.get_suit()) ==
                    upcard.get_suit() && hand[i].is_face_or_ace()) {
                    count++;
                }
            }
            if (count >= 2) {
                order_up_suit = upcard.get_suit();
                return true;
            }
            else {
                return false;
            }
        }
        if (round == 2) {
            if (is_dealer) {
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
            }
            for (int i = 0; i < MAX_HAND_SIZE; i++) {
                if (hand[i].get_suit(Suit_next(upcard.get_suit())) ==
                    Suit_next(upcard.get_suit()) &&
                    hand[i].is_face_or_ace()) {
                    count++;
                }
            }
            if (count >= 1) {
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
            }
            else {
                return false;
            }
        }
        return false;
    }

//REQUIRES Player has at least one card
//EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) {
         hand.push_back(upcard);
        int count = 0;
        int num = 0;
        Card min;
        for (int i = 0; i < MAX_HAND_SIZE + 1; i++) {
            if (hand[i].get_suit(upcard.get_suit()) != upcard.get_suit()) {
                min = hand[i];
                num = i;
                count++;
            }
        }
        if (count == 0) {
            min = hand[0];
            for (int i = 1; i < MAX_HAND_SIZE + 1; i++) {
                if (hand[i] < min) {
                    min = hand[i];
                    num = i;
                }
            }
        }
        else {
            for (int i = 0; i < MAX_HAND_SIZE + 1; i++) {
                if ((hand[i].get_suit(upcard.get_suit()) != upcard.get_suit())
                    && (Card_less(hand[i], min, upcard.get_suit()))) {
                    min = hand[i];
                    num = i;
                }
            }
        }
        hand.erase(hand.begin() + num);
    }

//REQUIRES Player has at least one card, trump is a valid suit
//EFFECTS  Leads one Card from Player's hand according to their strategy
//  "Lead" means to play the first Card in a trick.  The card
//  is removed the player's hand.
    Card lead_card(const std::string &trump) {
        Card max;
        int non_trump = 0;
        for (size_t i = 0; i < hand.size(); i++) {
            if (!hand[i].is_trump(trump)) {
                max = hand[i];
                non_trump++;
            }
        }
        if (non_trump > 0) {
            int num = 0;
            for (size_t i = 0; i < hand.size(); i++) {
                if ((!hand[i].is_trump(trump)) &&
                    (!Card_less(hand[i], max, trump))) {
                    max = hand[i];
                    num = static_cast<int>(i);
                }
            }
            Card lead = hand[num];
            hand.erase(hand.begin() + num);
            return lead;
        }
        else {
            int num = 0;
            Card max = hand[0];
            for (size_t i = 1; i < hand.size(); i++) {
                if (!Card_less(hand[i], max, trump)) {
                    max = hand[i];
                    num = static_cast<int>(i);
                }
            }
            Card lead = hand[num];
            hand.erase(hand.begin() + num);
            return lead;
        }
    }

//REQUIRES Player has at least one card, trump is a valid suit
//EFFECTS  Plays one Card from Player's hand according to their strategy.
//  The card is removed from the player's hand.
    Card play_card(const Card &led_card, const std::string &trump) {
        Card max;
        int num = 0;
        int follows = 0;
        for (size_t i = 0; i < hand.size(); i++) {
            if (hand[i].get_suit(trump) == led_card.get_suit(trump)) {
                max = hand[i];
                num = static_cast<int>(i);
                follows++;
            }
        }
        if (follows >= 1) {
            for (size_t i = 0; i < hand.size(); i++) {
                if ((hand[i].get_suit(trump) == led_card.get_suit(trump)) &&
                    (!Card_less(hand[i], max, led_card, trump))) {
                    max = hand[i];
                    num = static_cast<int>(i);
                }
            }
            Card a = max;
            hand.erase(hand.begin() + num);
            return max;
        }
        else {
            int num = 0;
            Card min = hand[0];
            for (size_t i = 0; i < hand.size(); i++) {
                if (Card_less(hand[i], min, led_card, trump)) {
                    min = hand[i];
                    num = static_cast<int>(i);
                }
            }
            Card a = min;
            hand.erase(hand.begin() + num);
            return min;
        }
    }

// Maximum number of cards in a player's hand
static const int MAX_HAND_SIZE = 5;

};

class HumanPlayer : public Player {
private:
    std::string player_name;
    std::vector<Card> hand;
public:
    HumanPlayer(std::string name) : Player() {
        player_name = name;
    }
//EFFECTS returns player's name
    const std::string & get_name() const {
        return player_name;
    }

//REQUIRES player has less than MAX_HAND_SIZE cards
//EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) {
        assert(hand.size() < MAX_HAND_SIZE);
        hand.push_back(c);
        std::sort(hand.begin(), hand.end());
    }

//REQUIRES round is 1 or 2
//MODIFIES order_up_suit
//EFFECTS If Player wishes to order up a trump suit then return true and
//  change order_up_suit to desired suit.  If Player wishes to pass, then do
//  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, std::string &order_up_suit) const {
        print_hand();
        
        std::string output;
        std::cout << "Human player " << get_name() <<
        ", please enter a suit, or \"pass\":\n";
        std::cin >> output;
        if (output == "pass") {
            return false;
        }
        else {
            order_up_suit = output;
            return true;
        }
    }

//REQUIRES Player has at least one card
//EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) {
        print_hand();
        int index;
        std::cout << "Discard upcard: [-1]\n";
        std::cout << "Human player " << get_name() <<
        ", please select a card to discard:\n";
        std::cin >> index;
        if (index == -1) {
            return;
        }
        else {
            hand.push_back(upcard);
            hand.erase(hand.begin() + index);
            std::sort(hand.begin(), hand.end());
        }
    }

//REQUIRES Player has at least one card, trump is a valid suit
//EFFECTS  Leads one Card from Player's hand according to their strategy
//  "Lead" means to play the first Card in a trick.  The card
//  is removed the player's hand.
    Card lead_card(const std::string &trump) {
        int index;
        print_hand();
        std::cout << "Human player " << get_name() <<
        ", please select a card:\n";
        std::cin >> index;
        Card lead = hand[index];
        hand.erase(hand.begin() + index);
        return lead;
    }

//REQUIRES Player has at least one card, trump is a valid suit
//EFFECTS  Plays one Card from Player's hand according to their strategy.
//  The card is removed from the player's hand.
    Card play_card(const Card &led_card, const std::string &trump) {
        int index;
        print_hand();
        std::cout << "Human player " << get_name() <<
        ", please select a card:\n";
        std::cin >> index;
        Card play = hand[index];
        hand.erase(hand.begin() + index);
        return play;
    }
    
    void print_hand() const{
        std::vector<Card> copy_hand;
        for (size_t i = 0; i < hand.size(); i++) {
            copy_hand.push_back(hand[i]);
        }
        std::sort(copy_hand.begin(), copy_hand.end());
        for (size_t i = 0; i < hand.size(); i++) {
            std::cout << "Human player " << get_name() << "'s hand: "
            << "[" << i << "] " << copy_hand[i] << "\n";
        }
    }

// Maximum number of cards in a player's hand
static const int MAX_HAND_SIZE = 5;


};
//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy) {
    if (strategy == "Simple") {
        return new SimplePlayer(name);
    }
    else if (strategy == "Human") {
        return new HumanPlayer(name);
    }
    
    assert(false);
    return nullptr;
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p) {
    os << p.get_name();
    return os;
}

