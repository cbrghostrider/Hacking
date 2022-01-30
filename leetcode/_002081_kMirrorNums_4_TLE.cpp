class Solution {
    vector<int> baseKNum(long long num, int k) {
        vector<int> ans;
        while (num) {
            int rem = num%k;
            num /= k;
            ans.push_back(rem);
        }
        return ans;
    } 
    
    bool isSymmetric(const vector<int>& digits) {
        if (digits.empty()) return true;
        int left=0, right=digits.size()-1;
        while (left < right) {
            if (digits[left] != digits[right]) return false;
            left++; right--;
        }
        return true;
    }
    
    // Generates base-10 symmetric numbers.
    class Generator10 {
      public:
        Generator10() {
            generated = {{1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}};            
        }
        
        long long next() {
            if (s_ptr >= generated.size()) {                
                populateSurplus();
            }
            long long ret = 0;
            if (single_digit_nums.size() > 0) {                
                ret = single_digit_nums.back();
                single_digit_nums.pop_back();
                if (single_digit_nums.size() == 0) {s_ptr = generated.size();}
            } else {
                ret = addReverse(generated[s_ptr++]);
            }
            return ret;
        }
      private:
        
        // squishes all the digits into one big number
        long long squish(const vector<int>& num) {
            long long ret=0;
            for (int i=0; i<num.size(); i++) {
                ret *= 10;
                ret += num[i];
            }
            return ret;
        }
        
        long long addReverse(vector<int>& gen) {        
            long long ret;
            int limit = !expansion_phase ? gen.size()-2 : gen.size()-1;
            for (int i=limit; i>=0; i--) {
                gen.push_back(gen[i]);
            }
            ret = squish(gen);
            limit += !expansion_phase ? 2 : 1;                
            gen.erase(gen.begin()+limit, gen.end());
            return ret;
        }
        
        void expand() {
            vector<vector<int>> new_generated;
            for (vector<int>& num : generated) {                                
                // num will expand to 10 new numbers
                vector<vector<int>> expansions;
                for (int d=0; d<=9; d++) {
                    num.push_back(d);
                    expansions.push_back(num);
                    num.pop_back();
                }
                new_generated.insert(new_generated.end(), expansions.begin(), expansions.end());
            }
            std::swap(generated, new_generated);
            new_generated.clear();
        }
                
        void populateSurplus() {
            if (expansion_phase) {expand();}            
            expansion_phase = !expansion_phase;
            s_ptr=0;
        }
        
        // Base-10 mirror numbers are handed out from here, 
        // as long as they are available.                        
        // We store them as partial numbers, in chain format (digit by digit).
        // Also used to generate new surplus numbers.
        vector<vector<int>> generated;
        int s_ptr=0;
        vector<long long> single_digit_nums = {9,8,7,6,5,4,3,2,1};
        
        // If we are not in expansion phase, 
        //    Then generated numbers will have their reversed digits added at the end.
        // If we are in expansion phase,
        //    We will add digits 0..9 at the end of each generated num.
        //    Then we will reverse digits from the digits before the ones just added.
        bool expansion_phase=false;        
    };              
    
public:
    // Using a generator for Base-10, so we only check already base-10 numbers.
    long long kMirror(int k, int n) {
        int count=0;
        long long sum=0;
        Generator10 generator;
        while (count < n) {
            long long num = generator.next();            
            vector<int> baseK = baseKNum(num, k);
            if (isSymmetric(baseK)) {
                sum += num;
                count++;
            }            
        }
        return sum;
    }  
};
