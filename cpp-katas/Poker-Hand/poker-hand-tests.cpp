// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//Author - Sourabh S Joshi
#include <gtest/gtest.h>


#include <string>
#include <sstream>
#include "poker-hand.h"
#include <algorithm>
#include <utility>

using std::string;

std::string TieBreakString(vector<Card> tbc) {
    std::ostringstream oss;
    for_each (tbc.begin(), tbc.end(), [&oss] (Card c) -> void {oss << c << " ";});
    return oss.str();
}

TEST(PokerHandTest, CardCompareEq) {
        EXPECT_EQ(Card(Card::Hearts, Card::Queen), Card(Card::Hearts, Card::Queen));
}

TEST(PokerHandTest, CardCompareLt) {
        EXPECT_LT(Card(Card::Hearts, Card::Queen), Card(Card::Spades, Card::King));
}

TEST(PokerHandTest, CardCompareGt) {
        EXPECT_GT(Card(Card::Diamonds, Card::King), Card(Card::Hearts, Card::Queen));
}

TEST(PokerHandTest, HighCard) {
        std::string cards("QH 2D 5S JH AC");

        Pokerhand hand(cards);
        hand.ProcessPokerHand();

        vector<Card> retval = hand.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(hand.GetType(), Pokerhand::PHHighCard);
        EXPECT_EQ(tbc, std::string("AC QH JH 5S 2D "));
}

TEST(PokerHandTest, PairTest1) {
        std::string cards("QH 2D 5S 2H AC");

        Pokerhand hand(cards);
        hand.ProcessPokerHand();

        vector<Card> retval = hand.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(hand.GetType(), Pokerhand::PHPair);
        EXPECT_EQ(tbc, std::string("2D AC QH 5S "));
}


TEST(PokerHandTest, TwoPairTest0) {
        std::string cards("QH 2D QS 2H AC");

        Pokerhand hand(cards);
        hand.ProcessPokerHand();

        vector<Card> retval = hand.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(hand.GetType(), Pokerhand::PHTwoPair);
        EXPECT_EQ(tbc, std::string("QH 2D AC "));
}

TEST(PokerHandTest, ThreeOfAKind0) {
        std::string cards("QH 2D QS AH QC");

        Pokerhand hand(cards);
        hand.ProcessPokerHand();

        vector<Card> retval = hand.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(hand.GetType(), Pokerhand::PHThreeOfAKind);
        EXPECT_EQ(tbc, std::string("QH AH 2D "));
}

TEST(PokerHandTest, ThreeOfAKind1) {
        std::string cards("QH QS QC KD AH");

        Pokerhand hand(cards);
        hand.ProcessPokerHand();

        vector<Card> retval = hand.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(hand.GetType(), Pokerhand::PHThreeOfAKind);
        EXPECT_EQ(tbc, std::string("QH AH KD "));
}

TEST(PokerHandTest, Straight0) {
        std::string cards("TD KS JC 9H QH");

        Pokerhand hand(cards);
        hand.ProcessPokerHand();

        vector<Card> retval = hand.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(hand.GetType(), Pokerhand::PHStraight);
        EXPECT_EQ(tbc, std::string("KS QH JC TD 9H "));
}

TEST(PokerHandTest, Straight1) {
        std::string cards("TD KS JC AH QH");

        Pokerhand hand(cards);
        hand.ProcessPokerHand();

        vector<Card> retval = hand.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(hand.GetType(), Pokerhand::PHStraight);
        EXPECT_EQ(tbc, std::string("AH KS QH JC TD "));
}

TEST(PokerHandTest, Straight2) {
        std::string cards("3D 4S AC 5H 2H");
        Pokerhand hand(cards);
        hand.ProcessPokerHand();

        vector<Card> retval = hand.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(hand.GetType(), Pokerhand::PHStraight);
        EXPECT_EQ(tbc, std::string("5H 4S 3D 2H AC "));
}

TEST(PokerHandTest, Flush) {
        std::string cards("QH 2H 5H JH AH");
        Pokerhand hand(cards);
        hand.ProcessPokerHand();

        vector<Card> retval = hand.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(hand.GetType(), Pokerhand::PHFlush);
        EXPECT_EQ(tbc, std::string("AH QH JH 5H 2H "));
}

TEST(PokerHandTest, FullHouse0) {
        std::string cards("3S KS 3H KC 3D");

        Pokerhand hand(cards);
        hand.ProcessPokerHand();

        vector<Card> retval = hand.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(hand.GetType(), Pokerhand::PHFullHouse);
        EXPECT_EQ(tbc, std::string("3S KS "));
}


TEST(PokerHandTest, FourOfAKind0) {
        std::string cards("3S 3S 3H 3C 3D"); //illegal case, duplicate card

        Pokerhand hand(cards);
        hand.ProcessPokerHand();

        EXPECT_EQ(hand.GetType(), Pokerhand::PHHighCard);
}

