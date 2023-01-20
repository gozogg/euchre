// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <cassert>
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>
#include <array>
#include "Player.h"
#include "Pack.h"
#include "Card.h"

using namespace std;

class Game {
private:
    int round;
    bool if_shuffle;
    vector<Player*> players;
    Pack pack;
    // team 1 is players 0 and 2
    int t1_scoring;
    // team 2 is players 1 and 3
    int t2_scoring;
    int const MAX_PLAYERS = 4;
    int const MAX_TRICKS = 5;
    int score;
    int dealer;
    int num_hand;
    Player* ordered_up;
    string trump;
    
    void shuffle() {
        if (if_shuffle) {
            pack.shuffle();
        }
        else {
            pack.reset();
        }
    }
    void deal() {
        cout << players[dealer]->get_name() << " deals" << endl;
        int num = 1;
        for (int i = 0; i < MAX_PLAYERS; i++) {
            int next = dealer + num;
            if (next >= MAX_PLAYERS) {
                next = next - MAX_PLAYERS;
            }
            if (((dealer % 2 == 0) && (next % 2 != 0)) ||
                ((dealer % 2 != 0) && (next % 2 == 0))) {
                for (int i = 0; i < 3; i++) {
                    players[next]->add_card(pack.deal_one());
                }
            }
            else if (((dealer % 2 == 0) && (next % 2 == 0)) ||
                     ((dealer % 2 != 0) && (next % 2 != 0))) {
                for (int i = 0; i < 2; i++) {
                    players[next]->add_card(pack.deal_one());
                }
            }
            num++;
        }
        num = 1;
        for (int i = 0; i < MAX_PLAYERS; i++) {
            int next = dealer + num;
            if (next >= MAX_PLAYERS) {
                next = next - MAX_PLAYERS;
            }
            if (((dealer % 2 == 0) && (next % 2 != 0)) ||
                ((dealer % 2 != 0) && (next % 2 == 0))) {
                for (int i = 0; i < 2; i++) {
                    players[next]->add_card(pack.deal_one());
                }
            }
            else if (((dealer % 2 == 0) && (next % 2 == 0)) ||
                     ((dealer % 2 != 0) && (next % 2 != 0))) {
                for (int i = 0; i < 3; i++) {
                    players[next]->add_card(pack.deal_one());
                }
            }
            num++;
        }
    }
    // need to store who made trump
    void make_trump_round_1(Card upcard) {
        int num = 1;
        cout << upcard << " turned up" << endl;
        for (int i = 0; i < MAX_PLAYERS; i++) {
            int next = dealer + num;
            if (next >= MAX_PLAYERS) {
                next = next - MAX_PLAYERS;
            }
            if (next != dealer) {
                if (players[next]->make_trump(upcard, false, 1, trump)){
                    cout << players[next]->get_name() << " orders up "
                    << upcard.get_suit() << endl << endl;
                    players[dealer]->add_and_discard(upcard);
                    ordered_up = players[next];
                    
                    return;
                }
                else {
                    cout << players[next]->get_name() << " passes" << endl;
                }
            }
            else if (next == dealer) {
                if (players[next]->make_trump(upcard, true, 1, trump)){
                    cout << players[next]->get_name() << " orders up "
                    << upcard.get_suit() << endl << endl;
                    players[dealer]->add_and_discard(upcard);
                    ordered_up = players[next];
                    return;
                }
                else {
                    cout << players[next]->get_name() << " passes" << endl;
                }
            }
            num++;
        }
    }
    void make_trump_round_2(Card upcard) {
        int num = 1;
        for (int i = 0; i < MAX_PLAYERS; i++) {
            int next = dealer + num;
            if (next >= MAX_PLAYERS) {
                next = next - MAX_PLAYERS;
            }
            if (next != dealer) {
                if (players[next]->make_trump(upcard, false, 2, trump)){
                    cout << players[next]->get_name() << " orders up "
                    << trump << endl << endl;;
                    ordered_up = players[next];
                    return;
                }
                else {
                    cout << players[next]->get_name() << " passes" << endl;
                }
            }
            else if (next == dealer) {
                if (players[next]->make_trump(upcard, true, 2, trump)){
                    cout << players[next]->get_name() << " orders up "
                    << trump << endl << endl;;
                    ordered_up = players[next];
                    return;
                }
                else {
                    cout << players[next]->get_name() << " passes" << endl;
                }
            }
            num++;
        }
    }
    void hand_scoring (int t1_tricks, int t2_tricks) {
        if (t1_tricks > t2_tricks) {
            cout << players[0]->get_name() << " and " << players[2]->get_name()
            << " win the hand" << endl;
            if ((players[1] == ordered_up) || (players[3] == ordered_up)) {
                t1_scoring = t1_scoring + 2;
                cout << "euchred!" << endl;
            }
            else if (t1_tricks == 5){
                t1_scoring = t1_scoring + 2;
                cout << "march!" << endl;
            }
            else {
                t1_scoring++;
            }
        }
        else if (t2_tricks > t1_tricks) {
            cout << players[1]->get_name() << " and " << players[3]->get_name()
            << " win the hand" << endl;
            if ((players[0] == ordered_up) || (players[2] == ordered_up)) {
                t2_scoring = t2_scoring + 2;
                cout << "euchred!" << endl;
            }
            else if (t2_tricks == 5){
                t2_scoring = t2_scoring + 2;
                cout << "march!" << endl;
            }
            else {
                t2_scoring++;
            }
        }
    }
    void print_score() {
        cout << players[0]->get_name() << " and " << players[2]->get_name() <<
        " have " << t1_scoring << " points" << endl;
        cout << players[1]->get_name() << " and " << players[3]->get_name() <<
        " have " << t2_scoring << " points" << endl << endl;
    }
    void trick_takened (int &t1_tricks, int &t2_tricks, int trick_taken) {
        cout << players[trick_taken]->get_name() << " takes the trick"
        << endl << endl;
        if (trick_taken % 2 == 0) {
            t1_tricks++;
        }
        else if (trick_taken % 2 != 0) {
            t2_tricks++;
        }
    }
    Card player_play_card (int &next, Card &max, int &trick_taken, Card &led_card) {
        Card next_card;
        if (next >= MAX_PLAYERS) {
            next = next - MAX_PLAYERS;
        }
        next_card = players[next]->play_card(led_card, trump);
        cout << next_card << " played by " << players[next]->get_name()
        << endl;
        if (Card_less(max, next_card, led_card, trump)) {
            max = next_card;
            // the index of the player who is winnning
            trick_taken = next;
        }
        next++;
        return next_card;
    }
    Card player_lead_card (Card &max, int &trick_taken, int &next) {
        Card led_card;
        led_card = players[trick_taken]->lead_card(trump);
        max = led_card;
        cout << led_card << " led by " << players[trick_taken]->get_name()
        << endl;
    // this for loop for the following players playing their cards to
        //follow suit. keeps track of highest card
        int num = 1;
        next = trick_taken + num;
        return led_card;
    }
    void play_hand() {
        shuffle();
        cout << "Hand " << num_hand << endl;
        deal();
        Card upcard = pack.deal_one();
        make_trump_round_1(upcard);
        if (trump == " ") {
            make_trump_round_2(upcard);
        }
        Card max;
        Card led_card;
        Card next_card;
        int t1_tricks = 0;
        int t2_tricks = 0;
        int num = 1;
        int next = 0;
        // determining the person to the left of dealer who
        //always leads for this hand
        int trick_taken = dealer + num;
        if (trick_taken >= MAX_PLAYERS) {
            trick_taken = trick_taken - MAX_PLAYERS;
        }
        // plays all 5 hands with the next person always leading.
        //keeps tracks of how many tricks each TEAM got
        for (int i = 0; i < MAX_TRICKS; i++) {
            led_card = player_lead_card (max, trick_taken, next);
            for (int i = 1; i < MAX_PLAYERS; i++) {
                next_card = player_play_card (next, max, trick_taken, led_card);
            }
            trick_takened (t1_tricks, t2_tricks, trick_taken);
        }
        hand_scoring(t1_tricks, t2_tricks);
        print_score();
        
        dealer++;
        if (dealer == MAX_PLAYERS) {
            dealer = 0;
        }
        num_hand++;
        trump = " ";
    }
    
public:
    Game(vector<Player*> inputed_players, int input_score,
         string shuffle, istream &input_pack) {
        round = 0;
        if_shuffle = false;
        t1_scoring = 0;
        t2_scoring = 0;
        score = 10;
        dealer = 0;
        num_hand = 0;
        trump = " ";
        
        for (size_t i = 0; i < MAX_PLAYERS; i++) {
            players.push_back(inputed_players[i]);
        }
        score = input_score;
        if (shuffle == "shuffle") {
            if_shuffle = true;
        }
        else if (shuffle == "noshuffle") {
            if_shuffle = false;
        }
        Pack new_pack(input_pack);
        pack = new_pack;
    }
    void play() {
        while ((t2_scoring < score) && (t1_scoring < score)) {
            play_hand();
        }
        if (t1_scoring > score) {
            cout << players[0]->get_name() << " and " << players[2]->get_name()
            << " win!" << endl;
        }
        else if (t2_scoring > score) {
            cout << players[1]->get_name() << " and " << players[3]->get_name()
            << " win!" << endl;
        }
    }
    
    
};
void error_message() {
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
         << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
         << "NAME4 TYPE4" << endl;
}
int error(int argc, char **argv) {
    if (argc != 12) {
        error_message();
        return 1;
    }
    if ((atoi(argv[3]) > 100) || (atoi(argv[3]) < 1) ) {
        error_message();
        return 1;
    }
    string shuffle = argv[2];
    if (!(shuffle == "shuffle") && !(shuffle == "noshuffle")) {
        error_message();
        return 1;
    }
    for (int i = 5; i < argc; ) {
        string type = argv[i];
        if (!(type == "Simple") && !(type == "Human")) {
            error_message();
            return 1;
        }
        i = i + 2;
    }
    return 0;
}
int main(int argc, char **argv) {
    int num = error(argc, argv);
    if (num == 1) {
        return 1;
    }
    string input = argv[1];
    ifstream fin;
    fin.open(input);
    if (!fin.is_open()) {
        cout << "Error opening " << input << endl;
        return 1;
    }
    string shuffle = argv[2];
    vector<Player*> players;
    int points = atoi(argv[3]);
    Player *zero = Player_factory(argv[4], argv[5]);
    Player *one = Player_factory(argv[6], argv[7]);
    Player *two = Player_factory(argv[8], argv[9]);
    Player *three = Player_factory(argv[10], argv[11]);
    
    players.push_back(zero);
    players.push_back(one);
    players.push_back(two);
    players.push_back(three);
    
    Game game(players, points, shuffle, fin);
    
    for (int i = 0; i < argc; i++) {
        cout << argv[i] << " ";
    }
    cout << endl;
    
    game.play();
    
    for (size_t i = 0; i < players.size(); i++) {
        delete players[i];
    }
    return 0;
}
