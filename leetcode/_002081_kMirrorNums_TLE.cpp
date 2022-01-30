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
            for (int d=1; d<=9; d++) {
                surplus.push(d);
            }
        }
        long long next() {
            if (surplus.empty()) {
                digits++;
                populateSurplus(digits);
            }
            long long ret = surplus.front(); surplus.pop();
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
        
        queue<long long> generate(vector<vector<int>>& so_far, int on_digit, int num_digits) {
            queue<long long> ret;
            if (so_far.empty() || on_digit == 0) {
                // cannot start with 0
                vector<vector<int>> vvsf = {{1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}};
                return generate(vvsf, on_digit+1, num_digits);
            }

            int mid = num_digits/2;
            bool odd_digits = num_digits % 2 != 0;
            if ((odd_digits && on_digit > mid) || (!odd_digits && on_digit >= mid) ){                
                for (vector<int>& num : so_far) {
                    int copy_from_index = num_digits % 2 == 0 ? num.size()-1 : num.size()-2;
                    for (int i=copy_from_index; i>=0; i--) {
                        num.push_back(num[i]);
                    }
                    long long nsquished = squish(num);
                    ret.push(nsquished);
                }
                return ret;
            }
            
            vector<vector<int>> recurse;
            for (vector<int> sub_num : so_far) {
                for (int d=0; d<=9; d++) {
                    sub_num.push_back(d);
                    recurse.push_back(sub_num);
                    sub_num.pop_back();
                }
            }
            return generate(recurse, on_digit+1, num_digits);
        }
        
        // populates surplus with num_digits symmetric base 10 numbers
        void populateSurplus(int num_digits) {
            auto& qqq = surplus;
            vector<vector<int>> seed;
            surplus = generate(seed, 0, num_digits);
            int l = qqq.front();
        }
        
        // Numbers are handed out from here, as long as they are available.
        queue<long long> surplus;
        
        // Up to "digits" digit numbers have been generated
        int digits=1;
    };
    
    // Using a better base-10 number generator
    class BetterGenerator10 {
      public:
        BetterGenerator10() {
            for (int d=1; d<=9; d++) {
                surplus.push(d);
            }
            surplus.push(11); surplus.push(22); surplus.push(33); surplus.push(44); surplus.push(55);
            surplus.push(66); surplus.push(77); surplus.push(88); surplus.push(99);
            
            last_surplus = {
                {1,1}, {2,2}, {3,3}, {4,4}, {5,5}, {6,6}, {7,7}, {8,8}, {9,9}
            };
        }
        long long next() {
            if (surplus.empty()) {                
                populateSurplus();
            }
            long long ret = surplus.front(); surplus.pop();
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
        
        // populates surplus with num_digits symmetric base 10 numbers
        void populateSurplus() {
            auto& qqq = surplus; auto& np = next_pos;
            vector<vector<int>> new_surplus;
            if (!processing_new) {
                for (const vector<int>& num : last_surplus) {
                    new_surplus.push_back({});
                    for (int i=0; i<next_pos; i++) {
                        new_surplus.back().push_back(num[i]);
                    }
                    // At next_pos, just duplicate the prev digit
                    new_surplus.back().push_back(num[next_pos-1]);
                    for (int i=next_pos; i<num.size(); i++) {
                        new_surplus.back().push_back(num[i]);
                    }
                }
            } else {
                for (const vector<int>& num : last_surplus) {
                    vector<int> new_num;
                    new_num.insert(new_num.end(), num.begin(), num.begin()+next_pos);
                    
                    // new_num will expand to 10 new numbers
                    vector<vector<int>> expansions;
                    for (int d=0; d<=9; d++) {
                        new_num.push_back(d);
                        expansions.push_back(new_num);
                        new_num.pop_back();
                    }
                    
                    for (vector<int>& ex : expansions) {
                        ex.insert(ex.end(), num.begin()+next_pos, num.end());
                    }
                    new_surplus.insert(new_surplus.end(), expansions.begin(), expansions.end());
                }
            }
            
            std::swap(last_surplus, new_surplus);
            new_surplus.clear();
            for (const vector<int>& num : last_surplus) {
                surplus.push(squish(num));
            }            
            if (processing_new) {
                next_pos++;
            }
            processing_new = !processing_new;
        }
        
        // Numbers are handed out from here, as long as they are available.
        queue<long long> surplus;
        vector<vector<int>> last_surplus;
        
        // The next position to generate.
        // Digits will be "shoved" into this position, per number, for each number in last_surplus.
        // if odd, the digits will be generated from 0-9
        // if even, the digit at the prev position is repeated
        // used along with processing_new
        int next_pos=1;
        // do we "shove" entirely new digits, or just duplicate
        bool processing_new = true; 
    };
    
public:
    // Using a better generator for Base-10, so we only check already base-10 numbers.
    long long kMirror_3(int k, int n) {
        int count=0;
        long long sum=0;
        BetterGenerator10 generator;
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
    
    // Brute force.
    long long kMirror_1(int k, int n) {
        int count=0;
        long long sum=0;
        long long num=1;
        while (count < n) {
            vector<int> base10 = baseKNum(num, 10);
            vector<int> baseK = baseKNum(num, k);
            if (isSymmetric(base10) && isSymmetric(baseK)) {
                sum += num;
                count++;
            }
            num++;
        }
        return sum;
    }
};
