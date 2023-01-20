// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Pack.h"

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack() {
    int i = 0;
    for (int suit = 0; suit < NUM_SUITS; suit++) {
        for (int rank = 7; rank < NUM_RANKS; rank++) {
            Card c(RANK_NAMES_BY_WEIGHT[rank], SUIT_NAMES_BY_WEIGHT[suit]);
            cards[i] = c;
            i++;
        }
    }
    next = 0;
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input) {
    // change the custom working directory
    std::string rank;
    std::string junk;
    std::string suit;
    for (int i = 0; i < PACK_SIZE; i++) {
        pack_input >> rank;
        pack_input >> junk;
        pack_input >> suit;
        Card c(rank, suit);
        cards[i] = c;
    }
    next = 0;
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
    next++;
    return cards[next - 1];
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
    next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() {
    std::array<Card, PACK_SIZE / 2> first;
    std::array<Card, PACK_SIZE / 2> second;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < PACK_SIZE / 2; j++) {
            first[j] = cards[j];
            }
        int num = 0;
        for (int last = PACK_SIZE / 2; last < PACK_SIZE; last++) {
            second[num] = cards[last];
            num++;
        }
        int fir = 0;
        int sec = 0;
        for (int all = 0; all < PACK_SIZE; all++) {
            if (all % 2 == 0) {
                cards[all] = second[sec];
                sec++;
            }
            else {
                cards[all] = first[fir];
                fir++;
            }
        }
    }
    reset();
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {
    if (next == PACK_SIZE) {
        return true;
    }
    else {
        return false;
    }
}
