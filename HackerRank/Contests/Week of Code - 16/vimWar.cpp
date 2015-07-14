// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include <algorithm>

using std::unordered_map;
using std::string;
using std::vector;
using std::pair;
using std::make_pair;

typedef unsigned long long U64;

#define MODNUM (1000000007)

class VimWar {
public:
    VimWar();
    U64 numWays();
private:
    void readInput();
    void filterSoldiers();

    int numSoldiers;
    int numSkills;
    vector<U64> soldiers;
    U64 skillsReq;
};

VimWar::VimWar() 
: numSoldiers(0), numSkills(0), soldiers(), skillsReq(0)  {
    readInput();
}

void VimWar::readInput() {
    std::cin >> numSoldiers >> numSkills;
    string myskillstr;
    for (int s=0; s<numSoldiers; s++) {
        std::cin >> myskillstr;
        U64 myskills = 0, mymask = 1;
        for (int b=0; b<numSkills; b++) {
            if (myskillstr[b] == '1') myskills |= mymask;
            mymask <<= 1;
        }
        soldiers.push_back(myskills);
    }
    std::cin >> myskillstr;
    U64 myskills = 0, mymask = 1;
    for (int b=0; b<numSkills; b++) {
        if (myskillstr[b] == '1') myskills |= mymask;
        mymask <<= 1;
    }
    skillsReq = myskills;
}

//throw out those soldiers who can *never* be chosen
void VimWar::filterSoldiers() {
    vector<U64> chosen;
    for (const U64& skill : soldiers) {
        if (skill & (~skillsReq)) continue;
        chosen.push_back(skill);
    }
    soldiers = chosen;
}

U64 VimWar::numWays() {
    filterSoldiers();
    if (soldiers.size() == 0) return 0; //not possible

    std::sort(soldiers.begin(), soldiers.end(), std::greater<U64>());

    unordered_map<U64, U64> curCombos; //mapping from skills possible to -> number of ways to build those skills up so far
    curCombos.insert(make_pair(0,1));  //1 ways to build up 0, by not taking anyone


    for (int i=0; i<soldiers.size(); i++) {
        unordered_map<U64, U64> mynewcombos;

        for (pair<const U64, U64>& combo : curCombos) {
            const U64& checkskills = combo.first;
            U64& waysskills = combo.second;

            if ((checkskills | soldiers[i]) == checkskills) {
                waysskills *= 2;
                waysskills %= MODNUM;
            } else {
                //if you take me, I can add new skills (which might overlap with some other entry of yours in curCombos but not THIS combo)
                U64 newcombo = checkskills | soldiers[i];

                U64 newcomboways = waysskills;
                newcomboways %= MODNUM;

                auto mit = mynewcombos.find(newcombo);
                if (mit != mynewcombos.end()) { //new combo overlaps with something we already have
                    mit->second += newcomboways;
                    mit->second %= MODNUM;
                } else {
                    mynewcombos.insert(make_pair(newcombo, newcomboways));
                }

                //if you drop me, you cankeep doing this in same number of ways 
                //waysskills *= 1;
                //waysskills %= MODNUM;
            }
        }
        for (pair<const U64, U64>& combo : mynewcombos) {
            auto it = curCombos.find(combo.first);
            if (it != curCombos.end()) {
                it->second += combo.second;
                it->second %= MODNUM;
            } else {
                curCombos.insert(make_pair(combo.first, combo.second)); //only 1 way to build this skill set, and that is by including me
            }
        }
    }
    

    U64 numways = 0;
    for (auto combo: curCombos) {
        if (combo.first == skillsReq) {
            numways += combo.second;
            numways %= MODNUM;
        }
    }

    return numways;
}

int main () {
    VimWar vimwar;
    U64 ans = vimwar.numWays();
    std::cout << ans << std::endl;
}

