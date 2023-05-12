// This is a generic version of the solution, which does not rely on values
// being restricted between [-50, 50].
//
// This solution is also efficient and accepted by the OJ.
//
// The idea here is to manipulate the min_heap and max_heap in tandem.
// Such that the top elem on the max_heap is the x-th thing we need at all times.
//
// Note that elements in both the max and min heaps are kept in "buckets".
// i.e. One "key" in either heap may correspond to multiple "counts" of elements.
// So each key represents a bucket of elements of the same value.
//
// The key for counts map is the numerical value of the element, and the value for counts map is the count of that key.
// A given key is either in the min heap or the max heap, but not both at the same time.
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

    // Return val indicates whether entry was created.
    bool add_to_htable(int elem) {
        bool ret = false;
        if (counts.find(elem) == counts.end()) {
            ret = true;
            counts[elem] = 1;
        } else {
            counts[elem]++;
        }
        return ret;
    }

    void cleanup() {
        while (!max_heap.empty() && counts[max_heap.top()] == 0) {
            int elem = max_heap.top();
            counts.erase(elem);
            max_heap.pop();
        }
        while (!min_heap.empty() && counts[min_heap.top()] == 0) {
            int elem = min_heap.top();
            counts.erase(elem);
            min_heap.pop();
        }        
    }

    void add_elem(int elem) {
        // printf("Adding elem %d\n", elem);    
        if (total_max_heap < X) {  
            // Initialization time only
            total_max_heap++;
            if (add_to_htable(elem)) {
                max_heap.push(elem);
            }
            return;
        }

        cleanup();

        if (!max_heap.empty() && elem > max_heap.top()) {            
            // elem goes directly to min_heap.
            if (add_to_htable(elem)) {
                min_heap.push(elem);
            }
            return;
        }

        total_max_heap++;
        // Max_heap gets the new elem.
        if (add_to_htable(elem)) {
            max_heap.push(elem);
        }

        int top_bucket = counts[max_heap.top()];
        int all_but_top_bucket = total_max_heap - top_bucket;
        if (all_but_top_bucket >= X) {
            // Biggest elem in max heap goes to min_heap.        
            int temp = max_heap.top();
            max_heap.pop();
            min_heap.push(temp);
            total_max_heap -= top_bucket;
        }
    }

    void remove_elem(int elem) {    
        // printf("Removing elem %d\n", elem);    
        cleanup();
        if (!min_heap.empty() && elem == min_heap.top()) {
            counts[elem]--;
            if (counts[elem] == 0) {
                counts.erase(elem);
                min_heap.pop();
            }
            return;
        } else if (!min_heap.empty() && elem > min_heap.top()) {
            // Will conceptually be removed, but cleanup will adjust heap later.
            counts[elem]--;
            return;
        }

        // Need to remove from max_heap.
        total_max_heap--;
        counts[elem]--;        
        cleanup();
        
        // Move something from min_heap to max_heap, to maintain invariant of x valid things in max_heap.
        if (total_max_heap < X) {
            int temp = min_heap.top();
            min_heap.pop();
            max_heap.push(temp);
            total_max_heap += counts[temp];
        }
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
