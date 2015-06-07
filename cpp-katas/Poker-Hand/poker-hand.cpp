// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// Author - Sourabh S Joshi
#include "poker-hand.h"
#include <iostream>
#include <array>
#include <algorithm>
#include <assert.h>
#include <map>

using std::string;
using std::array;

ostream& operator<<(ostream& os, const Card& cd)
{
    array<string, Card::NUM_SUITS> suit_name = {"C", "D", "H", "S"};
    array<string, Card::NUM_VALS>  val_name = {"2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"}; 

    string my_suit = suit_name[cd.suit_];
    string my_val = val_name[cd.val_];

    os << my_val << my_suit;

    return os;
}

Pokerhand::Pokerhand(std::string istr) 
: hand_(), type_(PH_NUM_TYPES), tiebreak_cards_()
{
    std::map<std::string, Card::CardSuit> suit_map = {{"C", Card::Clubs}, {"D", Card::Diamonds}, {"H", Card::Hearts}, {"S", Card::Spades}};
    std::map<std::string, Card::CardVal>  val_map  = {{"2", Card::Two},   {"3", Card::Three},    {"4", Card::Four},   {"5", Card::Five},
                                                      {"6", Card::Six},   {"7", Card::Seven},    {"8", Card::Eight},  {"9", Card::Nine},
                                                      {"T", Card::Ten},   {"J", Card::Jack},     {"Q", Card::Queen},  {"K", Card::King},
                                                      {"A", Card::Ace}};

    std::transform(istr.begin(), istr.end(), istr.begin(), ::toupper);

    std::istringstream iss(istr);
    while (iss) {
        std::string scard;
        iss >> scard;
        if (scard != "") {
            Card::CardSuit suit;
            Card::CardVal  val;

            //find suit
            for_each(suit_map.begin(), suit_map.end(), [scard, &suit] (std::pair<std::string, Card::CardSuit> mapelem) -> void {
                if (scard.find(mapelem.first) != std::string::npos) {
                    suit = mapelem.second;
                }
            });

            //and value
            for_each(val_map.begin(), val_map.end(), [scard, &val] (std::pair<std::string, Card::CardVal> mapelem) -> void {
                if (scard.find(mapelem.first) != std::string::npos) {
                    val = mapelem.second;
                }
            });

            hand_.push_back(Card(suit, val));
        }
    }
}

ostream& operator<<(ostream& os, const Pokerhand& ph)
{
    os << ph.hand_[0] << " " << ph.hand_[1] << " " << ph.hand_[2] << " " << ph.hand_[3] << " " << ph.hand_[4];
    return os;
}

std::string Pokerhand::GetTypeStr() const
{
    assert(type_ >= Pokerhand::PHHighCard && type_ <= Pokerhand::PHStraightFlush);

    std::map<Pokerhand::HandType, std::string> hand_map = 
        {{PHHighCard, "High Card"}, {PHPair, "Pair"},   {PHTwoPair, "Two Pair"},     {PHThreeOfAKind, "Three Of A Kind"},
         {PHStraight, "Straight"},  {PHFlush, "Flush"}, {PHFullHouse, "Full House"}, {PHFourOfAKind, "Four Of A Kind"},
         {PHStraightFlush, "Straight Flush"}};

    auto elemiter = hand_map.find(type_);

    assert(elemiter != hand_map.end());
    return ((*elemiter).second);
}

//assigns the proper hand type to type_
//and assigns tiebreak_cards_ in the proper order
void Pokerhand::ProcessPokerHand()
{
    tiebreak_cards_ = hand_;

    //sort cards on value
    std::sort(tiebreak_cards_.begin(), tiebreak_cards_.end(), std::greater<Card>());

    if (StraightFlush_()) {
        assert(tiebreak_cards_.size() == 5);
    } else if (FourOfAKind_()) {
        assert(tiebreak_cards_.size() == 2);
    } else if (FullHouse_()) {
        assert(tiebreak_cards_.size() == 2);
    } else if (Flush_()) {
        assert(tiebreak_cards_.size() == 5);
    } else if (Straight_()) {
        assert(tiebreak_cards_.size() == 5);
    } else if (ThreeOfAKind_()) {
        assert(tiebreak_cards_.size() == 3);
    } else if (TwoPair_()) {
        assert(tiebreak_cards_.size() == 3);
    } else if (Pair_()) {
        assert(tiebreak_cards_.size() == 4);
    } else {
        HighCard_();
        assert(tiebreak_cards_.size() == 5);
    }
}

