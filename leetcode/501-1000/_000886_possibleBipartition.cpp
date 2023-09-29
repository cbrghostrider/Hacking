class Solution {
    
public:
    // Well this turned out to be uglier than I like.
    // Mostly the complexity got added when I found a bug.
    // If there are disconnected components, we have to make sure those get handled.
    //
    // So when current component graph coloring gets done, we have to go hunting
    // through the placed set, to find a new person to place.
    // Of course, then the question is, should I place this person in A or B group.
    // Unlike at the start (where any choice is valid), we have to NOW look at
    // the dislikes relationship of this person to decide where to place him
    // (or fail outright if the dislikes are in both groups).
    //
    // Ugh...
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        vector<unordered_set<int>> info(n+1, unordered_set<int>());
        for (int i=0; i<dislikes.size(); i++) {
            info[dislikes[i][0]].insert(dislikes[i][1]);
        }
        
        unordered_set<int> ga, gb;        
        unordered_set<int> placed;
        
        std::queue<int> curr, next;
        curr.push(1);
        bool turn_a = true;
        
        while (!curr.empty()) {
            unordered_set<int>& my_set = turn_a ? ga : gb;
            
            while (!curr.empty()) {
                int me = curr.front(); curr.pop();
                for (int d : info[me]) {  // people I hate
                    if (my_set.find(d) != my_set.end()) {
                        return false;
                    }
                    if (placed.find(d) == placed.end()) next.push(d);
                }
                my_set.insert(me);
                placed.insert(me);
            }
                        
            std::swap(curr, next);
            
            if (curr.empty()) {                
                int i=1;
                for (; i<=n; i++) {
                    if (placed.find(i) == placed.end()) {
                        curr.push(i);
                        break;
                    }
                }
                if (i <= n) {
                    bool haters_in_b = false, haters_in_a = false;
                    for (int d : info[i]) {
                        if (ga.find(d) != ga.end()) haters_in_a = true;
                        if (gb.find(d) != gb.end()) haters_in_b = true;
                    }
                    if (haters_in_a && haters_in_b) return false;
                    if (haters_in_b) turn_a = true;
                    else turn_a = false;
                } else {
                    return true;
                }
            } else {
                turn_a = !turn_a;
            }
        }
        return true;
    }
}; 
