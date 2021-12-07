class Solution {
    void pancakeFlip(vector<int>& arr, int k) {
        int limit=k/2;
        for (int i=0; i<limit; i++) {
            std::swap(arr[i], arr[k-1-i]);
        }
    }
public:
    vector<int> pancakeSort(vector<int>& arr) {
        vector<int> flips;
        int last_done = arr.size();
        while (last_done > 0) {
            int ind=-1, max=-1;
            for (int i=0; i<last_done; i++) {
                if (arr[i] > max) {
                    max = arr[i];
                    ind = i;
                }
            }
            pancakeFlip(arr, ind+1);
            flips.push_back(ind+1);
            pancakeFlip(arr, last_done);
            flips.push_back(last_done);
            last_done--;
        }
        return flips;
    }
};
