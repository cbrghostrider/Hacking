// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <cstdio>
#include <limits>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;
//code prior to this was auto-gen by online judge
/* Head ends here */

int pairs(vector <int> a,int k) {
    unordered_set<int> nums;
    for (int& num : a) nums.insert(num);
    int ans = 0;
    for (int& check : a) {
        auto it = nums.find(k+check);
        if (it != nums.end()) ans++;
    }
    return ans;
}

/* Tail starts here */
//code after this was auto-gen by online judge
int main() {
    int res;
    
    int _a_size,_k;
    cin >> _a_size>>_k;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    vector<int> _a;
    int _a_item;
    for(int _a_i=0; _a_i<_a_size; _a_i++) {
        cin >> _a_item;
        _a.push_back(_a_item);
    }
    
    res = pairs(_a,_k);
    cout << res;
    
    return 0;
}
