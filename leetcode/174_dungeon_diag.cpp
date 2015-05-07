//O(mn) time and O(min(m, n)) space
//
// imagine diagonal lines going through the matrix, with positive slopes
// start with a diagonal line through the princess cell
// then move diagonal lines northwest, one at a time
// every iteration computes this diagonal, using the values from the previous diagonal only
// final iteration is the diagonal that goes through knight start, and computes final value
//
class Solution {
    typedef pair<int, int> Coord;

    //converting coord to unique key for lookup in hashtables
    long coordToLong_(Coord coord) {
        int x = coord.first;
        int y = coord.second;
        return (((long)x << 32) | (long)y);
    }
    
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
        
        //to keep track of coords computed in last iteration
        //read from old healthMap, write to new healthMap
        unordered_map<long, int> healthMap[2]; 
        int prev = 0; //old
        int next = 1; //new
        
        Coord princess = make_pair(limitx-1, limity-1);
        int ih = computeIncomingHealthCell_(dungeon, princess.first, princess.second, 1); //reach princess with minimum 1 health left.
        healthMap[prev].insert(make_pair(coordToLong_(princess), ih));
        
        int numIters = (limitx + limity - 1);
        int lessDim  = (limitx < limity) ? limitx : limity;
        for (int diag=1; diag < numIters; diag++) { //diag 0 was princess
            int rdiag  = numIters - 1 - diag; 
	    int delta  = (diag < (lessDim - 1)) ? diag : ((rdiag < (lessDim - 1)) ? rdiag : (lessDim - 1) );
            int xstart = (limitx - 1 - diag) < 0 ? 0 : (limitx - 1 - diag);
            int yend   = (limity - 1 - diag) < 0 ? 0 : (limity - 1 - diag);
            int xend   = xstart + delta;
            int ystart = yend + delta;
            for (int x = xstart, y = ystart; x <= xend && y >= yend; x++, y--) {
                Coord me  = make_pair(x, y);
                Coord rhs = make_pair(x+1, y); 
                Coord bot = make_pair(x, y+1);
                int ih = std::numeric_limits<int>::max();
                if (me.first  != (limitx - 1)) {
                    auto rhsit = healthMap[prev].find(coordToLong_(rhs));
                    int ohrhs = rhsit->second;
                    int ihcand1 = computeIncomingHealthCell_(dungeon, x, y, ohrhs);
                    if (ihcand1 < ih) ih = ihcand1; 
                }
                if (me.second != (limity - 1)) {
                    auto botit = healthMap[prev].find(coordToLong_(bot));
                    int ohbot = botit->second;
                    int ihcand2 = computeIncomingHealthCell_(dungeon, x, y, ohbot);
                    if (ihcand2 < ih) ih = ihcand2; 
                }
                healthMap[next].insert(make_pair(coordToLong_(me), ih));
            }
            healthMap[prev].clear();
            prev = 1 - prev;
            next = 1 - next;
        }
        
        Coord knight = make_pair(0, 0);
        auto kit = healthMap[prev].find(coordToLong_(knight));
        return kit->second;
    }
};

