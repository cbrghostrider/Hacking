// Makes use of the data constraints to trivialize the problem.
//
// The idea here is to manipulate the min_heap and max_heap in tandem.
// Such that the top elem on the max_heap is the x-th thing we need at all times.
class Solution {    
  public:
    vector<int> values;
    int vvv(int v) {
        return v + 50;
    }
    int computeInternal(int x) {
        for (int v=-50; v<=50; v++) {
            if (values[vvv(v)] >= x) {return v;}
            x -= values[vvv(v)];
        }
        return -1;  // should not get here
    }
    int compute(int x) {
        int r = computeInternal(x);
        return r > 0 ? 0 : r;
    }

    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
        values = vector<int>(101, 0);
        for (int v=-50; v<=50; v++) {
            values[vvv(v)] = 0;
        }
        for (int i=0; i<k; i++) {
            values[vvv(nums[i])]++;
        }
        vector<int> result;
        result.push_back(compute(x));
        for (int i=k; i<nums.size(); i++) {
            values[vvv(nums[i])]++;
            values[vvv(nums[i-k])]--;
            int r = compute(x);
            result.push_back(r);
        }
        return result;
    }
};
