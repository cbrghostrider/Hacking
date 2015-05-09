class Solution {
    typedef pair<int, int> t_ACCNMAX; //(accumulator, maximum-so-far)
public:
    int trap(vector<int>& height) {
        if (height.size() == 0 || height.size() == 1) return 0;
        
        int max = std::accumulate(height.begin(), height.end(), std::numeric_limits<int>::min(), 
            [] (const int& acc, const int& val) -> int {
            return (acc > val ? acc : val);
        });
        auto maxrit = std::find(height.rbegin(), height.rend(), max);
        auto maxfit = (maxrit + 1).base();
        
        std::function<t_ACCNMAX (t_ACCNMAX, int)> foldFunc = [] (t_ACCNMAX summaxht, int ht) -> t_ACCNMAX {
            int maxht   = summaxht.second;
            int sumsofar= summaxht.first;
            int newsum = maxht > ht ? (maxht - ht) : 0;
            return make_pair(sumsofar + newsum, ht > maxht ? ht : maxht);
        };
        
        t_ACCNMAX accumulator = make_pair(0, 0);
        t_ACCNMAX lhsMono = std::accumulate(height.begin(),  maxfit, accumulator, foldFunc);
        t_ACCNMAX rhsMono = std::accumulate(height.rbegin(), maxrit, accumulator, foldFunc);
        
        return (lhsMono.first + rhsMono.first);
    }
};