//If X number of same value cards found, will delete them, and return a card of that value
Card* Pokerhand::XOfAKind__(unsigned int x)
{
    Card check_card = *(tiebreak_cards_.begin());
    auto startiter = tiebreak_cards_.begin();

    //get range of equal cards
    while (startiter != tiebreak_cards_.end()) {
        check_card = *startiter;
        auto range_val = std::equal_range(startiter, tiebreak_cards_.end(), check_card, std::greater<Card>());
        size_t dist = std::distance(range_val.first, range_val.second);
        if (dist == x) { //x of a kind
            break;
        }
        startiter = range_val.second;
    }

    if (startiter == tiebreak_cards_.end()) {
        return NULL;
    }

    //remove the x of a kind card
    auto newlastiter = std::remove(tiebreak_cards_.begin(), tiebreak_cards_.end(), check_card);
    tiebreak_cards_.erase(newlastiter, tiebreak_cards_.end());

    Card *retval = new Card(check_card);
    return retval;
}

//This function detects 1 successful application of XOfAKind__ 
//and leaves tiebreak_cards_ in the correct sequence if successful
bool Pokerhand::XOfAKind_(unsigned int x)
{
    Card *card = XOfAKind__(x);
    if (card == NULL) {
        return false;
    }

    //insert the x of a kind card in front
    tiebreak_cards_.insert(tiebreak_cards_.begin(), *card);
    delete card;

    return true;
}

//This function detects 2 successful applications of XOfAKind__ 
//and leaves tiebreak_cards_ in the correct sequence if successful
bool Pokerhand::MNOfAKind_(unsigned int m, unsigned int n)
{
    vector<Card> restore = tiebreak_cards_;

    Card* card_m = XOfAKind__(m);
    if (card_m == NULL) {
        return false;
    }

    Card* card_n = XOfAKind__(n);
    if (card_n == NULL) {
        tiebreak_cards_ = restore;
        delete card_m;
        return false;
    }

    //insert the x and y of a kind cards in front, in the proper order
    tiebreak_cards_.insert(tiebreak_cards_.begin(), *card_n);
    tiebreak_cards_.insert(tiebreak_cards_.begin(), *card_m);
    delete card_m;
    delete card_n;

    return true;
}

bool Pokerhand::HighCard_()
{
    type_ = PHHighCard; 
    return true;
}

bool Pokerhand::Pair_()
{
    if (XOfAKind_(2)) {
        type_ = PHPair;
        return true;
    }
    return false;
}

bool Pokerhand::TwoPair_()
{
    if (MNOfAKind_(2, 2)) {
        type_ = PHTwoPair;
        return true;
    }
    return false;
}

bool Pokerhand::ThreeOfAKind_()
{
    if (XOfAKind_(3)) {
        type_ = PHThreeOfAKind;
        return true;
    }
    return false;
}

bool Pokerhand::FourOfAKind_()
{
    if (XOfAKind_(4)) {
        type_ = PHFourOfAKind;
        return true;
    }
    return false;
}

bool Pokerhand::FullHouse_()
{
    if (MNOfAKind_(3, 2)) {
        type_ = PHFullHouse;
        return true;
    }
    return false;
}

bool Pokerhand::Straight_()
{
    //special case for straight, if the sorted order is Ace, 5, 4, 3, 2 (considered 5, 4, 3, 2, Ace)
    vector<Card> special_cards = {Card(Card::Hearts, Card::Ace), Card(Card::Hearts, Card::Five), Card(Card::Hearts, Card::Four), 
                                  Card(Card::Hearts, Card::Three), Card(Card::Hearts, Card::Two)};

    if (special_cards == tiebreak_cards_) {
        std::rotate(tiebreak_cards_.begin(), tiebreak_cards_.begin() + 1, tiebreak_cards_.end());
    } else {
        //check if we have a normal straight
        for (unsigned int c=0; c<4; c++) {
            if (tiebreak_cards_[c+1].GetVal() != ((Card::CardVal)(((int)(tiebreak_cards_[c].GetVal())) - 1))) {
                return false;
            }
        }
    }

    type_ = PHStraight;
    return true;
}

