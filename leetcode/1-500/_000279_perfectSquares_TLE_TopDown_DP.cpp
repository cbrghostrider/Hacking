class Solution {
    vector<int> perfect_squares;
    
    // (sig, least num)
    unordered_map<int, int> cache;
    
    void genSquares(int n) {
        int i=1;
        do {
            perfect_squares.push_back(i*i);
            i++;
        } while (i*i <= n);        
    }
    
    int signature(int index, int val) {
        return ((index << 16) | (val));
    }
    
    // considering numbers from indices [0...index] in perfect_squares
    // what are the least number that sum to val
    int leastNum(int index, int val) {
        int sig = signature(index, val);
        if (cache.find(sig) != cache.end()) return cache[sig];
        if (index == 0) {cache[sig] = val; return val;}
        
        int least=std::numeric_limits<int>::max();
        int div = val / perfect_squares[index];
        
        // Try all combos from taking 0 to div values of perfect_squares[index]
        for (int count=0; count <= div; count++) {
            int consumed = count * perfect_squares[index];
            int new_val = val - consumed;
            int recurse = leastNum(index - 1, new_val);
            int my_least = count + recurse;
            if (my_least < least) {least = my_least;}
        }
        
        cache[sig] = least;
        return cache[sig];
    }
    
public:
    int numSquares(int n) {        
        genSquares(n);
        int num = leastNum(perfect_squares.size()-1, n);
        return num;
    }
};
