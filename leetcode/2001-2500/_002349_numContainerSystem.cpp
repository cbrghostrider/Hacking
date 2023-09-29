using MinHeap = priority_queue<int, vector<int>, std::greater<int>>;
class NumberContainers {
    // This maintains the actual mapping.
    unordered_map<int, int> ind_to_num;

    // This maintains the smallest index for a number.
    // Keep in mind that the index may be outdated, since it is lazily cleaned up.
    // So we check against the main map too.
    unordered_map<int, MinHeap> num_to_heap;
public:
    NumberContainers() {
        
    }
    
    void change(int index, int number) {
        ind_to_num[index] = number;
        num_to_heap[number].push(index);
    }
    
    int find(int number) {
        if (num_to_heap.find(number) == num_to_heap.end()) return -1;
        MinHeap& heap = num_to_heap[number];
        while (!heap.empty()) {
            int ind = heap.top(); 
            heap.pop();
            if (ind_to_num[ind] != number) continue;  // outdated old mapping
            heap.push(ind);
            return ind;
        }
        return -1; // should not get here
    }
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */
