class Solution {
    // sorts num (0 can't come first), 
    // finds smallest val in num
    // appends that to the end of the sorted num
    // returns this overall val    
    // e.g. ret val: 10234560 or 12345671
    string increaseSizeAndMin(string num) {        
        if (num.size() == 1) return num+num;
        
        std::sort(num.begin(), num.end(), std::less<char>());        
        char msb = num[0];
        if (msb == '0') {
            std::swap(num[0], num[1]);
        }
        num += string(1, msb);
        return num;
    }
    
    // Moves the least digit greater than MSB digit to MSB
    // sorts the rest in ascending order and appends after MSB
    string nextGreater(string num) {
        std::reverse(num.begin(), num.end());
        char msb = num[num.size()-1];
        char chosen_index=-1;
        for (int i=num.size()-2; i>=0; i--) {
            if (num[i] > msb) {
                if (chosen_index == -1) {
                    chosen_index = i;
                } else if (num[i] < num[chosen_index]) {
                    chosen_index = i;
                }
            }
        }        
        char chosen = num[chosen_index];
        num[chosen_index] = msb;
        num.erase(num.size()-1);
        std::sort(num.begin(), num.end(), std::less<char>());
        num = std::string(1, chosen) + num;
        return num;
    }
    
    // If num can be represented in 32 bits, returns it
    // else returns -1
    int changeToNum(string num) {
        const string largest = "2147483647";
        if (num.size() < largest.size()) {
            return std::stoi(num);
        }
        if (num.size() > largest.size()) return -1;
        for (int i=0; i<num.size(); i++) {
            if (largest[i] < num[i]) return -1;
            if (largest[i] > num[i]) break;
        }
        return std::stoi(num);
    }
    
public:
    int nextGreaterElement(int n) {        
        string num = to_string(n);  // Note: MSB is at index 0!
        string ng;
        // std::reverse(num.begin(), num.end());
        
        int i=num.size()-2;
        for (; i>=0; i--) {
            if (num[i] >= num[i+1]) {continue;}
            ng = nextGreater(num.substr(i));
            if (i != 0) {
                ng = num.substr(0, i) + ng;
            }
            break;
        }
        
        if (i == -1) {
            // Don't need this, as we want exactly same #digits in ans... d'oh...
            // ng = increaseSizeAndMin(num);            
            return -1;
        }
        
        return changeToNum(ng);
    }
};
