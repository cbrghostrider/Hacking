// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// Author - Sourabh S Joshi
#ifndef POKER_HAND_H_
#define POKER_HAND_H_

#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <sstream>

using std::vector;
using std::ostream;
using std::pair;

class Card {
public:
    enum CardSuit {
        Clubs, Diamonds, Hearts, Spades, NUM_SUITS
    };

    enum CardVal {
        Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace, NUM_VALS
    };

    Card(CardSuit suit, CardVal val) : suit_(suit), val_(val) {}
    ~Card() {}

    //comparison operators only compare on value of card
    bool operator==(const Card& rhs) const { return (val_ == rhs.val_);}
    bool operator<(const Card& rhs) const { return (val_ < rhs.val_);}
    bool operator>(const Card& rhs) const { return (val_ > rhs.val_);}

    CardVal GetVal()  const {return val_;}
    CardSuit GetSuit() const {return suit_;}

    friend ostream& operator<<(ostream& os, const Card& cd);

private:
    CardSuit suit_;
    CardVal  val_;
};

class Pokerhand {
public:
    enum HandType {
        PHHighCard, PHPair, PHTwoPair, PHThreeOfAKind, PHStraight, PHFlush, PHFullHouse, PHFourOfAKind, PHStraightFlush, PH_NUM_TYPES
    };

    Pokerhand(std::string istr);
    virtual ~Pokerhand() {}

    vector<Card> AllCards() const {return hand_;}
    vector<Card> TieBreakCards() const {return tiebreak_cards_;} 
    HandType GetType() const {return type_;}
    std::string GetTypeStr() const;

    //comparison to compare 2 poker hands
    bool operator>(const Pokerhand& rhs) const  {return (Compare_(rhs) == PH_GT);}
    bool operator<(const Pokerhand& rhs) const  {return (Compare_(rhs) == PH_LT);}
    bool operator==(const Pokerhand& rhs) const {return (Compare_(rhs) == PH_EQ);}

    friend ostream& operator<<(ostream& os, const Pokerhand& ph);

    void ProcessPokerHand();

private:
    //each of these methods returns a bool, saying whether the poker hand is of that type
    //also returns a vector of cards in order, so that tie-breakers can be resolved
    Card* XOfAKind__(unsigned int num);
    bool XOfAKind_(unsigned int num);
    bool MNOfAKind_(unsigned int m, unsigned int n);
    bool HighCard_();
    bool Pair_();
    bool TwoPair_();
    bool ThreeOfAKind_();
    bool Straight_();
    bool Flush_();
    bool FullHouse_();
    bool FourOfAKind_();
    bool StraightFlush_();

    //since C++ STL lacks an ordering type, I am forced to create one
    enum Ordering {
        PH_LT, PH_EQ, PH_GT
    };

    Ordering Compare_(const Pokerhand& rhs) const;
private:
    vector<Card> hand_;
    HandType type_;
    vector<Card> tiebreak_cards_;
};

int PlayPokerHands(vector<std::pair<int, Pokerhand> >& hands);
bool DetectCheating(vector<std::pair<int, Pokerhand> >& hands);

#endif /* POKER_HAND_H_ */
