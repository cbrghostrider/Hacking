// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// Input:  Given an array of N numbers, and number of partitions K (where N >> K)
//         Also define PVal(partition) = sum of numbers in a contiguous partition of the array
// Output: A partitioning of the array such that the maximum of all the PVals is minimized.
//
// E.g.    Input:  3 4 2 5 1 and 3 partitions needed
//         Output: 3 | 4 2 | 5 1
//       
//         Input:  4 5 1 9 7 and 3 partitions needed
//         Output: 4 5 | 1 9 | 7
//
// Solution: Dynamic Programming. Currently O(k*n^2). Might be able to improve further... 
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <limits>
#include <cmath>
#include <utility>

typedef unsigned int Elem;
using std::vector;
using std::pair;
using std::make_pair;

//////////////////////////////////////////////////////////////////////////////////
class RangeSumQuery {
public: 
    RangeSumQuery(const vector<Elem>& nums);
    Elem getSum(int from, int to);
private:
    vector<Elem> csum;
};

RangeSumQuery::RangeSumQuery(const vector<Elem>& nums) 
: csum() {
    Elem sum = 0;
    for (int i=0; i<nums.size(); i++) {
        sum += nums[i];
        csum.push_back(sum);
    }
}

Elem RangeSumQuery::getSum(int from, int to) {
    if (from == 0) return csum[to];
    return (csum[to] - csum[from-1]);
}


//////////////////////////////////////////////////////////////////////////////////

typedef pair<Elem, int> TableInfo; //pair of (max of sums of partitions, size of first partition)

class FairWorkload {
public:
    FairWorkload(const vector<Elem>& ns, int k);
    void print();
private:
    void partition();
    vector<Elem> nums;
    int K;
    RangeSumQuery rsq;
    vector<vector<TableInfo>> table; //dynamic programming table
    vector<int> chosenElems; //the number of chosen elements for the k partitions
};

FairWorkload::FairWorkload(const vector<Elem>& ns, int k)
: nums(ns), K(k), rsq(nums), table(), chosenElems() {
}

void FairWorkload::partition() {
    const int n = nums.size();

    //table (P, Q) denotes max of Q partitions-sums starting at P, and the size of the first 
    table = vector<vector<TableInfo>>(nums.size(), vector<TableInfo>(K+1, make_pair(std::numeric_limits<Elem>::max(), 0)));

    //base case for K = 1
    for (int p=0; p<n; p++) {
        int sz = n-p;
        Elem val = rsq.getSum(p, n-1);
        table[p][1] = make_pair(val, sz);
    }

    for (int k=2; k<=K; k++) {
        for (int p=n-k; p>=0; p--) {
            //initially assume this partition is size 1
            int size = 1;
            Elem val = std::max(nums[p], table[p+1][k-1].first);
            for (int psize=2; psize <= (n - p - k + 1); psize++ ) {
                Elem thispart = rsq.getSum(p, p+psize-1);
                Elem thiscand = std::max(thispart, table[p+psize][k-1].first);
                if (thiscand < val) {
                    val = thiscand;
                    size = psize;
                }
            }
            table[p][k] = make_pair(val, size);
        }
    }
}

void FairWorkload::print() {
    partition();
    int index=0;

    int num_partitions = K;
    auto val = table[0][num_partitions];

    while (num_partitions) {
        std::cout << "| ";
        for (int i=index; i< (index+val.second); i++) {
            std::cout << nums[i] << " ";
        }
        if ((index + val.second) >= nums.size()) {
            break;
        }
        auto newval = table[index+val.second][num_partitions-1];
        index += val.second;
        val = newval;
        num_partitions--;
    }
    std::cout << "| " << std::endl;
}


//////////////////////////////////////////////////////////////////////////////////

int main() {
    //testRMQ();
    int tc; std::cin >> tc;
    for (int t=0; t<tc; t++) {
        int n, k; std::cin >> n >> k;
        vector<Elem> nums;
        for (int i=0; i<n; i++) {
            Elem elem; std::cin >> elem;
            nums.push_back(elem);
        }
        FairWorkload fw(nums, k);
        fw.print();
    }
}

