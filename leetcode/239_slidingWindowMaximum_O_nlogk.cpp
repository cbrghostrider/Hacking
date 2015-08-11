// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
typedef pair<int, int> HeapElem; //(value, index) pair

class HeapCompare {
public:
    bool operator() (const HeapElem& lhs, const HeapElem& rhs) {
        return (lhs.first < rhs.first);
    }
};

typedef priority_queue<HeapElem, vector<HeapElem>, HeapCompare> MaxHeap;

class Solution {
    MaxHeap maxHeap;
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<bool> deleted(nums.size(), false);
        vector<int> retval;

        if (nums.empty() || k == 0) return retval;

        for (int i=0; i<k; i++) {
            maxHeap.push(make_pair(nums[i], i));
        }
        retval.push_back(maxHeap.top().first);

        for (int i=k; i<nums.size(); i++) {
            int delIndex = i-k; //this element is thrown out now
            deleted[delIndex] = true;
            maxHeap.push(make_pair(nums[i], i));

            //heap bookkeeping, throwing out "max elements" that have been deleted
            while (!maxHeap.empty() && deleted[maxheap.top().second]) { maxHeap.pop(); }

            retval.push_back(maxHeap.top().first);
        }

        return retval;
    }
};
