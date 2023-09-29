class Solution {    
    // Subproblems for free!!!!!
    //
    // We populate additional answers into the cache for each sub-problem solved.
    // If s[left, right] is a k-palindrome 
    //    then it is definitely also a p-palindrome for k <= p <= k_limit
    // If s[left, right] is NOT a k-palindrome
    //    then it is definitely also NOT a p-palindrome for 0 <= p <= k
    
    using BigKey=uint32_t;
    using SmallKey=uint32_t;
    
    // memoization cache
    unordered_map<BigKey, bool> cache;
    
    // any k val greater than stored "value" should return true.
    unordered_map<SmallKey, int> cache_true;
    
    // any k val lesser than stored "value" should return false.
    unordered_map<SmallKey, int> cache_false;
    
    // creates a memoization key for the subproblem
    BigKey signature(int left, int right, int k) {
        uint32_t ret = ((left << 20) | (right << 10) | (k));
        return ret;
    }
    
    SmallKey signatureLR(int left, int right) {
        uint32_t ret = ((left << 20) | (right << 10));
        return ret;        
    }
    
    // returns true if there's a cache hit
    // Note that either of the 3 caches may provide an answer!
    // If cache hit, then answer is in "ans"
    bool checkCache(int left, int right, int k, bool& ans) {
        BigKey bkey = signature(left, right, k);
        SmallKey skey = signatureLR(left, right);
        if (cache.find(bkey) != cache.end()) {
            ans = cache[bkey];
            return true;
        }
        if (cache_true.find(skey) != cache_true.end() && k >= cache_true[skey]) {
            ans = true;
            return true;
        }
        if (cache_false.find(skey) != cache_false.end() && k <= cache_false[skey]) {
            ans = false;
            return true;
        }
        return false;
    }
    

    void populateCache(int left, int right, int k, bool ans) {
        BigKey bkey = signature(left, right, k);
        SmallKey skey = signatureLR(left, right);
        cache[bkey] = ans;
        if (ans) {
            // populate cache_true (only if we have a better ans than a possibly already existing one)
            if (cache_true.find(skey) == cache_true.end() || cache_true[skey] > k) {
                cache_true[skey] = k;
            }
        } else {
            // populate cache_false (only if we have a better ans than a possibly already existing one)
            if (cache_false.find(skey) == cache_false.end() || cache_false[skey] < k) {
                cache_false[skey] = k;
            }            
        }
    }
    
    bool isPalin(const string& s, int left, int right) {
        if (left >= right) return true;
        
        while (left < right) {
            if (s[left] != s[right]) return false;
            left++;
            right--;
        }
        return true;
    }
    
    // Is s, a valid k-palindrome between [left, right] inclusive.
    bool isValid(const string& s, int left, int right, int k) {
        if (left >= right) {
            populateCache(left, right, k, true);
            return true;
        }
        
        bool ans=false;
        if (checkCache(left, right, k, ans)) {
            return ans;
        }
        
        if (k == 0) {
            ans = isPalin(s, left, right);
            populateCache(left, right, k, ans);
            return ans;
        }
                
        if (s[left] == s[right]) {
            ans = isValid(s, left+1, right-1, k);
        } else {
            // drop left
            bool choice1 = isValid(s, left+1, right, k-1);
            // or drop right
            bool choice2 = isValid(s, left, right-1, k-1);
            
            ans = choice1 || choice2;
        }
        
        populateCache(left, right, k, ans);        
        return ans;
    }
    
public:
    // Tremendous progress, with subproblems for free!!
    // 43/51 tests pass now, rest TLE.
    bool isValidPalindrome(string s, int k) {        
        bool ans = isValid(s, 0, s.size()-1, k);
        return ans;
    }
};
