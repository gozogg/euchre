// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
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

//EFFECTS Initializes Card to the Two of Spades
Card::Card() {
    rank = RANK_TWO;
    suit = SUIT_SPADES;
}

//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
//EFFECTS Initializes Card to specified rank and suit
Card::Card(const std::string &rank_in, const std::string &suit_in) {
    rank = rank_in;
    suit = suit_in;
}

//EFFECTS Returns the rank
std::string Card::get_rank() const {
    return rank;
}


//EFFECTS Returns the suit.  Does not consider trump.
std::string Card::get_suit() const {
    return suit;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
std::string Card::get_suit(const std::string &trump) const {
    if (trump == SUIT_SPADES) {
        if (rank == RANK_JACK && suit == SUIT_CLUBS) {
            return SUIT_SPADES;
        }
        else {
            return get_suit();
        }
    }
    else if (trump == SUIT_CLUBS) {
        if (rank == RANK_JACK && suit == SUIT_SPADES) {
            return SUIT_CLUBS;
        }
        else {
            return get_suit();
        }
    }
    else if (trump == SUIT_HEARTS) {
        if (rank == RANK_JACK && suit == SUIT_DIAMONDS) {
            return SUIT_HEARTS;
        }
        else {
            return get_suit();
        }
    }
    else {
        if (rank == RANK_JACK && suit == SUIT_HEARTS) {
            return SUIT_DIAMONDS;
        }
        else {
            return get_suit();
        }
    }
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face_or_ace() const {
    if (rank == RANK_JACK || rank == RANK_QUEEN
        || rank == RANK_KING || rank == RANK_ACE) {
        return true;
    }
    else {
        return false;
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const std::string &trump) const {
    if (suit == trump) {
        if (rank == RANK_JACK) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const std::string &trump) const {
    if (get_rank() == Card::RANK_JACK) {
        std::string new_suit = get_suit();
        if (new_suit == trump) {
            return false;
        }
        else {
            return true;
        }
    }
    else {
        return false;
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const std::string &trump) const {
    if (get_suit(trump) == trump) {
        return true;
    }
    else {
        return false;
    }
}
//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs) {
    int lh = 0;
    int rh = 0;
    for (int i = 0; i < NUM_RANKS; i++) {
        if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            lh = i;
        }
        if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            rh = i;
        }
    }
    if (lh < rh) {
        return true;
    }
    else if (rh < lh) {
        return false;
    }
    else {
        for (int i = 0; i < NUM_SUITS; i++) {
            if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                lh = i;
            }
            if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                rh = i;
            }
        }
    }
    if (lh < rh) {
        return true;
    }
    else {
        return false;
    }
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs) {
    return lhs < rhs || lhs == rhs;
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs) {
    int lh = 0;
    int rh = 0;
    for (int i = 0; i < NUM_RANKS; i++) {
        if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            lh = i;
        }
        if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            rh = i;
        }
    }
    if (lh > rh) {
        return true;
    }
    else if (rh > lh) {
        return false;
    }
    else {
        for (int i = 0; i < NUM_SUITS; i++) {
            if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                lh = i;
            }
            if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                rh = i;
            }
        }
    }
    if (lh > rh) {
        return true;
    }
    else {
        return false;
    }
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs) {
    return lhs > rhs || lhs == rhs;
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs) {
    if (lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit()) {
        return true;
    }
    else {
        return false;
    }
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs) {
    return !(lhs == rhs);
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit) {
    if (suit == Card::SUIT_SPADES) {
        return Card::SUIT_CLUBS;
    }
    else if (suit == Card::SUIT_CLUBS) {
        return Card::SUIT_SPADES;
    }
    else if (suit == Card::SUIT_DIAMONDS) {
        return Card::SUIT_HEARTS;
    }
    else {
        return Card::SUIT_DIAMONDS;
    }
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump) {
    if ((b.get_suit(trump) == trump) && (a.get_suit(trump) != trump)) {
        return true;
    }
    else if ((b.get_suit(trump) != trump) && (a.get_suit(trump) == trump)) {
        return false;
    }
    else if ((b.get_suit(trump) != trump) && (a.get_suit(trump) != trump)) {
        if (a < b) {
            return true;
        }
        else if (a > b) {
            return false;
        }
    }
    else if ((b.get_suit(trump) == trump) && (a.get_suit(trump) == trump)) {
        if (b.get_suit() == a.get_suit() && ((!a.is_right_bower(trump))
                                             && !b.is_right_bower(trump))) {
            if (b > a) {
                return true;
            }
            else {
                return false;
            }
        }
        else if (b.get_suit() == a.get_suit() &&
                 (b.is_right_bower(trump) || a.is_right_bower(trump))) {
            if (b.is_right_bower(trump)) {
                return true;
            }
            else if (a.is_right_bower(trump)) {
                return false;
            }
        }
        else if (b.get_suit() == Suit_next(trump)) {
            if (a.get_rank() != Card::RANK_JACK) {
                return true;
            }
            else {
                return false;
            }
        }
        else if (a.get_suit() == Suit_next(trump)) {
            if (b.get_rank() != Card::RANK_JACK) {
                return false;
            }
            else {
                return true;
            }
        }
    }
    return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump) {
    if ((a.get_suit(trump) != led_card.get_suit(trump)) && (b.get_suit(trump)
                                            != led_card.get_suit(trump))) {
        return Card_less(a, b, trump);
    }
    else if ((a.get_suit(trump) != led_card.get_suit(trump)) &&
             (b.get_suit(trump) == led_card.get_suit(trump))) {
        if (a.get_suit(trump) == trump) {
            return false;
        }
        else {
            return true;
        }
    }
    else if ((a.get_suit(trump) == led_card.get_suit(trump)) &&
             (b.get_suit(trump) != led_card.get_suit(trump))) {
        if (b.get_suit(trump) == trump) {
            return true;
        }
        else {
            return false;
        }
    }
    else if ((a.get_suit(trump) == led_card.get_suit(trump)) &&
             (b.get_suit(trump) == led_card.get_suit(trump))) {
        return Card_less(a, b, trump);
    }
    return false;
}




// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=