TEST(PokerHandTest, FourOfAKind1) {
        std::string cards("3S KS 3H 3C 3D");

        Pokerhand hand(cards);
        hand.ProcessPokerHand();

        vector<Card> retval = hand.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(hand.GetType(), Pokerhand::PHFourOfAKind);
        EXPECT_EQ(tbc, std::string("3S KS "));
}

TEST(PokerHandTest, StraightFlush0) {
        std::string cards("TD KD JD 9D QD");

        Pokerhand hand(cards);
        hand.ProcessPokerHand();

        vector<Card> retval = hand.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(hand.GetType(), Pokerhand::PHStraightFlush);
        EXPECT_EQ(tbc, std::string("KD QD JD TD 9D "));
}

TEST(PokerHandTest, StraightFlush1) {
        std::string cards("TS KS JS AS QS");

        Pokerhand hand(cards);
        hand.ProcessPokerHand();

        vector<Card> retval = hand.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(hand.GetType(), Pokerhand::PHStraightFlush);
        EXPECT_EQ(tbc, std::string("AS KS QS JS TS "));
}

TEST(PokerHandTest, StraightFlush2) {
        std::string cards("3H 4H AH 5H 2H");

        Pokerhand hand(cards);
        hand.ProcessPokerHand();

        vector<Card> retval = hand.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(hand.GetType(), Pokerhand::PHStraightFlush);
        EXPECT_EQ(tbc, std::string("5H 4H 3H 2H AH "));
}

TEST(PokerHandTest, GameTest1) {

        vector<std::pair<int, Pokerhand> > hands;
        hands.push_back(std::make_pair(1, Pokerhand(std::string("8S AD 5H 8H 8C"))));
        hands.push_back(std::make_pair(2, Pokerhand(std::string("3C 2S TS 4D JD"))));

        PlayPokerHands(hands);

        Pokerhand winner = (*(hands.begin())).second;
        int winnum = (*(hands.begin())).first;

        vector<Card> retval = winner.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(winnum, 1);

        EXPECT_EQ(winner.GetType(), Pokerhand::PHThreeOfAKind);
        EXPECT_EQ(tbc, std::string("8S AD 5H "));
}

TEST(PokerHandTest, GameTest2) {

        vector<std::pair<int, Pokerhand> > hands;
        hands.push_back(std::make_pair(1, Pokerhand(std::string("4S 7S AC JS TS"))));
        hands.push_back(std::make_pair(2, Pokerhand(std::string("7C AH TH 4D JH"))));

        PlayPokerHands(hands);

        Pokerhand winner = (*(hands.begin())).second;
        int winnum = (*(hands.begin())).first;

        vector<Card> retval = winner.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(winnum, 1);

        EXPECT_EQ(winner.GetType(), Pokerhand::PHHighCard);
        EXPECT_EQ(tbc, std::string("AC JS TS 7S 4S "));
}

TEST(PokerHandTest, GameTest3) {

        vector<std::pair<int, Pokerhand> > hands;
        hands.push_back(std::make_pair(1, Pokerhand(std::string("4C 7H 9D 2C QS"))));
        hands.push_back(std::make_pair(2, Pokerhand(std::string("4S 4H 4D 3H 3D"))));

        PlayPokerHands(hands);

        Pokerhand winner = (*(hands.begin())).second;
        int winnum = (*(hands.begin())).first;

        vector<Card> retval = winner.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(winnum, 2);

        EXPECT_EQ(winner.GetType(), Pokerhand::PHFullHouse);
        EXPECT_EQ(tbc, std::string("4S 3H "));
}

TEST(PokerHandTest, GameTest4) {

        vector<std::pair<int, Pokerhand> > hands;
        hands.push_back(std::make_pair(1, Pokerhand(std::string("AH 4D 2S 8D QC"))));
        hands.push_back(std::make_pair(2, Pokerhand(std::string("5h Ks 6h Kc 5c"))));

        PlayPokerHands(hands);

        Pokerhand winner = (*(hands.begin())).second;
        int winnum = (*(hands.begin())).first;

        vector<Card> retval = winner.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(winnum, 2);

        EXPECT_EQ(winner.GetType(), Pokerhand::PHTwoPair);
        EXPECT_EQ(tbc, std::string("KS 5H 6H "));
}

TEST(PokerHandTest, GameTest5) {

        vector<std::pair<int, Pokerhand> > hands;
        hands.push_back(std::make_pair(1, Pokerhand(std::string("6c 2s 2c 2h 6d"))));
        hands.push_back(std::make_pair(2, Pokerhand(std::string("Kc As 5h Ac Js"))));

        PlayPokerHands(hands);

        Pokerhand winner = (*(hands.begin())).second;
        int winnum = (*(hands.begin())).first;

        vector<Card> retval = winner.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(winnum, 1);

        EXPECT_EQ(winner.GetType(), Pokerhand::PHFullHouse);
        EXPECT_EQ(tbc, std::string("2S 6C "));
}

