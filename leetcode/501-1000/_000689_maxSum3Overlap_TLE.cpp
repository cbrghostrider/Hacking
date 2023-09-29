class Solution {
    struct Info {
        // The starts of subarrays of length k.
        vector<int> starts;
        // The sum of all subarrays above.
        int sum=0;
    };
    
    vector<int> nums;
    
    // contains the sum of subarrays of len k starting at index
    // {[0..k-1], [1..k], [2...k+1], ...}
    vector<int> ksums;
    
    unordered_map<int, Info> cache;
    
    int signature(int index, int rem, int k) {
        return ((index << 16) | (rem));
    }
    
    // returns best choice for
    // rem number of subarrays of length k starting at index
    // if not possible, returns 0 for sum, and empty starts
    Info solve(int index, int rem, int k) {   
        int sig = signature(index, rem, k);
        if (cache.find(sig) != cache.end()) return cache[sig];
        
        if (nums.size() - index < rem*k) {
            cache[sig] = Info();
            return cache[sig];
        }
        
        Info best;
        for (int i=index; i<=nums.size()-rem*k; i++) {
            int arr1_sum = ksums[i];
            Info my_info = {{i}, arr1_sum};
            if (rem-1 > 0) {
                Info my_soln = solve(i+k, rem-1, k);                
                if (my_soln.starts.empty()) continue;
                my_info.starts.insert(my_info.starts.end(), my_soln.starts.begin(), my_soln.starts.end());
                my_info.sum += my_soln.sum;
            }
            if (best.sum < my_info.sum) {
                best = my_info;
            }
        }
        
        if (best.starts.size() != rem) {best = Info();}
        cache[sig] = best;        
        return cache[sig];
    }
    
    
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& n, int k) {
        if (n.size() < k*3) return {};
        nums = n;
        
        // Initialization
        int sum=0;
        for (int i=0; i<k; i++) {
            sum += nums[i];
        }
        ksums.push_back(sum);
        
        for (int i=k; i<nums.size(); i++) {
            sum -= nums[i-k];
            sum += nums[i];
            ksums.push_back(sum);
        }
        
        Info info = solve(0, 3, k);
        return info.starts;
    }
};
