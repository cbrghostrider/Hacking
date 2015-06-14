// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef int Elem;

Elem computeContiguous(const vector<Elem>& nums) {
    if (nums.size() == 0) return 0; 
    
    //contiguous subarray that ends at index i
    vector<Elem> cache(nums.size(), 0);
    Elem maxval;
    maxval = cache[0] = nums[0];
    for (int i=1; i<nums.size(); i++) {
        Elem cand1 = cache[i-1] + nums[i];
        Elem cand2 = nums[i];
        cache[i] = cand1 > cand2 ? cand1 : cand2;
        if (cache[i] > maxval) maxval = cache[i];
    }
    
    return maxval;
}

Elem computeNonContiguous(vector<Elem>& nums) {
    if (nums.size() == 0) return 0;
    Elem sumPos = std::accumulate(nums.begin(), nums.end(), 0, [] (const Elem& acc, const Elem& n) -> Elem {
        return ((n > 0) ? acc+n : acc);
    });
    Elem max = std::accumulate(nums.begin(), nums.end(), std::numeric_limits<Elem>::min(), 
                               [] (const Elem& acc, const Elem& n) -> Elem {
        return ((n>acc) ? n:acc);
    });
    return (max < 0 ? max : sumPos);
}

int main() {
    int tc;
    std::cin >> tc;
    for (int i=0; i<tc; i++) {
        vector<Elem> nums;
        int n;
        std::cin >> n;
        for (int j=0; j<n; j++) {
            Elem num;
            std::cin >> num;
            nums.push_back(num);
        }
        Elem ansContiguous    = computeContiguous(nums);
        Elem ansNonContiguous = computeNonContiguous(nums);
        std::cout << ansContiguous << " " << ansNonContiguous << std::endl;
    }
    return 0;
}