TEST(PokerHandTest, GameTest6) {

        vector<std::pair<int, Pokerhand> > hands;
        hands.push_back(std::make_pair(1, Pokerhand(std::string("9s Jd 9h 9c 9d"))));
        hands.push_back(std::make_pair(2, Pokerhand(std::string("2h 4s 5s Tc Th"))));

        PlayPokerHands(hands);

        Pokerhand winner = (*(hands.begin())).second;
        int winnum = (*(hands.begin())).first;

        vector<Card> retval = winner.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(winnum, 1);

        EXPECT_EQ(winner.GetType(), Pokerhand::PHFourOfAKind);
        EXPECT_EQ(tbc, std::string("9S JD "));
}

TEST(PokerHandTest, GameTest7) {

        vector<std::pair<int, Pokerhand> > hands;
        hands.push_back(std::make_pair(1, Pokerhand(std::string("9s Jd 9h 9c 9d"))));
        hands.push_back(std::make_pair(2, Pokerhand(std::string("Td As Ts Tc Th"))));

        PlayPokerHands(hands);

        Pokerhand winner = (*(hands.begin())).second;
        int winnum = (*(hands.begin())).first;

        vector<Card> retval = winner.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(winnum, 2);

        EXPECT_EQ(winner.GetType(), Pokerhand::PHFourOfAKind);
        EXPECT_EQ(tbc, std::string("TD AS "));
}

TEST(PokerHandTest, GameTest8) {

        vector<std::pair<int, Pokerhand> > hands;
        hands.push_back(std::make_pair(1, Pokerhand(std::string("KH KD 2S 2D QC"))));
        hands.push_back(std::make_pair(2, Pokerhand(std::string("5h Ks 6h Kc 5c"))));

        PlayPokerHands(hands);

        Pokerhand winner = (*(hands.begin())).second;
        int winnum = (*(hands.begin())).first;

        vector<Card> retval = winner.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(winnum, 2);

        EXPECT_EQ(winner.GetType(), Pokerhand::PHTwoPair);
        EXPECT_EQ(tbc, std::string("KS 5H 6H "));
}

TEST(PokerHandTest, GameTest9) {

        vector<std::pair<int, Pokerhand> > hands;
        hands.push_back(std::make_pair(1, Pokerhand(std::string("KH KD 5S 5D QC"))));
        hands.push_back(std::make_pair(2, Pokerhand(std::string("5h Ks 6h Kc 5c"))));

        PlayPokerHands(hands);

        Pokerhand winner = (*(hands.begin())).second;
        int winnum = (*(hands.begin())).first;

        vector<Card> retval = winner.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(winnum, 1);

        EXPECT_EQ(winner.GetType(), Pokerhand::PHTwoPair);
        EXPECT_EQ(tbc, std::string("KH 5S QC "));
}

TEST(PokerHandTest, ThreePlayerTest1) {

        vector<std::pair<int, Pokerhand> > hands;
        hands.push_back(std::make_pair(1, Pokerhand(std::string("KH KD 5S 5D QC"))));
        hands.push_back(std::make_pair(2, Pokerhand(std::string("5h Ks 6h Kc 5c"))));
        hands.push_back(std::make_pair(3, Pokerhand(std::string("6c 2s 2c 2h 6d"))));

        PlayPokerHands(hands);

        Pokerhand winner = (*(hands.begin())).second;
        int winnum = (*(hands.begin())).first;

        vector<Card> retval = winner.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(winnum, 3);

        EXPECT_EQ(winner.GetType(), Pokerhand::PHFullHouse);
        EXPECT_EQ(tbc, std::string("2S 6C "));
}

TEST(PokerHandTest, CheatingTest1) {

        vector<std::pair<int, Pokerhand> > hands;
        hands.push_back(std::make_pair(1, Pokerhand(std::string("KH KD 5S 5D QC"))));
        hands.push_back(std::make_pair(2, Pokerhand(std::string("5h Ks 6h Kh 5c"))));
        hands.push_back(std::make_pair(3, Pokerhand(std::string("6c 2s 2c 2h 6d"))));

        PlayPokerHands(hands);

        Pokerhand winner = (*(hands.begin())).second;
        int winnum = (*(hands.begin())).first;

        vector<Card> retval = winner.TieBreakCards();
        std::string tbc = TieBreakString(retval);

        EXPECT_EQ(winnum, 3);

        EXPECT_EQ(winner.GetType(), Pokerhand::PHFullHouse);
        EXPECT_EQ(tbc, std::string("2S 6C "));
}

