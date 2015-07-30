// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// after much optimization, passing 19/21 cases, TLE on 2
// Funny how O(n^2 * logn) actually performed better than O(n^2)
// because of other optimizations in the code
// i.e We almost never hit the worst case bound for this one
// and often are able to break out pretty quickly from the inner loops
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <limits>
#include <utility>

using std::pair;
using std::make_pair;
using std::vector;

typedef int Elem;

class TeamFormation {
public:
    TeamFormation();
    int pickTeams();
private:
    void readInput();
    int findTeamEndingIn(const vector<pair<Elem, int>>& curTeams, int val);

    vector<Elem> skills;
    vector<pair<Elem, int>> teams; //each team is (ending value, length)
};

TeamFormation::TeamFormation() 
: skills(), teams() {
    readInput();
}

void TeamFormation::readInput() {
    int n; std::cin >> n;
    for (int i=0; i<n; i++) {
        Elem elem; std::cin >> elem;
        skills.push_back(elem);
    }
}

int TeamFormation::findTeamEndingIn(const vector<pair<Elem, int>>& curTeams, int val) {
    int chosen = -1;
    for (int ti=0; ti<curTeams.size(); ti++) {
        if (curTeams[ti].first == val) {
            chosen = ti;
            break;
        }
    }
    return chosen;
}

int TeamFormation::pickTeams() {
    std::sort(skills.begin(), skills.end());

    vector<pair<Elem, int>> curTeams;

    for (int si=0; si<skills.size(); si++) {

        //try to find smallest team to attach this to
        int teamIndex = findTeamEndingIn(curTeams, skills[si] - 1);

        if (teamIndex == -1) {
            //need to create new team
            pair<Elem, int> newteam(skills[si], 1);
            curTeams.push_back(newteam);
        } else {
            curTeams[teamIndex] = make_pair(skills[si], curTeams[teamIndex].second + 1);
        }

        std::sort(curTeams.begin(), curTeams.end(), [] (const pair<Elem, int>& lhs, const pair<Elem, int>& rhs) -> bool {
            if (lhs.first != rhs.first) { //for different endings, sort descending on value
                return (lhs.first > rhs.first);
            } else {                      //for same endings, sort ascending on lengths
                return (lhs.second < rhs.second);
            }
        });

        //move teams with index other than this and prev to finalized teams
        int ctr=0;
        for (int i=0; i<curTeams.size(); i++) {
            if (curTeams[i].first < skills[si] - 1) { //only this and prev allowed to remain
                teams.push_back(curTeams[i]);
            } else {
                ctr++;
            }
        }
        curTeams.erase(curTeams.begin() + ctr, curTeams.end());
    }

    teams.insert(teams.end(), curTeams.begin(), curTeams.end());

    int minsize = std::numeric_limits<int>::max();

    for (int i=0; i<teams.size(); i++) {
        if (teams[i].second < minsize) {
            minsize = teams[i].second;
        }
    }

    return (teams.size() == 0 ? 0 : minsize);
}

int main() {
    int tc; std::cin >> tc;
    for (int i=0; i<tc; i++) {
        TeamFormation tf;
        int ans = tf.pickTeams();
        std::cout << ans << std::endl;
    }
}