bool Pokerhand::Flush_()
{
    Card::CardSuit check_suit = tiebreak_cards_[0].GetSuit();
    bool is_flush = std::all_of(tiebreak_cards_.begin(), tiebreak_cards_.end(), [check_suit] (Card cd) {return (cd.GetSuit() == check_suit);});

    if (is_flush) {
        type_ = PHFlush;
    }
    return is_flush;
}

bool Pokerhand::StraightFlush_()
{
    if (Flush_() && Straight_()) {
        type_ = PHStraightFlush;
        return true;
    }
    return false;
}

typename Pokerhand::Ordering Pokerhand::Compare_(const Pokerhand& rhs) const
{
    if (type_ != rhs.type_) {
        return ((type_ > rhs.type_) ? PH_GT : PH_LT);
    }

    assert(tiebreak_cards_.size() == rhs.tiebreak_cards_.size());

    for(auto myiter  = tiebreak_cards_.begin(), rhsiter = rhs.tiebreak_cards_.begin(); myiter != tiebreak_cards_.end(); myiter++, rhsiter++) {
        if (!(*myiter == *rhsiter)) {
            return ((*myiter > *rhsiter) ? PH_GT : PH_LT);
        }
    }
    return PH_EQ;
}

//Method that plays various players hands, and picks winner
int PlayPokerHands(vector<std::pair<int, Pokerhand> >& hands)
{
    assert(hands.size() >= 2);

    if (DetectCheating(hands)) {
        std::cout << "*************** Cheating: Duplicate cards detected! ***************" << std::endl;
    }

    for_each(hands.begin(), hands.end(), [] (std::pair<int, Pokerhand>& num_hand) -> void {
        std::cout << "P" << num_hand.first << ": " << num_hand.second << "; ";
        num_hand.second.ProcessPokerHand();
    });

    //sort to handle more than 1 player
    std::partial_sort(hands.begin(), hands.begin() + 1, hands.end(), [](const std::pair<int, Pokerhand>& lhs, const std::pair<int, Pokerhand>& rhs) {return lhs.second > rhs.second;});

    auto firstiter = hands.begin();
    auto seciter = firstiter + 1;

    if ((*firstiter).second > (*seciter).second) {
        std::cout << "P" << (*firstiter).first << " wins with " << (*firstiter).second.GetTypeStr() << std::endl;
        return ((*firstiter).first);
    } else {
        std::cout << "Tie: " << (*firstiter).second.GetTypeStr() << std::endl;
        return 0;
    }
    return -1;
}

bool DetectCheating(vector<std::pair<int, Pokerhand> >& hands)
{
    vector<Card> all_cards;
    all_cards.reserve(hands.size() * 5);

    for_each(hands.begin(), hands.end(), [&all_cards] (const std::pair<int, Pokerhand>& arg) -> void {
        vector<Card> these_cards = arg.second.AllCards();
        all_cards.insert(all_cards.end(), these_cards.begin(), these_cards.end());
    });

    vector<Card> unique_cards = all_cards;

    std::sort(unique_cards.begin(), unique_cards.end(), [] (const Card& lhs, const Card& rhs) -> bool {
        if (lhs.GetSuit() != rhs.GetSuit()) {
            return (lhs.GetSuit() > rhs.GetSuit());
        }
        return (lhs.GetVal() > rhs.GetVal());
    });

    auto newlast = std::unique(unique_cards.begin(), unique_cards.end(), 
                        [] (const Card& lhs, const Card& rhs) {return ((lhs.GetSuit() == rhs.GetSuit()) && (lhs.GetVal() == rhs.GetVal()));});

    return (newlast != unique_cards.end());
}



