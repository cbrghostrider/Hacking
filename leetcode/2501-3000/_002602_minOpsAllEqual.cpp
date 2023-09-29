class Solution {
    vector<int> snums;

    // Sum to the left, not including number.
    // Sum to the right, not including number.
    vector<long long> leftSums, rightSums;

    void initialize(const vector<int>& nums) {
        snums = nums;
        std::sort(snums.begin(), snums.end());
        long long sum=0;
        for (int i=0; i<snums.size(); i++) {
            leftSums.push_back(sum);
            sum += snums[i];            
        }
        sum=0;
        for (int i=snums.size()-1; i>=0; i--) {
            rightSums.push_back(sum);
            sum += snums[i];            
        }
        std::reverse(rightSums.begin(), rightSums.end());
    }

    // find boundary index where every number to the left <= val, and right > val
    // Note: Can return -1 if val is less than all numbers.
    // Note: If val is equal to a number in the sorted list, it will return the rightmost index of that number instance.
    int findBoundaryIndex(int val, int left, int right) {
        if (snums[0] > val) return -1;
        if (snums[snums.size()-1] <= val) return snums.size()-1;
        if (left == right) { return left; }
        if (left + 1 == right) {
            if (snums[right] <= val) return right;
            return left;
        }

        int mid=(left + right)/2;
        int midplus = mid+1;
        if (snums[mid] <= val && snums[midplus] > val) return mid;
        if (snums[midplus] > val) return findBoundaryIndex(val, left, mid);
        return findBoundaryIndex(val, midplus, right);
    }

    long long computeQuery(long long query) {
        int index = findBoundaryIndex(query, 0, snums.size()-1);
        if (index == -1) {
            long long rsum = rightSums[0] + snums[0];
            long long subtract = query * snums.size();
            return (rsum - subtract);
        }
        if (index == snums.size()-1) {
            long long lsum = leftSums[snums.size()-1] + snums[snums.size()-1];
            long long subtract = query * snums.size();
            return (subtract - lsum);
        }
        long long left = (index+1) * query - (leftSums[index] + snums[index]);
        long long right = rightSums[index] - (snums.size()-index-1) * query;
        return left+right;
    }
public:
    // This solution is O(m*n) and gives TLE after 24/31.
    vector<long long> minOperations2(vector<int>& nums, vector<int>& queries) {
        vector<long long> result;
        for (int q : queries) {
            long long ops=0;
            for (int n : nums) {
                ops += std::llabs(q - n);
            }
            result.push_back(ops);
        }
        return result;
    }
    // This solution gets accepted (AC)!!
    // Complexity is O(m log n). -- m = |queries|, n = |nums|
    vector<long long> minOperations(vector<int>& nums, vector<int>& queries) {
        initialize(nums);
        vector<long long> result;
        for (int query : queries) {
            long long ans = computeQuery(query);
            result.push_back(ans);
        }
        return result;
    }
};
