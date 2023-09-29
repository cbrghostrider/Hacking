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
            generated = {0};
        }
        
        long long next() {     
            auto &ggg = generated;
            long long ret = 0;
            if (carry) {
                generated[0] = 1;                                
                if (expansion_phase) generated.push_back(0);
                expansion_phase = !expansion_phase;
            }              
            ret = addReverse(generated);
            carry = inc(generated);   
            if (ret == 0)  {ret = next();}
            return ret;
        }
      private:
        
        bool inc(vector<int>& gen) {
            bool carry = true;
            for (int i=gen.size()-1; i>=0; i--) {
                gen[i] = (carry ? 1 : 0) + gen[i];
                carry = gen[i]/10;
                gen[i] %= 10;
            }
            return carry;
        }
        
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
            if (limit < 0) return gen[0];
            for (int i=limit; i>=0; i--) {
                gen.push_back(gen[i]);
            }
            ret = squish(gen);
            limit += !expansion_phase ? 2 : 1;                
            gen.erase(gen.begin()+limit, gen.end());
            return ret;
        }        
        
        // Base-10 mirror numbers are handed out from here, 
        // as long as they are available.                        
        // We store them as partial numbers, in chain format (digit by digit).
        // Also used to generate new surplus numbers.
        vector<int> generated;  
        bool carry = false;
        
        // If we are not in expansion phase, 
        //    Then generated numbers will have their reversed digits added at the end.
        // If we are in expansion phase,
        //    We will add digits 0..9 at the end of each generated num.
        //    Then we will reverse digits from the digits before the ones just added.
        bool expansion_phase=false;   
        int expansion_digit=0;
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
