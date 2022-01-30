class Solution {
    // 
    // The real "aha" moment in this problem is the following:
    // Going from the question:
    //    What is the max number of tasks you can complete?
    // To the question:
    //    Can I complete K tasks?
    //
    // If you can answer the latter, you can binary search on the full range to find the former.
    //
    
    unordered_map<int, bool> cache;
    
    // Takes the K strongest workers,
    // Sees if they can complete the K weakest tasks
    // If this can't work, then no combination of workers/tasks can satisfy K.
    bool canCompleteKTasks(const vector<int>& tasks, const vector<int>& workers, int pills, int strength, int K) {
        if (K == 0) return true;
        if (cache.find(K) != cache.end()) return cache[K];
        
        int t_ptr = K-1;
        int w_ptr = workers.size()-1;
        
        unordered_map<int, bool> used;
        int count=0;
        int pills_used=0;
        while (t_ptr >=0 && w_ptr >=workers.size()-K) {
            if (used[w_ptr]) {
                w_ptr--;
                continue;
            }
            
            if (tasks[t_ptr] <= workers[w_ptr]) {
                count++;
                t_ptr--;
                w_ptr--;
            } else if ((tasks[t_ptr] > workers[w_ptr] + strength)|| 
                      (tasks[t_ptr] > workers[w_ptr] && pills_used >= pills)) {
                // This task has to be thrown out.
                // t_ptr--; 
                return false;
            } else {
                // Find the weakest worker who can finish the task when boosted.                                
                int weakest_ind=workers.size()-K;
                while (weakest_ind <= w_ptr && 
                       (workers[weakest_ind]+strength < tasks[t_ptr] || used[weakest_ind])) {
                    weakest_ind++;
                }
                if (weakest_ind > w_ptr) return false;
                
                pills_used++;
                count++;
                t_ptr--;
                used[weakest_ind] = true;                
            }
        }
        cache[K] = (count >= K);
        return cache[K];
    }
    
    int binSearchK(const vector<int>& tasks, const vector<int>& workers, int pills, int strength,
                   int lo_guess, int hi_guess) {
        if (lo_guess == hi_guess) { return lo_guess; }
        if (lo_guess+1 == hi_guess) {
            if (canCompleteKTasks(tasks, workers, pills, strength, hi_guess)) return hi_guess;
            return lo_guess;
        }
        
        int mid_guess = (lo_guess+hi_guess)/2;
        bool mid_possible = canCompleteKTasks(tasks, workers, pills, strength, mid_guess);
        if (mid_possible) {
            return binSearchK(tasks, workers, pills, strength, mid_guess, hi_guess);
        }
        return binSearchK(tasks, workers, pills, strength, lo_guess, mid_guess);
    }
    
public:
    
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        std::sort(tasks.begin(), tasks.end());
        std::sort(workers.begin(), workers.end());
        
        int lo_guess = 0;
        int hi_guess = std::min(tasks.size(), workers.size());
        
        int ans = binSearchK(tasks, workers, pills, strength, lo_guess, hi_guess);
        return ans;
    }
};


