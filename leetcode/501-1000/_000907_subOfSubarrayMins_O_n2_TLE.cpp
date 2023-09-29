class Solution {
    struct Interval {
        int start=0;  // index
        int end=0;    // index
        
        bool operator<(const Interval& rhs) const {
            if (start != rhs.start) return start < rhs.start;
            return false;
        }
    };
    struct Info {
        int val=0;
        int index=0;
    };
    
public:
    // This one is also O(n^2) alas...
    // Functionally correct, but TLE.
    int sumSubarrayMins_(vector<int>& arr) {
        vector<Info> infos;
        for (int i=0; i<arr.size(); i++) {
            infos.push_back({arr[i], i});
        }
        std::sort(infos.begin(), infos.end(), [](const Info& lhs, const Info& rhs) -> bool {
            if (lhs.val != rhs.val) {return lhs.val < rhs.val;}
            return lhs.index < rhs.index;
        });
        
        set<Interval> iset;
        iset.insert({0, (int)(arr.size())-1});
        int msum = 0;        
        
        for (const Info& info : infos) {
            
            // 
            // If I could directly access the root of the underlying RB tree, 
            // I might be able to find the right interval in O(log n) time.
            // 
            // Unfortunately right now it still takes O(n) time by
            // iterating thorough the entire set in order...
            //
            auto it = iset.begin();
            for (; it != iset.end(); it++) {
                if (it->start <= info.index && it->end >= info.index) {
                    break;
                }
            }            
            
            Interval interval = *it;
            iset.erase(it);
            
            int lhs_num = info.index-interval.start;
            int rhs_num = interval.end-info.index;
            
            msum += info.val;  // for the solo set
            msum %= 1000000007;
            msum += info.val * lhs_num;  // for each subset on the lhs
            msum %= 1000000007;
            msum += info.val * rhs_num;  // for each subset on the rhs
            msum %= 1000000007;
            msum += info.val * lhs_num * rhs_num;  // for cross subsets
            msum %= 1000000007;
            
            if (lhs_num > 0) {                
                iset.insert({interval.start, info.index-1});
            }
            if (rhs_num > 0) {
                iset.insert({info.index+1, interval.end});
            }
        }
        
        return msum;
    }
    
    // O(n^2) time, O(n) space.
    // Functionally correct, but TLE.
    int sumSubarrayMins(vector<int>& arr) {
        vector<int> mins(arr.size(), 0);
        
        int msum=0;
        
        for (int i=0; i<arr.size(); i++) {
            msum += arr[i];
            msum %= 1000000007;
            
            for (int j=0; j<i; j++) {
                mins[j] = std::min(mins[j], arr[i]);
                msum += mins[j];                
                msum %= 1000000007;
            }     
            
            mins[i] = arr[i];
        }
        
        return msum;
    }
    
};
