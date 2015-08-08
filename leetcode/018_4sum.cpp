// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <utility>

using std::unordered_map;
using std::unordered_set;
using std::pair;
using std::make_pair;
using std::vector;

typedef unsigned long long U64;
typedef pair<int, int> TwoNums; 
typedef unordered_set<U64> TwoCombos;
typedef unordered_map<int, TwoCombos> Bag; //(sum of 2 numbers, [vector of pairs of 2 numbers that add up to this sum])

class Solution {
private:
    Bag bag;
    unordered_map<int, int> freqs;

private:
    U64 makeKey(unsigned int m, unsigned int n) {
        return ((((U64)(m)) << 32) | ((U64) n));
    }

    TwoNums breakKey(U64 key) {
        TwoNums tn(0, 0);
        tn.first = (key >> 32);
        tn.second = key & (0x00000000FFFFFFFF);
        return tn;
    }

    void updateBag(int m, int n) {
        int sum = m+n;
        auto fit = bag.find(sum);
        if (fit == bag.end()) { 
            TwoCombos tc;
            tc.insert(makeKey(m, n));
            bag.insert(make_pair(sum, tc));
        } else {
            U64 key = makeKey(m, n);
            auto tcit = fit->second.find(key);
            if (tcit == fit->second.end()) {
                fit->second.insert(key);
            }
        }
    }

    void computeFreqs(const vector<int>& nums, unordered_map<int, int>& fmap) {
        for (const int n: nums) {
            auto fit = fmap.find(n);
            if (fit == fmap.end()) {
                fmap.insert(make_pair(n, 1));
            } else {
                fmap[n]++;
            }
        }
    }

public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> cands;

        std::sort(nums.begin(), nums.end());

        //count frequencies of various numbers
        computeFreqs(nums, freqs);

        //fill up the bag
        for (int mi = 0; mi < nums.size(); mi++) {
            for (int ni = mi+1; ni < nums.size(); ni++) {
                updateBag(nums[mi], nums[ni]);
            }
        }

        //find all the twosum values
        vector<int> twosums;
        for (auto bagelem : bag) {
            twosums.push_back(bagelem.first);
        }

        //check values of 2 twosums that add up to target
        for (const int ts : twosums) {
            int check = target - ts;

            auto bit = bag.find(ts);
            auto fit = bag.find(check);

            if (fit == bag.end()) {continue; }

            for (const U64& bs : bit->second) {
                TwoNums tn1 = breakKey(bs);
                for (const U64& fs : fit->second) {
                    TwoNums tn2 = breakKey(fs);
                    vector<int> nums = {tn1.first, tn1.second, tn2.first, tn2.second};

                    std::sort(nums.begin(), nums.end());
                    cands.push_back(nums);
                }
            }
        }

        //remove duplicate quadruplets
        std::sort(cands.begin(), cands.end(), [] (const vector<int>& lhs, const vector<int>& rhs) -> bool {
            if (lhs[0] != rhs[0]) {
                return (lhs[0] < rhs[0]);
            } else if (lhs[1] != rhs[1]) {
                return (lhs[1] < rhs[1]);
            } else if (lhs[2] != rhs[2]) {
                return (lhs[2] < rhs[2]);
            } else {
                return (lhs[3] < rhs[3]);
            }
        });
        auto it = std::unique(cands.begin(), cands.end());
        cands.erase(it, cands.end());

        //check that cands satisfy frequency requirements
        vector<bool> flags(cands.size(), true);
        for (int i=0; i<cands.size(); i++) {
            vector<int> cv = cands[i];
            unordered_map<int, int> localfreqs;
            computeFreqs(cv, localfreqs);

            for (const pair<int, int>& p : localfreqs) {
                if (p.second != freqs.find(p.first)->second) {
                    flags[i] = false;
                    break;
                }
            }
        }

        vector<vector<int>> retval;
        for (int i=0; i<cands.size(); i++) {
            if (flags[i] == false) continue;
            retval.push_back(cands[i]);
        }

        return retval;
    }
};


int main() {
    vector<int> nums = {1, 0, -1, 0, -2, 2};
    Solution sln;
    vector<vector<int>> ans = sln.fourSum(nums, 0);
    for (const vector<int>& iv : ans) {
        for (const int& n : iv) {
            std::cout << n << " ";
        }
        std::cout << std::endl;
    }
}
