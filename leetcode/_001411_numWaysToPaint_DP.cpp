class Solution {
    enum Color {
        RED=0,
        YELLOW=1,
        GREEN=2
    };        
    
    const int MODULO=1000000007;
    
    void add(int& lhs, const int rhs) {
        lhs += rhs;
        lhs %= MODULO;
    }
public:
    int numOfWays(int n) {
        // vector<Info> dp(n, Info());
        
        vector<vector<vector<int>>> ways, new_ways, cleared;
        cleared = new_ways = ways = vector<vector<vector<int>>>(3, vector<vector<int>>(3, vector<int>(3, 0)));
        
        // Base case.
        ways[0][1][0] = 1; ways[1][0][1] = 1; ways[2][0][1] = 1;
        ways[0][1][2] = 1; ways[1][0][2] = 1; ways[2][0][2] = 1;
        ways[0][2][0] = 1; ways[1][2][0] = 1; ways[2][1][0] = 1;
        ways[0][2][1] = 1; ways[1][2][1] = 1; ways[2][1][2] = 1;
        
        // DP.
        for (int i=1; i<n; i++) {
            
            // c0, c1, c2 stand for current cell positions 0, 1, 2
            // p0, p1, p2 stand for prev cell positions 0, 1, 2
            
            for (int c0=RED; c0<=GREEN; c0++) {
                for (int c1=RED; c1<=GREEN; c1++) {
                    if (c0 == c1) continue;
                    for (int c2=RED; c2<=GREEN; c2++) {
                        if (c1 == c2) continue;
                        
                        for (int p0=RED; p0<=GREEN; p0++) {
                            for (int p1=RED; p1<=GREEN; p1++) {
                                if (p0 == p1) continue;
                                for (int p2=RED; p2<=GREEN; p2++) {
                                    if (p1 == p2) continue;
                                    
                                    if (c0 == p0 || c1 == p1 || c2 == p2) continue;
                                    add(new_ways[c0][c1][c2], ways[p0][p1][p2]);
                                }
                            }
                        }                        
                    }
                }
            }
            ways = new_ways;
            new_ways = cleared;
        }
        
        int ans=0;
        for (int c0=RED; c0<=GREEN; c0++) {
            for (int c1=RED; c1<=GREEN; c1++) {
                if (c0 == c1) continue;
                for (int c2=RED; c2<=GREEN; c2++) {
                    if (c1 == c2) continue;        
                    ans += ways[c0][c1][c2];
                    ans %= MODULO;
                }
            }
        }
        return ans;
        
    }
};
