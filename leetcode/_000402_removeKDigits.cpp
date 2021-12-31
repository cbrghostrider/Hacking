// Initially move from MSB to LSB
// if ith digit is bigger than i-1th digit, then scan backwards and remove
// as many digits as possible (mark them as removed)
//
// after this is done, continue scanning original number until you get to the end
// removing as needed
// try to remove k such digits, if so done.
//
// If not, if you reach the end, then it means number is now in ascending digit order
// so the biggest digits are at the LSB positions
// just remove remaining LSB positions as needed.
//
// Finally check for leading zeros and adjust.
class Solution {
public:
    string removeKdigits(string num, int k) {
        
        if (k >= num.size()) return "0";
        
        unordered_set<int> remove;
        
        int s_ptr=0, sentinel=-1;
        for (int i=0; i<num.size()-1; i++) {
            if (num[i] < num[i+1]) continue;
            
            int s_ptr=i+1, e_ptr=i;
            while (k>0 && e_ptr>sentinel) {
                if (remove.find(e_ptr) != remove.end()) {
                    e_ptr--;
                } else if (num[e_ptr] > num[s_ptr]) {
                   remove.insert(e_ptr);
                   e_ptr--;
                   k--;
                } else {
                    break;
                }
            }
            if (k == 0) {break;}
            // sentinel = s_ptr;
        }
        

        // Handle entirely ascending number with non-zero k.
        string ans;
        for (int i=0;i<num.size(); i++) {
            if (remove.find(i) != remove.end()) continue;
            ans.push_back(num[i]);
        }
        if (k != 0) {
            ans = ans.substr(0, ans.size()-k);
        }
        
        // remove leading zeros
        string ret;
        bool found_non_zero=false;
        for (char ch: ans) {
            if (ch != '0') { found_non_zero = true; }
            if (found_non_zero) {
                ret.push_back(ch);
            }
        }
        if (ret == "") ret = "0";
        return ret;
    }
};
