class Solution {
    class GridIterator {
      public:
        GridIterator(const vector<vector<int>>& nums) 
            : vals(nums), R(nums.size()) {
                for (const auto& v : vals) {
                    remainder += v.size();
                    C = std::max(C, int(v.size()));
                }
            }
        
        bool hasNext() const {return (remainder > 0);}
        
        int next() {
            if (!hasNext()) return -1;
            int ret = vals[r][c];
            remainder--;
            if (remainder) {
                do {
                    forward();
                }while (!isValid());
            }
            return ret;
        }
        
      private:    
        bool isValid() const {return (r < R && c < vals[r].size());}
        
        // Moves the iterator forward to the next valid position.
        void forward() {
            int& cr=c; int& rr=r; int& remr=remainder;
            if (C >= R && c == C-1) {
                c = C-R + r+1;
                r = R-1;                            
            } else if (C >= R && r == 0) {
                if (c < R-1) { r = c+1; c = 0; }
                else { c = c-R+2 ; r = R-1;}
            } else if (R >= C && r == 0) {
                r = c + 1;
                c = 0;
            } else if (R >= C && c == C-1) {                
                if (C + r < R) { c = 0; r = C + r; }
                else {c = C-(R-r)+1; r = R-1;}
            } else {
                r -= 1;
                c += 1;
            }
        }                
      
        const vector<vector<int>>& vals;
        const int R;
        int C=0;
        int r=0, c=0;     // stores next value to be provided
        int remainder=0;  // how many can still be provided
    };
public:
    //
    // This solution is functionally correct... but...
    //
    // The problem with this solution is that it generates "many" coordinates,
    // a bunch of which are invalid (and it re-generates them to avoid those).
    // This is why it gets TLE for some inputs.
    //
    // It would be better to prune the search space to *not* generate invalid
    // coordinates at all.
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        GridIterator iter(nums);
        vector<int> ans;
        while (iter.hasNext()) {
            ans.push_back(iter.next());
        }
        return ans;
    }
};
