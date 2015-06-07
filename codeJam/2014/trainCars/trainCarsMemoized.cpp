// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <string>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
#include <utility>

using std::list;
using std::string;
using std::unordered_map;

#define MAGIC (1000000007)

// dyn programming cache
//stores concat str set S, ++, ending with some letter x, ++ cannot use string
//i.e. how many ways can I construct a VALID string with all of S that ends in x?
// without using anything in cannotUse
//given a set of strings in S
//key = (sort S) ++ x ++ cannotUse
//value = answer to Q
class Cache {
public:
  Cache() : cache_() {}
  void Add(list<string> ss, char endLetter, string cantuse, unsigned long long val);
  bool Exists(list<string> ss, char endLetter, string cantuse) const;
  unsigned long long GetValue(list<string> ss, char ch, string cantuse) const;
private:
  void Normalize_(list<string>& ss, string& cannotUse) const;
  string MakeKey_(list<string>& ss, char ch, string cannotUse)const ;
  unordered_map<string, unsigned long long> cache_;
};

void Cache::Normalize_(list<string>& ss, string& cantuse) const
{
    // to make lookup predictable
    ss.sort(); 

    std::sort(cantuse.begin(), cantuse.end());

    // VERY CRYPTIC BUG FIX; found that keys were not being normalized correctly when 
    // the same string, with same length, was being repeated in ss
    // at various times, these would have corresponded to different combos
    // in the original problem, and needed to be counted correctly
    string pholder("%");
    unsigned int ctr=0;
    for(auto it = ss.begin(); it != ss.end(); it++) {
        string myend = pholder;
        myend.append(std::to_string(ctr));
        (*it).append(myend);
        ctr++;
    } 
    
}

string Cache::MakeKey_(list<string>& ss, char ch, string cantuse) const
{
    string key;
    Normalize_(ss, cantuse);

    std::for_each(ss.begin(), ss.end(), [&key] (const string& s) -> void {
        key.append(s);
    });
    key.append('@', ch); //marker char
    key.append(1, ch);
    key.append('@', ch); //marker char
    key.append(cantuse);

    return key;
}

void Cache::Add(list<string> ss, char ch, string cantuse, unsigned long long val)
{
    string key = MakeKey_(ss, ch, cantuse);
    cache_.insert(make_pair(key, val));
}

bool Cache::Exists(list<string> ss, char ch, string cantuse) const
{
    string key = MakeKey_(ss, ch, cantuse);
    return (cache_.find(key) != cache_.end());
}

unsigned long long Cache::GetValue(list<string> ss, char ch, string cantuse) const
{
    assert(Exists(ss, ch, cantuse));
    string key = MakeKey_(ss, ch, cantuse);
    return ((cache_.find(key))->second);
}

class TrainCars {
public:
  TrainCars() : cache_(), cars_() {}
  void readInput();
  unsigned long long computeValidCombos();
private:
  unsigned long long computeValidCombos_(list<string>& ss, char ch, string cannotUse);
  void readCars_(unsigned int num);
  bool validUseOfWord_(string word, char& ch, string& cannotuse);
  Cache cache_;
  list<string> cars_;
};

void TrainCars::readCars_(unsigned int num)
{
    for (unsigned int n=0; n<num; n++) {
        string car;
        std::cin >> car;
        cars_.push_back(car);
    }
}

void TrainCars::readInput()
{
    unsigned int number=0;
    std::cin >> number;
    readCars_(number);
}

//checks to see if using word at the end will break any rules
//rules broken if
//   1. word uses ch in any position other than (possibly) contiguous sequence at the end
//   2. or word uses anything in cannotuse
//   3. or word repeats a char with some other char in between
//if rules broken, returns false without changing anything
//if no rules broken, then
//   adds chars from word to cannotuse list
//   re-writes ch as front() of word
//   and returns true
bool TrainCars::validUseOfWord_(string word, char& ch, string& cannotuse)
{
    bool violation = false;

    //word using anything in cannot use
    for(char& c : cannotuse) {
        if (word.find(c) != string::npos) {
            violation = true;
        }
    }

    //word uses ch in any position other than (possibly) contiguous sequence at the end
    auto it = word.rbegin();
    for (; it != word.rend(); it++) {
        if ((*it) != ch) {
            break;
        }
    }

    for (; it != word.rend(); it++) {
        if ((*it) == ch) {
            violation = true;
        }
    }

    //word repeats a char with some other char in between
    string localCannotUse;
    char last = word.back();
    for (auto it = word.rbegin() + 1; it != word.rend(); it++) {
        if ((*it) == last) {
            continue;
        } else {
            localCannotUse.append(1, last);
            if (localCannotUse.find(*it) != string::npos) {
                violation = true;
                break;
            }
            last = *it;
        }
    }

    if (violation) {
        return false;
    }

    char chfront = word.front();
    if (chfront == ch) {
        //the entire word was ch only
        //no need to change ch or cannotuse
        return true;
    } else {
        cannotuse.append(1, ch);
    }

    //now determined that use is valid
    //so adjust ch and cannotuse
    for (char& c: word) {
        if (cannotuse.find(c) == string::npos && c != chfront) {
            cannotuse.append(1, c);
        }
    }
    ch = chfront;
    return true;
}

//how many valid combos can I construct, ending in ch, 
//and can't use chars from cannot use (except string of ch's at the end)
unsigned long long TrainCars::computeValidCombos_(list<string>& ss, char ch, string cannotUse)
{
    if (cache_.Exists(ss, ch, cannotUse)) {
        return cache_.GetValue(ss, ch, cannotUse);
    }

    if (ss.size() == 1) {
        string str = ss.front();
        char chPar = ch;
        string cannotUsePar = cannotUse;
        if (validUseOfWord_(str, chPar, cannotUsePar)) {
            cache_.Add(ss, ch, cannotUse, 1);
            return 1;
        } else {
            cache_.Add(ss, ch, cannotUse, 0);
            return 0;
        }
    }

    unsigned long long combos = 0;

    for (unsigned int i=0; i<ss.size(); i++) {
        //take one string from the input, and place it at the end
        //also create a subset of other string that I need to recurse on
        list<string> subset = ss;

        auto it = subset.begin();
        std::advance(it, i);
        string chosen = *it;

        char chPar = ch;
        string cannotUsePar = cannotUse;
        if (!validUseOfWord_(chosen, chPar, cannotUsePar)) {
            continue; //this string cannot be at the end
        }

        subset.erase(it);

        unsigned long long myCombos = computeValidCombos_(subset, chPar, cannotUsePar);
        combos += myCombos;
    }

    cache_.Add(ss, ch, cannotUse, combos);
    return combos;
}

unsigned long long TrainCars::computeValidCombos()
{
    unsigned long long val = computeValidCombos_(cars_, '#', "");
    return (val % MAGIC);
}

int main() 
{
    unsigned int numTests;
    std::cin >> numTests;
    for (unsigned int i=1; i<=numTests; i++) {
        TrainCars tc;
        tc.readInput();
        unsigned int combos = tc.computeValidCombos();

        std::cout << "Case #" << i << ": " << combos << std::endl;
    }
}



