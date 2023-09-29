class Solution {
public:
    // O(n) time, O(n) space.
    int countElements2(vector<int>& arr) {
        unordered_set<int> elems;
        for (int n : arr) {elems.insert(n);}
        int count = 0;
        for (int n : arr) {
            if (elems.find(n+1) != elems.end()) count++;
        }
        return count;
    }
    
    // O(nlogn) time, O(1) space.
    int countElements(vector<int>& arr) {
        std::sort(arr.begin(), arr.end());
        int count = 0;
        int elem_prev = -2, num_prev = 0;
        for (int i=0; i<arr.size();) {
            int ptr = i+1;
            while (ptr < arr.size() && arr[i] == arr[ptr]) {ptr++;}
            int new_elem = arr[i];
            int new_num = ptr-i;
            if (new_elem == elem_prev + 1) {
                count += num_prev;
            }
            elem_prev = new_elem;
            num_prev = new_num;
            i = ptr;
        }
        return count;
    }
};
