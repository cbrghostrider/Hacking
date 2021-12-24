class Solution {
public:
    // Algorithm is functionally correct, but gets TLE.
    // But this will be slow for large n values, because:
    // 1. The min heap will grow too large too quickly.
    // 2. We need to maintain a hash table to eliminate dups. 
    //    It would be better to not create dups in the first place.
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        
        std::priority_queue<int, vector<int>, std::greater<int>> mh;
        mh.push(1);
        int counter=0;
        
        unordered_set<int> gone;
        
        while (!mh.empty()) {
            int num=mh.top(); mh.pop();

	    // Should optimize it so we don't get dups in the first place.
            if (gone.find(num) != gone.end()) continue;

            gone.insert(num);
            counter++;
            if (n == counter) return num;
            
            for (int i=0; i<primes.size(); i++) {
		long val = (primes[i] * (long)num);
	        // throw away sequence values that don't fit in int... 
	        // yeah, a bit lame, we should optimize it so we don't generate these
	        // in the first place.
                if (val >= std::numeric_limits<int>::max()) { continue; }
		// throw away dups again... lame
                if (gone.find(val) != gone.end()) {continue;}
                mh.push(val);
            }
        }
        return -1;  // should not get here.
    }
};
