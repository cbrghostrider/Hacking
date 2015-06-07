// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// O(mn) time and O(mn) space
// Dynamic Programming

class Solution {
    int** health_;
    
    //what is the minimum health knight should have while entering this cell
    int computeIncomingHealthCell_(vector<vector<int> >& dungeon, unsigned int x, unsigned int y, int outgoing_health) {
        int computedVal;
        if (dungeon[y][x] <= 0) {
            computedVal = abs(dungeon[y][x]) + outgoing_health; //still alive after losing health
        } else if (outgoing_health > dungeon[y][x]) {
            computedVal = outgoing_health - dungeon[y][x];      //knight gains appropriate health here
        } else {
            computedVal = 1;                                    //he has to be alive when he enters
        }
        return computedVal;
    }
    
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        if (dungeon.size() == 0 || dungeon[0].size() == 0) return 1; //undefined problem
        int limity = dungeon.size();
        int limitx = dungeon[0].size();
        
        //dynamic programming cache
        health_ = new int*[limity];
        for (int i=0; i<limity; i++) {
            health_[i] = new int[limitx];
        }
        
        //at princess cell, ultimate outgoing health should be 1 at least
        health_[limity - 1][limitx - 1] = computeIncomingHealthCell_(dungeon, limitx - 1, limity - 1, 1);
        for (int y=limity-1; y>=0; y--) {
            for (int x=limitx-1; x>=0; x--) {
                if (y == (limity - 1) && x == (limitx - 1)) continue; //skip princess 
                int ihcand1 = std::numeric_limits<int>::max();
                int ihcand2 = std::numeric_limits<int>::max();
                if (x != (limitx - 1)) { //rhs exists
                    ihcand1 = computeIncomingHealthCell_(dungeon, x, y, health_[y][x+1]);
                }
                if (y != (limity - 1)) { //bottom exists
                    ihcand2 = computeIncomingHealthCell_(dungeon, x, y, health_[y+1][x]);
                }
                health_[y][x] = (ihcand1 < ihcand2) ? ihcand1 : ihcand2;
            }
        }
        int retval = health_[0][0]; //knight is at (0, 0)

	//free cache
	for (int i=0; i<limity; i++) {
	    delete [] health_[i];
	}
	delete [] health_;

	return retval;
    }
};
