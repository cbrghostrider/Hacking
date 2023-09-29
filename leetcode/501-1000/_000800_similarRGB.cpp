class Solution {
    unordered_map<char, int> char_to_wt = {
        {'0', 0},  {'1', 1},  {'2', 2},  {'3', 3},
        {'4', 4},  {'5', 5},  {'6', 6},  {'7', 7},
        {'8', 8},  {'9', 9},  {'a', 10}, {'b', 11},
        {'c', 12}, {'d', 13}, {'e', 14}, {'f', 15}
    };
    vector<char> wt_to_char = {
        '0', '1', '2', '3', '4', '5', '6', '7', 
        '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
    };
    
    int toDecimal(string comp) {
        int ret = (char_to_wt[comp[0]] * 16 + char_to_wt[comp[1]]);
        return ret;
    }
    
    string getClosest(string comp) {
        if (comp[0] == comp[1]) return comp;
        string cand1, cand2;
        if (char_to_wt[comp[0]] < char_to_wt[comp[1]]) {
            cand1 = {comp[0], comp[0]};
            char ch = wt_to_char[char_to_wt[comp[0]] + 1];
            cand2 = {ch, ch};
        } else {
            cand2 = {comp[0], comp[0]};
            char ch = wt_to_char[char_to_wt[comp[0]] - 1];
            cand1 = {ch, ch};
        }
        int diff1 = std::abs(toDecimal(comp) - toDecimal(cand1));
        int diff2 = std::abs(toDecimal(comp) - toDecimal(cand2));
        if (diff1 < diff2) return cand1;
        return cand2;
    }
    
public:
    string similarRGB(string color) {
        return "#" + getClosest(color.substr(1, 2)) + getClosest(color.substr(3, 2)) + 
                     getClosest(color.substr(5, 2));
    }
};
