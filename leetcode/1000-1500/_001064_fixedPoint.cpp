class Solution {
public:
    // Constraint: Distinct integers.
    // Constraint: Ascending order.
    //
    // Hypothesis: if arr[mid] < mid, then we don't have a solution in the left half.
    // 
    // Proof by contradiction: Assume, when arr[mid] < mid, we have a solution in the left half.
    // So we have an arr[i] == i, i < mid in the left half.
    // So we should have mid-i+1 distinct integers that we can fill between indices i and mid.
    // These all have to be in ascending order.
    // But since arr[mid] < mid, and arr[i] = i, we can't find enough such distinct integers to fill all the indices.
    int findSolution(const vector<int>& arr, int left, int right) {
        if (right-left <= 1) {
            if (arr[left] == left) {
                return left;
            } else if (arr[right] == right) {
                return right;
            }
            return -1;
        }
        
        int mid = ((long long)left + right)/2;
        if (arr[mid] == mid) {
            // altSoln is needed because we want to find the "earliest" index satisfying the constraints.
            int altSoln = findSolution(arr, left, mid);
            return (altSoln == -1) ? mid : altSoln;
        } else if (arr[mid] < mid) {
            return findSolution(arr, mid, right);
        }
        return findSolution(arr, left, mid);
    }
    
    
    int fixedPoint(vector<int>& arr) {
        return findSolution(arr, 0, arr.size()-1);
    }
};
