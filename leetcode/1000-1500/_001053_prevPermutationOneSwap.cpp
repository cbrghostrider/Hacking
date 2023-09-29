class Solution {
    // Constraints to solution:
    // i < j
    // arr[i] > arr[j]
    // the moment you get an arr[i] that satisfies, swap it with the biggest number smaller than it on the rhs
    
public:
    vector<int> prevPermOpt1(vector<int>& arr) {        
        int i_chosen=-1;
        for (int i=arr.size()-2; i>=0; i--) {
            if (arr[i] <= arr[i+1]) continue;
            i_chosen=i;
            break;
        }
        if (i_chosen == -1) return arr;
        // swap i_chosen with the biggest number smaller than it on the rhs
        int max=0, ind=-1;
        for (int i=i_chosen; i<arr.size(); i++) {
            if (arr[i] > max && arr[i] < arr[i_chosen]) {
                max = arr[i];
                ind = i;
            }
        }
        std::swap(arr[i_chosen], arr[ind]);
        return arr;
    }
};
