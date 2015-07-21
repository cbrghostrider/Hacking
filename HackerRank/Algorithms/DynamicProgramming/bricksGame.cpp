// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>

using std::pair;
using std::make_pair;
using std::vector;

typedef unsigned long long Brick;

typedef pair<Brick, int> Choice; //(Score, #bricks picked)

class BricksGame {
public:
    BricksGame();
    Brick computeScore();
private:
    void readInput();
    void playGame();
    vector<Brick> bricks;
    vector<Choice> choices;
};

BricksGame::BricksGame()
: bricks() {
    readInput();
}

void BricksGame::readInput() {
    int n; std::cin >> n;
    bricks.reserve(n);
    for (int i=0; i<n; i++) {
        Brick brick; std::cin >> brick;
        bricks.push_back(brick);
    }

    //0-index is bottom of bricks stack
    std::reverse(bricks.begin(), bricks.end());

    choices = vector<Choice>(n+1, make_pair(0, 0));
}

void BricksGame::playGame() {
    //base cases
    if (bricks.size() > 0) choices[1] = make_pair(bricks[0], 1);
    if (bricks.size() > 1) choices[2] = make_pair(choices[1].first + bricks[1], 2);
    if (bricks.size() > 2) choices[3] = make_pair(choices[2].first + bricks[2], 3);

    for (int i=3; i<bricks.size(); i++) {
        //candidate 1: pick 1 brick
        Choice choice1 = make_pair(bricks[i] + choices[i - choices[i].second].first, 1);

        //candidate 2: pick 2 bricks
        Choice choice2 = make_pair(bricks[i] + bricks[i-1] + choices[i - 1 - choices[i-1].second].first, 2);

        //candidate 3: pick 3 bricks
        Choice choice3 = make_pair(bricks[i] + bricks[i-1] + bricks[i-2] + choices[i - 2 - choices[i-2].second].first, 3);

        vector<Choice> localChoices = {choice1, choice2, choice3};
        std::sort(localChoices.begin(), localChoices.end(), [] (const Choice& lhs, const Choice& rhs) -> bool {
            return (lhs.first > rhs.first);
        });

        choices[i+1] = localChoices[0];
    }
}

Brick BricksGame::computeScore() {
    playGame();

    return choices[bricks.size()].first;
}


int main() {
    int tc; std::cin >> tc;
    for (int i=0; i<tc; i++) {
        BricksGame bg;
        Brick ans = bg.computeScore();
        std::cout << ans << std::endl;
    }
}
