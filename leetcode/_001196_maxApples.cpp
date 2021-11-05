class Solution {
public:
    int maxNumberOfApples(vector<int>& weight) {
        std::sort(weight.begin(), weight.end());
        int remaining = 5000;
        int count = 0;
        for (int i=0; i<weight.size(); i++) {
            remaining -= weight[i];
            if (remaining < 0) { break; }
            count++;
        }
        return count;
    }
};
