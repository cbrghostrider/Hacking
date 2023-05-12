//
// Solution gets buffer overflow, possibly because I'm pushing too many things to min_heap, max_heap, and counts combined.
//
// The idea here is to manipulate the min_heap and max_heap in tandem.
// Such that the top elem on the max_heap is the x-th thing we need at all times.
class Solution {    
    int X=0;

    // Counts is needed because we might want to remove elements out of order from the heaps.
    // i.e. the non-top elems may need to be deleted.
    // So we keep count of all elems, and delete them lazily later in cleanup.
    unordered_map<int, int> counts;
    
    // All elements that are (x+1) ranked or greater are kept in a min heap.
    priority_queue<int, vector<int>, std::greater<int>> min_heap;

    // Lowest x elements at all times are kept in max_heap.
    priority_queue<int, vector<int>, std::less<int>> max_heap;
    int total_max_heap=0;

    void add_to_htable(int elem) {
        if (counts.find(elem) == counts.end()) {
            counts[elem] = 1;
        } else {
            counts[elem]++;
        }
    }

    void cleanup() {
        while (!max_heap.empty() && counts[max_heap.top()] == 0) {
            max_heap.pop();
        }
        while (!min_heap.empty() && counts[min_heap.top()] == 0) {
            min_heap.pop();
        }        
    }

    void add_elem(int elem) {
        if (total_max_heap < X) {  
            // Initialization time only
            add_to_htable(elem);
            total_max_heap++;
            max_heap.push(elem);
            return;
        }

        cleanup();

        if (!max_heap.empty() && elem >= max_heap.top()) {            
            // elem goes directly to min_heap.
            add_to_htable(elem);
            min_heap.push(elem);
            return;
        }

        // Biggest elem in max heap goes to min_heap.        
        int temp = max_heap.top();
        max_heap.pop();
        min_heap.push(temp);
                
        // And max_heap gets the new elem.
        add_to_htable(elem);
        max_heap.push(elem);
    }

    void remove_elem(int elem) {        
        cleanup();
        if (!min_heap.empty() && elem == min_heap.top()) {
            counts[elem]--;
            min_heap.pop();
            return;
        } else if (!min_heap.empty() && elem > min_heap.top()) {
            // Will conceptually be removed, but cleanup will adjust heap later.
            counts[elem]--;
            return;
        }

        // Need to remove from max_heap.
        counts[elem]--;
        cleanup();
        
        // Move something from min_heap to max_heap, to maintain invariant of x valid things in max_heap.
        int temp = min_heap.top();
        min_heap.pop();
        max_heap.push(temp);
    }

    int beauty(int x) {
        cleanup();
        int b = max_heap.top();
        return b > 0 ? 0 : b;
    }
public:
    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
        // Initialization.
        X = x;
        for (int i=0; i<k; i++) {
            add_elem(nums[i]);
        }
        
        vector<int> result;        
        int b = beauty(x);
        result.push_back(b);
        for (int i=k; i<(int)(nums.size()); i++) {
            add_elem(nums[i]);
            remove_elem(nums[i-k]);            
            int b = beauty(x);
            result.push_back(b);
        }
        return result;
    }
};
