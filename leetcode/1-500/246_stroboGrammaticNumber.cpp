// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    //0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    unordered_map<char, pair<bool, char>> strobos;
    void populateStrobos() {
        strobos.insert(make_pair('0', make_pair(true,  '0')));
        strobos.insert(make_pair('1', make_pair(true,  '1')));
        strobos.insert(make_pair('2', make_pair(false, '-')));
        strobos.insert(make_pair('3', make_pair(false, '-')));
        strobos.insert(make_pair('4', make_pair(false, '-')));
        strobos.insert(make_pair('5', make_pair(false, '-')));
        strobos.insert(make_pair('6', make_pair(true,  '9')));
        strobos.insert(make_pair('7', make_pair(false, '-')));
        strobos.insert(make_pair('8', make_pair(true,  '8')));
        strobos.insert(make_pair('9', make_pair(true,  '6')));
    }
public:
  
    bool isStrobogrammatic(string num) {
        if (num.size() <= 0) return true; //??
        populateStrobos();
        
        string rev = num;
        std::reverse(rev.begin(), rev.end());
        const int N = num.length();
        
        for (int i=0; i<(N/2 + N%2); i++) {
            auto it = strobos.find(num[i]);
            if (it == strobos.end()) return false; //non numeric char
            if (it->second.first == false) return false; //not strobo
            if (it->second.second != rev[i]) return false;
        }
        return true;
    }
};
